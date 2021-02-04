/*
 * Based on code from https://codereview.stackexchange.com/questions/165408/resource-manager-in-c-for-games
 */

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <SDL.h>
#include <iostream>
#include "Resource.hpp"
#include "base/Level.hpp"

//! \brief A class for managing game resources.  Allows access to resources
//! and makes sure there is only one copy of each resource loaded at a time.
class ResourceManager {
private:
  ResourceManager(); //!< Does nothing. Call ResourceManager::getInstance() to get the singleton instance and call startUp() on it to initialize.
  ResourceManager(ResourceManager const&) = delete; // Avoid copy constructor.
  void operator=(ResourceManager const&) = delete; // Don't allow copy assignment.
  ResourceManager(ResourceManager const&&) = delete; // Avoid move constructor.
  void operator=(ResourceManager const&&) = delete; // Don't allow move assignment.

  static ResourceManager* instance; //!< The singleton instance for ResourceManager.

  std::unordered_map<std::string, Resource*> resources; //!< The map of resource names to resources.
  
public:
  static ResourceManager& getInstance(); //!< Returns a pointer to the singleton instance of ResourceManager.

  void startUp(); //!< Handles any initialization behavior necessary for the instance of ResourceManager.
  void shutDown(); //!< Destroys the instance of ResourceManager and handles any destruction behavior.

  //! \brief Adds the given resource to the resource table and returns it, after ensuring that it is loaded.
  //! If a resource with the same name already exists in the table, it returns that resource.
  template <typename T>
  static T* add(Resource* resource) {
	  if (instance->resources.count(resource->getName()) >= 1) {
		  return ResourceManager::get<T>(resource->getName());
	  }
	  std::cout << "Created new resource: " << resource->getName() << std::endl;
	  if (!resource->isLoaded()) { resource->load(); }
	  instance->resources.emplace(resource->getName(), resource);
	  return dynamic_cast<T*>(resource);
  }

  //! \brief Retrieves a resource with the given identifier from the resource table
  template <typename T>
  static T* get(const std::string& name) {
	  if (instance->resources.count(name) <= 0) {
		  return nullptr;
	  }
	  return dynamic_cast<T*>(instance->resources[name]);
  }
  
  static void erase(const std::string& name); //!< Unloads the resource at the given path from memory and removes it from the resources map.
};

#endif
