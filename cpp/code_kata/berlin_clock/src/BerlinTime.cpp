#include "BerlinTime.h"
#include <sstream>

BerlinTime::BerlinTime(Time& time) {
	std::stringstream ss;

	if (time.getSeconds() % 2 == 0) { ss << "Y"; }
	else { 				  ss << "O"; }

	ss << getShortString(time.getHours() / 5, 'R');
	ss << getShortString(time.getHours() % 5, 'R');

	ss << getMinutesString(time.getMinutes() / 5);
	ss << getShortString(time.getMinutes() % 5, 'Y');

	berlin_time = ss.str();
}

std::string BerlinTime::getShortString(short how_many, char color) {
	char values[5] = "OOOO";

	for (short i = 0; i < how_many; i++) {
		values[i] = color;
	}

	return std::string(values);
}

std::string BerlinTime::getMinutesString(short how_many) {
	char values[12] = "OOOOOOOOOOO";
	char color;

	for (short i = 0; i < how_many; i++) {
		if (i % 3 == 2) { color = 'R'; }
		else 		{ color = 'Y'; }
		values[i] = color;
	}

	return std::string(values);
}

std::string BerlinTime::getString() {
	return berlin_time;
}

std::string BerlinTime::getSeconds() {
	return berlin_time.substr(0, 1);
}

std::string BerlinTime::getTopHours() {
	return berlin_time.substr(1, 4);
}

std::string BerlinTime::getBottomHours() {
	return berlin_time.substr(5, 4);
}

std::string BerlinTime::getTopMinutes() {
	return berlin_time.substr(9, 11);
}

std::string BerlinTime::getBottomMinutes() {
	return berlin_time.substr(20, 4);
}
