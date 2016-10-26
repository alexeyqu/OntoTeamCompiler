#pragma once

#include "IStatement.h"
#include <string>

class IExpression;

class CAssignStatement : public IStatement
{
public:
	std::string id;
	IExpression* expression;

	CAssignStatement( std::string id, IExpression* expression );
	virtual void Accept( IVisitor* v ) override;
};