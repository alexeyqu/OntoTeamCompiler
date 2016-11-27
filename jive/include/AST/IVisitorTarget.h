#pragma once

#include "IVisitor.h"
#include "../jive.h"
#include "Coordinates.h"

class IVisitorTarget
{
public:
   	virtual ~IVisitorTarget() {}

   	virtual void Accept( IVisitor *visitor ) = 0;

   	Coordinates coordinates;
};