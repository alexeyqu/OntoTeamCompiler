#pragma once

#include <cstdlib>
#include "IExpression.h"

namespace AST 
{

class CNumberExpression : public IExpression
{
public:
   	CNumberExpression( const char *_number );

   	void Accept( IVisitor *visitor ) override;

   	int number;
};

}