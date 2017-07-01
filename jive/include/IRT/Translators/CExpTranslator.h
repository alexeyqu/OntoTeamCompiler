#pragma once

#include "ITranslator.h"

namespace IRTTRANSLATOR
{

class CExpTranslator : public ITranslator
{
public:
	CExpTranslator( IExp *_exp ) : exp( _exp ) {}
	
	IExp *unEx() const override { return exp; }
	IStm *unNx() const override { return new CEXP( exp ); }
	IStm *unCx( CLabel *ifTrue, CLabel *ifFalse ) const override \
		{ return new CCJUMP( TCJUMP::NE, exp, new CCONST( 0 ), ifTrue, ifFalse ); }

private:
	IExp *exp;
};

}