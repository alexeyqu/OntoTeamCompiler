#pragma once

#include "IRTree/IIRTreeVisitor.h"
#include <string>
#include <fstream>
#include <stack>
#include <map>
#include <vector>

class CIRTreePrinter : public IIRTreeVisitor
{
public:
	CIRTreePrinter( const std::string& outputFileName );
	~CIRTreePrinter();

	void Visit( BINOP* node ) override;
	void Visit( CALL* node ) override;
	void Visit( CONST* node ) override;
	void Visit( ESEQ* node ) override;
	void Visit( MEM* node ) override;
	void Visit( NAME* node ) override;
	void Visit( TEMP* node ) override;
	void Visit( CExpList* node ) override;

	void Visit( CJUMP* node ) override;
	void Visit( EXP* node ) override;
	void Visit( JUMP* node ) override;
	void Visit( LABEL* node ) override;
	void Visit( MOVE* node ) override;
	void Visit( SEQ* node ) override;
	void Visit( CStmList* node ) override;

	void OpenFile();
	void CloseFile();
	void WriteGraphToFile();
	void ResetPrinter( const std::string& _prefix, const std::string& fragmentName );

private:
	std::ofstream graphvizOut;
	std::string prefix;
	size_t curNodeId;
	size_t prevNodeId;
	size_t visitedNodesCount;
	std::stack<size_t> nodeStack;
	std::map<size_t, std::string> nodeLabels;
	std::vector<std::pair<size_t, size_t> > treeEdges;

	void visitNewNode();
	void leaveNode();
	size_t createNewNode();
	void addEdge( size_t from, size_t to );
};