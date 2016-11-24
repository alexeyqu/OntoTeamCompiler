#include "CProgram.h"

CProgram::CProgram( IVisitorTarget *_rootVertex, CJiveEnvironment *_jiveEnv ) : rootVertex( _rootVertex ), jiveEnv( _jiveEnv ) {}
 
void CProgram::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}