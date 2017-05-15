#include "IRTree/TreeNodes/Stm/ExpCall.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"
#include "IRTree/TreeNodes/Stm/EXP.h"
#include "IRTree/TreeNodes/Exp/CALL.h"

void ExpCall::Accept( IIRTreeVisitor *visitor ) {}

CExpList* ExpCall::Kids() { 
	return call->Kids(); 
}
IStm* ExpCall::Build( CExpList* kids ) { 
	return new EXP( call->Build( kids ) ); 
}