#pragma once

#include "IRTree/IIRTreeVisitor.h"

class IExp
{
public:
	virtual ~IExp() {};
	virtual void Accept( IIRTreeVisitor *visitor ) = 0;
};