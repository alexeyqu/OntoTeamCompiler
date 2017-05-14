#pragma once

#include "IRTree/Wrappers/CConditionalWrapper.h"

class CAndConverter : public CConditionalWrapper
{
public:
	CAndConverter( IExp* _leftExp, IExp* _rightExp )
		: leftExp( _leftExp ), rightExp( _rightExp ) {};
	IStm* ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const;
private:
	IExp* leftExp;
	IExp* rightExp;
};