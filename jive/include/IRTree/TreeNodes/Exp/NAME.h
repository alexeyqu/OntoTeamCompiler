#pragma once

#include "../IExp.h"
#include "IRTree/IIRTreeVisitor.h"
#include "IRTree/Temp/CLabel.h"

class NAME : public IExp
{
public:
	NAME( const CLabel* _label ) : label( _label ) {};
	const CLabel* GetLabel() const;
	void Accept( IIRTreeVisitor *visitor );

private:
	const CLabel* label;
};