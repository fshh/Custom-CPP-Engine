#ifndef INCLUDE_BASE_ANIMATORCOMPONENT_HPP_
#define INCLUDE_BASE_ANIMATORCOMPONENT_HPP_

#include "base/GenericComponent.hpp"
#include "base/AnimationState.hpp"
#include "base/SpriteSheetRenderComponent.hpp"
#include <vector>
#include <unordered_map>

class AnimatorComponent: public GenericComponent {
public:
	AnimatorComponent(GameObject& gameObject, std::shared_ptr<SpriteSheetRenderComponent> renderer, std::vector<AnimationState> animations);

	void update(Level& level) override;

	inline bool addAnimation(const AnimationState animation) { return mStates.emplace(animation.name(), animation).second; }
	inline bool removeAnimation(const std::string& name) { return mStates.erase(name) > 0; }

	bool setState(const std::string& name);

private:
	static const float FRAMES_PER_SECOND;
	static const float FRAME_DURATION;

	std::shared_ptr<SpriteSheetRenderComponent> mRenderer;
	std::unordered_map<std::string, AnimationState> mStates;
	AnimationState mCurrentState;
	int mCurrentID;
	float mFrameTimeElapsed;
};



#endif /* INCLUDE_BASE_ANIMATORCOMPONENT_HPP_ */
