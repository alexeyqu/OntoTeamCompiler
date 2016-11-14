#pragma once
#include "IVisitor.h"

class IVisitorTarget
{
public:
   	virtual void Accept( IVisitor* ) = 0;
   	virtual ~IVisitorTarget() {}
};