#pragma once

#include "ICondTranslator.h"

class CAndTranslator : public ICondTranslator
{
public:
	CAndTranslator( IExp *_leftExp, IExp *_rightExp )
		: leftExp( _leftExp ), rightExp( _rightExp ) {}
	
	IStm *unCx( CLabel *ifTrue, CLabel *ifFalse ) const override;

private:
	IExp *leftExp;
	IExp *rightExp;
};