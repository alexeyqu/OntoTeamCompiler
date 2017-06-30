#pragma once

#include "ICondTranslator.h"

namespace IRTTRANSLATOR
{

class CJumpTranslator : public ICondTranslator
{
public:
	CJumpTranslator( TCJUMP _operation, IExp *_left, IExp *_right )
		:  left( _left ), right( _right ), operation( _operation ) {};
	
	IStm *unCx( CLabel *ifTrue, CLabel *ifFalse ) const override \
		{ return new CCJUMP( operation, left, right, ifTrue, ifFalse ); }

private:
	IExp *left;
	IExp *right;
	TCJUMP operation;
};

}