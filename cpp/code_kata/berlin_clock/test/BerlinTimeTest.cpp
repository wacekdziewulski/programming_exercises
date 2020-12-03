#include "../src/BerlinTime.h"
#include <gtest/gtest.h>
#include <vector>

class BerlinTimeTest : public ::testing::Test {
public:
	typedef enum {
		CHECK_SECONDS,
		CHECK_TOP_MINUTES,
		CHECK_BOTTOM_MINUTES,
		CHECK_TOP_HOURS,
		CHECK_BOTTOM_HOURS,
		CHECK_ENTIRE_CLOCK
	} TestType;

	virtual void SetUp() {
		Time* times[6];
		times[0] = new Time(0,0,0);
		times[1] = new Time(23,59,59);
		times[2] = new Time(12,32,0);
		times[3] = new Time(8,14,13);
		times[4] = new Time(11,36,1);
		times[5] = new Time(16,53,6);

		for (unsigned short i = 0; i < sizeof(times)/sizeof(times[0]); i++) {
			test_times.push_back(BerlinTime(*times[i]));
		}
	}

	virtual void TearDown() {
		test_times.clear();
		answers.clear();
	}

	void check(TestType type) {
		std::vector<BerlinTime>::iterator test_it = test_times.begin();
		std::vector<std::string>::iterator answer_it = answers.begin();

		for (; test_it != test_times.end(), answer_it != answers.end(); test_it++, answer_it++) {
			switch (type) {
				case CHECK_SECONDS:
					ASSERT_STREQ(test_it->getSeconds().c_str(), answer_it->c_str());
					break;
				case CHECK_BOTTOM_MINUTES:
					ASSERT_STREQ(test_it->getBottomMinutes().c_str(), answer_it->c_str());
					break;
				case CHECK_TOP_MINUTES:
					ASSERT_STREQ(test_it->getTopMinutes().c_str(), answer_it->c_str());
					break;
				case CHECK_BOTTOM_HOURS:
					ASSERT_STREQ(test_it->getBottomHours().c_str(), answer_it->c_str());
					break;
				case CHECK_TOP_HOURS:
					ASSERT_STREQ(test_it->getTopHours().c_str(), answer_it->c_str());
					break;
				case CHECK_ENTIRE_CLOCK:
					ASSERT_STREQ(test_it->getTopHours().c_str(), answer_it->c_str());
					break;
			}
		}
	}

	std::vector<BerlinTime> test_times;
	std::vector<std::string> answers;
};

TEST_F(BerlinTimeTest, checkSeconds) {
	answers.push_back("Y");
	answers.push_back("O");
	answers.push_back("Y");
	answers.push_back("O");
	answers.push_back("O");
	answers.push_back("Y");

	check(CHECK_SECONDS);
}

TEST_F(BerlinTimeTest, checkBottomMinutes) {
	answers.push_back("OOOO");
	answers.push_back("YYYY");
	answers.push_back("YYOO");
	answers.push_back("YYYY");
	answers.push_back("YOOO");
	answers.push_back("YYYO");

	check(CHECK_BOTTOM_MINUTES);
}

TEST_F(BerlinTimeTest, checkTopMinutes) {
	answers.push_back("OOOOOOOOOOO");
	answers.push_back("YYRYYRYYRYY");
	answers.push_back("YYRYYROOOOO");
	answers.push_back("YYOOOOOOOOO");
	answers.push_back("YYRYYRYOOOO");
	answers.push_back("YYRYYRYYRYO");

	check(CHECK_TOP_MINUTES);
}

TEST_F(BerlinTimeTest, checkBottomHours) {
	answers.push_back("OOOO");
	answers.push_back("RRRO");
	answers.push_back("RROO");
	answers.push_back("RRRO");
	answers.push_back("ROOO");
	answers.push_back("ROOO");

	check(CHECK_BOTTOM_HOURS);
}

TEST_F(BerlinTimeTest, checkTopHours) {
	answers.push_back("OOOO");
	answers.push_back("RRRR");
	answers.push_back("RROO");
	answers.push_back("ROOO");
	answers.push_back("RROO");
	answers.push_back("RRRO");

	check(CHECK_TOP_HOURS);
}

TEST_F(BerlinTimeTest, checkEntireClock) {
    answers = {"YOOOOOOOOOOOOOOOOOOOOOOO",
               "ORRRRRRROYYRYYRYYRYYYYYY",
               "YRRROROOOYYRYYRYYRYOOOOO",
               "ORROOROOOYYRYYRYOOOOYYOO"};

    check(CHECK_ENTIRE_CLOCK);
}
