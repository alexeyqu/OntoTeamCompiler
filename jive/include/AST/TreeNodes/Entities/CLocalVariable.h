#pragma once

#include "CType.h"
#include "../IEntity.h"
#include "../IExpression.h"

class CLocalVariable : public IEntity
{
public:
   	CLocalVariable( CType *_type, CIdExpression *_id );

   	void Accept( IVisitor *visitor ) override;
   	enums::TType getType();

	CType *type;
	CIdExpression *id;
};