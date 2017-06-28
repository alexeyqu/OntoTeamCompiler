#include "CClassTable.h"

namespace ST
{

CClassSymbol *CClassTable::lookup( CSymbol *name ) {
    for( auto classTuple : table ) {
        if( classTuple.first->getString() == name->getString() ) {
            return classTuple.second;
        }
    }

    return nullptr;
}

}