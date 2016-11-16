%code requires {
	#include <stdio.h>
	#include <string.h>
	#include "AST/CProgram.h"
	#include "AST/TreeNodes/CCompoundStatement.h"
	#include "AST/TreeNodes/CAssignStatement.h"
	#include "AST/TreeNodes/CPrintStatement.h"
	#include "AST/TreeNodes/CIdExpression.h"
	#include "AST/TreeNodes/CBinaryExpression.h"
	#include "AST/TreeNodes/CNumberExpression.h"
	#include "AST/TreeNodes/IExpression.h"

	#define YYERROR_VERBOSE 1 
}

%code {    
	int yylex (void);

	void yyerror(CProgram **program, const char *str) {
	    fprintf(stderr, "Error: %s\n", str);
	}
}

%error-verbose
%verbose
%parse-param { CProgram **program }
%locations

%union {
	char *string;
	CProgram *Program;
	IStatement *Statement;
	IExpression *Expression;
	IExpression *Identifier;
}

%token <string> NUM
%token <string> ID STRING

%token VOID INT BOOL
%token CLASS PUBLIC STATIC EXTENDS THIS
%token MAIN
%token IF ELSE
%token WHILE FOR
%token RETURN NIL
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token EQU EQUEQU ADD SUB MUL DIV MOD LESS GREATER
%token TRUE FALSE AND OR NOT
%token COMMA DOT SEMI AMPERSAND
%token PRINT
%token ERROR

%left ADD SUB
%left MUL DIV

%type <Program> Program
%type <Statement> Statement
%type <Expression> Expression
%type <Expression> Identifier

%start Program

%%

Program: Statement { *program = $$ = new CProgram( $1 ); }
;

Statement:  Statement Statement { $$ = new CCompoundStatement( $1, $2 ); }
			|
			Identifier EQU Expression SEMI { $$ = new CAssignStatement( $1, $3 ); }
			|
			PRINT LPAREN Identifier RPAREN SEMI { $$ = new CPrintStatement( $3 ); }
;

Expression:	NUM { $$ = new CNumberExpression( $1 ); }
			|
			Identifier { $$ = $1; }
			|
			Expression ADD Expression { $$ = new CBinaryExpression( $1, enums::ADD, $3 ); }
			|
			Expression SUB Expression { $$ = new CBinaryExpression( $1, enums::SUB, $3 ); }
			|
			Expression MUL Expression { $$ = new CBinaryExpression( $1, enums::MUL, $3 ); }
			|
			Expression DIV Expression { $$ = new CBinaryExpression( $1, enums::DIV, $3 ); }
			|
			LPAREN Expression RPAREN { $$ = $2; }
;

Identifier: ID { $$ = new CIdExpression( $1 ); }
;

%%