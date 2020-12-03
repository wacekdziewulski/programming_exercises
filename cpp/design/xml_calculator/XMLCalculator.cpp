// XMLCalculator.cpp : Defines the entry point for the console application.

#include <iostream>
#include <vector>
#include <stdexcept>
#include "file.h"
#include "XMLParser.h"

void usage() {
	std::cout << "USAGE: XMLCalculator <input_file>.xml" << std::endl;
}

int main(int argc, char** argv)
{
	using namespace XMLCalculator;

	// check input arguments
	if (argc != 2) {
		std::cerr << "Invalid number of arguments!";
		usage();
		return -1;
	}

	std::vector<char> fileBuffer;

	try {
		fileBuffer = File::readFileContents(argv[1]);
		fileBuffer.push_back('\0');
		XMLProcessor::processXML(fileBuffer);
	}
	catch (std::runtime_error& exception) {
		std::cerr << exception.what() << std::endl;
		usage();
	}
	catch (std::invalid_argument& exception) {
		std::cerr << exception.what() << std::endl;
		usage();
	}

	return 0;
}