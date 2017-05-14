#pragma once

#include "IRTree/IIRTreeVisitor.h"

class IStm
{
public:
	virtual ~IStm() {};
	virtual void Accept( IIRTreeVisitor* visitor ) = 0;
};