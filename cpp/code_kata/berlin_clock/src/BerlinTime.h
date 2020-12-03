#ifndef __BERLIN_TIME_H__
#define __BERLIN_TIME_H__

#include <string>
#include "Time.h"

class BerlinTime {
public:
	BerlinTime(Time& time);

	std::string getString();

	std::string getSeconds();
	std::string getTopHours();
	std::string getBottomHours();
	std::string getTopMinutes();
	std::string getBottomMinutes();
private:
	std::string berlin_time;

	std::string getShortString(short how_many, char color);
	std::string getMinutesString(short how_many);
};

#endif // __BERLIN_TIME_H__
