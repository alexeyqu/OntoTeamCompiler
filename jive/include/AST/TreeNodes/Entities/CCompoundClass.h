#pragma once

#include "IEntity.h"

class CCompoundClass : public IEntity
{
public:
	CCompoundClass( CCompoundClass *_class1, CClass *_class2 );

	void Accept( IVisitor *visitor ) override;

	CCompoundClass *class1;
	CClass *class2;
};

