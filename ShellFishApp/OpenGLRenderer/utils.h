#pragma once
#include <vector>
#include <string>
namespace utils
{
	std::vector<char> loadFile(const std::string& fileName);
	uint8_t* loadImageFile(const std::string& file, int& width, int& height);
}