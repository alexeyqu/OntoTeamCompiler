#include "IVisitor.h"
#include "CIdExpression.h"

CIdExpression::CIdExpression( const std::string& id ) {
	this->id = id;
}
 
void CIdExpression::Accept( IVisitor* v ) {
	v->Visit( this );
}