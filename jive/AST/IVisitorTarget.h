#pragma once
#include "IVisitor.h"
#include "../jive.h"

class IVisitorTarget
{
public:
   	virtual void Accept( IVisitor* ) = 0;
   	virtual ~IVisitorTarget() {}
};