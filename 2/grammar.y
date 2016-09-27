%{
#include <stdio.h>
#include <string.h>

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

%%

commands:
    | commands command
    ;

command:
	any_command
	;

any_command:
	  NUM { printf("NUM\n"); }
	| INT { printf("INT\n"); }
	| IF { printf("IF\n"); }
	| ELSE { printf("ELSE\n"); }
	| RETURN { printf("RETURN\n"); }
	| SEMI { printf("SEMI\n"); }
	| COMMA { printf("COMMA\n"); }
	| STAR { printf("STAR\n"); }
	| NOT { printf("NOT\n"); }
	| LPAREN { printf("LPAREN\n"); }
	| RPAREN { printf("RPAREN\n"); }
	| LBRACE { printf("LBRACE\n"); }
	| RBRACE { printf("RBRACE\n"); }
	| ID { printf("ID\n"); }
	| STRING { printf("STRING\n"); }
;

%%

int main()
{
        yyparse();
}
