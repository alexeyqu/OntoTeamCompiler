
#pragma once

#include "IType.h"

class CBuiltInType : public IType
{
public:
   	CBuiltInType( enums::TType _type );

   	void Accept( IVisitor *visitor ) override;

   	// CSymbol *getSymbol() override;
};