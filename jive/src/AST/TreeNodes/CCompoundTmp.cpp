#include "CCompoundTmp.h"

CCompoundTmp::CCompoundTmp( IVisitorTarget *_tmp1, IVisitorTarget *_tmp2 ) : \
	tmp1( _tmp1 ), tmp2( _tmp2 ) {}
 
void CCompoundTmp::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}