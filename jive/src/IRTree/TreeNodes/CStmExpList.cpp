#include "IRTree/TreeNodes/CStmExpList.h"

IStm* CStmExpList::GetStm() { 
	return stm; 
}

CExpList* CStmExpList::GetExps() { 
	return exps; 
}
