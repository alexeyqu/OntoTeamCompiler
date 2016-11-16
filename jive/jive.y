%code requires {
	#include <cstdio>
	#include <cstring>
	#include "AST/CProgram.h"

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

%left AND OR
%left LESS GREATER
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
			IF LPAREN Expression RPAREN Statement ELSE Statement { $$ = new CIfStatement( $3, $5, $7 ); }
			|
			WHILE LPAREN Expression RPAREN LBRACE Statement RBRACE { $$ = new CWhileStatement( $3, $6 ); }
			|
			PRINT LPAREN Identifier RPAREN SEMI { $$ = new CPrintStatement( $3 ); }
			|
			Identifier EQU Expression SEMI { $$ = new CAssignStatement( $1, $3 ); }
;

Expression: Expression AND Expression { $$ = new CBinaryBooleanExpression( $1, enums::AND, $3 ); }
			|
			Expression OR Expression { $$ = new CBinaryBooleanExpression( $1, enums::OR, $3 );  }
			|
			Expression LESS Expression { $$ = new CBinaryBooleanExpression( $1, enums::LESS, $3 ); }
			|
			Expression GREATER Expression { $$ = new CBinaryBooleanExpression( $1, enums::GREATER, $3 ); }
			|
			Expression ADD Expression { $$ = new CBinaryExpression( $1, enums::ADD, $3 ); }
			|
			Expression SUB Expression { $$ = new CBinaryExpression( $1, enums::SUB, $3 ); }
			|
			Expression MUL Expression { $$ = new CBinaryExpression( $1, enums::MUL, $3 ); }
			|
			Expression DIV Expression { $$ = new CBinaryExpression( $1, enums::DIV, $3 ); }
			|
			Expression MOD Expression { $$ = new CBinaryExpression( $1, enums::MOD, $3 ); }
			|
			NUM { $$ = new CNumberExpression( $1 ); }
			|
			TRUE { $$ = new CBooleanExpression( true ); }
			|
			FALSE { $$ = new CBooleanExpression( false ); }
			|
			THIS { $$ = new CThisExpression(); }
			|
			Identifier { $$ = $1; }
			|
			NOT Expression { $$ = new CBooleanExpression( !$2 ); }
			|
			LPAREN Expression RPAREN { $$ = $2; }
;

Identifier: ID { $$ = new CIdExpression( $1 ); }
;

%%

/*
	Goal ::= MainClass ( ClassDeclaration )* <EOF>
	MainClass ::= "class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" Statement "}" "}"
	ClassDeclaration ::= "class" Identifier ( "extends" Identifier )? "{" ( VarDeclaration )* ( MethodDeclaration )* "}"
	VarDeclaration ::= Type Identifier ";"
	MethodDeclaration ::= "public" | “private” Type Identifier "(" ( Type Identifier ( "," Type Identifier )* )? ")" "{" ( VarDeclaration )*( Statement )* "return" Expression ";" "}"
	Type ::= "int" "[" "]"
	| "boolean"
	| "int"
	| Identifier
	Statement ::= "{" ( Statement )* "}"
q	| "if" "(" Expression ")" Statement "else" Statement
q	| "while" "(" Expression ")" Statement
q	| "System.out.println" "(" Expression ")" ";"
q	| Identifier "=" Expression ";"
	| Identifier "[" Expression "]" "=" Expression ";"
q	Expression ::= Expression ( "&&" | "<" | "+" | "-" | "*" | "%" | "||" ) Expression
	| Expression "[" Expression "]"
	| Expression "." "length"
	| Expression "." Identifier "(" ( Expression ( "," Expression )* )? ")"
q	| <INTEGER_LITERAL>
q	| "true"
q	| "false"
q	| Identifier
q	| "this"
	| "new" "int" "[" Expression "]"
	| "new" Identifier "(" ")"
q	| "!" Expression 
q	| "(" Expression ")"
q	Identifier ::= <IDENTIFIER>
*/