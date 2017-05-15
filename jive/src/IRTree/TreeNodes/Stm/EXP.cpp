#include "IRTree/TreeNodes/Stm/EXP.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"

IExp* EXP::GetExp() const { 
	return exp; 
}

void EXP::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

CExpList* EXP::Kids() {
	return new CExpList( exp, nullptr );
}

IStm* EXP::Build( CExpList* kids ) {
	return new EXP( kids->GetHead() );
}
