#pragma once

#include "IStatement.h"
#include <string>

class IExpression;

class CAssignStatement : public IStatement
{
	std::string id;
	IExpression* expression;

public:
	CAssignStatement( std::string id, IExpression* expression );
	virtual void Accept( IVisitor* v ) override;
};