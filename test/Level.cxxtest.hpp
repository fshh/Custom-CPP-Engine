#ifndef TEST_LEVEL_CXXTEST_HPP_
#define TEST_LEVEL_CXXTEST_HPP_

#include <cxxtest/TestSuite.h>
#include "base/GetResourcePath.hpp"
#include "base/Level.hpp"

class LevelTestSuite: public CxxTest::TestSuite {
public:
	const float EPSILON = 0.001f;

	void testContains() {
		return;
		Level level(getResourcePath("levels") + "testBlocks.json");
		level.load();
	}
};



#endif /* TEST_LEVEL_CXXTEST_HPP_ */
