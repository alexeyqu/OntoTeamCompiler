#include "IStatement.h"

class CCompoundStatement : public IStatement
{
	IStatement* leftStatement;
	IStatement* rightStatement;

public:
	CCompoundStatement( IStatement* leftStatement, IStatement* rightStatement );
	virtual void Accept( IVisitor* v ) override	;
};