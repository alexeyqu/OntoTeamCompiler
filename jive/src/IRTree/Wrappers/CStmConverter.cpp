#include "IRTree/Wrappers/CStmConverter.h"
#include "IRTree/TreeNodes/Nodes.h"
#include <cassert>

IExp* CStmConverter::ToExp() const { 
	assert( false ); 
	return 0; 
}

IStm* CStmConverter::ToStm() const { 
	return stm; 
}

IStm* CStmConverter::ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const { 
	assert( false );
	return 0;
}