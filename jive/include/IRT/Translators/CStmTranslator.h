#pragma once

#include "ITranslator.h"

namespace IRTTRANSLATOR
{
	
class CStmTranslator : public ITranslator
{
public:
	CStmTranslator( IStm *_stm ) : stm( _stm ) {}
	
	IExp *unEx() const override { assert( !"Stm to Exp" ); return nullptr; }
	IStm *unNx() const override { return stm; }
	IStm *unCx( CLabel *ifTrue, CLabel *ifFalse ) const override { assert( !"Stm to Cond" ); return nullptr; }

private:
	IStm *stm;
};

}