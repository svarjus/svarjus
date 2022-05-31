#pragma once

#ifndef keystuff
#define keystuff
#include "filesystem.h"

namespace KEY
{
	unsigned char keyPressed();
	void ReadKeys();
	bool isNumerical(char ch);

	namespace glob
	{
		inline bool can_read_keys;
	}
}

#endif