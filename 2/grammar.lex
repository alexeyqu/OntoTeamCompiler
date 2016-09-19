/* flex grammar for a sample minijava code */

%{
#include <math.h>

int STRING_IDX = 1, SYMBOL_IDX = 1;
%}

DIGIT       [0-9]
ID          [a-z][a-z0-9]*

%%

-?{DIGIT}+    {
            printf( "NUM(%d){%d, %d} ", atoi( yytext ), STRING_IDX, SYMBOL_IDX );
            SYMBOL_IDX += yyleng;
            }

{DIGIT}+"."{DIGIT}* {
            printf( "NUM(%g){%d, %d} ", atof( yytext ), STRING_IDX, SYMBOL_IDX );
            SYMBOL_IDX += yyleng;
            }

int         {
                printf( "INT(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

if          {
                printf( "IF(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

else        {
                printf( "ELSE(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

return      {
                printf( "RETURN(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

{ID}+       {
                printf( "ID(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"("         {
                printf( "LPAREN(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

")"         {
                printf( "RPAREN(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"{"         {
                printf( "LBRACE(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"}"         {
                printf( "RBRACE(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"*"         {
                printf( "STAR(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"!"         {
                printf( "BANG(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

","         {
                printf( "COMMA(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

";"         {
                printf( "SEMI(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

\"[^\"]*\"  {
                printf( "STRING(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"//"[^\n]*  {
                printf( "COMMENT(%s){%d, %d}\n", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"\n"        {
                printf( "%s", yytext );
                STRING_IDX++;
                SYMBOL_IDX = 1;
            }

[ \t]+      {
                printf( "%s", yytext );
                SYMBOL_IDX += yyleng;
            }

<<EOF>>     {
                printf( "EOF{%d, %d}\n", STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
                yyterminate();
            }

.           printf( "\n\nUnrecognized character: %s, length = %d\n\n\n", yytext, STRING_IDX, SYMBOL_IDX );

%%

int main( int argc, char **argv ) {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yylex();
}
