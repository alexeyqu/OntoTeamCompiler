#include "IRTree/TreeNodes/Stm/MoveCall.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"
#include "IRTree/TreeNodes/Stm/MOVE.h"
#include "IRTree/TreeNodes/Exp/CALL.h"
#include "IRTree/TreeNodes/Exp/TEMP.h"

void MoveCall::Accept( IIRTreeVisitor * visitor ) {}

CExpList* MoveCall::Kids() {
	return src->Kids(); 
}

IStm* MoveCall::Build( CExpList* kids ) { 
	return new MOVE( dest, src->Build( kids ) ); 
}