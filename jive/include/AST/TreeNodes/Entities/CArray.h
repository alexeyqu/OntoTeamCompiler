#pragma once

#include "../IEntity.h"

class CArray : public IEntity
{
public:
   	CArray( CType *_type, int _size );

   	void Accept( IVisitor *visitor ) override;

	CType *type;
	int size;
};