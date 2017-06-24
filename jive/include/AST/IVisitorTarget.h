#pragma once

#include "jive.h"
#include "IVisitor.h"
#include "Coordinates.h"

namespace AST
{

class IVisitorTarget
{
public:
   	virtual ~IVisitorTarget() {}

   	virtual void Accept( IVisitor *visitor ) = 0;

   	jive::Coordinates coordinates;
};

}