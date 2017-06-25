#include "CGoal.h"

namespace AST 
{

CGoal::CGoal( IVisitorTarget *_left, IVisitorTarget *_right ) : \
	left( _left ), right( _right ) {}
 
void CGoal::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}

}