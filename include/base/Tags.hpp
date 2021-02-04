#ifndef INCLUDE_BASE_TAGS_HPP_
#define INCLUDE_BASE_TAGS_HPP_

#include <string>
#include <unordered_map>

//! \brief Handles the tags of game objects.
class Tags {
public:
	virtual ~Tags() {}

	static Tags& getInstance();
	static void deleteInstance();

	static int tagOf(const std::string& tagName) { return getInstance().tags[tagName]; };
	static void addTag(const std::string& tagName, int value) { getInstance().tags.emplace(tagName, value); };
	static void removeTag(const std::string& tagName) { getInstance().tags.erase(tagName); }

private:
	Tags() { }
	Tags(Tags const&) = delete; // Avoid copy constructor.
	void operator=(Tags const&) = delete; // Don't allow copy assignment.
	Tags(Tags const&&) = delete; // Avoid move constructor.
	void operator=(Tags const&&) = delete; // Don't allow move assignment.

	static Tags* instance;

protected:
	std::unordered_map<std::string, int> tags;
};


#endif /* INCLUDE_BASE_TAGS_HPP_ */
