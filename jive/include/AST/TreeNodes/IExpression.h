#pragma once

#include "IVisitorTarget.h"
#include "Types.h"

namespace AST 
{

class IExpression : public IVisitorTarget {
public:
	IType *type;
};

}