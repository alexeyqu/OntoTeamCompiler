#pragma once

#include "../IType.h"
#include "../IEntity.h"

class CArgument : public IEntity
{
public:
   	CArgument( IType *_type, CIdExpression *_id );

   	void Accept( IVisitor *visitor ) override;

	IType *type;
	CIdExpression *id;
};