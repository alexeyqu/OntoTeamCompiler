#pragma once

#include "../IEntity.h"
#include "../IExpression.h"

class CField : public IEntity
{
public:
   	CField( CType *_type, CIdExpression *_id );

   	void Accept( IVisitor *visitor ) override;

	CType *type;
	CIdExpression *id;
};