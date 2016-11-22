%code requires {
	#include <cstdio>
	#include <cstring>
	#include "CProgram.h"

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
	IVisitorTarget *Tmp;
	CType* Type;
	CArray* Array;
	CVariable* Variable;
	CCompoundVariable* Variables;
	CMethod* Method;
	CCompoundMethod* Methods;
	CClass* Class;
	CCompoundArgument* Arguments;
	CCompoundStatement* Statements;
	CIdExpression *Identifier;

	IEntity *Entity;
	IStatement *Statement;
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
%token ASSIGN EQU ADD SUB MUL DIV MOD LESS GREATER
%token TRUE FALSE AND OR NOT
%token COMMA DOT SEMI AMPERSAND
%token PRINT
%token ERROR

%left AND OR
%left LESS GREATER
%left ADD SUB
%left MUL DIV

%type <Program> Program
%type <Tmp> Tmp
%type <Type> Type
%type <Array> Array
%type <Variable> Variable
%type <Variables> Variables
%type <Method> Method
%type <Methods> Methods
%type <Class> Class
%type <Arguments> Arguments
%type <Arguments> RestArguments
%type <Identifier> Identifier
%type <Statement> Statement
%type <Statements> Statements
%type <Expression> Expression

%start Program

%%

Program: 	Tmp { *program = $$ = new CProgram( $1 ); }
;

Tmp:	Tmp Tmp { $$ = new CCompoundTmp( $1, $2 ); }
		|
		Variable { $$ = $1; }
		|
		Method { $$ = $1; } 
		|
		Class { $$ = $1; } 
		|
		Statement { $$ = $1; }
;

Class: 	CLASS Identifier EXTENDS Identifier LBRACE Variables Methods RBRACE { $$ = new CClass( $2, $4, $6, $7 ); }
		|
		CLASS Identifier LBRACE Variables Methods RBRACE { $$ = new CClass( $2, nullptr, $4, $5 ); }
;

Method: PUBLIC Type Identifier LPAREN Arguments RPAREN LBRACE Variables Statements RETURN Expression SEMI RBRACE {	$$ = new CMethod( $2, $3, $5, $8, $9, $11 ); }
;

Methods: 	Methods Method { $$ = new CCompoundMethod( $1, $2 ); }
			|
			{ $$ = nullptr; }
;

Variable:	Type Identifier SEMI { $$ = new CVariable( $1, $2 ); }
			|
			Array Identifier SEMI { $$ = new CVariable( $1, $2 ); }
;

Array:      Type LBRACKET RBRACKET { $$ = new CArray( $1, 0 ); }

Variables:  Variables Variable { $$ = new CCompoundVariable( $1, $2 ); }
			|
			{ $$ = nullptr; }
;

Arguments:  RestArguments Type Identifier { $$ = new CCompoundArgument( $1, new CArgument( $2, $3 ) ); }
			|
			{ $$ = nullptr; }
;

RestArguments: RestArguments Type Identifier COMMA { $$ = new CCompoundArgument( $1, new CArgument( $2, $3 ) ); }
			|
			{ $$ = nullptr; }
;

Statements: Statements Statement { $$ = new CCompoundStatement( $1, $2 ); }
			|
			{ $$ = nullptr; }
;

Statement:  IF LPAREN Expression RPAREN Statement ELSE Statement { $$ = new CIfStatement( $3, $5, $7 ); }
			|
			WHILE LPAREN Expression RPAREN LBRACE Statement RBRACE { $$ = new CWhileStatement( $3, $6 ); }
			|
			PRINT LPAREN Identifier RPAREN SEMI { $$ = new CPrintStatement( $3 ); }
			|
			Identifier ASSIGN Expression SEMI { $$ = new CAssignStatement( $1, $3 ); }
;

Type:	INT { $$ = new CType( enums::INTEGER ); }
		|
		BOOL { $$ = new CType( enums::BOOLEAN ); }
		|
		STRING { $$ = new CType( enums::STRING ); }
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
			|
			SUB Expression { $$ = new CBinaryExpression ($2, enums::MUL, new CNumberExpression ( "-1" ) ); } // FIXIT
;

Identifier: ID { $$ = new CIdExpression( $1 ); }
;

%%

/*
	Goal ::= MainClass ( ClassDeclaration )* <EOF>
	MainClass ::= "class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" Statement "}" "}"
n	ClassDeclaration ::= "class" Identifier ( "extends" Identifier )? "{" ( VarDeclaration )* ( MethodDeclaration )* "}"
q	VarDeclaration ::= Type Identifier ";"
n	MethodDeclaration ::= "public" | “private” Type Identifier "(" ( Type Identifier ( "," Type Identifier )* )? ")" "{" ( VarDeclaration )*( Statement )* "return" Expression ";" "}"
n	Type ::= "int" "[" "]"
q	| "boolean"
q	| "int"
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