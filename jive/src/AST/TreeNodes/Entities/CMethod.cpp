#include "CMethod.h"

CMethod::CMethod( IType *_returnType, CIdExpression *_id, 
   		CCompoundArgument *_arguments,
   		CCompoundVariable *_variables,
		CCompoundStatement *_statements,
		IExpression *_returnExpression ) : \
	returnType( _returnType ), id( _id ), arguments( _arguments ),
	variables( _variables ),
	statements( _statements ),
	returnExpression( _returnExpression ) {}

void CMethod::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}
