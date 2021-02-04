/*
 * Based on code from https://codereview.stackexchange.com/questions/165408/resource-manager-in-c-for-games
 */

#include "base/ResourceManager.hpp"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager&
ResourceManager::getInstance()
{
	if (instance == nullptr) {
		instance = new ResourceManager();
	}
	return *instance;
}

void
ResourceManager::startUp()
{
	std::cout << "Starting up ResourceManager..." << std::endl;
}

void
ResourceManager::shutDown()
{
	std::cout << "Shutting down ResourceManager..." << std::endl;
	for (const auto& resource : resources) {
		ResourceManager::erase(resource.first);
	}
	std::cout << "ResourceManager shut down successfully" << std::endl;
	delete instance;
}

void
ResourceManager::erase(const std::string& name)
{
	if (instance->resources.count(name) >= 1) {
		std::cout << "unloadResource(): Deleting resource pointer for " << name << std::endl;
		delete instance->resources[name];
		std::cout << "unloadResource(): Erasing table entry for " << name << std::endl;
    instance->resources.erase(name);
	}
}
