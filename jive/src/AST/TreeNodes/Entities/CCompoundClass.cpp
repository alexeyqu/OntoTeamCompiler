#include "CCompoundClass.h"

CCompoundClass::CCompoundClass( 
    CCompoundClass *_class1, 
    CClass *_class2 ) : \
    class1( _class1 ), class2( _class2 ) {}

void CCompoundClass::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}