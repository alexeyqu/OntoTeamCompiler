#pragma once

#include "IVisitorTarget.h"
#include "Types.h"

class IExpression : public IVisitorTarget {
public:
	IType *type;
};