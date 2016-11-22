 #include "CCompoundMethod.h"

CCompoundMethod::CCompoundMethod( 
	CCompoundMethod *_method1, 
	CMethod *_method2 ) : \
	method1( _method1 ), method2( _method2 ) {}

void CCompoundMethod::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}
