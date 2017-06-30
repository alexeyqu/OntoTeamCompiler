#include "CAndTranslator.h"

namespace IRTTRANSLATOR
{

IStm *CAndTranslator::unCx( CLabel *ifTrue, CLabel *ifFalse ) const {
    CLabel *leftIsTrue = new CLabel();
    return new CSEQ( // (left != 0) && (right != 0) => ifTrue, otherwise => ifFalse
        new CCJUMP( TCJUMP::NE, leftExp, new CCONST( 0 ), leftIsTrue, ifFalse ), // test left
        new CSEQ(  
            new CLABEL( leftIsTrue ), // left != 0
            new CCJUMP( TCJUMP::NE, rightExp, new CCONST( 0 ), ifTrue, ifFalse ) // test right
        )
     );
}

}