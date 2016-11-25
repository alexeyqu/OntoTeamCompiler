%code requires {
	#include <cstdio>
	#include <cstring>
	#include "CJiveEnvironment.h"

	#define YYERROR_VERBOSE 1 
}

%code {    
	int yylex (void);

	void yyerror(CJiveEnvironment **jiveEnv, const char *str) {
	    fprintf(stderr, "Error: {%d, %d} %s\n", yylloc.first_line, yylloc.first_column, str);
	    exit(1);
	}
}

%error-verbose
%verbose
%parse-param { CJiveEnvironment **jiveEnv }
%locations

%union {
	char *string;
	CJiveEnvironment *JiveEnv;
	IVisitorTarget *Goal;
	IType* Type;
	CVariable* Variable;
	CCompoundVariable* Variables;
	CMethod* Method;
	CCompoundMethod* Methods;
	CClass* Class;
	CCompoundClass* Classes;
	CMainClass* MainClass;
	CCompoundArgument* Arguments;
	CCompoundStatement* Statements;
	CCompoundExpression* Expressions;
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
%token RETURN NIL NEW
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token ASSIGN EQU ADD SUB MUL DIV MOD LESS GREATER
%token TRUE FALSE AND OR NOT
%token COMMA DOT SEMI AMPERSAND
%token PRINT LENGTH
%token ERROR

%left AND OR
%left LESS GREATER
%left ADD SUB
%left MUL DIV

%type <JiveEnv> JiveEnv
%type <Goal> Goal
%type <Type> Type
%type <Variable> Variable
%type <Variables> Variables
%type <Method> Method
%type <Methods> Methods
%type <Class> Class
%type <Classes> Classes
%type <MainClass> MainClass
%type <Arguments> Arguments
%type <Arguments> RestArguments
%type <Identifier> Identifier
%type <Statement> Statement
%type <Statements> Statements
%type <Expression> Expression
%type <Expressions> Expressions
%type <Expressions> RestExpressions

%start JiveEnv

%%

JiveEnv: Goal { 
	(*jiveEnv)->LoadProgram( new CProgram( $1 ) ); 
	$$ = *jiveEnv; }
;

Goal: 	MainClass Classes { $$ = new CGoal( $1, $2 ); }
;

MainClass:	CLASS Identifier LBRACE 
				PUBLIC STATIC VOID MAIN LPAREN STRING LBRACKET RBRACKET Identifier RPAREN LBRACE 
				Statement 
				RBRACE 
			RBRACE { $$ = new CMainClass( $2, $12, $15 ); }
;

Classes: 	Classes Class { $$ = new CCompoundClass( $1, $2 ); }
			|
			%empty { $$ = nullptr; }
;

Class: 	CLASS Identifier EXTENDS Identifier LBRACE 
			Variables 
			Methods 
		RBRACE { $$ = new CClass( $2, $4, $6, $7 ); }				 
		|
		CLASS Identifier LBRACE 
			Variables 
			Methods 
		RBRACE { $$ = new CClass( $2, nullptr, $4, $5 ); }
;

Variables:  Variables Variable { $$ = new CCompoundVariable( $1, $2 ); }
			|
			%empty { $$ = nullptr; }
;

Variable:	Type Identifier SEMI { $$ = new CVariable( $1, $2 ); }
;

Methods: 	Methods Method { $$ = new CCompoundMethod( $1, $2 ); }
			|
			%empty { $$ = nullptr; }
;

Method: 	PUBLIC Type Identifier LPAREN Arguments RPAREN LBRACE 
				Variables 
				Statements 
				RETURN Expression SEMI
			RBRACE { $$ = new CMethod( $2, $3, $5, $8, $9, $11 ); }
;

Arguments:  RestArguments Type Identifier { $$ = new CCompoundArgument( $1, new CArgument( $2, $3 ) ); }
			|
			%empty { $$ = nullptr; }
;

RestArguments: RestArguments Type Identifier COMMA { $$ = new CCompoundArgument( $1, new CArgument( $2, $3 ) ); }
			|
			%empty { $$ = nullptr; }
;

Statements: Statement Statements { $$ = new CCompoundStatement( $2, $1 ); }
			|
			LBRACE Statements RBRACE { $$ = new CCompoundStatement( $2, nullptr ); }
			|
			%empty { $$ = nullptr; }
;

Statement:  LBRACE Statements RBRACE { $$ = new CCompoundStatement( $2, nullptr ); }
			|
			IF LPAREN Expression RPAREN 
				Statements 
			ELSE 	
				Statements { $$ = new CIfStatement( $3, $5, $7 ); }
			|
			WHILE LPAREN Expression RPAREN LBRACE 
				Statements
			RBRACE { $$ = new CWhileStatement( $3, $6 ); }
			|
			PRINT LPAREN Expression RPAREN SEMI { $$ = new CPrintStatement( $3 ); }
			|
			Identifier ASSIGN Expression SEMI { $$ = new CAssignStatement( $1, $3 ); }
			|
			Identifier LBRACKET Expression RBRACKET ASSIGN Expression  SEMI { $$ = new CAssignStatement( $1, $3 ); }
;

Type:	INT { $$ = new CBuiltInType( enums::INTEGER ); }
		|
		INT LBRACKET RBRACKET { $$ = new CBuiltInType( enums::INTEGERARRAY ); }
		|
		BOOL { $$ = new CBuiltInType( enums::BOOLEAN ); }
		|
		STRING { $$ = new CBuiltInType( enums::STRING ); }
		|
		Identifier { $$ = new CBuiltInType( enums::CLASS ); }
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
			Expression LBRACKET Expression RBRACKET { $$ = new CArrayIndexExpression( $1, $3 ); }
			|
			Expression DOT LENGTH { $$ = new CArrayLengthExpression( $1 ); }
			|
			Expression DOT Identifier LPAREN Expressions RPAREN { $$ = new CMethodCallExpression( $1, $3, $5 ); }
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
			NEW INT LBRACKET Expression RBRACKET { $$ = new CNewIntArrayExpression( $4 ); }
			|
			NEW Identifier LPAREN RPAREN { $$ = new CNewObjectExpression( $2 ); }
			|
			NOT Expression { $$ = new CBooleanExpression( !$2 ); }
			|
			LPAREN Expression RPAREN { $$ = $2; }
			|
			SUB Expression { $$ = new CBinaryExpression ($2, enums::MUL, new CNumberExpression ( "-1" ) ); } // FIXIT
;

Expressions:	RestExpressions Expression { $$ = new CCompoundExpression( $1, $2 ); }
			|
			%empty { $$ = nullptr; }
;

RestExpressions: RestExpressions Expression COMMA { $$ = new CCompoundExpression( $1, $2 ); }
			|
			%empty { $$ = nullptr; }
;

Identifier: ID { $$ = new CIdExpression( $1 ); }
;

%%

/*
q	Goal ::= MainClass ( ClassDeclaration )* <EOF>
q	MainClass ::= "class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" Statement "}" "}"
n	ClassDeclaration ::= "class" Identifier ( "extends" Identifier )? "{" ( VarDeclaration )* ( MethodDeclaration )* "}"
q	VarDeclaration ::= Type Identifier ";"
n	MethodDeclaration ::= "public" | “private” Type Identifier "(" ( Type Identifier ( "," Type Identifier )* )? ")" "{" ( VarDeclaration )*( Statement )* "return" Expression ";" "}"
n	Type ::= "int" "[" "]"
q	| "boolean"
q	| "int"
q	| Identifier
q	Statement ::= "{" ( Statement )* "}"
q	| "if" "(" Expression ")" Statement "else" Statement
q	| "while" "(" Expression ")" Statement
q	| "System.out.println" "(" Expression ")" ";"
q	| Identifier "=" Expression ";"
q	| Identifier "[" Expression "]" "=" Expression ";"
q	Expression ::= Expression ( "&&" | "<" | "+" | "-" | "*" | "%" | "||" ) Expression
q	| Expression "[" Expression "]"
q	| Expression "." "length"
q	| Expression "." Identifier "(" ( Expression ( "," Expression )* )? ")"
q	| <INTEGER_LITERAL>
q	| "true"
q	| "false"
q	| Identifier
q	| "this"
q	| "new" "int" "[" Expression "]"
q	| "new" Identifier "(" ")"
q	| "!" Expression 
q	| "(" Expression ")"
q	Identifier ::= <IDENTIFIER>
*/