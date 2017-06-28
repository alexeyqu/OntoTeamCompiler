#pragma once

#include "IExpression.h"

namespace AST 
{

class CVoidExpression : public IExpression
{
public:
   	CVoidExpression() : IExpression() {}

   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }
};

}