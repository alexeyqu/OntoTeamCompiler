%{
#include <stdio.h>
#include "grammar.tab.h"
%}

%option noyywrap

DIGIT       [0-9]
ID          [a-zA-Z][a-zA-Z0-9_]*

%%
{DIGIT}+"."{DIGIT}*     yylval=strdup(yytext); return NUM;
-?{DIGIT}+              yylval=strdup(yytext); return NUM;
int                     return INT;
char                    return CHAR;
if                      return IF;
else                    return ELSE;
return                  return RETURN;
;                       return SEMI;
,                       return COMMA;
\*                      return STAR;
!                       return NOT;
\(                      return LPAREN;
\)                      return RPAREN;
\{                      return LBRACE;
\}                      return RBRACE;
{ID}+                   yylval=strdup(yytext); return ID;

\"(\\.|[^"])*\"         yylval=strdup(yytext); return STRING;

"//"[^\n]*              yylval=strdup(yytext); return COMMENT;
"/*"[^"*/"]*"*/"        yylval=strdup(yytext); return COMMENT;
\n                      return EOL;
\t                      return TAB;
[ ]                     return WHITESPACE;

%%
