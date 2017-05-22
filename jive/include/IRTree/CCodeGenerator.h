#pragma once

#include "IInstruction.h"
#include "CFrame.h"
#include "CTypeHelper.h"

class CCodeGenerator {
public:
	CCodeGenerator( CStmList* _stms, CFrame* _methodFrame ) :
		stms( _stms ), methodFrame( _methodFrame ) {}
	void Generate();
	std::list<IInstruction*> GetInstrucions() const;

private:
	CStmList* stms;
	CFrame* methodFrame;
	std::list<IInstruction*> instructions;

	CTypeHelper helper;

	void emit( IInstruction* instruction );

	std::list<IInstruction*> generateCode( IStm* rootStm );

	CTempList*  ToList( CTemp* t1 ) { return new CTempList( t1 ); }
	CTempList*  ToList( CTemp* t1, CTemp* t2 ) { return new CTempList( t1, t2 ); }
	CTempList*  ToList( CTemp* t1, CTemp* t2, CTemp* t3 ) { return new CTempList( t1, t2, t3 ); }

	CLabelList* ToList( CLabel* l1 ) { return new CLabelList( l1 ); }
	CLabelList* ToList( CLabel* l1, CLabel* l2 ) { return new CLabelList( l1, l2 ); }

	void munchStm( IStm* stm );
	void munchStm( MOVE* move );
	void munchStm( EXP* exp );
	void munchStm( JUMP* jump );
	void munchStm( CJUMP* cjump );
	void munchStm( SEQ* seq );
	void munchStm( LABEL* label );

	CTemp* munchExp( IExp* exp );
	CTemp* munchExp( CONST* constExp );
	CTemp* munchExp( NAME* name );
	CTemp* munchExp( TEMP* temp );
	CTemp* munchExp( BINOP* binop );
	CTemp* munchExp( MEM* mem );
	CTemp* munchExp( CALL* call );

	bool munchFunctionCall( MOVE* move );
	bool munchProcedureCall( EXP* exp );

	CTempList* munchArgs( CExpList* expList );

	void munchSEQ( IStm* );
	void munchMOVE( IStm* );
};
