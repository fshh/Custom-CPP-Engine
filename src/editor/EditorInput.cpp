#include "editor/EditorInput.hpp"
#include "editor/EditorLevel.hpp"
#include "base/InputManager.hpp"
#include <iostream>

void EditorInputComponent::update(Level& level) {
	addedObj = nullptr;

	EditorLevel* editorLevel = dynamic_cast<EditorLevel*>(&level);
	if (editorLevel == nullptr) {
		std::cout << "Trying to use EditorInputComponent on a non-EditorLevel";
		return;
	}

	ObjectType inputType = handleKey();
	if (inputType != ObjectType::INVALID) {
		currType = inputType;
	}

	int x, y;
	SDL_GetMouseState(&x, &y);
	if (cursor == nullptr) {
		cursor = editorLevel->addEditorObject(x, y, currType, true);
	}
	else if(cursor->getObjectType() != currType) {
		editorLevel->removeObject(cursor);
		cursor = editorLevel->addEditorObject(x, y, currType, true);
	}
	else {
		cursor->setX(x);
		cursor->setY(y);
	}


	// Add an object to the level when the user clicks
	if (SDL_GetMouseState(&x,&y) & SDL_BUTTON_LMASK) {
		// Delete all objects at the clicked position
		std::vector<std::shared_ptr<GameObject>> objects;
		if (editorLevel->getCollisions(x, y, objects)) {
			for (auto obj: objects) {
				if (obj != cursor) {
					editorLevel->removeObject(obj);
				}
			}
		}

		int gx = x - x % editorLevel->getSize();
		int gy = y - y % editorLevel->getSize();
		addedObj = editorLevel->addEditorObject(gx, gy, currType);
	}

	if (InputManager::getInstance().isKeyDown(SDLK_s)) {
		editorLevel->save(cursor);
	}
}
