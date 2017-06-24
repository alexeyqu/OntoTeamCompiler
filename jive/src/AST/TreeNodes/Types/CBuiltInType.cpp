#include "CBuiltInType.h"

namespace AST 
{

CBuiltInType::CBuiltInType( jive::TType _type ) : \
	IType( _type ) {}

void CBuiltInType::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

CSymbol CBuiltInType::getSymbol() {
	switch( type ) {
		case jive::INTEGER :
			return CSymbol( "int" );
		case jive::INTEGERARRAY :
			return CSymbol( "int[]" );
		case jive::BOOLEAN :
			return CSymbol( "boolean" );
		case jive::STRING :
			return CSymbol( "String" );
		case jive::STRINGARRAY :
			return CSymbol( "String[]" );
		case jive::UNKNOWNTYPE :
			return CSymbol( "UnknownType" );
		case jive::VOID :
			return CSymbol( "void" );
		default:
			return CSymbol( "ErrorType" );
	}
}

}