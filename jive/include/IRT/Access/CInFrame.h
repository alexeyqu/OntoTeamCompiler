#pragma once

#include "IAccess.h"
#include "CTemp.h"
#include "IExp.h"
#include "CMEM.h"
#include "CBINOP.h"
#include "CTEMP.h"
#include "CCONST.h"

namespace IRT
{

class CInFrame : public IAccess
{
public:
	CInFrame( int _offset, CTemp *_framePointer ) : offset( _offset ), framePointer( _framePointer ) {}

	IExp *getExp() const { return new CMEM( new CBINOP( TBINOP::ADD, new CTEMP( framePointer ), new CCONST( offset ) ) ); }

private:
	CTemp *framePointer;
	int offset;
};

}