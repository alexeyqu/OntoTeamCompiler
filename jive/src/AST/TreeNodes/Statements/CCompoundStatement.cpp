#include "AST/TreeNodes/Statements/CCompoundStatement.h"

CCompoundStatement::CCompoundStatement( IStatement *_leftStatement, IStatement *_rightStatement ) : \
	leftStatement( _leftStatement ), rightStatement( _rightStatement ) {}
 
void CCompoundStatement::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}