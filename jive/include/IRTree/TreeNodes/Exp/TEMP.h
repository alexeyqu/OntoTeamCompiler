#pragma once

#include "../IExp.h"
#include "CExpList.h"
#include "IRTree/IIRTreeVisitor.h"
#include "IRTree/Temp/CTemp.h"

class TEMP : public IExp
{
public:
	TEMP( const CTemp* _temp ) : temp( _temp ) {};
	const CTemp* GetTemp() const;
	void Accept( IIRTreeVisitor *visitor );

	CExpList* Kids();
	IExp* Build( CExpList* kids );

private:
	const CTemp* temp;
};