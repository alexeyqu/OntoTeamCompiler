#pragma once

#include "IRTree/Wrappers/CConditionalWrapper.h"

class COrConverter : public CConditionalWrapper
{
public:
	COrConverter( IExp* _leftExp, IExp* _rightExp )
		: leftExp( _leftExp ), rightExp( _rightExp ) {};
	IStm* ToConditional( CLabel* ifTrue, CLabel* ifFalse ) const;
private:
	IExp* leftExp;
	IExp* rightExp;
};