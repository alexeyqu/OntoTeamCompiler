%code requires {
	#include <stdio.h>
	#include <string.h>
	#include "AST/TreeNodes/CBinaryExpression.h"
	#include "AST/TreeNodes/CNumberExpression.h"
	#include "AST/TreeNodes/IExpression.h"
	#include "AST/CProgram.h"

	#define YYERROR_VERBOSE 1 
}

%code {    
	int yylex (void);

	void yyerror(CProgram** program, const char *str) {
	    fprintf(stderr, "Error: %s\n", str);
	}
}

%error-verbose
%verbose
%parse-param { CProgram** program }
%locations

%union {

	char *string;
	CProgram *Program;
	IExpression *Expression;

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
%token ERROR

%type <Program> Program
%type <Expression> Expression

%start Program

%%

Program: Expression { *program = $$ = new CProgram( $1 ); }
;

Expression:	NUM { $$ = new CNumberExpression( $1 ); }
		|
		Expression ADD Expression { $$ = new CBinaryExpression( $1, CBinaryExpression::OT_Plus, $3 ); }
		|
		Expression SUB Expression { $$ = new CBinaryExpression( $1, CBinaryExpression::OT_Minus, $3 ); }
;

%%