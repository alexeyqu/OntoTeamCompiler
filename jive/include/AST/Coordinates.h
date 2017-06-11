#pragma once

#include <iostream>

#ifndef OUT_COORDINATES
	#define OUT_COORDINATES( entity ) \
		"[" << entity->coordinates.first_line << ", " << entity->coordinates.first_column << "] " 
#endif

class Coordinates 
{
public:
	int first_line;
	int first_column;
};
