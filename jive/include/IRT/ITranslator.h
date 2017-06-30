#pragma once

#include "Exps.h"
#include "Stms.h"
#include "CLabel.h"

namespace IRTTRANSLATOR
{

using IRT::TBINOP;
using IRT::TCJUMP;

using IRT::CLabel;
using IRT::CTemp;

using IRT::IExp;
using IRT::IStm;

using IRT::CCONST;
using IRT::CNAME;
using IRT::CTEMP;
using IRT::CBINOP;
using IRT::CMEM;
using IRT::CCALL;
using IRT::CESEQ;

using IRT::CMOVE;
using IRT::CEXP;
using IRT::CJUMP;
using IRT::CCJUMP;
using IRT::CSEQ;
using IRT::CLABEL;

class ITranslator
{
public:
	virtual IExp *unEx() const = 0;
	virtual IStm *unNx() const = 0;
	virtual IStm *unCx( CLabel *ifTrue, CLabel *ifFalse ) const = 0;
};

}