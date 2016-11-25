#include "IType.h"
#include <string>

 class ISymbol {
public:
	ISymbol( std::string _name, IType* _type ) : name( _name ), type( _type ) {}
	std::string name;
	IType* type;	
};