#pragma once

#include "CTemp.h"

namespace IRT
{

class CTempList
{
public:
    CTempList( CTemp *_temp, CTempList *_next ) : temp( _temp ), next( _next ) {}
    CTempList( CTemp *_temp ) : temp( _temp ), next( nullptr ) {}

    const CTemp *getTemp() const { return temp; }
    const CTempList *getNext() const { return next; }

private:
    CTemp *temp;
    CTempList *next;
};

}