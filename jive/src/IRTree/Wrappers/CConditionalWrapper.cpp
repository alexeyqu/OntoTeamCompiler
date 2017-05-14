#include "IRTree/Wrappers/CConditionalWrapper.h"
#include "IRTree/TreeNodes/Nodes.h"

IExp* CConditionalWrapper::ToExp() const {
	CTemp* temp = new CTemp();
	TEMP* returnValue = new TEMP( temp );
	MOVE* moveTrue = new MOVE( returnValue, new CONST( 1 ) );
	MOVE* moveFalse = new MOVE( returnValue, new CONST( 0 ) );
	CLabel* trueLabel = new CLabel();
	CLabel* falseLabel = new CLabel();
	CLabel* endLabel = new CLabel();

	return new ESEQ( new SEQ
		( new SEQ
			( new SEQ
				( new SEQ
					( ToConditional( trueLabel, falseLabel ),
					new SEQ( new LABEL( trueLabel ), moveTrue ) ),
					new JUMP( endLabel ) ),
					new SEQ( new LABEL( falseLabel ), moveFalse ) ),
					new LABEL( endLabel ) ),
					returnValue );
}

IStm* CConditionalWrapper::ToStm() const {
	CLabel* tempLabel = new CLabel();
	IStm* conditional = ToConditional( tempLabel, tempLabel );
	return new SEQ( conditional, new LABEL( tempLabel ) );
}