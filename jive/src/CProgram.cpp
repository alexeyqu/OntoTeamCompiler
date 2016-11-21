#include "CProgram.h"

CProgram::CProgram( IVisitorTarget *_rootVertex ) : rootVertex( _rootVertex ), symbolTable( new CSymbolTable ) {}
 
void CProgram::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}