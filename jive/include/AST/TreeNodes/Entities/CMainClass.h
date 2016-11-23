 #pragma once

#include "../IEntity.h"
#include "../IStatement.h"
#include "../IExpression.h"

class CMainClass : public IEntity
{
public:
    CMainClass( CIdExpression *_name, 
        CIdExpression *_cmdArgs,
        IStatement *_statement );

    void Accept( IVisitor *visitor ) override;

    CIdExpression *name;
    CIdExpression *cmdArgs;
    IStatement *statement;
};
