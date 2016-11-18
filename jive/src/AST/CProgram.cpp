#include "CProgram.h"

CProgram::CProgram( IStatement *_statement ) : statement( _statement ) {}
 
void CProgram::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}