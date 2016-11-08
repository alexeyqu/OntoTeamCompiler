#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "errormsg.h"
#include "tokens.h"

YYSTYPE yylval;

int yylex(void);

string toknames[] = {
	"ID", "NUM"
};

string tokname(int tok)
{
	return tok < 257 || tok > 299 ? "BAD_TOKEN" : toknames[tok-257];
}

int main(int argc, char **argv)
{
	string fname;
	int tok;

	if (argc != 2) {fprintf(stderr, "usage: a.out filename\n"); exit(1);}

	fname = argv[1];

	EM_reset(fname);

	for(;;)
	{
		tok = yylex();
		if (tok == 0) break;

		switch(tok)
		{
		case ID:
			printf("%10s %4d %s\n", tokname(tok), EM_tokPos, yylval.sval);
			break;

		case NUM:	
			printf("%10s %4d %d\n", tokname(tok), EM_tokPos, yylval.ival);
			break;

		default:
			printf("%10s %4d\n", tokname(tok), EM_tokPos);
		}
	}

	return 0;
}
