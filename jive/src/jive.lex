/* flex grammar for a sample minijava code */

%{
    #include <cmath>
    #include <cstdio>
    #include "jive.tab.h"

    extern YYLTYPE yylloc;
    #define YY_USER_INIT yylloc.first_line = 1;

    #ifdef LEXER
        #define PRINT_LEXEM( lex ) \
            { printf("%s(%s){%d, %d} ", #lex, yytext, yylloc.first_line, yylloc.first_column); }
    #else
        #define PRINT_LEXEM( lex ) ;
    #endif

    #define PROCESS_LEXEM( lex ) \
        { PRINT_LEXEM(lex); return lex; }

    static int line_idx = 1;
    static int symbol_idx = 1;

    void adjust();

    #define YY_USER_ACTION adjust();
%}

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({DIGIT}|{LETTER})*
INTEGER     [1-9]{DIGIT}*|0

%option noyywrap

%%
            /* NUMBERS */

{INTEGER}   { yylval.string = yytext; PROCESS_LEXEM(NUM); }

            /* TYPES */

void        { PROCESS_LEXEM(VOID); }
int         { PROCESS_LEXEM(INT); }
boolean     { PROCESS_LEXEM(BOOL); }

            /* KEYWORDS */

class       { PROCESS_LEXEM(CLASS); }
public      { PROCESS_LEXEM(PUBLIC); }
static      { PROCESS_LEXEM(STATIC); }
main        { PROCESS_LEXEM(MAIN); }
extends     { PROCESS_LEXEM(EXTENDS); }
this        { PROCESS_LEXEM(THIS); }
if          { PROCESS_LEXEM(IF); }
else        { PROCESS_LEXEM(ELSE); }
while       { PROCESS_LEXEM(WHILE); }
for         { PROCESS_LEXEM(FOR); }
return      { PROCESS_LEXEM(RETURN); }
null        { PROCESS_LEXEM(NIL); }

            /* PARENTHESES */

"("         { PROCESS_LEXEM(LPAREN); }
")"         { PROCESS_LEXEM(RPAREN); }
"{"         { PROCESS_LEXEM(LBRACE); }
"}"         { PROCESS_LEXEM(RBRACE); }
"["         { PROCESS_LEXEM(LBRACKET); }
"]"         { PROCESS_LEXEM(RBRACKET); }

            /* ARITHMETICS */

"=="        { PROCESS_LEXEM(EQUEQU); }
"="         { PROCESS_LEXEM(EQU); }
"+"         { PROCESS_LEXEM(ADD); }
"-"         { PROCESS_LEXEM(SUB); }
"*"         { PROCESS_LEXEM(MUL); }
"/"         { PROCESS_LEXEM(DIV); }
"<"         { PROCESS_LEXEM(LESS); }
">"         { PROCESS_LEXEM(GREATER); }
"%"         { PROCESS_LEXEM(MOD); }

            /* LOGICAL */

true        { PROCESS_LEXEM(TRUE); }
false       { PROCESS_LEXEM(FALSE); }
"&&"        { PROCESS_LEXEM(AND); }
"||"        { PROCESS_LEXEM(OR); }
"!"         { PROCESS_LEXEM(NOT); }

            /* SYNTACTIC */

","         { PROCESS_LEXEM(COMMA); }
"."         { PROCESS_LEXEM(DOT); }
"&"         { PROCESS_LEXEM(AMPERSAND); }
";"         { PROCESS_LEXEM(SEMI); }

            /* COMMANDS */

"System.out.println"    { PROCESS_LEXEM(PRINT); }

            /* IDENTIFIERS */

{ID}+       { yylval.string = yytext; PROCESS_LEXEM(ID); }

            /* STRING */

\"[^\"]*\"  { PROCESS_LEXEM(STRING); }

            /* COMMENTS */

"//"[^\n]*  { PRINT_LEXEM(COMMENT); }
"/*"[^"*/"]*"*/" { PRINT_LEXEM(COMMENT); }

            /* WHITESPACE */

"\n"        { ; /* printf("\n"); */ }
[ \t]+      { ; /* printf( "%s", yytext ); */ }

            /* EOFS */

            /* ERROR */

.           { PROCESS_LEXEM(ERROR); }

%%

void adjust() {
    yylloc.first_line = line_idx;
    yylloc.first_column = symbol_idx;

    for( int i = 0; i < yyleng; i++ ) {
        if( yytext[i] == '\n' ) {
            line_idx++;
            symbol_idx = 1;
        } else {
            symbol_idx++;
        }
    }

    yylloc.last_line = line_idx;
    yylloc.last_column = symbol_idx;
}