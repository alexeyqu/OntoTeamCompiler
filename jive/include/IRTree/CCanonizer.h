#pragma once

#include "IRTree/TreeNodes/Nodes.h"
#include "IRTree/CFrame.h"
#include "IRTree/TreeNodes/IStm.h"
#include "IRTree/CBasicBlock.h"

class CCanonizer {
	
public:
	CCanonizer( IStm* _stm, CFrame* frame ): stm( _stm ), methodFrame( frame ) {
		done = new LABEL( new CLabel() );
	}

	void Canonize();
	bool IsNop( IStm* stm );
	bool Commute( IStm* stm, IExp* exp );
	IStm* Seq( IStm* stm, IStm* exp );

	IStm* DoStm( SEQ* stm );
	IStm* DoStm( MOVE* stm );
	IStm* DoStm( EXP* stm );
	IStm* DoStm( IStm* stm );

	ESEQ* DoExp( ESEQ* exp );
	ESEQ* DoExp( IExp* exp );

	CStmExpList* Reorder( CExpList* exps );
	IStm* ReorderStm( IStm* stm );
	ESEQ* ReorderExp( IExp* stm );

	CStmList* Linear( SEQ* seq, CStmList* stms );
	CStmList* Linear( IStm* stm, CStmList* stms );
	CStmList* Linearize( IStm* stm );
	CStmList* GetCanonizedStms() const {
		return canonizedStmList;
	}

private:
	IStm* stm;
	CFrame* methodFrame;
	LABEL* done;

	CStmList* linearizedStms;

	CBasicBlock curBlock;
	std::vector<CBasicBlock> basicBlocks;
	CStmList* canonizedStmList;

	static CStmExpList* nopNull;

	void linearizeStm();
	void split();
	void makeBlocks( CStmList* list );
	void doStms( CStmList* list );
	void connect();
	void generateTraces();
	void optimizeCjumpBlocks();
	void translateToStms();

	static bool isLABEL( IStm* stm ) {
		return ( dynamic_cast<LABEL*>( stm ) != nullptr );
	}
	static bool isJUMP( IStm* stm ) {
		return ( dynamic_cast<JUMP*>( stm ) != nullptr );
	};
	static bool isCJUMP( IStm* stm ) {
		return ( dynamic_cast<CJUMP*>( stm ) != nullptr );
	};
};

