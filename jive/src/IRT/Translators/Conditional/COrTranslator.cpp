#include "COrTranslator.h"

namespace IRTTRANSLATOR
{

IStm *COrTranslator::unCx( CLabel *ifTrue, CLabel *ifFalse ) const {
    CLabel *leftIsFalse = new CLabel();
    return new CSEQ( // (left != 0) || (right != 0) => ifTrue, otherwise => ifFalse
        new CCJUMP( TCJUMP::NE, leftExp, new CCONST( 0 ), ifTrue, leftIsFalse ), // test left
        new CSEQ(  
            new CLABEL( leftIsFalse ), // left == 0
            new CCJUMP( TCJUMP::NE, rightExp, new CCONST( 0 ), ifTrue, ifFalse ) // test right
        )
     );
}

}