#pragma once

#include "IRTree/IAccess.h"
#include "IRTree/Temp/CTemp.h"

class CInRegAccess : public IAccess {
	public:
		CInRegAccess( CTemp* _registerId ) : registerId( _registerId ) {};
		IExp* GetExp() const;
	private:
		CTemp* registerId;
	};