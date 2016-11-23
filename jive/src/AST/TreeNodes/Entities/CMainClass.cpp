#include "CMainClass.h"

CMainClass::CMainClass( CIdExpression *_name, 
        CIdExpression *_cmdArgs,
        IStatement *_statement ) : \
    name( _name ), cmdArgs( _cmdArgs ), 
    statement( _statement ) {}

void CMainClass::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}
 
