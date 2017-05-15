#include "IRTree/TreeNodes/Exp/CALL.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"

IExp* CALL::GetFunc() const { 
	return func; 
}

CExpList* CALL::GetArgs() const { 
	return args; 
}

void CALL::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

CExpList* CALL::Kids() {
	return new CExpList( func, args );
}

IExp* CALL::Build( CExpList* kids ) {
	return new CALL( kids->GetHead(), kids->GetTail() );
}