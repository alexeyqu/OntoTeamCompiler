#pragma once

#include "../IEntity.h"

class CArgument : public IEntity
{
public:
   	CArgument( CType *_type, CIdExpression *_id );

   	void Accept( IVisitor *visitor ) override;

	CType *type;
	CIdExpression *id;
};