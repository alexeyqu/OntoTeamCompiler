#include "IVisitor.h"
#include "CBinaryExpression.h"

CBinaryExpression::CBinaryExpression( IExpression* leftOperand, IExpression* rightOperand) {
	this->leftOperand = leftOperand;
	this->rightOperand = rightOperand;
}
 
void CBinaryExpression::Accept( IVisitor* v ) {
	v->Visit(this);
}