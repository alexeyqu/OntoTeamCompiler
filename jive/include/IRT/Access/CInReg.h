#pragma once

#include "IAccess.h"
#include "IExp.h"
#include "CTemp.h"
#include "CTEMP.h"

namespace IRT
{

class CInReg : public IAccess
{
public:
	CInReg( CTemp *_regId ) : regId( _regId ) {}

	IExp *getExp() const { return new CTEMP( regId ); }

private:
	CTemp *regId;
};

}