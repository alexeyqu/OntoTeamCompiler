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
	CVariable* Variable;
	CArgument* Argument;
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

	IType* Type;
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
%type <Argument> Argument
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
			RBRACE { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CMainClass( $2, $12, $15 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
;

Classes: 	Classes Class { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CCompoundClass( $1, $2 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			%empty { $$ = nullptr;
			 }
;

Class: 	CLASS Identifier EXTENDS Identifier LBRACE 
			Variables 
			Methods 
		RBRACE { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CClass( $2, $4, $6, $7 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }				 
			|
		CLASS Identifier LBRACE 
			Variables 
			Methods 
		RBRACE { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CClass( $2, nullptr, $4, $5 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
;

Variables:  Variables Variable { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CCompoundVariable( $1, $2 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			%empty { $$ = nullptr; }
;

Variable:	Type Identifier SEMI { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CVariable( $1, $2 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
;

Methods: 	Methods Method { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CCompoundMethod( $1, $2 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			%empty { $$ = nullptr; }
;

Method: 	PUBLIC Type Identifier LPAREN Arguments RPAREN LBRACE 
				Variables 
				Statements 
				RETURN Expression SEMI
			RBRACE {
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CMethod( $2, $3, $5, $8, $9, $11 ); 
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
;

Arguments:  RestArguments Argument { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CCompoundArgument( $1, $2 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			%empty { $$ = nullptr; }
;

Argument:	Type Identifier { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CArgument( $1, $2 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
;

RestArguments: RestArguments Type Identifier COMMA {
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CCompoundArgument( $1, new CArgument( $2, $3 ) );
			$$->coordinates.first_line = yylloc.first_line;
			$$->coordinates.first_column = yylloc.first_column; }
			|
			%empty { $$ = nullptr; }
;

Statements: Statement Statements { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CCompoundStatement( $2, $1 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			LBRACE Statements RBRACE { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CCompoundStatement( $2, nullptr );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			%empty { $$ = nullptr; }
;

Statement:  LBRACE Statements RBRACE { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CCompoundStatement( $2, nullptr );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			IF LPAREN Expression RPAREN 
				Statements 
			ELSE 	
				Statements { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CIfStatement( $3, $5, $7 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			WHILE LPAREN Expression RPAREN LBRACE 
				Statements
			RBRACE { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CWhileStatement( $3, $6 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			PRINT LPAREN Expression RPAREN SEMI { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CPrintStatement( $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Identifier ASSIGN Expression SEMI { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CAssignStatement( $1, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Identifier LBRACKET Expression RBRACKET ASSIGN Expression  SEMI {
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CAssignStatement( $1, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
;

Type:	INT { 
		int temp_line = yyloc.first_line;
		int temp_column = yyloc.first_column;
		$$ = new CBuiltInType( enums::INTEGER );
		$$->coordinates.first_line = temp_line;
		$$->coordinates.first_column = temp_column; }
		|
		INT LBRACKET RBRACKET { 
		int temp_line = yyloc.first_line;
		int temp_column = yyloc.first_column;
		$$ = new CBuiltInType( enums::INTEGERARRAY );
		$$->coordinates.first_line = temp_line;
		$$->coordinates.first_column = temp_column; }
		|
		BOOL { 
		int temp_line = yyloc.first_line;
		int temp_column = yyloc.first_column;
		$$ = new CBuiltInType( enums::BOOLEAN );
		$$->coordinates.first_line = temp_line;
		$$->coordinates.first_column = temp_column; }
		|
		STRING { 
		int temp_line = yyloc.first_line;
		int temp_column = yyloc.first_column;
		$$ = new CBuiltInType( enums::STRING );
		$$->coordinates.first_line = temp_line;
		$$->coordinates.first_column = temp_column; }
		|
		Identifier { 
		int temp_line = yyloc.first_line;
		int temp_column = yyloc.first_column;
		$$ = new CUserType( $1->name );
		$$->coordinates.first_line = temp_line;
		$$->coordinates.first_column = yylloc.first_column; }
;

Expression: Expression AND Expression { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBinaryBooleanExpression( $1, enums::AND, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Expression OR Expression { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBinaryBooleanExpression( $1, enums::OR, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column;  }
			|
			Expression LESS Expression { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBinaryBooleanExpression( $1, enums::LESS, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Expression GREATER Expression { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBinaryBooleanExpression( $1, enums::GREATER, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Expression ADD Expression { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBinaryExpression( $1, enums::ADD, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Expression SUB Expression { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBinaryExpression( $1, enums::SUB, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Expression MUL Expression { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBinaryExpression( $1, enums::MUL, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Expression DIV Expression { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBinaryExpression( $1, enums::DIV, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Expression MOD Expression { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBinaryExpression( $1, enums::MOD, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Expression LBRACKET Expression RBRACKET { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CArrayIndexExpression( $1, $3 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Expression DOT LENGTH {
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CArrayLengthExpression( $1 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Expression DOT Identifier LPAREN Expressions RPAREN { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CMethodCallExpression( $1, $3, $5 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			NUM { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CNumberExpression( $1 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			TRUE { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBooleanExpression( true );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			FALSE { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBooleanExpression( false );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			THIS { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CThisExpression();
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			Identifier { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = $1;
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|	
			NEW INT LBRACKET Expression RBRACKET { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CNewIntArrayExpression( $4 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			NEW Identifier LPAREN RPAREN { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CNewObjectExpression( $2 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			NOT Expression { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBooleanExpression( !$2 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			LPAREN Expression RPAREN { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = $2;
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
			|
			SUB Expression { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CBinaryExpression ($2, enums::MUL, new CNumberExpression ( "-1" ) );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; } // FIXIT
;

Expressions:	RestExpressions Expression { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				$$ = new CCompoundExpression( $1, $2 );
				$$->coordinates.first_line = temp_line;
				$$->coordinates.first_column = temp_column; }
				|
				%empty { $$ = nullptr; }
;

RestExpressions: RestExpressions Expression COMMA { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				$$ = new CCompoundExpression( $1, $2 );
				$$->coordinates.first_line = temp_line;
				$$->coordinates.first_column = temp_column; }
				|
				%empty { $$ = nullptr; }
;

Identifier: ID { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			$$ = new CIdExpression( $1 );
			$$->coordinates.first_line = temp_line;
			$$->coordinates.first_column = temp_column; }
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