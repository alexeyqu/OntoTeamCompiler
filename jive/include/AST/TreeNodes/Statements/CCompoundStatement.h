#pragma once

#include "IStatement.h"

namespace AST 
{

class CCompoundStatement : public IStatement
{
public:
	CCompoundStatement( IStatement *_leftStatement, IStatement *_rightStatement ) : \
		leftStatement( _leftStatement ), rightStatement( _rightStatement ) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit(this); }

	IStatement *getLeftStatement() const { return leftStatement; }
	IStatement *getRightStatement() const { return rightStatement; }

private:
	IStatement *leftStatement;
	IStatement *rightStatement;
};

}