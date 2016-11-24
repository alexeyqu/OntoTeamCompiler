#pragma once

#include "../IVisitorTarget.h"
#include "CType.h"

class IExpression : public IVisitorTarget 
{
public:
   virtual CType *getType() = 0;
};