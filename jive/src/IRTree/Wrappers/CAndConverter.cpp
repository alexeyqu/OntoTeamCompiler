#include "IRTree/Wrappers/CAndConverter.h"
#include "IRTree/TreeNodes/Nodes.h"

IStm* CAndConverter::ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const {
	CLabel* firstTrueLabel = new CLabel();
	CJUMP* firstTrueJump = 
		new CJUMP( enums::NE, leftExp, new CONST( 0 ), firstTrueLabel, ifFalse );
	CJUMP* secondTrueJump = 
		new CJUMP( enums::NE, rightExp, new CONST( 0 ), ifTrue, ifFalse );
	return new SEQ( firstTrueJump, new SEQ( 
		new LABEL( firstTrueLabel ), secondTrueJump ) );
}
