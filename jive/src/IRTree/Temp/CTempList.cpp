#include "IRTree/Temp/CTempList.h"	

CTempList::CTempList( CTemp* one, CTemp* two ) {
	head = one;
	tail = new CTempList( two );
}
	
CTempList::CTempList( CTemp* one, CTemp* two, CTemp* three ) {
	head = one;
	tail = new CTempList( two, three );
}

CTemp* CTempList::GetHead() const { 
	return head; 
}

CTempList* CTempList::GetTail() const { 
	return tail; 
}