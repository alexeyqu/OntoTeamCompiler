%{
#include <stdio.h>
#include "grammar.tab.h"
%}
%%
[0-9]+                  yylval=atoi(yytext); return NUMBER;
heat                    return TOKHEAT;
on|off                  yylval=!strcmp(yytext,"on"); return STATE;
target                  return TOKTARGET;
temperature             return TOKTEMPERATURE;
\n                      /* игнорируем символ конца строки */;
[ \t]+                  /* игнорируем пробелы и символы табуляции */;
%%
