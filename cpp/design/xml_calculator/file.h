#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

namespace XMLCalculator {
namespace File {

	/**
	* @brief Opens a file and returns its contents as a char vector
	* @throw std::runtime_error if the file wasn't found or read properly
	*/
	std::vector<char> readFileContents(const std::string& filename) {
		std::ifstream inputFileStream(filename, std::fstream::in | std::fstream::binary);
		if (!inputFileStream.good()) {
			throw std::runtime_error("Couldn't open file!");
		}

		// read xml contents
		std::vector<char> fileBuffer((std::istreambuf_iterator<char>(inputFileStream)),
			(std::istreambuf_iterator<char>()));

		return fileBuffer;
	}

} // namespace File
} // namespace XMLCalculator