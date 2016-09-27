%{
#include <stdio.h>
#include <string.h>

#define YYSTYPE char*

int yylex(void);

int yywrap()
{
        return 1;
}

void yyerror(const char *str)
{
        fprintf(stderr,"Error: %s\n",str);
}

%}

%token NUM;
%token CHAR;
%token INT;
%token IF;
%token ELSE;
%token RETURN;
%token SEMI;
%token COMMA;
%token STAR;
%token NOT;
%token LPAREN;
%token RPAREN;
%token LBRACE;
%token RBRACE;
%token ID;

%token STRING;

%token COMMENT;
%token EOL;
%token TAB;
%token WHITESPACE;

%%

commands:
    | commands command
    ;

command:
	any_command
	;

any_command:
	  NUM { printf("NUM(%s) ", $1); }
	| INT { printf("INT "); }
	| CHAR { printf("CHAR "); }
	| IF { printf("IF "); }
	| ELSE { printf("ELSE "); }
	| RETURN { printf("RETURN "); }
	| SEMI { printf("SEMI "); }
	| COMMA { printf("COMMA "); }
	| STAR { printf("STAR "); }
	| NOT { printf("NOT "); }
	| LPAREN { printf("LPAREN "); }
	| RPAREN { printf("RPAREN "); }
	| LBRACE { printf("LBRACE "); }
	| RBRACE { printf("RBRACE "); }
	| ID { printf("ID(%s) ", $1); }
	| STRING { printf("STRING(%s) ", $1); }
	| COMMENT { printf("COMMENT(%s) ", $1); }
	| EOL { printf("\n"); }
	| TAB { printf("\t"); }
	| WHITESPACE { printf(""); }
;

%%

int main()
{
        yyparse();
}
