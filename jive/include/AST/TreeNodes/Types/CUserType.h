#pragma once

#include "../IType.h"
#include "CClass.h"

class CUserType : public IType
{
public:
   	CUserType( CClass *type );

   	void Accept( IVisitor *visitor ) override;

	CClass *typeClass;
}; 
