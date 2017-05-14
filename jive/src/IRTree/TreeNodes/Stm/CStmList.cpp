#include "IRTree/TreeNodes/Stm/CStmList.h"

IStm* CStmList::GetHead() const { 
	return head; 
}

CStmList* CStmList::GetTail() const { 
	return tail; 
}

void CStmList::Accept( IIRTreeVisitor *visitor ) { 
	visitor->Visit( this );
}