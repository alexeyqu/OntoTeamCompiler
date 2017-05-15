/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

#line 67 "jive.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "jive.tab.h".  */
#ifndef YY_YY_JIVE_TAB_H_INCLUDED
# define YY_YY_JIVE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "jive.y" /* yacc.c:355  */

	#include <cstdio>
	#include <cstring>
	#include "CJiveEnvironment.h"

	#define YYERROR_VERBOSE 1 

#line 105 "jive.tab.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    ID = 259,
    STRING = 260,
    VOID = 261,
    INT = 262,
    BOOL = 263,
    CLASS = 264,
    PUBLIC = 265,
    STATIC = 266,
    EXTENDS = 267,
    THIS = 268,
    MAIN = 269,
    IF = 270,
    ELSE = 271,
    WHILE = 272,
    FOR = 273,
    RETURN = 274,
    NIL = 275,
    NEW = 276,
    LPAREN = 277,
    RPAREN = 278,
    LBRACE = 279,
    RBRACE = 280,
    LBRACKET = 281,
    RBRACKET = 282,
    ASSIGN = 283,
    EQU = 284,
    ADD = 285,
    SUB = 286,
    MUL = 287,
    DIV = 288,
    MOD = 289,
    LESS = 290,
    GREATER = 291,
    TRUE = 292,
    FALSE = 293,
    AND = 294,
    OR = 295,
    NOT = 296,
    COMMA = 297,
    DOT = 298,
    SEMI = 299,
    AMPERSAND = 300,
    PRINT = 301,
    LENGTH = 302,
    ERROR = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 23 "jive.y" /* yacc.c:355  */

	char *string;
	CJiveEnvironment *JiveEnv;
	IVisitorTarget *Goal;
	CVariable* Variable;
	CArgument* Argument;
	CCompoundVariable* Variables;
	CMethod* Method;
	CCompoundMethod* Methods;
	CClass* Class;
	CCompoundClass* Classes;
	CMainClass* MainClass;
	CCompoundArgument* Arguments;
	CCompoundStatement* Statements;
	CCompoundExpression* Expressions;
	CIdExpression *Identifier;

	IType* Type;
	IEntity *Entity;
	IStatement *Statement;
	IExpression *Expression;

#line 189 "jive.tab.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (CJiveEnvironment **jiveEnv);

#endif /* !YY_YY_JIVE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 218 "jive.tab.cpp" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 9 "jive.y" /* yacc.c:359  */

	int yylex (void);

	void yyerror(CJiveEnvironment **jiveEnv, const char *str) {
	    fprintf(stderr, "Error: {%d, %d} %s\n", yylloc.first_line, yylloc.first_column, str);
	    exit(1);
	}

#line 229 "jive.tab.cpp" /* yacc.c:359  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   273

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  151

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,   101,   104,   117,   125,   128,   139,   151,
     159,   162,   171,   179,   182,   195,   203,   206,   214,   217,
     226,   234,   237,   245,   256,   266,   274,   283,   291,   299,
     308,   316,   325,   333,   341,   349,   357,   366,   374,   382,
     390,   398,   406,   414,   422,   430,   438,   446,   454,   462,
     470,   478,   486,   494,   502,   510,   519,   527,   530,   538,
     541
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "ID", "STRING", "VOID", "INT",
  "BOOL", "CLASS", "PUBLIC", "STATIC", "EXTENDS", "THIS", "MAIN", "IF",
  "ELSE", "WHILE", "FOR", "RETURN", "NIL", "NEW", "LPAREN", "RPAREN",
  "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "ASSIGN", "EQU", "ADD",
  "SUB", "MUL", "DIV", "MOD", "LESS", "GREATER", "TRUE", "FALSE", "AND",
  "OR", "NOT", "COMMA", "DOT", "SEMI", "AMPERSAND", "PRINT", "LENGTH",
  "ERROR", "$accept", "JiveEnv", "Goal", "MainClass", "Classes", "Class",
  "Variables", "Variable", "Methods", "Method", "Arguments",
  "RestArguments", "Argument", "Statements", "Statement",
  "CallableExpression", "LeftExpression", "Type", "Expression",
  "Expressions", "RestExpressions", "Identifier", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -97

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-97)))

#define YYTABLE_NINF -37

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -8,     2,    11,   -97,   -97,   -97,    25,   -97,    48,    56,
       2,   -97,    50,    -9,    71,     2,   -97,    64,    65,    90,
      66,   -97,   -97,    73,   -97,   -97,    10,     2,   -97,    87,
      90,    74,    90,   -97,   -97,    58,    80,    17,   -97,     2,
     -97,    81,   -97,    85,     2,    90,    86,    89,    75,     2,
      91,    92,    90,   -97,   -97,    13,   -97,    75,    97,   101,
      13,   111,    88,    13,    36,   -97,    76,   -97,    83,    83,
     112,    83,   122,   -97,    83,    83,   117,   146,   -97,   -97,
      51,    83,    83,   -97,   -97,    83,   -97,   125,    95,   109,
     -97,   123,   -97,   151,   179,    83,   135,   142,   137,   -10,
     223,    13,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    -2,   141,   130,   -97,   -97,   194,    83,   152,   -97,
     163,   -10,   -10,   145,   145,    20,   230,   230,   223,   223,
     -97,   167,    13,   -97,   168,   165,   -97,    13,    83,   177,
     -97,   -97,   -97,   209,   180,   -97,    83,   -97,   -97,   209,
     -97
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     6,    60,     0,     1,     3,     0,
       0,     5,     0,     0,     0,     0,    10,     0,     0,    13,
       0,    10,    35,    32,    34,     9,     0,     0,    36,     0,
      13,     0,     0,     8,    12,     0,     0,     0,    33,     0,
      11,     0,     7,     0,     0,    16,     0,     0,    18,     0,
       0,     0,     0,    15,    19,    21,    10,    18,     0,     0,
      21,     0,     0,    21,     0,    31,    21,    17,     0,     0,
       0,     0,     0,    20,     0,     0,     0,    31,    48,    28,
       0,     0,     0,    49,    50,     0,    55,    27,     0,     0,
      22,     0,     4,     0,     0,     0,     0,     0,     0,    54,
      52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    30,    26,     0,     0,     0,    53,
       0,    41,    42,    43,    44,    45,    39,    40,    37,    38,
      46,     0,    21,    25,     0,     0,    29,     0,    57,     0,
      14,    51,    23,    59,     0,    24,     0,    56,    47,    59,
      58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -97,   -97,   -97,   -97,   -97,   -97,     0,   -97,   176,   -97,
     -97,   150,   164,   -56,   -96,   -97,   -47,   -20,   -35,   -97,
      68,    -1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     8,    11,    19,    25,    26,    34,
      47,    53,    48,    62,    63,    86,    87,    27,    88,   144,
     147,    65
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       6,     1,     5,    15,    70,   120,     5,    73,    64,    13,
      76,     7,    39,    64,    18,    16,    64,     5,    28,    64,
      32,    30,   104,   105,   106,    49,    35,    32,    58,    28,
      59,    28,    49,   111,    89,    33,    91,    60,    43,    93,
      94,   142,    42,    46,    28,   130,    98,    99,    54,     9,
     100,    28,   104,   105,    64,     5,    66,    10,    96,    61,
     116,    14,    74,   111,    75,    77,    12,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   139,    17,    20,    97,
       5,    22,   135,    23,    24,    64,    78,     5,    29,    21,
      64,    58,    36,    59,     5,    22,    79,    23,    24,    31,
      60,    38,    40,   143,    80,    81,    41,    45,    44,    50,
     131,   149,    51,    72,    82,    55,    56,    52,   101,    68,
      83,    84,    61,    69,    85,   102,   103,   104,   105,   106,
     107,   108,   112,    71,   109,   110,    95,    90,   111,   102,
     103,   104,   105,   106,   107,   108,   113,    92,   109,   110,
     -36,    74,   111,   102,   103,   104,   105,   106,   107,   108,
     119,   117,   109,   110,   118,   132,   111,   102,   103,   104,
     105,   106,   107,   108,   133,   136,   109,   110,   114,   137,
     111,   102,   103,   104,   105,   106,   107,   108,   111,   138,
     109,   110,   141,   140,   111,   102,   103,   104,   105,   106,
     107,   108,   145,   148,   109,   110,    37,    67,   111,   102,
     103,   104,   105,   106,   107,   108,    57,   150,   109,   110,
       0,     0,   111,   115,   102,   103,   104,   105,   106,   107,
     108,     0,     0,   109,   110,     0,     0,   111,   134,   102,
     103,   104,   105,   106,   107,   108,     0,     0,   109,   110,
       0,   146,   111,   102,   103,   104,   105,   106,   107,   108,
     102,   103,   104,   105,   106,     0,   111,     0,     0,     0,
       0,     0,     0,   111
};

static const yytype_int16 yycheck[] =
{
       1,     9,     4,    12,    60,   101,     4,    63,    55,    10,
      66,     0,    32,    60,    15,    24,    63,     4,    19,    66,
      10,    21,    32,    33,    34,    45,    27,    10,    15,    30,
      17,    32,    52,    43,    69,    25,    71,    24,    39,    74,
      75,   137,    25,    44,    45,    47,    81,    82,    49,    24,
      85,    52,    32,    33,   101,     4,    56,     9,     7,    46,
      95,    11,    26,    43,    28,    66,    10,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   132,     6,    14,    80,
       4,     5,   117,     7,     8,   132,     3,     4,    22,    24,
     137,    15,     5,    17,     4,     5,    13,     7,     8,    26,
      24,    27,    44,   138,    21,    22,    26,    22,    27,    23,
     111,   146,    23,    25,    31,    24,    24,    42,    23,    22,
      37,    38,    46,    22,    41,    30,    31,    32,    33,    34,
      35,    36,    23,    22,    39,    40,    19,    25,    43,    30,
      31,    32,    33,    34,    35,    36,    23,    25,    39,    40,
       4,    26,    43,    30,    31,    32,    33,    34,    35,    36,
      23,    26,    39,    40,    22,    24,    43,    30,    31,    32,
      33,    34,    35,    36,    44,    23,    39,    40,    27,    16,
      43,    30,    31,    32,    33,    34,    35,    36,    43,    22,
      39,    40,    27,    25,    43,    30,    31,    32,    33,    34,
      35,    36,    25,    23,    39,    40,    30,    57,    43,    30,
      31,    32,    33,    34,    35,    36,    52,   149,    39,    40,
      -1,    -1,    43,    44,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    40,    -1,    -1,    43,    44,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    40,
      -1,    42,    43,    30,    31,    32,    33,    34,    35,    36,
      30,    31,    32,    33,    34,    -1,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    50,    51,    52,     4,    70,     0,    53,    24,
       9,    54,    10,    70,    11,    12,    24,     6,    70,    55,
      14,    24,     5,     7,     8,    56,    57,    66,    70,    22,
      55,    26,    10,    25,    58,    70,     5,    57,    27,    66,
      44,    26,    25,    70,    27,    22,    70,    59,    61,    66,
      23,    23,    42,    60,    70,    24,    24,    61,    15,    17,
      24,    46,    62,    63,    65,    70,    55,    60,    22,    22,
      62,    22,    25,    62,    26,    28,    62,    70,     3,    13,
      21,    22,    31,    37,    38,    41,    64,    65,    67,    67,
      25,    67,    25,    67,    67,    19,     7,    70,    67,    67,
      67,    23,    30,    31,    32,    33,    34,    35,    36,    39,
      40,    43,    23,    23,    27,    44,    67,    26,    22,    23,
      63,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      47,    70,    24,    44,    44,    67,    23,    16,    22,    62,
      25,    27,    63,    67,    68,    25,    42,    69,    23,    67,
      69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    52,    53,    53,    54,    54,    55,
      55,    56,    57,    57,    58,    59,    59,    60,    60,    61,
      62,    62,    63,    63,    63,    63,    63,    64,    64,    64,
      65,    65,    66,    66,    66,    66,    66,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    68,    68,    69,    69,
      70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,    17,     2,     0,     8,     6,     2,
       0,     3,     2,     0,    13,     2,     0,     3,     0,     2,
       2,     0,     3,     7,     7,     5,     4,     1,     1,     4,
       4,     1,     1,     3,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     6,     1,     1,
       1,     5,     2,     3,     2,     1,     2,     0,     3,     0,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (jiveEnv, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, jiveEnv); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, CJiveEnvironment **jiveEnv)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (jiveEnv);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, CJiveEnvironment **jiveEnv)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, jiveEnv);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, CJiveEnvironment **jiveEnv)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , jiveEnv);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, jiveEnv); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, CJiveEnvironment **jiveEnv)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (jiveEnv);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (CJiveEnvironment **jiveEnv)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 96 "jive.y" /* yacc.c:1646  */
    { 
	(*jiveEnv)->LoadProgram( new CProgram( (yyvsp[0].Goal) ) ); 
	(yyval.JiveEnv) = *jiveEnv; }
#line 1513 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 101 "jive.y" /* yacc.c:1646  */
    { (yyval.Goal) = new CGoal( (yyvsp[-1].MainClass), (yyvsp[0].Classes) ); }
#line 1519 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 108 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line; \
				int temp_column = yyloc.first_column; \
				(yyval.MainClass) = new CMainClass( (yyvsp[-15].Identifier), (yyvsp[-5].Identifier), (yyvsp[-2].Statements)  ); \
				(yyval.MainClass)->coordinates.first_line = temp_line; \
				(yyval.MainClass)->coordinates.first_column = temp_column;
			}
#line 1531 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 117 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Classes) = new CCompoundClass( (yyvsp[-1].Classes), (yyvsp[0].Class) );
				(yyval.Classes)->coordinates.first_line = temp_line;
				(yyval.Classes)->coordinates.first_column = temp_column; 
			}
#line 1543 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 125 "jive.y" /* yacc.c:1646  */
    { (yyval.Classes) = nullptr; }
#line 1549 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 131 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Class) = new CClass( (yyvsp[-6].Identifier), (yyvsp[-4].Identifier), (yyvsp[-2].Variables), (yyvsp[-1].Methods) );
				(yyval.Class)->coordinates.first_line = temp_line;
				(yyval.Class)->coordinates.first_column = temp_column; 
			}
#line 1561 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 142 "jive.y" /* yacc.c:1646  */
    { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			(yyval.Class) = new CClass( (yyvsp[-4].Identifier), nullptr, (yyvsp[-2].Variables), (yyvsp[-1].Methods) );
			(yyval.Class)->coordinates.first_line = temp_line;
			(yyval.Class)->coordinates.first_column = temp_column; 
		}
#line 1573 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 151 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Variables) = new CCompoundVariable( (yyvsp[-1].Variables), (yyvsp[0].Variable) );
				(yyval.Variables)->coordinates.first_line = temp_line;
				(yyval.Variables)->coordinates.first_column = temp_column; 
			}
#line 1585 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 159 "jive.y" /* yacc.c:1646  */
    { (yyval.Variables) = nullptr; }
#line 1591 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 162 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Variable) = new CVariable( (yyvsp[-2].Type), (yyvsp[-1].Identifier) );
				(yyval.Variable)->coordinates.first_line = temp_line;
				(yyval.Variable)->coordinates.first_column = temp_column; 
			}
#line 1603 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 171 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Methods) = new CCompoundMethod( (yyvsp[-1].Methods), (yyvsp[0].Method) );
				(yyval.Methods)->coordinates.first_line = temp_line;
				(yyval.Methods)->coordinates.first_column = temp_column; 
			}
#line 1615 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 179 "jive.y" /* yacc.c:1646  */
    { (yyval.Methods) = nullptr; }
#line 1621 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 186 "jive.y" /* yacc.c:1646  */
    {
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Method) = new CMethod( (yyvsp[-11].Type), (yyvsp[-10].Identifier), (yyvsp[-8].Arguments), (yyvsp[-5].Variables), (yyvsp[-4].Statements), (yyvsp[-2].Expression) ); 
				(yyval.Method)->coordinates.first_line = temp_line;
				(yyval.Method)->coordinates.first_column = temp_column; 
			}
#line 1633 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 195 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Arguments) = new CCompoundArgument( (yyvsp[-1].Argument), (yyvsp[0].Arguments) );
				(yyval.Arguments)->coordinates.first_line = temp_line;
				(yyval.Arguments)->coordinates.first_column = temp_column; 
			}
#line 1645 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 203 "jive.y" /* yacc.c:1646  */
    { (yyval.Arguments) = nullptr; }
#line 1651 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 206 "jive.y" /* yacc.c:1646  */
    {
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Arguments) = new CCompoundArgument( (yyvsp[-1].Argument), (yyvsp[0].Arguments) );
				(yyval.Arguments)->coordinates.first_line = yylloc.first_line;
				(yyval.Arguments)->coordinates.first_column = yylloc.first_column; 
			}
#line 1663 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 214 "jive.y" /* yacc.c:1646  */
    { (yyval.Arguments) = nullptr; }
#line 1669 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 217 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Argument) = new CArgument( (yyvsp[-1].Type), (yyvsp[0].Identifier) );
				(yyval.Argument)->coordinates.first_line = temp_line;
				(yyval.Argument)->coordinates.first_column = temp_column; 
			}
#line 1681 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 226 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Statements) = new CCompoundStatement( (yyvsp[0].Statements), (yyvsp[-1].Statement) );
				(yyval.Statements)->coordinates.first_line = temp_line;
				(yyval.Statements)->coordinates.first_column = temp_column; 
			}
#line 1693 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 234 "jive.y" /* yacc.c:1646  */
    { (yyval.Statements) = nullptr; }
#line 1699 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 237 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Statement) = new CCompoundStatement( nullptr, (yyvsp[-1].Statements) );
				(yyval.Statement)->coordinates.first_line = temp_line;
				(yyval.Statement)->coordinates.first_column = temp_column; 
			}
#line 1711 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 248 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Statement) = new CIfStatement( (yyvsp[-4].Expression), (yyvsp[-2].Statement), (yyvsp[0].Statement) );
				(yyval.Statement)->coordinates.first_line = temp_line;
				(yyval.Statement)->coordinates.first_column = temp_column; 
			}
#line 1723 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 258 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Statement) = new CWhileStatement( (yyvsp[-4].Expression), (yyvsp[-1].Statements) );
				(yyval.Statement)->coordinates.first_line = temp_line;
				(yyval.Statement)->coordinates.first_column = temp_column; 
			}
#line 1735 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 266 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Statement) = new CPrintStatement( (yyvsp[-2].Expression) );
				(yyval.Statement)->coordinates.first_line = temp_line;
				(yyval.Statement)->coordinates.first_column = temp_column; 
			}
#line 1747 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 274 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Statement) = new CAssignStatement( (yyvsp[-3].Expression), (yyvsp[-1].Expression) );
				(yyval.Statement)->coordinates.first_line = temp_line;
				(yyval.Statement)->coordinates.first_column = temp_column; 
			}
#line 1759 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 283 "jive.y" /* yacc.c:1646  */
    {
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = (yyvsp[0].Expression);
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1771 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 291 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CThisExpression();
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1783 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 299 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CNewObjectExpression( (yyvsp[-2].Identifier) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1795 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 308 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CArrayIndexExpression( (yyvsp[-3].Expression), (yyvsp[-1].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1807 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 316 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = (yyvsp[0].Identifier);
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1819 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 325 "jive.y" /* yacc.c:1646  */
    { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			(yyval.Type) = new CBuiltInType( enums::INTEGER );
			(yyval.Type)->coordinates.first_line = temp_line;
			(yyval.Type)->coordinates.first_column = temp_column; 
		}
#line 1831 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 333 "jive.y" /* yacc.c:1646  */
    { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			(yyval.Type) = new CBuiltInType( enums::INTEGERARRAY );
			(yyval.Type)->coordinates.first_line = temp_line;
			(yyval.Type)->coordinates.first_column = temp_column; 
		}
#line 1843 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 341 "jive.y" /* yacc.c:1646  */
    { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			(yyval.Type) = new CBuiltInType( enums::BOOLEAN );
			(yyval.Type)->coordinates.first_line = temp_line;
			(yyval.Type)->coordinates.first_column = temp_column; 
		}
#line 1855 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 349 "jive.y" /* yacc.c:1646  */
    { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			(yyval.Type) = new CBuiltInType( enums::STRING );
			(yyval.Type)->coordinates.first_line = temp_line;
			(yyval.Type)->coordinates.first_column = temp_column; 
		}
#line 1867 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 357 "jive.y" /* yacc.c:1646  */
    { 
			int temp_line = yyloc.first_line;
			int temp_column = yyloc.first_column;
			(yyval.Type) = new CUserType( (yyvsp[0].Identifier)->name );
			(yyval.Type)->coordinates.first_line = temp_line;
			(yyval.Type)->coordinates.first_column = yylloc.first_column; 
		}
#line 1879 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 366 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBinaryBooleanExpression( (yyvsp[-2].Expression), enums::AND, (yyvsp[0].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1891 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 374 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBinaryBooleanExpression( (yyvsp[-2].Expression), enums::OR, (yyvsp[0].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column;  
			}
#line 1903 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 382 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBinaryBooleanExpression( (yyvsp[-2].Expression), enums::LESS, (yyvsp[0].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1915 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 390 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBinaryBooleanExpression( (yyvsp[-2].Expression), enums::GREATER, (yyvsp[0].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1927 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 398 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBinaryExpression( (yyvsp[-2].Expression), enums::ADD, (yyvsp[0].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1939 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 406 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBinaryExpression( (yyvsp[-2].Expression), enums::SUB, (yyvsp[0].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1951 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 414 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBinaryExpression( (yyvsp[-2].Expression), enums::MUL, (yyvsp[0].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1963 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 422 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBinaryExpression( (yyvsp[-2].Expression), enums::DIV, (yyvsp[0].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1975 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 430 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBinaryExpression( (yyvsp[-2].Expression), enums::MOD, (yyvsp[0].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1987 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 438 "jive.y" /* yacc.c:1646  */
    {
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CArrayLengthExpression( (yyvsp[-2].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 1999 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 446 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CMethodCallExpression( (yyvsp[-5].Expression), (yyvsp[-3].Identifier), (yyvsp[-1].Expressions) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 2011 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 454 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CNumberExpression( (yyvsp[0].string) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 2023 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 462 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBooleanExpression( true );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 2035 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 470 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBooleanExpression( false );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 2047 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 478 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CNewIntArrayExpression( (yyvsp[-1].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 2059 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 486 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBooleanExpression( !(yyvsp[0].Expression) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 2071 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 494 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = (yyvsp[-1].Expression);
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 2083 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 502 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = new CBinaryExpression ((yyvsp[0].Expression), enums::MUL, new CNumberExpression ( "-1" ) );
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 2095 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 510 "jive.y" /* yacc.c:1646  */
    {
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Expression) = (yyvsp[0].Expression);
				(yyval.Expression)->coordinates.first_line = temp_line;
				(yyval.Expression)->coordinates.first_column = temp_column; 
			}
#line 2107 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 519 "jive.y" /* yacc.c:1646  */
    { 
					int temp_line = yyloc.first_line;
					int temp_column = yyloc.first_column;
					(yyval.Expressions) = new CCompoundExpression( (yyvsp[-1].Expression), (yyvsp[0].Expressions) );
					(yyval.Expressions)->coordinates.first_line = temp_line;
					(yyval.Expressions)->coordinates.first_column = temp_column; 
				}
#line 2119 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 527 "jive.y" /* yacc.c:1646  */
    { (yyval.Expressions) = nullptr; }
#line 2125 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 530 "jive.y" /* yacc.c:1646  */
    { 
					int temp_line = yyloc.first_line;
					int temp_column = yyloc.first_column;
					(yyval.Expressions) = new CCompoundExpression( (yyvsp[-1].Expression), (yyvsp[0].Expressions) );
					(yyval.Expressions)->coordinates.first_line = temp_line;
					(yyval.Expressions)->coordinates.first_column = temp_column; 
				}
#line 2137 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 538 "jive.y" /* yacc.c:1646  */
    { (yyval.Expressions) = nullptr; }
#line 2143 "jive.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 541 "jive.y" /* yacc.c:1646  */
    { 
				int temp_line = yyloc.first_line;
				int temp_column = yyloc.first_column;
				(yyval.Identifier) = new CIdExpression( (yyvsp[0].string) );
				(yyval.Identifier)->coordinates.first_line = temp_line;
				(yyval.Identifier)->coordinates.first_column = temp_column; 
			}
#line 2155 "jive.tab.cpp" /* yacc.c:1646  */
    break;


#line 2159 "jive.tab.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (jiveEnv, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (jiveEnv, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, jiveEnv);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, jiveEnv);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (jiveEnv, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, jiveEnv);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, jiveEnv);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 550 "jive.y" /* yacc.c:1906  */


/*
q	Goal ::= MainClass ( ClassDeclaration )* <EOF>
q	MainClass ::= "class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" Statement "}" "}"
n	ClassDeclaration ::= "class" Identifier ( "extends" Identifier )? "{" ( VarDeclaration )* ( MethodDeclaration )* "}"
q	VarDeclaration ::= Type Identifier ";"
n	MethodDeclaration ::= "public" | “private” Type Identifier "(" ( Type Identifier ( "," Type Identifier )* )? ")" "{" ( VarDeclaration )*( Statement )* "return" Expression ";" "}"
n	Type ::= "int" "[" "]"
q	| "boolean"
q	| "int"
q	| Identifier
q	Statement ::= "{" ( Statement )* "}"
q	| "if" "(" Expression ")" Statement "else" Statement
q	| "while" "(" Expression ")" Statement
q	| "System.out.println" "(" Expression ")" ";"
q	| Identifier "=" Expression ";"
q	| Identifier "[" Expression "]" "=" Expression ";"
q	Expression ::= Expression ( "&&" | "<" | "+" | "-" | "*" | "%" | "||" ) Expression
q	| Expression "[" Expression "]"
q	| Expression "." "length"
q	| Expression "." Identifier "(" ( Expression ( "," Expression )* )? ")"
q	| <INTEGER_LITERAL>
q	| "true"
q	| "false"
q	| Identifier
q	| "this"
q	| "new" "int" "[" Expression "]"
q	| "new" Identifier "(" ")"
q	| "!" Expression 
q	| "(" Expression ")"
q	Identifier ::= <IDENTIFIER>
*/
