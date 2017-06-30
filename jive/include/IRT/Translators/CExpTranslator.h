#pragma once

#include "ITranslator.h"

class CExpTranslator : public ITranslator
{
public:
	CExpConverter( IExp *_exp ) : exp( _exp ) {}
	
	IExp *unEx() const override { return exp; }
	IStm *unNx() const override { return new CEXP( exp ); }
	IStm *unCx( CLabel *ifTrue, CLarebel *ifFalse ) const override { return new CCJUMP( TCJUMP::NE, exp, new CCONST( 0 ), ifTrue, ifFalse ); }

private:
	IExp *exp;
};