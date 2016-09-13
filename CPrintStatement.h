#include "IStatement.h"

class CPrintStatement : public IStatement
{
public:

	IStatement* statement;

	CPrintStatement( IStatement* statement );
	virtual void Accept( IVisitor* v ) override	;
};