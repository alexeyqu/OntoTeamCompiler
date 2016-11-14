#include "../IVisitor.h"
#include "CBinaryExpression.h"

CBinaryExpression::CBinaryExpression( IExpression* leftOperand, TOperationType operation, IExpression* rightOperand) {
	this->leftOperand = leftOperand;
	this->rightOperand = rightOperand;
	this->operation = operation;
}
 
void CBinaryExpression::Accept( IVisitor* v ) {
	v->Visit(this);
}