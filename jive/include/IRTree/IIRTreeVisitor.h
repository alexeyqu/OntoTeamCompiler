#pragma once

#include "../jive.h"

class CExpList;
class CStmList;
class BINOP;
class CALL;
class CONST;
class ESEQ;
class MEM;
class NAME;
class TEMP;
class CJUMP;
class EXP;
class JUMP;
class LABEL;
class MOVE;
class SEQ;

class IIRTreeVisitor
{
public:
   	virtual void Visit( BINOP *exp ) = 0;
    virtual void Visit( CALL *exp ) = 0;
   	virtual void Visit( CONST *exp ) = 0;
    virtual void Visit( ESEQ *exp ) = 0;
    virtual void Visit( MEM *exp ) = 0;
    virtual void Visit( NAME *exp ) = 0;
    virtual void Visit( TEMP *exp ) = 0;
	virtual void Visit( CExpList * exp ) = 0;

    virtual void Visit( CJUMP *stm ) = 0;
    virtual void Visit( EXP *stm ) = 0;
    virtual void Visit( JUMP *stm ) = 0;
    virtual void Visit( LABEL *stm ) = 0;
	virtual void Visit( MOVE *stm ) = 0;
	virtual void Visit( SEQ *stm ) = 0;
   	virtual void Visit( CStmList *stm ) = 0;
};