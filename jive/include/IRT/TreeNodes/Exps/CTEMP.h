#pragma once

#include "IExp.h"
#include "CTemp.h"

namespace IRT
{

class CTEMP : public IExp
{
public:
    CTEMP( CTemp *_temp ) : temp( _temp ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    CTemp *getTemp() const { return temp; }

private:
    CTemp *temp;
};

}