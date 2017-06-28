#include "CClassTable.h"

namespace ST
{

CClassSymbol *CClassTable::lookup( CSymbol *name ) {
    for( auto classTuple : table ) {
        if( classTuple.first->name->name == name ) {
            return classTuple.second;
        }
    }

    return nullptr;
}

}