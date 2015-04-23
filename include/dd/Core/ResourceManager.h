/*
	This file is part of Daydream Engine.
	Copyright 2014 Adam Byléhn, Tobias Dahl, Simon Holmberg, Viktor Ljung
	
	Daydream Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Daydream Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with Daydream Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ResourceManager_h__
#define ResourceManager_h__

#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

#include "Util/UnorderedMapPair.h"
#include "Util/Factory.h"

namespace dd
{

/** Base Resource class.

	Implement this class for every resource to be handled by the resource manager.
	Implement Create() to return a new object of that type.
*/
class Resource
{
protected:
	Resource() { }

public:
	// Pretend that this is a pure virtual function that you have to implement
	// static Resource* Create(std::string resourceName);

	unsigned int TypeID;
	unsigned int ResourceID;
};

/** Singleton resource manager to keep track of and cache any external engine assets */ 
class ResourceManager
{
private:
	ResourceManager();

public:
	/*static ResourceManager& Instance()
	{
	static ResourceManager s;
	return s;
	}*/

	/** Registers the factory function of a resource type 
		
		@tparam T Resource type.
		@param factoryFunction Lambda function that creates a new instance of the resource.
	*/
	template <typename T>
	static void RegisterType(std::function<Resource*(std::string)> factoryFunction);

	/** Preloads a resource and caches it for future use

		@tparam T Resource type.
		@param resourceName Fully qualified name of the resource to preload.
	*/
	template <typename T>
	static void Preload(std::string resourceName);

	/** Checks if a resource is in cache

		@param resourceType Resource type as string.
		@param resourceName Fully qualified name of the resource to preload.
	*/
	// TODO: Templateify
	static bool IsResourceLoaded(std::string resourceType, std::string resourceName);

	/** Hot-loads a resource and caches it for future use
	
		@tparam T Resource type.
		@param resourceName Fully qualified name of the resource to load.
	*/
	template <typename T>
	static T* Load(std::string resourceName);

	/** Fetches a loaded resource

		@tparam T Resource type.
		@param resourceName Fully qualified name of the resource to fetch.
	*/
	template <typename T>
	static T* Fetch(std::string resourceName);

private:
	static std::unordered_map<std::string, std::function<Resource*(std::string)>> m_FactoryFunctions; // type -> factory function
	static std::unordered_map<std::pair<std::string, std::string>, Resource*> m_ResourceCache; // (type, name) -> resource

	// TODO: Getters for IDs
	static unsigned int m_CurrentResourceTypeID;
	static std::unordered_map<std::string, unsigned int> m_ResourceTypeIDs;
	// Number of resources of a type. Doubles as local ID.
	static std::unordered_map<unsigned int, unsigned int> m_ResourceCount;
	// Flag to suppress hot-load warnings when a preloading resource chain loads another resource
	static bool m_Preloading;

	static unsigned int GetTypeID(std::string resourceType);
	static unsigned int GetNewResourceID(unsigned int typeID);

	// Internal: Create a resource and cache it
	template <typename T>
	static T* CreateResource(std::string resourceName);
};

template <typename T>
T* ResourceManager::Load(std::string resourceName)
{
	auto resourceType = typeid(T).name();
	auto it = m_ResourceCache.find(std::make_pair(resourceType, resourceName));
	if (it != m_ResourceCache.end())
		return static_cast<T*>(it->second);

	if (m_Preloading) {
		LOG_INFO("Preloading resource \"%s\"", resourceName.c_str());
	} else {
		LOG_WARNING("Hot-loading resource \"%s\"", resourceName.c_str());
	}

	return CreateResource<T>(resourceName);
}

template <typename T>
T* ResourceManager::Fetch(std::string resourceName)
{
	auto resourceType = typeid(T).name();
	auto it = m_ResourceCache.find(std::make_pair(resourceType, resourceName));
	if (it == m_ResourceCache.end())
	{
		LOG_ERROR("Failed to fetch resource \"%s\": Resource not loaded!", resourceName.c_str());
		return nullptr;
	} else
	{
		return static_cast<T*>(it->second);
	}
}

template <typename T>
void ResourceManager::RegisterType(std::function<Resource*(std::string)> factoryFunction)
{
	m_FactoryFunctions[typeid(T).name()] = factoryFunction;
}

template <typename T>
void ResourceManager::Preload(std::string resourceName)
{
	auto resourceType = typeid(T).name();
	if (IsResourceLoaded(resourceType, resourceName))
	{
		LOG_WARNING("Attempted to preload resource \"%s\" multiple times!", resourceName);
		return;
	}

	m_Preloading = true;
	LOG_INFO("Preloading resource \"%s\"", resourceName.c_str());
	CreateResource<T>(resourceName);
	m_Preloading = false;
}

template <typename T>
T* ResourceManager::CreateResource(std::string resourceName)
{
	const char* resourceType = typeid(T).name();
	/*auto facIt = m_FactoryFunctions.find(resourceType);
	if (facIt == m_FactoryFunctions.end())
	{
	LOG_ERROR("Failed to load resource \"%s\" of type \"%s\": Type not registered", resourceName.c_str(), resourceType);
	return nullptr;
	}*/

	// Call the factory function
	T* resource = T::Create(resourceName);
	// Store IDs
	resource->TypeID = GetTypeID(resourceType);
	resource->ResourceID = GetNewResourceID(resource->TypeID);
	// Cache
	m_ResourceCache[std::make_pair(resourceType, resourceName)] = resource;

	return resource;
}

}

#endif // ResourceManager_h__
