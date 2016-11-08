%{
#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"

int charPos = 1;

int yywrap(void)
{
	charPos = 1;
	return 1;
}

void adjust(void)
{
	EM_tokPos = charPos;
	charPos += yyleng;
}

%}

digits	[0-9]+
id	[a-zA-Z][a-zA-Z0-9_]*

%%

" "	{adjust(); continue;}
{id}	{adjust(); yylval.sval = String(yytext); return ID;}
{digits} {adjust(); yylval.ival = atoi(yytext); return NUM;}
\n	{adjust(); EM_newline(); continue;}
.	{adjust(); EM_error(EM_tokPos, "illegal token");}

