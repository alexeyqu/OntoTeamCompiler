#pragma once

#include "IVisitor.h"

class CPrintVisitor : public IVisitor
{
public:
    
    CPrintVisitor();
    void Visit( CCompoundStatement* stmt );
    void Visit( CIdExpression* expr );
    void Visit( CBinaryExpression* expr );
    void Visit( CNumberExpression* expr );
    void Visit( CAssignStatement* stmt );
    void Visit( CPrintStatement* stmt );
    void Visit( CLastExpressionList* expr );
};
