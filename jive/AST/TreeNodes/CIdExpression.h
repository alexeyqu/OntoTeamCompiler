#pragma once

#include <string>
#include "IExpression.h"

class CIdExpression : public IExpression
{
public:
   	CIdExpression( const char *_name, std::size_t *_address = 0 );

   	void Accept( IVisitor *visitor ) override;

   	std::string name;
   	std::size_t *address;
};