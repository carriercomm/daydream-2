#include "PrecompiledHeader.h"
#include "Core/World.h"

void World::RecycleEntityID(EntityID id)
{
	m_RecycledEntityIDs.push(id);
}

EntityID World::GenerateEntityID()
{
	if (!m_RecycledEntityIDs.empty())
	{
		EntityID id = m_RecycledEntityIDs.top();
		m_RecycledEntityIDs.pop();
		return id;
	}
	else
	{
		return ++m_LastEntityID;
	}
}

void World::RecursiveUpdate(std::shared_ptr<System> system, double dt, EntityID parentEntity)
{
	for (auto &pair : m_EntityParents)
	{
		EntityID child = pair.first;
		EntityID parent = pair.second;

		system->UpdateEntity(dt, child, parent);
			//RecursiveUpdate(system, dt, child);
	}
}

void World::Update(double dt)
{
	for (auto pair : m_Systems)
	{
		const std::string &type = pair.first;
		auto system = pair.second;
		EventBroker->Process(type);
		system->Update(dt);
		RecursiveUpdate(system, dt, 0);
	}

	ProcessEntityRemovals();
}

//std::vector<EntityID> GetEntityChildren(EntityID entity);
//{
//	std::vector<EntityID> children;
//	auto range = m_SceneGraph.equal_range(entity);
//	for (auto it = range.first; it != range.second; ++it)
//		children.push_back(it->second);
//	return children;
//}

EntityID World::GetEntityParent(EntityID entity)
{
	auto it = m_EntityParents.find(entity);
	return it == m_EntityParents.end() ? 0 : it->second;
}

EntityID World::GetEntityBaseParent(EntityID entity)
{
	EntityID parent = GetEntityParent(entity);
	if (parent == 0)
		return entity;
	else
		return GetEntityBaseParent(parent);
}

bool World::ValidEntity(EntityID entity)
{
	return m_EntityParents.find(entity) != m_EntityParents.end()
		&& m_EntitiesToRemove.find(entity) == m_EntitiesToRemove.end();
}

void World::RemoveEntity(EntityID entity)
{
	m_EntitiesToRemove.insert(entity);

	auto it = m_EntityChildren.find(entity);
	if (it != m_EntityChildren.end())
	{
		for (auto entity : it->second)
		{
			RemoveEntity(entity);
		}
	}
}

void World::ProcessEntityRemovals()
{
	for (auto entity : m_EntitiesToRemove)
	{
		m_EntityParents.erase(entity);
		m_EntityChildren.erase(entity);
		// Remove components
		for (auto pair : m_EntityComponents[entity])
		{
			auto type = pair.first;
			auto component = pair.second;
			// Trigger events
			for (auto pair : m_Systems)
			{
				auto system = pair.second;
				system->OnComponentRemoved(entity, type, component.get());
			}
			m_ComponentsOfType[type].remove(component);
		}
		m_EntityComponents.erase(entity);
		RecycleEntityID(entity);

		// Trigger events
		for (auto pair : m_Systems)
		{
			auto system = pair.second;
			system->OnEntityRemoved(entity);
		}
	}
	m_EntitiesToRemove.clear();
}

EntityID World::CreateEntity(EntityID parent /*= 0*/)
{
	EntityID newEntity = GenerateEntityID();
	m_EntityParents[newEntity] = parent;
	m_EntityChildren[parent].push_back(newEntity);
	return newEntity;
}

void World::Initialize()
{
	RegisterSystems();
	AddSystems();
	for (auto pair : m_Systems)
	{
		auto system = pair.second;
		system->RegisterComponents(&m_ComponentFactory);
		system->RegisterResourceTypes(ResourceManager);
		system->Initialize();
	}
}

void World::CommitEntity(EntityID entity)
{
	for (auto pair : m_Systems)
	{
		auto system = pair.second;
		system->OnEntityCommit(entity);
	}
}

void World::AddComponent(EntityID entity, std::string componentType, std::shared_ptr<Component> component)
{
	component->Entity = entity;
	m_ComponentsOfType[componentType].push_back(component);
	m_EntityComponents[entity][componentType] = component;

	Events::ComponentCreated e;
	e.Entity = entity;
	e.Component = component;
	EventBroker->Publish(e);
}

EntityID World::CloneEntity(EntityID entity, EntityID parent /* = 0 */)
{
	int clone = CreateEntity(parent);

	for (auto pair : m_EntityComponents[entity])
	{
		auto type = pair.first;
		if (type == typeid(Components::Template).name())
			continue;
		auto component = std::shared_ptr<Component>(pair.second->Clone());
		if (component != nullptr)
		{
			AddComponent(clone, type, component);
		}
	}

	auto itChildren = m_EntityChildren.find(entity);
	if (itChildren != m_EntityChildren.end())
	{
		for (EntityID child : itChildren->second)
		{
			CloneEntity(child, clone);
		}
	}

	CommitEntity(clone);

	return clone;
}

std::list<EntityID> World::GetEntityChildren(EntityID entity)
{
	auto it = m_EntityChildren.find(entity);
	if (it == m_EntityChildren.end())
	{
		return std::list<EntityID>();
	}
	else
	{
		return it->second;
	}
}

void World::SetEntityParent(EntityID entity, EntityID newParent)
{
	EntityID currentParent = m_EntityParents[entity];
	m_EntityChildren[currentParent].remove(entity);
	m_EntityParents[entity] = newParent;
	m_EntityChildren[newParent].push_back(entity);
}
