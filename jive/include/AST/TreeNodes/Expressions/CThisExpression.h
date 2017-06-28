#pragma once

#include <string>
#include "IExpression.h"

namespace AST 
{

class CThisExpression : public IExpression
{
public:
   	CThisExpression( std::size_t _address = 0 ) : \
	   address( _address ) {}

   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	std::size_t getThisAddress() const { return address; }

private:
   	std::size_t address;
};

}