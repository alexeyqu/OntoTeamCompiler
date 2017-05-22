#pragma once

#include <string>
#include "CTemp.h"

class CTempMap 
{
public:
	std::string Map( CTemp* temp ) {
		if ( temp ) {
			return temp->Name();
		} else {
			return "TEMP_NOT_FOUND";
		}
	}
};
