#pragma once

#pragma once

#include "IRTree/IAccess.h"
#include "IRTree/Temp/CTemp.h"

class CInObjAccess : public IAccess {
public:
	CInObjAccess( int _offset, CTemp* _thisPointer ) : 
		offset( _offset ), thisPointer( _thisPointer ) {};
	IExp* GetExp() const;
private:
	CTemp* thisPointer;
	int offset;
};
