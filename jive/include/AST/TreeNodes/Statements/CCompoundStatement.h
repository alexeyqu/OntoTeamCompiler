#pragma once

#include "IStatement.h"

namespace AST 
{

class CCompoundStatement : public IStatement
{
public:
	CCompoundStatement( IStatement *_leftStatement, IStatement *_rightStatement );

	void Accept( IVisitor *visitor ) override;

	IStatement *leftStatement;
	IStatement *rightStatement;
};

}