#pragma once

#ifndef keystuff
#define keystuff
#include "filesystem.h"

namespace KEY
{
	unsigned char keyPressed();
	void ReadKeys();
	bool isNumerical(char ch);
}

#endif