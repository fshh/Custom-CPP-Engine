#ifndef INCLUDE_EDITOR_BREAKOUTEDITORLEVEL_HPP_
#define INCLUDE_EDITOR_BREAKOUTEDITORLEVEL_HPP_

#include "editor/EditorObject.hpp"
#include "editor/EditorLevel.hpp"

class BreakoutEditorLevel: public EditorLevel {
public:
	BreakoutEditorLevel(const std::string& jsonPath);
	virtual ~BreakoutEditorLevel() {}

	void load() override;

	std::shared_ptr<EditorObject> addEditorObject(float x, float y, ObjectType type, bool cursor = false) override;

	void save(std::shared_ptr<EditorObject> dontSave) override;
};

#endif /* INCLUDE_EDITOR_BREAKOUTEDITORLEVEL_HPP_ */
