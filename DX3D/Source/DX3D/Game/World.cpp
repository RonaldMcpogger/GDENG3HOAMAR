

#include <DX3D/Game/World.h>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Component/TransformComponent.h>

dx3d::World::World(const WorldDesc& desc) : Base(desc.base), m_gameContext(desc.gameContext)
{
}

void dx3d::World::destroyGameObject(GameObject& object)
{
	m_events.push_back({ &object, 0, EventType::Destroy });
	
}




void dx3d::World::update(f32 deltaTime)
{
	if (m_events.size())
	{
		std::swap(m_events, m_eventsSwapBuffer);
		std::swap(m_pendingObjects, m_pendingObjectsSwapBuffer);

		for (auto& e : m_eventsSwapBuffer)
		{
			auto objTypeId = e.object->getTypeId();

			if (e.eventType == EventType::Create)
			{
				auto& obj = m_pendingObjectsSwapBuffer[e.pendingObjectIndex];
				auto ptr = obj.get();
				m_objects[objTypeId].push_back(std::move(obj));
				ptr->onCreate();
			}
			///
			else if (e.eventType == EventType::Destroy)
			{
				
				GameObject* objPtr = e.object;
				if (!objPtr) continue;

				objPtr->onDestroy();

				//Remove components
				for (auto& [typeId, componentList] : m_components)
				{
					std::erase_if(componentList, [objPtr](Component* component) {
						return &component->getGameObject() == objPtr;
						});
				}

				//Remove dirty transforms
				std::erase_if(m_dirtyTransforms, [objPtr](TransformComponent* transform) {
					return &transform->getGameObject() == objPtr;
					});

				//Erase from active objects map
				auto objectsIt = m_objects.find(objTypeId);
				if (objectsIt != m_objects.end())
				{
					std::erase_if(objectsIt->second, [objPtr](const UniquePtr<GameObject>& current) {
						return current.get() == objPtr;
						});
				}
			}
		}

		m_pendingObjectsSwapBuffer.clear();
		m_eventsSwapBuffer.clear();
	}

	for (auto&& [typeId, objects] : m_objects)
	{
		for (auto& object : objects)
		{
			object->onUpdate(deltaTime);
		}
	}	

	for (auto& comp : m_dirtyTransforms)
	{
		comp->updateWorldMatrix();
	}
	m_dirtyTransforms.clear();
}

dx3d::GameObject* dx3d::World::createGameObjectInternal(UniquePtr<GameObject>& object)
{
	if (!object) return {};

	auto ptr = object.get();

	auto index = m_pendingObjects.size();
	m_pendingObjects.push_back(std::move(object));
	m_events.push_back({ ptr, index, EventType::Create });

	return ptr;
}

void dx3d::World::addComponentInternal(Component& component)
{
	auto typeId = component.getTypeId();
	m_components[typeId].push_back(&component);
}

void dx3d::World::addDirtyTransformInternal(TransformComponent& component)
{
	m_dirtyTransforms.push_back(&component);
}

dx3d::Component* const* dx3d::World::getComponentsInternal(size_t typeId, ui32* numComponents) const noexcept
{
	auto it = m_components.find(typeId);
	if (it != m_components.end())
	{
		*numComponents = static_cast<ui32>(it->second.size());
		return it->second.data();
	}

	*numComponents = 0u;
	return {};
}