#include "CType.h"

namespace AST
{

void CType::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

// CTypeTable::CTypeTable() {
// 	insert( CSymbol( "int" ), INTEGER );
//     insert( CSymbol( "int[]" ), INTEGERARRAY );
//     insert( CSymbol( "boolean" ), BOOLEAN );
//     insert( CSymbol( "String" ), STRING );
//     insert( CSymbol( "String[]" ), STRINGARRAY );
//     insert( CSymbol( "void" ), VOID );
// }

}