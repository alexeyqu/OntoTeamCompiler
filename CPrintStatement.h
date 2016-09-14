#include "IStatement.h"

class CPrintStatement : public IStatement
{
public:

	IExpression* expression;

	CPrintStatement( IExpression* expression );
	virtual void Accept( IVisitor* v ) override	;
};