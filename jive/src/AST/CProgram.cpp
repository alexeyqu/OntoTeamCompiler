#include "AST/CProgram.h"

CProgram::CProgram( IVisitorTarget *_rootVertex ) : rootVertex( _rootVertex ) {}
 
void CProgram::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}