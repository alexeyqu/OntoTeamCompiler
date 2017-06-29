#pragma once

#include "IExp.h"

namespace IRT
{

class IAccess 
{
public:
	virtual IExp *getExp() const = 0;
};

}