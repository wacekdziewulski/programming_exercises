#include "../src/Time.h"
#include <gtest/gtest.h>

TEST(TimeTest, Initialization) {
	Time test_time(12, 1, 2);
	
	ASSERT_EQ(test_time.getHours(), 12);
	ASSERT_EQ(test_time.getMinutes(), 1);
	ASSERT_EQ(test_time.getSeconds(), 2);
}

TEST(TimeTest, StringInitialization) {
	std::string str_time = std::string("12:01:02");
	Time test_time(str_time);
	
	ASSERT_EQ(test_time.getHours(), 12);
	ASSERT_EQ(test_time.getMinutes(), 1);
	ASSERT_EQ(test_time.getSeconds(), 2);
}
