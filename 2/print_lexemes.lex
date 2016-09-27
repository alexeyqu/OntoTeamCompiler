/* flex grammar for a sample minijava code */

%{
#include <math.h>
#include <fstream>
#include <iostream>

int string_idx = 1, symbol_idx = 1;
%}

%option noyywrap

DIGIT       [0-9]
ID          [a-zA-Z][a-zA-Z0-9_]*

%%
            /* NUMBERS */

{DIGIT}+"."{DIGIT}* |
-?{DIGIT}+  {
                std::cout << "NUM(" << atoi( yytext ) << "){" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

            /* TYPES */

void        {
                std::cout << "VOID{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

int         {
                std::cout << "INT{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

double      {
                std::cout << "DOUBLE{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

boolean     {
                std::cout << "BOOL{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

            /* KEYWORDS */

class       {
                std::cout << "CLASS{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

public      {
                std::cout << "PUBLIC{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

static      {
                std::cout << "STATIC{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

extends     {
                std::cout << "EXTENDS{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

this        {
                std::cout << "THIS{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

new         {
                std::cout << "NEW{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

null        {
                std::cout << "NULL{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

if          {
                std::cout << "IF{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

else        {
                std::cout << "ELSE{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

while       {
                std::cout << "WHILE{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

for         {
                std::cout << "FOR{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

return      {
                std::cout << "RETURN{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

            /* PARENTHESES */

"("         {
                std::cout << "LPAREN{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

")"         {
                std::cout << "RPAREN{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"{"         {
                std::cout << "LBRACE{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"}"         {
                std::cout << "RBRACE{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"["         {
                std::cout << "LBRACKET{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"]"         {
                std::cout << "RBRACKET{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

            /* ARITHMETICS */

"="         {
                std::cout << "EQUALS{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"=="         {
                std::cout << "DOUBLEEQUALS{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"+"         {
                std::cout << "PLUS{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"-"         {
                std::cout << "MINUS{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"*"         {
                std::cout << "STAR{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"/"         {
                std::cout << "DIVIDE{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"<"         {
                std::cout << "LESS{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

">"         {
                std::cout << "MORE{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

            /* LOGICAL */

true        {
                std::cout << "TRUE{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

false       {
                std::cout << "FALSE{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"&&"        {
                std::cout << "AND{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"||"        {
                std::cout << "OR{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

            /* SYNTACTIC */

"!"         {
                std::cout << "NOT{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

","         {
                std::cout << "COMMA{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"."         {
                std::cout << "DOT{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"&"         {
                std::cout << "AMPERSAND{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"|"         {
                std::cout << "BAR{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

";"         {
                std::cout << "SEMI{" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

            /* IDENTIFIERS */

{ID}+       {
                std::cout << "ID(" << yytext << "){" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }


            /* COMMENTS */

\"(\\.|[^"])*\"  {
                std::cout << "STRING(" << yytext << "){" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"//"[^\n]*  {
                std::cout << "COMMENT(" << yytext << "){" << string_idx <<", " << symbol_idx << "} ";
                symbol_idx += yyleng;
            }

"/*"[^"*/"]*"*/" {
                std::cout << "COMMENT(" << yytext << "){" << string_idx <<", " << symbol_idx << "} ";

                for( int index = 0; index < yyleng; ++index ) {
                    if( yytext[index] == '\n' ) {
                        symbol_idx = 1;
                        string_idx++;
                    }
                    else {
                        symbol_idx++;
                    }
                }
            }

            /* WHITESPACE */

"\n"        {
                std::cout << yytext;
                string_idx++;
                symbol_idx = 1;
            }

[ \t]+      {
                std::cout << yytext;
                symbol_idx += yyleng;
            }

<<EOF>>     {
                std::cout << "EOF{" << string_idx <<", " << symbol_idx << "}\n";
                symbol_idx += yyleng;
                yyterminate();
            }

.           std::cout << "\n\nUnrecognized character:" << yytext << ", length = " << yyleng << "\n\n\n";

%%

int main( int argc, char **argv ) {
    ++argv, --argc;  /* skip over program name */
    FlexLexer* lexer = new yyFlexLexer;
    if ( argc > 0 ) {
        std::ifstream new_in;
        new_in.open( argv[0] );
        if ( new_in.good() ) {
            std::istream* in_stream = &new_in;
            lexer->yylex( in_stream, &std::cout );
        } else {
        lexer->yylex();
        }
    } else {
        lexer->yylex();
    }
    return 0;
}
