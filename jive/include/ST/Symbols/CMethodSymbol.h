#include "ISymbol.h"
#include "CMethod.h"

class CMethodSymbol : public ISymbol {

public:
	CMethodSymbol( std::string _name, IType* _type, CMethod* _method) : ISymbol( _name, _type ), method( _method ) {}

	CMethod* method;
}; 
