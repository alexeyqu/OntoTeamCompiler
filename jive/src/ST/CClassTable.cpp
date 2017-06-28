#include "CClassTable.h"

namespace ST
{

CClassSymbol *CClassTable::lookup( CSymbol *name ) {
    for( auto classTuple : table ) {
        if( classTuple.first->name->name->get() == name->get() ) {
            return classTuple.second;
        }
    }

    return nullptr;
}

}