#include "CBuiltInType.h"

CBuiltInType::CBuiltInType( jive::TType _type ) : \
	IType( _type ) {}

void CBuiltInType::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

// std::string CBuiltInType::ToString() {
// 	switch( type ) {
// 		case jive::INTEGER :
// 			return "int";
// 		case jive::INTEGERARRAY :
// 			return "int[]";
// 		case jive::BOOLEAN :
// 			return "boolean";
// 		case jive::STRING :
// 			return "String";
// 		case jive::STRINGARRAY :
// 			return "String[]";
// 		case jive::UNKNOWNTYPE :
// 			return "UnknownType";
// 		case jive::VOID :
// 			return "void";
// 		default:
// 			return "ErrorType";
// 	}

// }