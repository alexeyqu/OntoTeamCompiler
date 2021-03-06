#pragma once

#include "ITranslator.h"

namespace IRTTRANSLATOR
{

class ICondTranslator : public ITranslator
{
public:
	virtual IExp *unEx() const override;
	virtual IStm *unNx() const override;
	virtual IStm *unCx( CLabel *ifTrue, CLabel *ifFalse ) const = 0;
};

}