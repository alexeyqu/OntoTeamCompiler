#pragma once

#include "IVisitor.h"
#include "../jive.h"

class IVisitorTarget
{
public:
   	virtual ~IVisitorTarget() {}

   	virtual void Accept( IVisitor *visitor ) = 0;
};