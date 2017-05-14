#include "IRTree/Wrappers/COrConverter.h"
#include "IRTree/TreeNodes/Nodes.h"

IStm* COrConverter::ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const {
	CLabel* firstFalseLabel = new CLabel();
	CJUMP* firstFalseJump = 
		new CJUMP( enums::NE, leftExp, new CONST( 0 ), ifTrue, firstFalseLabel );
	CJUMP* secondFalseJump = 
		new CJUMP( enums::NE, rightExp, new CONST( 0 ), ifTrue, ifFalse );
	return new SEQ( firstFalseJump, new SEQ( 
		new LABEL( firstFalseLabel ), secondFalseJump ) );
}