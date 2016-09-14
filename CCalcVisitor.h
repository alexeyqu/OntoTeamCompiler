#pragma once

#include "IVisitor.h"
#include "IVisitorTarget.h"
#include "CAssignStatement.h"
#include "CBinaryExpression.h"
#include "CCompoundStatement.h"
#include "CLastExpressionList.h"
#include "CNumberExpression.h"
#include "CPrintStatement.h"
#include "CPrintVisitor.h"
#include "CIdExpression.h"
#include "VariablesTable.h"

class CCalcVisitor : public IVisitor
{
public:

    VariablesTable* head;
	
	CCalcVisitor();
    void Start( IVisitorTarget* target );
    void Visit( CCompoundStatement* stmt );
    void Visit( CIdExpression* expr );
    void Visit( CBinaryExpression* expr );
    void Visit( CNumberExpression* expr );
    void Visit( CAssignStatement* stmt );
    void Visit( CPrintStatement* stmt );
    void Visit( CLastExpressionList* expr );

    ~CCalcVisitor();
};