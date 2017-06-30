#include "ICondTranslator.h"

namespace IRTTRANSLATOR
{

IExp *ICondTranslator::unEx() const {
    CTemp *r = new CTemp(); // resulting expression
    CLabel *t = new CLabel();
    CLabel *f = new CLabel();

    return new CESEQ( 
        new CSEQ(
            new CMOVE( new CTEMP( r ), new CCONST( 1 ) ), // assume we go to true label
            new CSEQ(
                unCx( t, f ), // decide path
                new CSEQ(
                    new CLABEL( f ), // oops, it's false label
                    new CSEQ(
                        new CMOVE( new CTEMP( r ), new CCONST( 0 ) ), // set r to 0
                        new CLABEL( t ) // r is 1 here
                    )
                )
            )
        ),
        new CTEMP( r ) // control flow: 0 or 1
    ); 
}

IStm *ICondTranslator::unNx() const {
    CLabel *t = new CLabel();

    return new CSEQ(
        unCx( t, t ), // anyway we go into t label
        new CLABEL( t )
    );
}

}
