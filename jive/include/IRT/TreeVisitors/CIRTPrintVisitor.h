#pragma once

namespace IRT
{

class CIRTPrintVisitor : public IIRTVisitor
{
public:
    CIRTPrintVisitor( CJiveEnvironment *_jiveEnv, std::ostream &_outputStream ) : \
		IIRTVisitor( _jiveEnv, _outputStream ) {}

    virtual void Visit( CCONST *exp ) = 0;
    virtual void Visit( CNAME *exp ) = 0;
    virtual void Visit( CTEMP *exp ) = 0;
    virtual void Visit( CBINOP *exp ) = 0;
    virtual void Visit( CMEM *exp ) = 0;
    virtual void Visit( CCALL *exp ) = 0;
    virtual void Visit( CESEQ *exp ) = 0;
    
    virtual void Visit( CMOVE *stm ) = 0;
    virtual void Visit( CEXP *stm ) = 0;
    virtual void Visit( CJUMP *stm ) = 0;
    virtual void Visit( CCJUMP *stm ) = 0;
    virtual void Visit( CSEQ *stm ) = 0;
    virtual void Visit( CLABEL *stm ) = 0;

    virtual void Visit( CExpList *exp ) = 0;
    virtual void Visit( CStmList *stm ) = 0;

};

}