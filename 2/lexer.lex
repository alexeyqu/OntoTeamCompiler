%{
#include <stdio.h>
#include "grammar.tab.h"
%}

%option noyywrap

DIGIT       [0-9]
ID          [a-zA-Z][a-zA-Z0-9_]*

%%
{DIGIT}+"."{DIGIT}* |
-?{DIGIT}+              return NUM;
int                     return INT;
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
{ID}+                   return ID;

\"(\\.|[^"])*\"         return STRING;

"//"[^\n]*              ;
"/*"[^"*/"]*"*/"        ;
\n                      ;
[ \t]+                  ;

%%
