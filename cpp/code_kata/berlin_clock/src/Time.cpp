#include "Time.h"

Time::Time(std::string& time) {
	std::string::size_type sz;
	hours = std::stod(time, &sz);
	time = time.substr(sz+1);
	minutes = std::stod(time, &sz);
	time = time.substr(sz+1);
	seconds = std::stod(time, &sz);

	if (hours > 24 || minutes > 60 || seconds > 60)
		throw InvalidTimeParameterException();
}

Time::Time(unsigned short _hours, unsigned short _minutes, unsigned short _seconds) : hours(_hours), minutes(_minutes), seconds(_seconds) {
	if (hours > 24 || minutes > 60 || seconds > 60)
		throw InvalidTimeParameterException();
}

unsigned short Time::getHours() {
	return hours;
}

unsigned short Time::getMinutes() {
	return minutes;
}

unsigned short Time::getSeconds() {
	return seconds;
}
