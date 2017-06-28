#pragma once

#include <cstdlib>
#include "IExpression.h"

namespace AST 
{

class CNumberExpression : public IExpression
{
public:
   	CNumberExpression( const char *_number ) : \
	   number( atoi( _number ) ) {}

   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	int getValue() { return number; }

private:
   	int number;
};

}