#include "CIRTPrintVisitor.h"
#include "Exps.h"
#include "Stms.h"

namespace IRT
{

void CIRTPrintVisitor::Visit( CBINOP* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "BINOP";
	visitNewNode();

	switch ( node->getBinop() ) {
		case TBINOP::ADD:
			nodeLabels[curNodeId] = "ADD";
			break;
		case TBINOP::SUB:
			nodeLabels[curNodeId] = "SUB";
			break;
		case TBINOP::MUL:
			nodeLabels[curNodeId] = "MUL";
			break;
		case TBINOP::DIV:
			nodeLabels[curNodeId] = "DIV";
			break;
		default:
			assert( false );
	}

	leaveNode();
	node->getLeft()->Accept( this );
	node->getRight()->Accept( this );
	leaveNode();
}

void CIRTPrintVisitor::Visit( CCALL* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "CALL";

	node->getFunc()->Accept( this );
	if ( node->getArgs() ) {
		node->getArgs()->Accept( this );
	}

	leaveNode();
}

void CIRTPrintVisitor::Visit( CCONST* node ) {
	visitNewNode();

	nodeLabels[curNodeId] = "CONST " + std::to_string( node->getValue() );

	leaveNode();
}

void CIRTPrintVisitor::Visit( CESEQ* node ) {
	visitNewNode();

	nodeLabels[curNodeId] = "ESEQ";

	node->getStm()->Accept( this );
	node->getExp()->Accept( this );

	leaveNode();
}

void CIRTPrintVisitor::Visit( CMEM* node ) {
	visitNewNode();

	nodeLabels[curNodeId] = "MEM";
	node->getExp()->Accept( this );

	leaveNode();
}

void CIRTPrintVisitor::Visit( CNAME* node ) {
	visitNewNode();

	nodeLabels[curNodeId] = "NAME " + node->getLabel()->getString().get();

	leaveNode();
}

void CIRTPrintVisitor::Visit( CTEMP* node ) {
	visitNewNode();

	nodeLabels[curNodeId] = "TEMP " + node->getTemp()->getString().get();

	leaveNode();
}

void CIRTPrintVisitor::Visit( CExpList* node ) {
	IExp* tail = node->getExp();
	CExpList* headExp = node->getNext();

	if ( tail ) {
		tail->Accept( this );
	}	

	if ( headExp ) {
		headExp->Accept( this );
	}	
}

void CIRTPrintVisitor::Visit( CCJUMP* node ) {
	visitNewNode();
	nodeLabels[ curNodeId ] = "CJUMP";
	int tempNode = createNewNode();

	switch ( node->getRelop() )
	{
		case TCJUMP::EQ:
			nodeLabels[tempNode] = "==";
			break;
		case TCJUMP::GE:
			nodeLabels[tempNode] = ">=";
			break;
		case TCJUMP::GT:
			nodeLabels[tempNode] = ">";
			break;
		case TCJUMP::LE:
			nodeLabels[tempNode] = "<=";
			break;
		case TCJUMP::LT:
			nodeLabels[tempNode] = "<";
			break;
		case TCJUMP::NE:
			nodeLabels[tempNode] = "!=";
			break;
		default:
			nodeLabels[tempNode] = "UNKNOWN";
			assert( false );
	}
	addEdge( curNodeId, tempNode );

	node->getLeft()->Accept( this );
	node->getRight()->Accept( this );	

	tempNode = createNewNode();
	nodeLabels[tempNode] = "LABEL " + node->getIfTrue()->getString().get();
	addEdge( curNodeId, tempNode );

	tempNode = createNewNode();
	nodeLabels[tempNode] = "LABEL " + node->getIfFalse()->getString().get();
	addEdge( curNodeId, tempNode );

	leaveNode();
}

void CIRTPrintVisitor::Visit( CEXP* node ) {
	visitNewNode();

	nodeLabels[curNodeId] = "EXP";
	node->getExp()->Accept( this );

	leaveNode();
}


void CIRTPrintVisitor::Visit( CJUMP* node ) {
	visitNewNode();

	nodeLabels[curNodeId] = "JUMP";
	node->getExp()->Accept( this );

	CLabel* curNode = node->getTargets()->getLabel();
	CLabelList* labelsTail = node->getTargets()->getNext();
	while ( curNode ) {
		int tempNode = createNewNode();

		nodeLabels[tempNode] = "LABEL " + curNode->getString().get();
		addEdge( curNodeId, tempNode );

		if ( labelsTail ) {
			curNode = labelsTail->getLabel();
			labelsTail = labelsTail->getNext();
		} else {
			curNode = nullptr;
		}		
	}

	leaveNode();
}

void CIRTPrintVisitor::Visit( CLABEL* node ) {
	visitNewNode();

	nodeLabels[ curNodeId ] = "LABEL " + node->getLabel()->getString().get();

	leaveNode();
}

void CIRTPrintVisitor::Visit( CMOVE* node ) {
	visitNewNode();

	nodeLabels[curNodeId] = "MOVE";	

	node->getDst()->Accept( this );
	node->getSrc()->Accept( this );

	leaveNode();
}

void CIRTPrintVisitor::Visit( CSEQ* node ) {
	visitNewNode();

	nodeLabels[ curNodeId ] = "SEQ";

	if ( node->getLeft() ) {
		node->getLeft()->Accept( this );
	}	

	if ( node->getRight() ) {
		node->getRight()->Accept( this );
	}

	leaveNode();
}

void CIRTPrintVisitor::Visit( CStmList* node ) {
	IStm* nextExp = node->getStm();

	CStmList* tail = node->getNext();	

	if ( nextExp ) {
		nextExp->Accept( this );
	}
	if ( tail ) {
		tail->Accept( this );
	}
}

void CIRTPrintVisitor::startIRForest() {
	outputStream << "digraph IRTree {" << std::endl;
}

void CIRTPrintVisitor::endIRForest() {
	outputStream << "}" << std::endl;
}

void CIRTPrintVisitor::writeIRTree() {			
	for ( auto& edge : treeEdges ) {
		outputStream << treePrefix << edge.first << " -> " << treePrefix << edge.second << std::endl;
	}
	for ( auto& node : nodeLabels ) {
		outputStream << treePrefix << node.first << "[ label = \"" << node.second << "\" ]" << std::endl;
	}
}

void CIRTPrintVisitor::newIRTree( const std::string& _treePrefix, CSymbol *fragmentName ) {
	visitedNodesCount = 0;
	curNodeId = prevNodeId = 0;
	nodeLabels.clear();
	treeEdges.clear();
	treePrefix = _treePrefix;
	nodeLabels[0] = fragmentName->getString().get();
	addEdge( 0, 1 );
}

void CIRTPrintVisitor::visitNewNode() {
	prevNodeId = curNodeId;
	visitedNodesCount++;
	curNodeId = visitedNodesCount;
	nodeStack.push( curNodeId );
	if ( prevNodeId != 0 ) {
		addEdge( prevNodeId, curNodeId );
	}			
}

void CIRTPrintVisitor::leaveNode() {
	prevNodeId = curNodeId;
	nodeStack.pop();
	if ( !nodeStack.empty() ) {
		curNodeId = nodeStack.top();
	}
}

int CIRTPrintVisitor::createNewNode() {
	visitedNodesCount++;
	return visitedNodesCount;
}

void CIRTPrintVisitor::addEdge( int from, int to ) {
	treeEdges.push_back( std::make_pair(from, to) );
}

}