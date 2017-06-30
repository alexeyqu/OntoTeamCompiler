#pragma once

#include "IExp.h"
#include "IStm.h"
#include "CLabel.h"

namespace IRT
{

class ITranslator
{
public:
	virtual IExp *unEx() const = 0;
	virtual IStm *unNx() const = 0;
	virtual IStm *unCx( CLabel *ifTrue, CLabel *ifFalse ) const = 0;
};

}