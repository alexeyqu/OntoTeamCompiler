#pragma once

#include <string>
#include "IVisitorTarget.h"
#include <string>

class VariablesTable 
{
public:
	const std::string name;
	const int value;
	IVisitorTarget* node;
	VariablesTable* next;
	const VariablesTable* const tail;

	VariablesTable( std::string name, const int value, 
		IVisitorTarget* node, VariablesTable* next, const VariablesTable* tail ):
		name( name ), value( value ), node( node ), next( next ), tail( tail == 0 ? this :  tail ) {}
};