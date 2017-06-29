#pragma once

#include "IIRTVisitor.h"

namespace IRT
{

class IIRTVisitorTarget
{
public:
   	virtual ~IIRTVisitorTarget() {}
       
    virtual void Accept( IIRTVisitor *visitor ) = 0;
};

}