#include "CProgram.h"

namespace AST 
{

CProgram::CProgram( IVisitorTarget *_rootVertex ) : rootVertex( _rootVertex ) {}
 
void CProgram::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}

}