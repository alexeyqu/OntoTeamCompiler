#pragma once

#include "CSymbol.h"

namespace IRT
{

using ST::CSymbol;

class CFrame
{
public:
    CFrame( CSymbol *_symbol );

private:
    CSymbol *symbol;

};

}