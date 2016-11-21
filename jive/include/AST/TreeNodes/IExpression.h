#pragma once

#include "../IVisitorTarget.h"

class IExpression : public IVisitorTarget 
{
public:
	virtual enums::TType getType() = 0;
};