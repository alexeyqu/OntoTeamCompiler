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

class CInObject : public IAccess
{
public:
	CInObject( int _offset, CTemp *_thisPointer ) : offset( _offset ), thisPointer( _thisPointer ) {}

	IExp *getExp() const { return new CMEM( new CBINOP( TBINOP::ADD, new CTEMP( thisPointer ), new CCONST( offset ) ) ); }

private:
	CTemp *thisPointer;
	int offset;
};

}