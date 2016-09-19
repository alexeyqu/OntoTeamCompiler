/* flex grammar for a sample minijava code */

%{
#include <math.h>

int STRING_IDX = 1, SYMBOL_IDX = 1;
%}

DIGIT       [0-9]
ID          [a-zA-Z][a-zA-Z0-9_]*

%%
            /* NUMBERS */

-?{DIGIT}+   {
            printf( "NUM(%d){%d, %d} ", atoi( yytext ), STRING_IDX, SYMBOL_IDX );
            SYMBOL_IDX += yyleng;
            }

{DIGIT}+"."{DIGIT}* {
            printf( "NUM(%g){%d, %d} ", atof( yytext ), STRING_IDX, SYMBOL_IDX );
            SYMBOL_IDX += yyleng;
            }

            /* TYPES */

void         {
                printf( "VOID(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

int         {
                printf( "INT(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

boolean     {
                printf( "BOOL(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

            /* KEYWORDS */

class      {
                printf( "CLASS(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

public      {
                printf( "PUBLIC(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

static      {
                printf( "STATIC(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

extends     {
                printf( "EXTENDS(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

this       {
                printf( "THIS(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
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

while       {
                printf( "WHILE(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

for         {
                printf( "FOR(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

return      {
                printf( "RETURN(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

            /* PARENTHESES */

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

"["         {
                printf( "LBRACKET(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"]"         {
                printf( "RBRACKET(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

            /* ARITHMETICS */

"="         {
                printf( "EQUALS(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"+"         {
                printf( "PLUS(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"-"         {
                printf( "MINUS(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"*"         {
                printf( "STAR(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"/"         {
                printf( "DIVIDE(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"<"         {
                printf( "LESS(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

">"         {
                printf( "MORE(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

            /* LOGICAL */

true        {
                printf( "TRUE(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

false       {
                printf( "FALSE%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

            /* SYNTACTIC */

"!"         {
                printf( "BANG(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

","         {
                printf( "COMMA(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"."         {
                printf( "DOT(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"&"         {
                printf( "AMPERSAND(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

";"         {
                printf( "SEMI(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

            /* IDENTIFIERS */

{ID}+       {
                printf( "ID(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }


            /* COMMENTS */

\"[^\"]*\"  {
                printf( "STRING(%s){%d, %d} ", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"//"[^\n]*  {
                printf( "COMMENT(%s){%d, %d}\n", yytext, STRING_IDX, SYMBOL_IDX );
                SYMBOL_IDX += yyleng;
            }

"/*"[^"*/"]*"*/" {
                printf( "COMMENT(%s){%d, %d}\n", yytext, STRING_IDX, SYMBOL_IDX );

                for(int index = 0; index < yyleng; index++) {
                        if( yytext[index] == '\n' ) {
                                    SYMBOL_IDX = 1;
                                    STRING_IDX++;
                        }
                        else {
                                    SYMBOL_IDX++;
                        }
                }
            }

            /* WHITESPACE */

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

.           printf( "\n\nUnrecognized character: %s, length = %d\n\n\n", yytext, yyleng );

%%

int main( int argc, char **argv ) {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yylex();
}
