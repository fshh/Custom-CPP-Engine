#include "base/AnimatorComponent.hpp"
#include "base/Timer.hpp"

const float AnimatorComponent::FRAMES_PER_SECOND = 10.0f;
const float AnimatorComponent::FRAME_DURATION = 1.0f / FRAMES_PER_SECOND;

AnimatorComponent::AnimatorComponent(GameObject& gameObject, std::shared_ptr<SpriteSheetRenderComponent> renderer, std::vector<AnimationState> animations):
	GenericComponent(gameObject),
	mRenderer(renderer), mStates(), mCurrentState(animations[0]), mCurrentID(mCurrentState.beginID()), mFrameTimeElapsed(0.0f)
{
	for (const AnimationState& animation : animations) {
		mStates.emplace(animation.name(), animation);
	}
}

void
AnimatorComponent::update(Level& level)
{
	// If we're at the end of a non-looping animation, stay there
	if (!mCurrentState.loops() && mCurrentID == mCurrentState.endID()) { return; }

	mFrameTimeElapsed += Timer::deltaTime();
	if (mFrameTimeElapsed > FRAME_DURATION)
	{
		mFrameTimeElapsed = 0.0f;

		// If at the end of the animation, loop back to start
		if (mCurrentID == mCurrentState.endID())
		{
			mCurrentID = mCurrentState.beginID();
		}
		else
		{
			mCurrentID++;
		}
	}

	mRenderer->setSpriteID(mCurrentID);
}

bool
AnimatorComponent::setState(const std::string& name)
{
	if (name == mCurrentState.name()) { return true; }

	try
	{
		AnimationState& state = mStates.at(name);
		// If new state is lower priority than current state, only change states if current state is at end of animation
		if (state.priority() < mCurrentState.priority() && mCurrentID != mCurrentState.endID()) { return false; }
		mCurrentState = state;
		mCurrentID = mCurrentState.beginID();
		mFrameTimeElapsed = 0.0f;
		return true;
	}
	catch (const std::out_of_range& err)
	{
		return false;
	}
}





