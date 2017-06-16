#include "CBuiltInType.h"

CBuiltInType::CBuiltInType( enums::TType _type ) : \
	IType( _type ) {}

void CBuiltInType::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

std::string CBuiltInType::ToString() {
	switch( type ) {
		case enums::INTEGER :
			return "int";
		case enums::INTEGERARRAY :
			return "int[]";
		case enums::BOOLEAN :
			return "boolean";
		case enums::STRING :
			return "String";
		case enums::STRINGARRAY :
			return "String[]";
		case enums::UNKNOWNTYPE :
			return "UnknownType";
		case enums::VOID :
			return "void";
		default:
			return "ErrorType";
	}

}