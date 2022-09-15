#include "../includes.h"

void error(const char* errorName, const char* errorMsg)
{
	MessageBox(NULL, errorMsg, errorName, NULL);
	exit(-1);
}
