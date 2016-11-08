typedef union {
	int pos;
	int ival;
	string sval;
} YYSTYPE;
extern YYSTYPE yylval;

#define ID 257 
#define NUM 258
