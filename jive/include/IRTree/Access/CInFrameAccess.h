#pragma once

#include "IRTree/IAccess.h"
#include "IRTree/Temp/CTemp.h"

class CInFrameAccess : public IAccess {
public:
	CInFrameAccess( int _offset, CTemp* _framePointer ) : 
		offset( _offset ), framePointer( _framePointer ) {};
	IExp* GetExp() const;
private:
	CTemp* framePointer;
	int offset;
};