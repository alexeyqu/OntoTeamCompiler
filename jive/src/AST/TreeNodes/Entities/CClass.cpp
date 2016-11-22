#include "CClass.h"

CClass::CClass( CIdExpression *_name, 
   		CIdExpression *_parentName,
   		CCompoundVariable *_fields,
		CCompoundMethod *_methods ) : \
	name( _name ), parentName( _parentName ), 
	fields( _fields ), methods( _methods ) {}

void CClass::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}
 
