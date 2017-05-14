#pragma once

#include "../IExp.h"
#include "IRTree/IIRTreeVisitor.h"

class CONST : public IExp {
public:
	CONST( int _value )	: value( _value ) {};
	int GetValue() const;
	void Accept( IIRTreeVisitor *visitor );

private:
	int value;
};