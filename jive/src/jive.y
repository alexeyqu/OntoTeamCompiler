%code requires {
	#include <cstring>
	#include <iostream>
	#include "CProgram.h"
	#include "CSymbolTable.h"

	#define YYERROR_VERBOSE 1 
}

%code {    
	int yylex (void);

	void yyerror(CProgram **program, const char *str) {
	    std::cerr << "Error: " << str << "\n";
	}

	CSymbolTable symbolTable;
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
	CLocalVariable* VarDeclaration;
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
%token DEBUG

%left AND OR
%left LESS GREATER
%left ADD SUB
%left MUL DIV

%type <Program> Program
%type <Tmp> Tmp
%type <Type> Type
%type <VarDeclaration> VarDeclaration
%type <Identifier> Identifier
%type <Statement> Statement
%type <Expression> Expression

%start Program

%%

Program: Tmp { *program = $$ = new CProgram( $1 ); }
;

Tmp:	Tmp Tmp { $$ = new CCompoundTmp( $1, $2 ); }
		|
		VarDeclaration { $$ = $1; }
		|
		Statement { $$ = $1; }
;

VarDeclaration:	Type Identifier SEMI { symbolTable.Insert( $$ = new CLocalVariable( $1, $2 ) ); }
;

Statement:  Statement Statement { $$ = new CCompoundStatement( $1, $2 ); }
			|
			IF LPAREN Expression RPAREN 
				Statement 
			ELSE 
				Statement { 
				if($3->getType() == enums::BOOLEAN) 
					$$ = new CIfStatement( $3, $5, $7 );  
				else
					yyerror(program, "ERROR");
			}
			|
			WHILE LPAREN Expression RPAREN 
			LBRACE 
				Statement 
			RBRACE { 
				if($3->getType() == enums::BOOLEAN) 
					$$ = new CWhileStatement( $3, $6 ); 
				else
					yyerror(program, "ERROR");
			}
			|
			PRINT LPAREN Identifier RPAREN SEMI { 
				if(symbolTable.Lookup( $3 ) &&
					symbolTable.Lookup( $3 )->getType() == enums::INTEGER) 
					$$ = new CPrintStatement( $3 ); 
				else
					yyerror(program, "ERROR");
			}
			|
			Identifier ASSIGN Expression SEMI { 
				if(symbolTable.Lookup( $1 ) &&
					symbolTable.Lookup( $1 )->getType() == $3->getType()) 
					$$ = new CAssignStatement( $1, $3 ); 
				else
					yyerror(program, "ERROR");
			}
			|
			DEBUG { symbolTable.Dump(); }
;

Type:	INT { $$ = new CType( enums::INTEGER ); }
		|
		BOOL { $$ = new CType( enums::BOOLEAN ); }
;

Expression: Expression AND Expression { 
				if( $1->getType() == enums::BOOLEAN && $3->getType() == enums::BOOLEAN ) 
					$$ = new CBinaryBooleanExpression( $1, enums::AND, $3 ); 
				else
					yyerror(program, "ERROR");
			}
			|
			Expression OR Expression { 
				if( $1->getType() == enums::BOOLEAN && $3->getType() == enums::BOOLEAN ) 
					$$ = new CBinaryBooleanExpression( $1, enums::OR, $3 );  
				else
					yyerror(program, "ERROR");
			}
			|
			Expression ADD Expression { 
				if( $1->getType() == enums::INTEGER && $3->getType() == enums::INTEGER ) 
					$$ = new CBinaryExpression( $1, enums::ADD, $3 ); 
				else
					yyerror(program, "ERROR");
			}
			|
			Expression SUB Expression { 
				if( $1->getType() == enums::INTEGER && $3->getType() == enums::INTEGER ) 
					$$ = new CBinaryExpression( $1, enums::SUB, $3 );
				else
					yyerror(program, "ERROR");
			}
			|
			Expression MUL Expression { 
				if( $1->getType() == enums::INTEGER && $3->getType() == enums::INTEGER ) 
					$$ = new CBinaryExpression( $1, enums::MUL, $3 ); 
				else
					yyerror(program, "ERROR");
			}
			|
			Expression DIV Expression { 
				if( $1->getType() == enums::INTEGER && $3->getType() == enums::INTEGER ) 
					$$ = new CBinaryExpression( $1, enums::DIV, $3 ); 
				else
					yyerror(program, "ERROR");
			}
			|
			Expression MOD Expression { 
				if( $1->getType() == enums::INTEGER && $3->getType() == enums::INTEGER ) 
					$$ = new CBinaryExpression( $1, enums::MOD, $3 ); 
				else
					yyerror(program, "ERROR");
			}
			|
			NUM { $$ = new CNumberExpression( $1 ); }
			|
			TRUE { $$ = new CBooleanExpression( true ); }
			|
			FALSE { $$ = new CBooleanExpression( false ); }
			|
			Identifier { if(symbolTable.Lookup( $1 )) $$ = $1; }
			|
			NOT Expression { 
				if( $2->getType() == enums::BOOLEAN ) 
					$$ = new CBooleanExpression( !$2 );
				else
					yyerror(program, "ERROR"); 
			}
			|
			LPAREN Expression RPAREN { $$ = $2; }
			|
			SUB Expression { // FIXIT
			if( $2->getType() == enums::INTEGER ) 
				$$ = new CBinaryExpression ($2, enums::MUL, new CNumberExpression ( "-1" ) );
			else
				yyerror(program, "ERROR");
			} 
;

Identifier: ID { $$ = new CIdExpression( $1 ); }
;

%%

/*
	Goal ::= MainClass ( ClassDeclaration )* <EOF>
	MainClass ::= "class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" Statement "}" "}"
	ClassDeclaration ::= "class" Identifier ( "extends" Identifier )? "{" ( VarDeclaration )* ( MethodDeclaration )* "}"
q	VarDeclaration ::= Type Identifier ";"
	MethodDeclaration ::= "public" | “private” Type Identifier "(" ( Type Identifier ( "," Type Identifier )* )? ")" "{" ( VarDeclaration )*( Statement )* "return" Expression ";" "}"
	Type ::= "int" "[" "]"
q	| "boolean"
q	| "int"
	| Identifier
	Statement ::= "{" ( Statement )* "}"
q	| "if" "(" Expression ")" Statement "else" Statement
q	| "while" "(" Expression ")" Statement
q	| "System.out.println" "(" Expression ")" ";"
q	| Identifier "=" Expression ";"
	| Identifier "[" Expression "]" "=" Expression ";"
q?	Expression ::= Expression ( "&&" | "<" | "+" | "-" | "*" | "%" | "||" ) Expression
	| Expression "[" Expression "]"
	| Expression "." "length"
	| Expression "." Identifier "(" ( Expression ( "," Expression )* )? ")"
q	| <INTEGER_LITERAL>
q	| "true"
q	| "false"
q	| Identifier
	| "this"
	| "new" "int" "[" Expression "]"
	| "new" Identifier "(" ")"
q	| "!" Expression 
q	| "(" Expression ")"
q	Identifier ::= <IDENTIFIER>
*/