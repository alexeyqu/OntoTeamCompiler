#include "IRTree/TreeNodes/Exp/MEM.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"

IExp* MEM::GetExp() const { 
	return exp; 
}

void MEM::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

CExpList* MEM::Kids() {
	return new CExpList( exp, nullptr );
}

IExp* MEM::Build( CExpList* kids ) {
	return new MEM( kids->GetHead() );
}