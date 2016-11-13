/* flex grammar for a sample minijava code */

%{
#include <math.h>
#include <fstream>
#include <iostream>

int string_idx = 1, symbol_idx = 1;

void print_lexeme(const char* token)
{
    std::cout << token << "{" << string_idx <<", " << symbol_idx << "} ";
}

void process_lexeme(const char* token)
{
    print_lexeme(token);
}
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
                process_lexeme("VOID");
                symbol_idx += yyleng;
            }

int         {
                process_lexeme("INT");
                symbol_idx += yyleng;
            }

double      {
                process_lexeme("DOUBLE");
                symbol_idx += yyleng;
            }

boolean     {
                process_lexeme("BOOL");
                symbol_idx += yyleng;
            }

            /* KEYWORDS */

class       {
                process_lexeme("CLASS");
                symbol_idx += yyleng;
            }

public      {
                process_lexeme("PUBLIC");
                symbol_idx += yyleng;
            }

static      {
                process_lexeme("STATIC");
                symbol_idx += yyleng;
            }

extends     {
                process_lexeme("EXTENDS");
                symbol_idx += yyleng;
            }

this        {
                process_lexeme("THIS");
                symbol_idx += yyleng;
            }

new         {
                process_lexeme("NEW");
                symbol_idx += yyleng;
            }

null        {
                process_lexeme("NULL");
                symbol_idx += yyleng;
            }

if          {
                process_lexeme("IF");
                symbol_idx += yyleng;
            }

else        {
                process_lexeme("ELSE");
                symbol_idx += yyleng;
            }

while       {
                process_lexeme("WHILE");
                symbol_idx += yyleng;
            }

for         {
                process_lexeme("FOR");
                symbol_idx += yyleng;
            }

return      {
                process_lexeme("RETURN");
                symbol_idx += yyleng;
            }

            /* PARENTHESES */

"("         {
                process_lexeme("LPAREN");
                symbol_idx += yyleng;
            }

")"         {
                process_lexeme("RPAREN");
                symbol_idx += yyleng;
            }

"{"         {
                process_lexeme("LBRACE");
                symbol_idx += yyleng;
            }

"}"         {
                process_lexeme("RBRACE");
                symbol_idx += yyleng;
            }

"["         {
                process_lexeme("LBRACKET");
                symbol_idx += yyleng;
            }

"]"         {
                process_lexeme("RBRACKET");
                symbol_idx += yyleng;
            }

            /* ARITHMETICS */

"="         {
                process_lexeme("EQUALS");
                symbol_idx += yyleng;
            }

"=="         {
                process_lexeme("DOUBLEEQUALS");
                symbol_idx += yyleng;
            }

"+"         {
                process_lexeme("PLUS");
                symbol_idx += yyleng;
            }

"-"         {
                process_lexeme("MINUS");
                symbol_idx += yyleng;
            }

"*"         {
                process_lexeme("STAR");
                symbol_idx += yyleng;
            }

"/"         {
                process_lexeme("DIVIDE");
                symbol_idx += yyleng;
            }

"<"         {
                process_lexeme("LESS");
                symbol_idx += yyleng;
            }

">"         {
                process_lexeme("MORE");
                symbol_idx += yyleng;
            }

            /* LOGICAL */

true        {
                process_lexeme("TRUE");
                symbol_idx += yyleng;
            }

false       {
                process_lexeme("FALSE");
                symbol_idx += yyleng;
            }

"&&"        {
                process_lexeme("AND");
                symbol_idx += yyleng;
            }

"||"        {
                process_lexeme("OR");
                symbol_idx += yyleng;
            }

            /* SYNTACTIC */

"!"         {
                process_lexeme("BANG");
                symbol_idx += yyleng;
            }

","         {
                process_lexeme("COMMA");
                symbol_idx += yyleng;
            }

"."         {
                process_lexeme("DOT");
                symbol_idx += yyleng;
            }

"&"         {
                process_lexeme("AMPERSAND");
                symbol_idx += yyleng;
            }

"|"         {
                process_lexeme("BAR");
                symbol_idx += yyleng;
            }

";"         {
                process_lexeme("SEMI");
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
                process_lexeme("EOF");
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