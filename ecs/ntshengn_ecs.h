#pragma once
#include "../utils/ntshengn_defines.h"
#include <stdexcept>
#include <bitset>
#include <queue>
#include <array>
#include <unordered_map>
#include <memory>
#include <set>
#include <string>

#define MAX_ENTITIES 4096
#define MAX_COMPONENTS 32

namespace NtshEngn {

	using Entity = uint32_t;
	using Component = uint8_t;
	using ComponentMask = std::bitset<MAX_COMPONENTS>;

	class EntityManager {
	public:
		EntityManager() {
			for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
				entities.push(entity);
			}
		}

		Entity createEntity() {
			NTSHENGN_ASSERT(numberOfEntities < MAX_ENTITIES);

			Entity id = entities.front();
			entities.pop();
			numberOfEntities++;

			return id;
		}

		void destroyEntity(Entity entity) {
			NTSHENGN_ASSERT(entity < MAX_ENTITIES);

			componentMasks[entity].reset();
			entities.push(entity);
			numberOfEntities--;
		}

		void setComponents(Entity entity, ComponentMask componentMask) {
			NTSHENGN_ASSERT(entity < MAX_ENTITIES);

			componentMasks[entity] = componentMask;
		}

		ComponentMask getComponents(Entity entity) {
			NTSHENGN_ASSERT(entity < MAX_ENTITIES);

			return componentMasks[entity];
		}
	private:
		std::queue<Entity> entities;
		std::array<ComponentMask, MAX_ENTITIES> componentMasks;
		uint32_t numberOfEntities = 0;
	};

	class IComponentArray {
	public:
		virtual ~IComponentArray() = default;
		virtual void entityDestroyed(Entity entity) = 0;
	};

	template <typename T>
	class ComponentArray : public IComponentArray {
	public:
		void insertData(Entity entity, T component) {
			NTSHENGN_ASSERT(entityToIndex.find(entity) == entityToIndex.end());

			size_t tmp = validSize;
			entityToIndex[entity] = tmp;
			indexToEntity[tmp] = entity;
			components[tmp] = component;
			validSize++;
		}

		void removeData(Entity entity) {
			NTSHENGN_ASSERT(entityToIndex.find(entity) != entityToIndex.end());

			size_t tmp = entityToIndex[entity];
			components[tmp] = components[validSize - 1];
			Entity entityLast = indexToEntity[validSize - 1];
			entityToIndex[entityLast] = tmp;
			indexToEntity[tmp] = entityLast;
			entityToIndex.erase(entity);
			indexToEntity.erase(validSize - 1);
			validSize--;
		}

		bool hasComponent(Entity entity) {
			return entityToIndex.find(entity) != entityToIndex.end();
		}

		T& getData(Entity entity) {
			NTSHENGN_ASSERT(entityToIndex.find(entity) != entityToIndex.end());

			return components[entityToIndex[entity]];
		}

		void entityDestroyed(Entity entity) override {
			if (entityToIndex.find(entity) != entityToIndex.end()) {
				removeData(entity);
			}
		}
	private:
		std::array<T, MAX_ENTITIES> components;
		std::unordered_map<Entity, size_t> entityToIndex;
		std::unordered_map<size_t, Entity> indexToEntity;
		size_t validSize;
	};

	class ComponentManager {
	public:
		template <typename T>
		void registerComponent() {
			std::string typeName = std::string(typeid(T).name());
			
			NTSHENGN_ASSERT(componentTypes.find(typeName) == componentTypes.end());

			componentTypes.insert({ typeName, nextComponent });
			componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
			nextComponent++;
		}

		template <typename T>
		Component getComponentId() {
			std::string typeName = std::string(typeid(T).name());

			NTSHENGN_ASSERT(componentTypes.find(typeName) != componentTypes.end());

			return componentTypes[typeName];
		}

		template <typename T>
		void addComponent(Entity entity, T component) {
			getComponentArray<T>()->insertData(entity, component);
		}

		template <typename T>
		void removeComponent(Entity entity) {
			getComponentArray<T>()->removeData(entity);
		}

		template <typename T>
		bool hasComponent(Entity entity) {
			return getComponentArray<T>()->hasComponent(entity);
		}

		template <typename T>
		T& getComponent(Entity entity) {
			return getComponentArray<T>()->getData(entity);
		}

		void entityDestroyed(Entity entity) {
			for (auto const& pair : componentArrays) {
				auto const& componentArray = pair.second;
				componentArray->entityDestroyed(entity);
			}
		}
	private:
		std::unordered_map<std::string, Component> componentTypes;
		std::unordered_map<std::string, std::shared_ptr<IComponentArray>> componentArrays;
		Component nextComponent = 0;

		template <typename T>
		std::shared_ptr<ComponentArray<T>> getComponentArray() {
			std::string typeName = std::string(typeid(T).name());

			NTSHENGN_ASSERT(componentTypes.find(typeName) != componentTypes.end());

			return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
		}
	};

	class System {
	public:
		std::set<Entity> entities;
	};

	class SystemManager {
	public:
		template <typename T>
		void registerSystem(System* system) {
			std::string typeName = std::string(typeid(T).name());

			NTSHENGN_ASSERT(systems.find(typeName) == systems.end());

			systems.insert({ typeName, system });
		}

		template <typename T>
		void setComponents(ComponentMask componentMask) {
			std::string typeName = std::string(typeid(T).name());

			NTSHENGN_ASSERT(systems.find(typeName) != systems.end());

			componentMasks.insert({ typeName, componentMask });
		}

		void entityDestroyed(Entity entity) {
			for (auto const& pair : systems) {
				auto const& system = pair.second;
				system->entities.erase(entity);
			}
		}

		void entityComponentMaskChanged(Entity entity, ComponentMask entityComponentMask) {
			for (auto const& pair : systems) {
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemComponentMask = componentMasks[type];
				if (entityComponentMask | systemComponentMask) {
					system->entities.insert(entity);
				} else {
					system->entities.erase(entity);
				}
			}
		}
	private:
		std::unordered_map<std::string, ComponentMask> componentMasks;
		std::unordered_map<std::string, System*> systems;
	};

	class ECS {
	public:
		void init() {
			entityManager = std::make_unique<EntityManager>();
			componentManager = std::make_unique<ComponentManager>();
			systemManager = std::make_unique<SystemManager>();
		}

		// Entity
		Entity createEntity() {
			return entityManager->createEntity();
		}

		void destroyEntity(Entity entity) {
			entityManager->destroyEntity(entity);
			componentManager->entityDestroyed(entity);
			systemManager->entityDestroyed(entity);
		}

		// Component
		template <typename T>
		void registerComponent() {
			return componentManager->registerComponent<T>();
		}

		template <typename T>
		void addComponent(Entity entity, T component) {
			componentManager->addComponent<T>(entity, component);
			auto components = entityManager->getComponents(entity);
			components.set(componentManager->getComponentId<T>(), true);
			entityManager->setComponents(entity, components);
			systemManager->entityComponentMaskChanged(entity, components);
		}

		template <typename T>
		void removeComponent(Entity entity) {
			componentManager->removeComponent<T>(entity);
			auto components = entityManager->getComponents(entity);
			components.set(componentManager->getComponentId<T>(), false);
			entityManager->setComponents(entity, components);
			systemManager->entityComponentMaskChanged(entity, components);
		}

		template <typename T>
		bool hasComponent(Entity entity) {
			return componentManager->hasComponent<T>(entity);
		}

		template <typename T>
		T& getComponent(Entity entity) {
			return componentManager->getComponent<T>(entity);
		}

		template <typename T>
		Component getComponentId() {
			return componentManager->getComponentId<T>();
		}

		// System
		template <typename T>
		void registerSystem(System* system) {
			systemManager->registerSystem<T>(system);
		}

		template <typename T>
		void setSystemComponents(ComponentMask componentMask) {
			systemManager->setComponents<T>(componentMask);
		}
	private:
		std::unique_ptr<EntityManager> entityManager;
		std::unique_ptr<ComponentManager> componentManager;
		std::unique_ptr<SystemManager> systemManager;
	};

}