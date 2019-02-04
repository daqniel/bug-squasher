#include "LevelReader.h"
#include <string>



LevelReader::LevelReader()
{
}


LevelReader::~LevelReader()
{
}

Dimensions LevelReader::ReadFileToBuffer(std::string file_path, std::vector<std::string>& buffer)
{
	Dimensions dims(0, 0);
	std::ifstream file(file_path, std::ios::binary);

	if (file.fail()) {
		perror(file_path.c_str());
		return dims;
	}
	std::string temp = " ";

	file >> dims.width >> dims.height;
	
	while (file >> temp) {
		
		buffer.push_back(temp);
	}

	
	return dims;
}
