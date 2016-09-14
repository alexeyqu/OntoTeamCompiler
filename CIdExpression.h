#pragma once

#include "IExpression.h"
#include <string>

class CIdExpression : public IExpression 
{
public:
	std::string id;

	CIdExpression( const std::string& id ); 
   	virtual void Accept( IVisitor* v ) override;
};