#pragma once
#include "../asset_manager/ntshengn_asset_manager.h"
#include "../ecs/ntshengn_ecs.h"
#include "../script/ntshengn_script_manager_interface.h"
#include "../utils/ntshengn_utils_json.h"
#include "../utils/ntshengn_utils_math.h"
#include <string>
#include <algorithm>
#include <limits>
#include <set>
#include <vector>

namespace NtshEngn {

	class SceneManager {
	public:
		void goToScene(const std::string& filePath) {
			JSON json;
			const JSON::Node& sceneRoot = json.read(filePath);

			m_ecs->destroyNonPersistentEntities();

			if (sceneRoot.contains("entities")) {
				const JSON::Node& entitiesNode = sceneRoot["entities"];
				for (size_t i = 0; i < entitiesNode.size(); i++) {
					const JSON::Node& entityNode = entitiesNode[i];

					std::string entityName = "";
					if (entityNode.contains("name")) {
						entityName = entityNode["name"].getString();
					}

					bool entityPersistent = false;
					if (entityNode.contains("isPersistent")) {
						entityPersistent = entityNode["isPersistent"].getBoolean();
					}

					std::vector<Entity> entities;

					// Renderable
					if (entityNode.contains("renderable")) {
						const JSON::Node& renderableNode = entityNode["renderable"];

						if (renderableNode.contains("modelPath")) {
							const JSON::Node& modelPathNode = renderableNode["modelPath"];

							Model* model = m_assetManager->loadModel(modelPathNode.getString());

							if (model) {
								entities.resize(model->primitives.size());
								for (size_t j = 0; j < model->primitives.size(); j++) {
									if (entityName != "") {
										if (model->primitives.size() > 1) {
											entities[j] = m_ecs->createEntity(entityName + "_" + std::to_string(j));
										}
										else {
											entities[j] = m_ecs->createEntity(entityName);
										}
									}
									else {
										entities[j] = m_ecs->createEntity();
									}

									m_ecs->setEntityPersistence(entities[j], entityPersistent);

									Renderable renderable;
									renderable.mesh = &model->primitives[j].mesh;
									renderable.material = model->primitives[j].material;
									m_ecs->addComponent(entities[j], renderable);
								}
							}
						}
					}

					if (entities.empty()) {
						Entity entity;
						if (entityName != "") {
							entity = m_ecs->createEntity(entityName);
						}
						else {
							entity = m_ecs->createEntity();
						}

						m_ecs->setEntityPersistence(entity, entityPersistent);

						entities.push_back(entity);
					}

					for (Entity entity : entities) {
						// Transform
						if (entityNode.contains("transform")) {
							const JSON::Node& transformNode = entityNode["transform"];

							Transform& transform = m_ecs->getComponent<Transform>(entity);
							if (transformNode.contains("position")) {
								const JSON::Node& positionNode = transformNode["position"];

								transform.position = { positionNode[0].getNumber(), positionNode[1].getNumber(), positionNode[2].getNumber() };
							}

							if (transformNode.contains("rotation")) {
								const JSON::Node& rotationNode = transformNode["rotation"];

								transform.rotation = { Math::toRad(rotationNode[0].getNumber()), Math::toRad(rotationNode[1].getNumber()), Math::toRad(rotationNode[2].getNumber()) };
							}

							if (transformNode.contains("scale")) {
								const JSON::Node& scaleNode = transformNode["scale"];

								transform.scale = { scaleNode[0].getNumber(), scaleNode[1].getNumber(), scaleNode[2].getNumber() };
							}
						}

						// Camera
						if (entityNode.contains("camera")) {
							const JSON::Node& cameraNode = entityNode["camera"];

							Camera camera;
							if (cameraNode.contains("forward")) {
								const JSON::Node& forwardNode = cameraNode["forward"];

								camera.forward = { forwardNode[0].getNumber(), forwardNode[1].getNumber(), forwardNode[2].getNumber() };
							}

							if (cameraNode.contains("up")) {
								const JSON::Node& upNode = cameraNode["up"];

								camera.up = { upNode[0].getNumber(), upNode[1].getNumber(), upNode[2].getNumber() };
							}

							if (cameraNode.contains("fov")) {
								const JSON::Node& fovNode = cameraNode["fov"];

								camera.fov = Math::toRad(fovNode.getNumber());
							}

							if (cameraNode.contains("nearPlane")) {
								const JSON::Node& nearPlaneNode = cameraNode["nearPlane"];

								camera.nearPlane = nearPlaneNode.getNumber();
							}

							if (cameraNode.contains("farPlane")) {
								const JSON::Node& farPlaneNode = cameraNode["farPlane"];

								camera.farPlane = farPlaneNode.getNumber();
							}

							m_ecs->addComponent(entity, camera);
						}

						// Light
						if (entityNode.contains("light")) {
							const JSON::Node& lightNode = entityNode["light"];

							Light light;
							if (lightNode.contains("type")) {
								const JSON::Node& typeNode = lightNode["type"];

								if (typeNode.getString() == "Directional") {
									light.type = LightType::Directional;
								}
								else if (typeNode.getString() == "Point") {
									light.type = LightType::Point;
								}
								else if (typeNode.getString() == "Spot") {
									light.type = LightType::Spot;
								}
							}

							if (lightNode.contains("color")) {
								const JSON::Node& colorNode = lightNode["color"];

								light.color = { colorNode[0].getNumber(), colorNode[1].getNumber(), colorNode[2].getNumber() };
							}

							if (lightNode.contains("direction")) {
								const JSON::Node& directionNode = lightNode["direction"];

								light.direction = { directionNode[0].getNumber(), directionNode[1].getNumber(), directionNode[2].getNumber() };
							}

							if (lightNode.contains("cutoff")) {
								const JSON::Node& cutoffNode = lightNode["cutoff"];

								light.cutoff = { Math::toRad(cutoffNode[0].getNumber()), Math::toRad(cutoffNode[1].getNumber()) };
							}

							m_ecs->addComponent(entity, light);
						}

						// Rigidbody
						if (entityNode.contains("rigidbody")) {
							const JSON::Node& rigidbodyNode = entityNode["rigidbody"];

							Rigidbody rigidbody;
							if (rigidbodyNode.contains("isStatic")) {
								const JSON::Node& isStaticNode = rigidbodyNode["isStatic"];

								rigidbody.isStatic = isStaticNode.getBoolean();
							}

							if (rigidbodyNode.contains("isAffectedByConstants")) {
								const JSON::Node& isAffectedByConstantsNode = rigidbodyNode["isAffectedByConstants"];

								rigidbody.isAffectedByConstants = isAffectedByConstantsNode.getBoolean();
							}

							if (rigidbodyNode.contains("lockRotation")) {
								const JSON::Node& lockRotationNode = rigidbodyNode["lockRotation"];

								rigidbody.lockRotation = lockRotationNode.getBoolean();
							}

							if (rigidbodyNode.contains("mass")) {
								const JSON::Node& massNode = rigidbodyNode["mass"];

								rigidbody.mass = massNode.getNumber();
							}

							if (rigidbodyNode.contains("inertia")) {
								const JSON::Node& inertiaNode = rigidbodyNode["inertia"];

								rigidbody.inertia = inertiaNode.getNumber();
							}

							if (rigidbodyNode.contains("restitution")) {
								const JSON::Node& restitutionNode = rigidbodyNode["restitution"];

								rigidbody.restitution = restitutionNode.getNumber();
							}

							if (rigidbodyNode.contains("staticFriction")) {
								const JSON::Node& staticFrictionNode = rigidbodyNode["staticFriction"];

								rigidbody.staticFriction = staticFrictionNode.getNumber();
							}

							if (rigidbodyNode.contains("dynamicFriction")) {
								const JSON::Node& dynamicFrictionNode = rigidbodyNode["dynamicFriction"];

								rigidbody.dynamicFriction = dynamicFrictionNode.getNumber();
							}

							m_ecs->addComponent(entity, rigidbody);
						}

						// Collidable
						if (entityNode.contains("collidable")) {
							const JSON::Node& collidableNode = entityNode["collidable"];

							Collidable collidable;
							if (collidableNode.contains("type")) {
								const JSON::Node& typeNode = collidableNode["type"];

								if (typeNode.getString() == "Box") {
									collidable.collider = std::make_unique<ColliderBox>();
									ColliderBox* colliderBox = static_cast<ColliderBox*>(collidable.collider.get());

									if (collidableNode.contains("center")) {
										const JSON::Node& centerNode = collidableNode["center"];

										colliderBox->center = { centerNode[0].getNumber(), centerNode[1].getNumber(), centerNode[2].getNumber() };
									}

									if (collidableNode.contains("halfExtent")) {
										const JSON::Node& halfExtentNode = collidableNode["halfExtent"];

										colliderBox->halfExtent = { halfExtentNode[0].getNumber(), halfExtentNode[1].getNumber(), halfExtentNode[2].getNumber() };
									}

									if (collidableNode.contains("rotation")) {
										const JSON::Node& rotationNode = collidableNode["rotation"];

										colliderBox->rotation = { Math::toRad(rotationNode[0].getNumber()), Math::toRad(rotationNode[1].getNumber()), Math::toRad(rotationNode[2].getNumber()) };
									}

									if (!collidableNode.contains("center") && !collidableNode.contains("halfExtent") && !collidableNode.contains("rotation")) {
										if (m_ecs->hasComponent<Renderable>(entity)) {
											// Calculate box from Renderable
											const Renderable& renderable = m_ecs->getComponent<Renderable>(entity);

											std::set<std::string> uniqueVertices;
											std::vector<float> verticesX(renderable.mesh->vertices.size());
											std::vector<float> verticesY(renderable.mesh->vertices.size());
											std::vector<float> verticesZ(renderable.mesh->vertices.size());
											for (size_t j = 0; j < renderable.mesh->vertices.size(); j++) {
												const std::string vertexAsString = Math::to_string(renderable.mesh->vertices[j].position);
												if (uniqueVertices.find(vertexAsString) == uniqueVertices.end()) {
													verticesX[j] = renderable.mesh->vertices[j].position.x;
													verticesY[j] = renderable.mesh->vertices[j].position.y;
													verticesZ[j] = renderable.mesh->vertices[j].position.z;
													uniqueVertices.insert(vertexAsString);
												}
											}

											float size = static_cast<float>(renderable.mesh->vertices.size());

											const float meanX = std::reduce(verticesX.begin(), verticesX.end()) / size;
											const float meanY = std::reduce(verticesY.begin(), verticesY.end()) / size;
											const float meanZ = std::reduce(verticesZ.begin(), verticesZ.end()) / size;

											Math::mat3 covarianceMatrix;
											for (size_t j = 0; j < renderable.mesh->vertices.size(); j++) {
												covarianceMatrix.x.x += (meanX - verticesX[j]) * (meanX - verticesX[j]);
												covarianceMatrix.y.y += (meanY - verticesY[j]) * (meanY - verticesY[j]);
												covarianceMatrix.z.z += (meanZ - verticesZ[j]) * (meanZ - verticesZ[j]);
												covarianceMatrix.x.y += (meanX - verticesX[j]) * (meanY - verticesY[j]);
												covarianceMatrix.x.z += (meanX - verticesX[j]) * (meanZ - verticesZ[j]);
												covarianceMatrix.y.z += (meanY - verticesY[j]) * (meanZ - verticesZ[j]);
											}
											covarianceMatrix.x.x /= size - 1.0f;
											covarianceMatrix.y.y /= size - 1.0f;
											covarianceMatrix.z.z /= size - 1.0f;
											covarianceMatrix.x.y /= size - 1.0f;
											covarianceMatrix.x.z /= size - 1.0f;
											covarianceMatrix.y.z /= size - 1.0f;

											covarianceMatrix.y.x = covarianceMatrix.x.y;
											covarianceMatrix.z.x = covarianceMatrix.x.z;
											covarianceMatrix.z.y = covarianceMatrix.y.z;

											std::array<std::pair<float, Math::vec3>, 3> eigen = covarianceMatrix.eigen();

											colliderBox->center = Math::vec3(meanX, meanY, meanZ);

											for (size_t j = 0; j < renderable.mesh->vertices.size(); j++) {
												const Math::vec3 positionMinusCenter = renderable.mesh->vertices[j].position - colliderBox->center;

												const float extentX = std::abs(Math::dot(eigen[0].second, positionMinusCenter));
												if (extentX > colliderBox->halfExtent.x) {
													colliderBox->halfExtent.x = extentX;
												}

												const float extentY = std::abs(Math::dot(eigen[1].second, positionMinusCenter));
												if (extentY > colliderBox->halfExtent.y) {
													colliderBox->halfExtent.y = extentY;
												}

												const float extentZ = std::abs(Math::dot(eigen[2].second, positionMinusCenter));
												if (extentZ > colliderBox->halfExtent.z) {
													colliderBox->halfExtent.z = extentZ;
												}
											}

											Math::mat4 rotationMatrix = Math::mat4(Math::vec4(eigen[0].second, 0.0f), Math::vec4(eigen[1].second, 0.0f), Math::vec4(eigen[2].second, 0.0f), Math::vec4(0.0f, 0.0f, 0.0f, 1.0f));
											colliderBox->rotation = Math::rotationMatrixToEulerAngles(rotationMatrix);
										}
										else {
											// Default box collider
											colliderBox->center = Math::vec3(0.0f, 0.0f, 0.0f);
											colliderBox->halfExtent = Math::vec3(0.5f, 0.5f, 0.5f);
											colliderBox->rotation = Math::vec3(0.0f, 0.0f, 0.0f);
										}
									}
								}
								else if (typeNode.getString() == "Sphere") {
									collidable.collider = std::make_unique<ColliderSphere>();
									ColliderSphere* colliderSphere = static_cast<ColliderSphere*>(collidable.collider.get());

									if (collidableNode.contains("center")) {
										const JSON::Node& centerNode = collidableNode["center"];

										colliderSphere->center = { centerNode[0].getNumber(), centerNode[1].getNumber(), centerNode[2].getNumber() };
									}

									if (collidableNode.contains("radius")) {
										const JSON::Node& radiusNode = collidableNode["radius"];

										colliderSphere->radius = radiusNode.getNumber();
									}

									if (!collidableNode.contains("center") && !collidableNode.contains("radius")) {
										if (m_ecs->hasComponent<Renderable>(entity)) {
											// Calculate sphere from Renderable
											const Renderable& renderable = m_ecs->getComponent<Renderable>(entity);
											const std::array<Math::vec3, 2> aabb = m_assetManager->calculateAABB(*renderable.mesh);

											colliderSphere->center = (aabb[0] + aabb[1]) / 2.0f;
											colliderSphere->radius = (colliderSphere->center - aabb[0]).length();
										}
										else {
											// Default sphere collider
											colliderSphere->center = Math::vec3(0.0f, 0.0f, 0.0f);
											colliderSphere->radius = 0.5f;
										}
									}
								}
								else if (typeNode.getString() == "Capsule") {
									collidable.collider = std::make_unique<ColliderCapsule>();
									ColliderCapsule* colliderCapsule = static_cast<ColliderCapsule*>(collidable.collider.get());

									if (collidableNode.contains("base")) {
										const JSON::Node& baseNode = collidableNode["base"];

										colliderCapsule->base = { baseNode[0].getNumber(), baseNode[1].getNumber(), baseNode[2].getNumber() };
									}

									if (collidableNode.contains("tip")) {
										const JSON::Node& tipNode = collidableNode["tip"];

										colliderCapsule->tip = { tipNode[0].getNumber(), tipNode[1].getNumber(), tipNode[2].getNumber() };
									}

									if (collidableNode.contains("radius")) {
										const JSON::Node& radiusNode = collidableNode["radius"];

										colliderCapsule->radius = radiusNode.getNumber();
									}

									if (!collidableNode.contains("base") && !collidableNode.contains("tip") && !collidableNode.contains("radius")) {
										if (m_ecs->hasComponent<Renderable>(entity)) {
											// Calculate capsule from Renderable
											const Renderable& renderable = m_ecs->getComponent<Renderable>(entity);
											std::array<Math::vec3, 2> aabb = m_assetManager->calculateAABB(*renderable.mesh);

											const Math::vec3 aabbCenter = (aabb[0] + aabb[1]) / 2.0f;
											const Math::vec3 aabbExtent = aabb[1] - aabb[0];
											std::vector<float> extentAsVector = { aabbExtent.x, aabbExtent.y, aabbExtent.z };
											std::vector<float>::iterator extentMaxIt = std::max_element(extentAsVector.begin(), extentAsVector.end());
											uint8_t extentMax = static_cast<uint8_t>(std::distance(extentAsVector.begin(), extentMaxIt));
											extentAsVector[extentMax] = std::numeric_limits<float>::lowest();
											extentMaxIt = std::max_element(extentAsVector.begin(), extentAsVector.end());
											uint8_t extentSecondMax = static_cast<uint8_t>(std::distance(extentAsVector.begin(), extentMaxIt));

											colliderCapsule->radius = std::abs(aabbExtent[extentSecondMax]) / 2.0f;
											colliderCapsule->base = aabbCenter;
											colliderCapsule->base[extentMax] = aabb[0][extentMax] + colliderCapsule->radius;
											colliderCapsule->tip = aabbCenter;
											colliderCapsule->tip[extentMax] -= aabb[1][extentMax] - colliderCapsule->radius;

											if (colliderCapsule->base[extentMax] == colliderCapsule->tip[extentMax]) {
												colliderCapsule->base[extentMax] -= 0.0001f;
												colliderCapsule->tip[extentMax] += 0.0001f;
											}
										}
										else {
											// Default capsule collider
											colliderCapsule->base = Math::vec3(0.0f, 0.25f, 0.0f);
											colliderCapsule->tip = Math::vec3(0.0f, 0.75f, 0.0f);
											colliderCapsule->radius = 0.25f;
										}
									}
								}
							}

							m_ecs->addComponent(entity, collidable);
						}

						// Scriptable
						if (entityNode.contains("scriptable")) {
							const JSON::Node& scriptableNode = entityNode["scriptable"];

							if (scriptableNode.contains("scriptName")) {
								if (scriptableNode["scriptName"].getString() != "") {
									const JSON::Node& scriptNameNode = scriptableNode["scriptName"];

									m_ecs->addComponent(entity, m_scriptManager->createScriptable(scriptNameNode.getString()));
								}
							}
						}
					}
				}
			}

			m_currentScenePath = filePath;
		}

		std::string getCurrentScenePath() {
			return m_currentScenePath;
		}

		void setECS(ECS* ecs) {
			m_ecs = ecs;
		}

		void setAssetManager(AssetManager* assetManager) {
			m_assetManager = assetManager;
		}

		void setScriptManager(ScriptManagerInterface* scriptManager) {
			m_scriptManager = scriptManager;
		}

	private:
		AssetManager* m_assetManager;

		ECS* m_ecs;

		ScriptManagerInterface* m_scriptManager;

		std::string m_currentScenePath = "";
	};

}