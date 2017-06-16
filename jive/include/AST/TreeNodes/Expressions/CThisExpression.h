#pragma once

#include <string>
#include "IExpression.h"

class CThisExpression : public IExpression
{
public:
   	CThisExpression( std::size_t _address = 0 );

   	void Accept( IVisitor *visitor ) override;

   	std::size_t address;
};