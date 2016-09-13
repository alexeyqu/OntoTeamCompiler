#include "IStatement.h"

class CPrintStatement : public IStatement
{
	IStatement* statement;

public:
	CPrintStatement( IStatement* statement );
	virtual void Accept( IVisitor* v ) override	;
};