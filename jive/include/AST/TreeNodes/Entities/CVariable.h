#pragma once

#include "../IType.h"
#include "../IEntity.h"
#include "../Expressions/CIdExpression.h"

class CVariable : public IEntity
{
public:
   	CVariable( IType *_type, CIdExpression *_id );

   	void Accept( IVisitor *visitor ) override;

	IType *type;
	CIdExpression *id;
};