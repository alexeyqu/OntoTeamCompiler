#include "CPrintStatement.h"

CPrintStatement::CPrintStatement( IExpression *_operand ) : \
	operand( _operand ) {}
 
void CPrintStatement::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}