#pragma once

#include "IExpression.h"

namespace AST 
{

class CVoidExpression : public IExpression
{
public:
   	CVoidExpression();

   	void Accept( IVisitor *visitor ) override;
};

}