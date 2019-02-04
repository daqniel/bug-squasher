#ifndef _LEVELREADER_H
#define _LEVELREADER_H

#include <fstream>
#include <vector>
#include "Dimensions.h"

class LevelReader
{
public:
	LevelReader();
	~LevelReader();

	//reads file to a buffer for sorting and placing into board
	 static Dimensions ReadFileToBuffer(std::string file_path, std::vector<std::string>& buffer);

};

#endif
