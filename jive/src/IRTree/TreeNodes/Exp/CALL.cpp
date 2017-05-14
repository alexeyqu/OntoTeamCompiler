#include "IRTree/TreeNodes/Exp/CALL.h"

IExp* CALL::GetFunc() const { 
	return func; 
}

CExpList* CALL::GetArgs() const { 
	return args; 
}

void CALL::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}