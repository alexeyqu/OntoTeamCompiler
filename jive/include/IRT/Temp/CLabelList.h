#pragma once

#include "CLabel.h"

namespace IRT
{

class CLabelList
{
public:
    CLabelList( CLabel *_label, CLabelList *_next ) : label( _label ), next( _next ) {}
    CLabelList( CLabel *_label ) : label( _label ), next( nullptr ) {}

    const CLabel *getLabel() const { return label; }
    const CLabelList *getNext() const { return next; }

private:
    CLabel *label;
    CLabelList *next;
};

}