#include "CGoal.h"

CGoal::CGoal( IVisitorTarget *_tmp1, IVisitorTarget *_tmp2 ) : \
	tmp1( _tmp1 ), tmp2( _tmp2 ) {}
 
void CGoal::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}