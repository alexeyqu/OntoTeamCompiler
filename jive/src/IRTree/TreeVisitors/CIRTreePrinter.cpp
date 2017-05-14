#include "IRTree/TreeVisitors/CIRTreePrinter.h"
#include "IRTree/TreeNodes/Nodes.h"
#include <cassert>

CIRTreePrinter::CIRTreePrinter( const std::string& outputFileName ) : 
	visitedNodesCount( 0 ), curNodeId( 0 ), prevNodeId( 0 ) {
	graphvizOut = std::ofstream( outputFileName );
}

CIRTreePrinter::~CIRTreePrinter() {
	graphvizOut.close();
}

void CIRTreePrinter::Visit( BINOP* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "BINOP";
	visitNewNode();
	switch ( node->GetOp() ) {
		case enums::BO_ADD:
			nodeLabels[curNodeId] = "PLUS";
			break;
		case enums::BO_SUB:
			nodeLabels[curNodeId] = "MINUS";
			break;
		case enums::BO_MUL:
			nodeLabels[curNodeId] = "MUL";
			break;
		case enums::BO_DIV:
			nodeLabels[curNodeId] = "DIV";
			break;
		default:
			assert( false );
	}
	leaveNode();
	node->GetLeft()->Accept( this );
	node->GetRight()->Accept( this );
	leaveNode();
}

void CIRTreePrinter::Visit( CALL* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "CALL";
	node->GetFunc()->Accept( this );
	if ( node->GetArgs() ) {
		node->GetArgs()->Accept( this );
	}
	leaveNode();
}

void CIRTreePrinter::Visit( CONST* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "CONST " + std::to_string( node->GetValue() );
	leaveNode();
}

void CIRTreePrinter::Visit( ESEQ* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "ESEQ";
	node->GetStm()->Accept( this );
	node->GetExp()->Accept( this );
	leaveNode();
}

void CIRTreePrinter::Visit( MEM* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "MEM";
	node->GetExp()->Accept( this );
	leaveNode();
}

void CIRTreePrinter::Visit( NAME* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "NAME " + node->GetLabel()->Name();
	leaveNode();
}

void CIRTreePrinter::Visit( TEMP* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "TEMP " + node->GetTemp()->Name();
	leaveNode();
}

void CIRTreePrinter::Visit( CExpList* node ) {
	IExp* tail = node->GetTail();
	CExpList* headExp = node->GetHead();	
	if ( tail ) {
		tail->Accept( this );
	}	
	if ( headExp ) {
		headExp->Accept( this );
	}	
}

void CIRTreePrinter::Visit( CJUMP* node ) {
	visitNewNode();
	nodeLabels[ curNodeId ] = "CJUMP";
	size_t tempNode = createNewNode();
	switch ( node->GetOp() )
	{
		case enums::EQ:
			nodeLabels[tempNode] = "==";
			break;
		case enums::GE:
			nodeLabels[tempNode] = ">=";
			break;
		case enums::GT:
			nodeLabels[tempNode] = ">";
			break;
		case enums::LE:
			nodeLabels[tempNode] = "<=";
			break;
		case enums::LT:
			nodeLabels[tempNode] = "<";
			break;
		case enums::NE:
			nodeLabels[tempNode] = "!=";
			break;
		default:
			nodeLabels[tempNode] = "UNKNOWN";
			assert( false );
	}
	addEdge( curNodeId, tempNode );
	node->GetLeft()->Accept( this );
	node->GetRight()->Accept( this );	
	tempNode = createNewNode();
	nodeLabels[tempNode] = "LABEL " + node->GetIfTrue()->Name();
	addEdge( curNodeId, tempNode );
	tempNode = createNewNode();
	nodeLabels[tempNode] = "LABEL " + node->GetIfFalse()->Name();
	addEdge( curNodeId, tempNode );
	leaveNode();
}

void CIRTreePrinter::Visit( EXP* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "EXP";
	node->GetExp()->Accept( this );
	leaveNode();
}


void CIRTreePrinter::Visit( JUMP* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "JUMP";
	node->GetExp()->Accept( this );
	CLabel* curNode = node->GetTargets()->GetHead();
	CLabelList* labelsTail = node->GetTargets()->GetTail();
	while ( curNode ) {
		size_t tempNode = createNewNode();
		nodeLabels[tempNode] = "LABEL " + curNode->Name();
		addEdge( curNodeId, tempNode );
		if ( labelsTail ) {
			curNode = labelsTail->GetHead();
			labelsTail = labelsTail->GetTail();
		} else {
			curNode = nullptr;
		}		
	}
	leaveNode();
}

void CIRTreePrinter::Visit( LABEL* node ) {
	visitNewNode();
	nodeLabels[ curNodeId ] = "LABEL " + node->GetLabel()->Name();
	leaveNode();
}

void CIRTreePrinter::Visit( MOVE* node ) {
	visitNewNode();
	nodeLabels[curNodeId] = "MOVE";	
	node->GetDst()->Accept( this );
	node->GetSrc()->Accept( this );
	leaveNode();
}

void CIRTreePrinter::Visit( SEQ* node ) {
	visitNewNode();
	nodeLabels[ curNodeId ] = "SEQ";
	if ( node->GetLeft() ) {
		node->GetLeft()->Accept( this );
	}	
	if ( node->GetRight() ) {
		node->GetRight()->Accept( this );
	}
	leaveNode();
}

void CIRTreePrinter::Visit( CStmList* node ) {
	IStm* nextExp = node->GetHead();
	CStmList* tail = node->GetTail();	
	if ( nextExp ) {
		nextExp->Accept( this );
	}
	if ( tail ) {
		tail->Accept( this );
	}
}

void CIRTreePrinter::OpenFile() {
	graphvizOut << "digraph IRTree {" << std::endl;
}

void CIRTreePrinter::CloseFile() {
	graphvizOut << "}" << std::endl;
	graphvizOut.close();
}

void CIRTreePrinter::WriteGraphToFile() {			
	for ( auto& edge : treeEdges ) {
		graphvizOut << prefix << edge.first << " -> " << prefix << edge.second << std::endl;
	}
	for ( auto& node : nodeLabels ) {
		graphvizOut << prefix << node.first << "[ label = \"" << node.second << "\" ]" << std::endl;
	}
}

void CIRTreePrinter::ResetPrinter( const std::string& _prefix, const std::string& fragmentName ) {
	visitedNodesCount = 0;
	curNodeId = prevNodeId = 0;
	nodeLabels.clear();
	treeEdges.clear();
	prefix = _prefix;
	nodeLabels[0] = fragmentName;
	addEdge( 0, 1 );
}

void CIRTreePrinter::visitNewNode() {
	prevNodeId = curNodeId;
	visitedNodesCount++;
	curNodeId = visitedNodesCount;
	nodeStack.push( curNodeId );
	if ( prevNodeId != 0 ) {
		addEdge( prevNodeId, curNodeId );
	}			
}

void CIRTreePrinter::leaveNode() {
	prevNodeId = curNodeId;
	nodeStack.pop();
	if ( !nodeStack.empty() ) {
		curNodeId = nodeStack.top();
	}
}

size_t CIRTreePrinter::createNewNode() {
	visitedNodesCount++;
	return visitedNodesCount;
}

void CIRTreePrinter::addEdge( size_t from, size_t to ) {
	treeEdges.push_back( std::make_pair(from, to) );
}