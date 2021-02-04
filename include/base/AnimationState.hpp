#ifndef INCLUDE_BASE_ANIMATIONSTATE_HPP_
#define INCLUDE_BASE_ANIMATIONSTATE_HPP_

#include <string>

class AnimationState {
public:
	AnimationState() = delete;
	AnimationState(const std::string& name, int beginID, int endID, int priority = 0, bool loops = true):
		mName(name), mBeginID(beginID), mEndID(endID), mPriority(priority), mLoops(loops) {}

	inline std::string name() const { return mName; }
	inline int beginID() const { return mBeginID; }
	inline int endID() const { return mEndID; }
	inline int priority() const { return mPriority; }
	inline bool loops() const { return mLoops; }

private:
	std::string mName;
	int mBeginID;
	int mEndID;
	int mPriority;
	bool mLoops;
};



#endif /* INCLUDE_BASE_ANIMATIONSTATE_HPP_ */
