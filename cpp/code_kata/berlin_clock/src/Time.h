#ifndef __TIME_H__
#define __TIME_H__

#include <string>
#include <exception>

class Time {
public:
	Time(std::string& time);
	Time(unsigned short hours, unsigned short minutes, unsigned short seconds);

	unsigned short getHours();
	unsigned short getMinutes();
	unsigned short getSeconds();
private:
	unsigned short hours;
	unsigned short minutes;
	unsigned short seconds;
};

struct TimeException : public std::exception {
	inline const char* what() const throw() {
		return "General Time class exception";
	}
};

struct InvalidTimeParameterException : public TimeException {
	inline const char* what() const throw() {
		return "Invalid parameter for time given";
	}
};

struct NotANumberException : public TimeException {
	inline const char* what() const throw() {
		return "Not a correct number";
	}
};

#endif // __TIME_H__
