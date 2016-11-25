#include "ISymbol.h"
#include "CClass.h"

class CMethodSymbol : public ISymbol {

public:
	CMethodSymbol( std::string _name, IType* _type, CClass* _thisClass) : ISymbol( _name, _type ), thisClass( _thisClass ) {}

	CClass* thisClass;
}; 

