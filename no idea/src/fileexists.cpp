#include "../includes.h"

bool fileexists(std::string fileName)
{
	struct stat buffer;
	return(stat(fileName.c_str(), &buffer) == 0);
}
