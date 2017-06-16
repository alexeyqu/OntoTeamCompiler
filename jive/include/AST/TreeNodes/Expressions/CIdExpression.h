#pragma once

#include <string>
#include "IExpression.h"

class CIdExpression : public IExpression
{
public:
   	CIdExpression( const char *_name );

   	void Accept( IVisitor *visitor ) override;

   	std::string name;
};