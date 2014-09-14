#include "PrecompiledHeader.h"
#include "Core/ResourceManager.h"

std::unordered_map<std::string, std::function<Resource*(std::string)>> ResourceManager::m_FactoryFunctions; // type -> factory function
std::unordered_map<std::pair<std::string, std::string>, Resource*> ResourceManager::m_ResourceCache; // (type, name) -> resource
unsigned int ResourceManager::m_CurrentResourceTypeID = 0;
std::unordered_map<std::string, unsigned int> ResourceManager::m_ResourceTypeIDs;
std::unordered_map<unsigned int, unsigned int> ResourceManager::m_ResourceCount;
bool ResourceManager::m_Preloading = false;

unsigned int ResourceManager::GetTypeID(std::string resourceType)
{
	if (m_ResourceTypeIDs.find(resourceType) == m_ResourceTypeIDs.end())
	{
		m_ResourceTypeIDs[resourceType] = m_CurrentResourceTypeID++;
	}
	return m_ResourceTypeIDs[resourceType];
}

unsigned int ResourceManager::GetNewResourceID(unsigned int typeID)
{
	return m_ResourceCount[typeID]++;
}

bool ResourceManager::IsResourceLoaded(std::string resourceType, std::string resourceName)
{
	return m_ResourceCache.find(std::make_pair(resourceType, resourceName)) != m_ResourceCache.end();
}