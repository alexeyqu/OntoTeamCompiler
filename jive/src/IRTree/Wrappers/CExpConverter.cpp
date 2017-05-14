#include "IRTree/Wrappers/CExpConverter.h"
#include "IRTree/TreeNodes/Nodes.h"

IExp* CExpConverter::ToExp() const { 
	return expr; 
}

IStm* CExpConverter::ToStm() const { 
	return new EXP( expr ); 
}

IStm* CExpConverter::ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const	{
	return new CJUMP( enums::NE, expr, new CONST( 0 ), ifTrue, ifFalse );
}