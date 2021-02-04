#ifndef TEST_GAMEOBJECT_CXXTEST_HPP_
#define TEST_GAMEOBJECT_CXXTEST_HPP_

#include <cxxtest/TestSuite.h>
#include "base/GameObject.hpp"

class GameObjectTestSuite: public CxxTest::TestSuite {
public:
	const float EPSILON = 0.001f;

	void testIsColliding() {
		GameObject obj(0,0,10,10,1);
		TS_ASSERT(obj.isColliding(5, 5));
		TS_ASSERT(!obj.isColliding(11, 11));
		TS_ASSERT(!obj.isColliding(-1, -1));
		TS_ASSERT(obj.isColliding(0, 0)); // For some reason this corner works but the others don't
		TS_ASSERT(!obj.isColliding(0, 10));
		TS_ASSERT(obj.isColliding(9.9, 0));
		TS_ASSERT(!obj.isColliding(10, 10));

		GameObject obj2(3,3,2,2,1);
		TS_ASSERT(obj.isColliding(obj2));
		TS_ASSERT(obj2.isColliding(obj));
		GameObject obj3(9,9,5,5,1);
		TS_ASSERT(obj.isColliding(obj3));
		TS_ASSERT(obj3.isColliding(obj));
		GameObject obj4(0,10,10,10,1);
		TS_ASSERT(!obj.isColliding(obj4));
		TS_ASSERT(!obj4.isColliding(obj));
		GameObject obj5(11,0,10,10,1);
		TS_ASSERT(!obj.isColliding(obj5));
		TS_ASSERT(!obj5.isColliding(obj));
		GameObject obj6(0,11,10,10,1);
		TS_ASSERT(!obj.isColliding(obj6));
		TS_ASSERT(!obj6.isColliding(obj));
		GameObject obj7(-9.9,0,10,10,1);
		TS_ASSERT(obj.isColliding(obj7));
		TS_ASSERT(obj7.isColliding(obj));
	}
};



#endif /* TEST_LEVEL_CXXTEST_HPP_ */
