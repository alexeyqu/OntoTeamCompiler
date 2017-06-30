#pragma once

#include "ICondTranslator.h"

namespace IRTTRANSLATOR
{

class COrTranslator : public ICondTranslator
{
public:
	COrTranslator( IExp *_leftExp, IExp *_rightExp )
		: leftExp( _leftExp ), rightExp( _rightExp ) {}
	
	IStm *unCx( CLabel *ifTrue, CLabel *ifFalse ) const override;

private:
	IExp *leftExp;
	IExp *rightExp;
};

}