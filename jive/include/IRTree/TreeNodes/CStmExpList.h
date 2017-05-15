#pragma once

#include "IStm.h"

class CStmExpList
{
public:
	CStmExpList( IStm* _stm, CExpList* _exps ) : stm( _stm ), exps( _exps ) {};

	IStm* GetStm();
	CExpList* GetExps();

private:
	IStm* stm;
	CExpList* exps;
};