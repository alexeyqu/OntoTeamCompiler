#pragma once

#include "IStatement.h"

class CCompoundStatement : public IStatement
{
public:
	IStatement* leftStatement;
	IStatement* rightStatement;

	CCompoundStatement( IStatement* leftStatement, IStatement* rightStatement );
	virtual void Accept( IVisitor* v ) override	;
};
