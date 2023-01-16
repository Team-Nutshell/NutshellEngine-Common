#pragma once
#include "../utils/ntshengn_defines.h"
#include "components/ntshengn_transform.h"
#include "components/ntshengn_renderable.h"
#include "components/ntshengn_camera.h"
#include "components/ntshengn_spherecollidable.h"
#include "components/ntshengn_aabbcollidable.h"
#include "components/ntshengn_capsulecollidable.h"
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
				m_entities.push(entity);
			}
		}

		Entity createEntity() {
			NTSHENGN_ASSERT(m_numberOfEntities < MAX_ENTITIES);

			Entity id = m_entities.front();
			m_entities.pop();
			m_numberOfEntities++;

			return id;
		}

		void destroyEntity(Entity entity) {
			NTSHENGN_ASSERT(entity < MAX_ENTITIES);

			m_componentMasks[entity].reset();
			m_entities.push(entity);
			m_numberOfEntities--;
		}

		void setComponents(Entity entity, ComponentMask componentMask) {
			NTSHENGN_ASSERT(entity < MAX_ENTITIES);

			m_componentMasks[entity] = componentMask;
		}

		ComponentMask getComponents(Entity entity) {
			NTSHENGN_ASSERT(entity < MAX_ENTITIES);

			return m_componentMasks[entity];
		}

	private:
		std::queue<Entity> m_entities;
		std::array<ComponentMask, MAX_ENTITIES> m_componentMasks;
		uint32_t m_numberOfEntities = 0;
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
			NTSHENGN_ASSERT(m_entityToIndex.find(entity) == m_entityToIndex.end());

			size_t tmp = m_validSize;
			m_entityToIndex[entity] = tmp;
			m_indexToEntity[tmp] = entity;
			m_components[tmp] = component;
			m_validSize++;
		}

		void removeData(Entity entity) {
			NTSHENGN_ASSERT(m_entityToIndex.find(entity) != m_entityToIndex.end());

			size_t tmp = m_entityToIndex[entity];
			m_components[tmp] = m_components[m_validSize - 1];
			Entity entityLast = m_indexToEntity[m_validSize - 1];
			m_entityToIndex[entityLast] = tmp;
			m_indexToEntity[tmp] = entityLast;
			m_entityToIndex.erase(entity);
			m_indexToEntity.erase(m_validSize - 1);
			m_validSize--;
		}

		bool hasComponent(Entity entity) {
			return m_entityToIndex.find(entity) != m_entityToIndex.end();
		}

		T& getData(Entity entity) {
			NTSHENGN_ASSERT(m_entityToIndex.find(entity) != m_entityToIndex.end());

			return m_components[m_entityToIndex[entity]];
		}

		void entityDestroyed(Entity entity) override {
			if (m_entityToIndex.find(entity) != m_entityToIndex.end()) {
				removeData(entity);
			}
		}

	private:
		std::array<T, MAX_ENTITIES> m_components;
		std::unordered_map<Entity, size_t> m_entityToIndex;
		std::unordered_map<size_t, Entity> m_indexToEntity;
		size_t m_validSize;
	};

	class ComponentManager {
	public:
		template <typename T>
		void registerComponent() {
			std::string typeName = std::string(typeid(T).name());
			
			NTSHENGN_ASSERT(m_componentTypes.find(typeName) == m_componentTypes.end());

			m_componentTypes.insert({ typeName, m_nextComponent });
			m_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
			m_nextComponent++;
		}

		template <typename T>
		Component getComponentId() {
			std::string typeName = std::string(typeid(T).name());

			NTSHENGN_ASSERT(m_componentTypes.find(typeName) != m_componentTypes.end());

			return m_componentTypes[typeName];
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
			for (auto const& pair : m_componentArrays) {
				auto const& componentArray = pair.second;
				componentArray->entityDestroyed(entity);
			}
		}

	private:
		std::unordered_map<std::string, Component> m_componentTypes;
		std::unordered_map<std::string, std::shared_ptr<IComponentArray>> m_componentArrays;
		Component m_nextComponent = 0;

		template <typename T>
		std::shared_ptr<ComponentArray<T>> getComponentArray() {
			std::string typeName = std::string(typeid(T).name());

			NTSHENGN_ASSERT(m_componentTypes.find(typeName) != m_componentTypes.end());

			return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
		}
	};

	class System {
	public:
		std::set<Entity> m_entities;
	};

	class SystemManager {
	public:
		template <typename T>
		void registerSystem(System* system) {
			std::string typeName = std::string(typeid(T).name());

			NTSHENGN_ASSERT(m_systems.find(typeName) == m_systems.end());

			m_systems.insert({ typeName, system });
		}

		template <typename T>
		void setComponents(ComponentMask componentMask) {
			std::string typeName = std::string(typeid(T).name());

			NTSHENGN_ASSERT(m_systems.find(typeName) != m_systems.end());

			m_componentMasks.insert({ typeName, componentMask });
		}

		void entityDestroyed(Entity entity) {
			for (auto const& pair : m_systems) {
				auto const& system = pair.second;
				system->m_entities.erase(entity);
			}
		}

		void entityComponentMaskChanged(Entity entity, ComponentMask entityComponentMask) {
			for (auto const& pair : m_systems) {
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemComponentMask = m_componentMasks[type];
				if ((entityComponentMask & systemComponentMask).any()) {
					system->m_entities.insert(entity);
				} else {
					system->m_entities.erase(entity);
				}
			}
		}

	private:
		std::unordered_map<std::string, ComponentMask> m_componentMasks;
		std::unordered_map<std::string, System*> m_systems;
	};

	class ECS {
	public:
		void init() {
			m_entityManager = std::make_unique<EntityManager>();
			m_componentManager = std::make_unique<ComponentManager>();
			m_systemManager = std::make_unique<SystemManager>();
		}

		// Entity
		Entity createEntity() {
			Entity newEntity = m_entityManager->createEntity();
			addComponent(newEntity, Transform{});
			
			return newEntity;
		}

		void destroyEntity(Entity entity) {
			m_entityManager->destroyEntity(entity);
			m_componentManager->entityDestroyed(entity);
			m_systemManager->entityDestroyed(entity);
		}

		// Component
		template <typename T>
		void registerComponent() {
			return m_componentManager->registerComponent<T>();
		}

		template <typename T>
		void addComponent(Entity entity, T component) {
			m_componentManager->addComponent<T>(entity, component);
			auto components = m_entityManager->getComponents(entity);
			components.set(m_componentManager->getComponentId<T>(), true);
			m_entityManager->setComponents(entity, components);
			m_systemManager->entityComponentMaskChanged(entity, components);
		}

		template <typename T>
		void removeComponent(Entity entity) {
			m_componentManager->removeComponent<T>(entity);
			auto components = m_entityManager->getComponents(entity);
			components.set(m_componentManager->getComponentId<T>(), false);
			m_entityManager->setComponents(entity, components);
			m_systemManager->entityComponentMaskChanged(entity, components);
		}

		template <typename T>
		bool hasComponent(Entity entity) {
			return m_componentManager->hasComponent<T>(entity);
		}

		template <typename T>
		T& getComponent(Entity entity) {
			return m_componentManager->getComponent<T>(entity);
		}

		template <typename T>
		Component getComponentId() {
			return m_componentManager->getComponentId<T>();
		}

		// System
		template <typename T>
		void registerSystem(System* system) {
			m_systemManager->registerSystem<T>(system);
		}

		template <typename T>
		void setSystemComponents(ComponentMask componentMask) {
			m_systemManager->setComponents<T>(componentMask);
		}

	private:
		std::unique_ptr<EntityManager> m_entityManager;
		std::unique_ptr<ComponentManager> m_componentManager;
		std::unique_ptr<SystemManager> m_systemManager;
	};

}