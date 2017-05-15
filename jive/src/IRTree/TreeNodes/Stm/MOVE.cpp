#include "IRTree/TreeNodes/Stm/MOVE.h"
#include "IRTree/TreeNodes/Exp/MEM.h"
#include "IRTree/TreeNodes/Exp/CExpList.h"

IExp* MOVE::GetDest() const { 
	return dest; 
}

IExp* MOVE::GetSrc() const { 
	return src; 
}

void MOVE::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this ); 
}

CExpList* MOVE::Kids() {
	MEM* castedDest = dynamic_cast<MEM*>( dest );
	if (castedDest) {
		return new CExpList( castedDest->GetExp(), new CExpList( src, nullptr ) );
	} else {
		return new CExpList( src, nullptr );
	}
}

IStm* MOVE::Build( CExpList* kids ) {
	MEM* castedDest = dynamic_cast<MEM*>( dest );
	if( castedDest ) {
		return new MOVE( new MEM( kids->GetHead() ), kids->GetTail()->GetHead() );
	} else {
		return new MOVE( dest, kids->GetHead() );
	}
}