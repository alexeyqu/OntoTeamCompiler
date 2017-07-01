#pragma once

#include <string>
#include <map>
#include <stack>
#include <vector>
#include "IIRTVisitor.h"
#include "CSymbol.h"

namespace IRT
{

using ST::CSymbol;

class CIRTPrintVisitor : public IIRTVisitor
{
public:
    CIRTPrintVisitor( CJiveEnvironment *_jiveEnv, std::ostream &_outputStream ) : \
        IIRTVisitor( _jiveEnv, _outputStream ), visitedNodesCount( 0 ), curNodeId( 0 ), prevNodeId( 0 )
    {}

    void Visit( CCONST *exp ) override;
    void Visit( CNAME *exp ) override;
    void Visit( CTEMP *exp ) override;
    void Visit( CBINOP *exp ) override;
    void Visit( CMEM *exp ) override;
    void Visit( CCALL *exp ) override;
    void Visit( CESEQ *exp ) override;
    
    void Visit( CMOVE *stm ) override;
    void Visit( CEXP *stm ) override;
    void Visit( CJUMP *stm ) override;
    void Visit( CCJUMP *stm ) override;
    void Visit( CSEQ *stm ) override;
    void Visit( CLABEL *stm ) override;

    void Visit( CExpList *exp ) override;
    void Visit( CStmList *stm ) override;

    void startIRForest();
    void endIRForest();

    void writeIRTree();
    void newIRTree( const std::string &_treePrefix, CSymbol *fragmentName );

private:
    std::string treePrefix;
    int visitedNodesCount;
    int curNodeId;
    int prevNodeId;

    std::stack<int> nodeStack;
    std::map<int, std::string> nodeLabels;
    std::vector<std::pair<int, int> > treeEdges;

    void visitNewNode();
    void leaveNode();
    int createNewNode();
    void addEdge( int from, int to );
};

}