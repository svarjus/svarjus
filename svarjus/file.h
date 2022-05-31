#pragma once

#ifndef varjous
#define varjous
#include "filesystem.h"

namespace _FILE    
{
	bool F_CreateDirectory(std::string path);
	bool F_CreateFile(std::string directory, std::string path);
	void SpamVarjus(std::string filepath);
	void ohno(std::string path);
}
#endif