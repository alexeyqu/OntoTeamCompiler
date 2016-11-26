#pragma once

#include "../IVisitorTarget.h"
#include "CTypes.h"

class IExpression : public IVisitorTarget {
public:
	IType *type;
};