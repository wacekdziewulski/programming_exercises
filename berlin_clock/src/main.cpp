#include <memory>
#include <iostream>

#include "Time.h"
#include "BerlinTime.h"

int main() {
	try {
        std::string time_str;
        std::cin >> time_str;
		std::unique_ptr<Time> time(new Time(time_str));
        std::unique_ptr<BerlinTime> berlin_time(new BerlinTime(*time));
        std::cout << berlin_time->getString() << std::endl;
	} 
	catch (const InvalidTimeParameterException& ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (const NotANumberException& ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
