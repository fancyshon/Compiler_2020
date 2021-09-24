/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "compiler_hw2.y"

    #include "common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1;

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    char *type1;
    char *type2;

    char *temp1 = "a";
    char *temp2 = "a";

    char *t;
    bool undefined=false;

    typedef struct{
        char *name;
        char *type;
        int address;
        int lineno;
        int scopeLevel;
        char element_type[10];
        
    }symbol_table;

    typedef struct{
        symbol_table stable[30];
    }table;

    table final_table[30];

    int table_number = 0;

    int table_number_number[30] = {0};
    int address = 0;

    /* Symbol table function - you can add new function if needed. */
    static void create_symbol();
    static void insert_symbol();
    static bool lookup_symbol();
    static void dump_symbol();

    void yyerror (char const *s)
    {
        if(!strcmp(s, "ADD") || !strcmp(s, "SUB") || !strcmp(s, "ASSIGN")){
            if(!undefined){
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno + 1,  s, temp1, temp2);
                undefined = false;
            }
        }
        if(!strcmp(s, "REM")){
            if(strcmp(temp1, "a"))
                printf("error:%d: invalid operation: (operator %s not defined on %s)\n", yylineno + 1,  s, temp1);
            else
                printf("error:%d: invalid operation: (operator %s not defined on %s)\n", yylineno + 1,  s, temp2);
        }
        if(!strcmp(s, "AND")){
                printf("error:%d: invalid operation: (operator %s not defined on %s)\n", yylineno + 1,  s, temp1);
        }
        if(!strcmp(s, "OR")){
                printf("error:%d: invalid operation: (operator %s not defined on %s)\n", yylineno + 1,  s, temp2);
        }
        if(!strcmp(s, "condition")){
                printf("error:%d: non-bool (type %s) used as for condition\n", yylineno + 2,  temp1);
        }
        if(!strcmp(s, "redeclared")){
            int prev = 0 ,find= 0;
            for(int i = table_number; i >=0; i--){
                for(int j = 0; j < table_number_number[i]; j++){
                    if(!strcmp(final_table[i].stable[j].name, t) && final_table[i].stable[j].scopeLevel == table_number && !find) {
                        // Same name and scope level.
                        // printf("LINENO:%d\n",final_table[i].stable[j].lineno);
                        prev = final_table[i].stable[j].lineno+1;
                        find = 1;
                    }
                }
            }
            printf("error:%d: %s redeclared in this block. previous declaration at line %d\n", yylineno + 1, t, prev);
        }
        if(!strcmp(s, "undefined")){
            printf("error:%d: undefined: %s\n", yylineno + 1, t);
            undefined=true;
        }
        if(!strcmp(s, "ADD_ASSIGN")){
            if(!strcmp(t,"INT_LIT"))
                printf("error:%d: cannot assign to %s\n", yylineno + 1,"int");
        }
    }

#line 163 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VAR = 258,
    INT = 259,
    FLOAT = 260,
    BOOL = 261,
    STRING = 262,
    INC = 263,
    DEC = 264,
    GEQ = 265,
    LEQ = 266,
    EQL = 267,
    NEQ = 268,
    ADD_ASSIGN = 269,
    SUB_ASSIGN = 270,
    MUL_ASSIGN = 271,
    QUO_ASSIGN = 272,
    REM_ASSIGN = 273,
    OR = 274,
    AND = 275,
    NEWLINE = 276,
    PRINT = 277,
    PRINTLN = 278,
    IF = 279,
    ELSE = 280,
    FOR = 281,
    WHILE = 282,
    TRUE = 283,
    FALSE = 284,
    INT_LIT = 285,
    FLOAT_LIT = 286,
    STRING_LIT = 287,
    ID = 288
  };
#endif
/* Tokens.  */
#define VAR 258
#define INT 259
#define FLOAT 260
#define BOOL 261
#define STRING 262
#define INC 263
#define DEC 264
#define GEQ 265
#define LEQ 266
#define EQL 267
#define NEQ 268
#define ADD_ASSIGN 269
#define SUB_ASSIGN 270
#define MUL_ASSIGN 271
#define QUO_ASSIGN 272
#define REM_ASSIGN 273
#define OR 274
#define AND 275
#define NEWLINE 276
#define PRINT 277
#define PRINTLN 278
#define IF 279
#define ELSE 280
#define FOR 281
#define WHILE 282
#define TRUE 283
#define FALSE 284
#define INT_LIT 285
#define FLOAT_LIT 286
#define STRING_LIT 287
#define ID 288

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 100 "compiler_hw2.y"

    int i_val;
    float f_val;
    char *s_val;
    /* ... */

#line 288 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  64
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   136

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  138

#define YYUNDEFTOK  2
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,     2,     2,    40,     2,     2,
      42,    43,    38,    36,     2,    37,     2,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
      34,    47,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   134,   134,   138,   139,   143,   151,   155,   163,   167,
     168,   172,   182,   186,   196,   200,   201,   205,   206,   207,
     208,   209,   210,   214,   215,   219,   220,   221,   225,   226,
     227,   231,   232,   233,   237,   238,   258,   262,   263,   264,
     265,   266,   270,   274,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   302,   303,   304,   308,   325,   328,   332,
     382,   383,   384,   385,   386,   387,   391,   395,   396,   400,
     400,   404,   408,   409,   410,   414,   421,   431,   434,   438,
     448,   452,   456,   463,   473,   474,   478,   479,   480,   481,
     485
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VAR", "INT", "FLOAT", "BOOL", "STRING",
  "INC", "DEC", "GEQ", "LEQ", "EQL", "NEQ", "ADD_ASSIGN", "SUB_ASSIGN",
  "MUL_ASSIGN", "QUO_ASSIGN", "REM_ASSIGN", "OR", "AND", "NEWLINE",
  "PRINT", "PRINTLN", "IF", "ELSE", "FOR", "WHILE", "TRUE", "FALSE",
  "INT_LIT", "FLOAT_LIT", "STRING_LIT", "ID", "'<'", "'>'", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'!'", "'('", "')'", "'['", "']'", "';'", "'='",
  "'{'", "'}'", "$accept", "Program", "StatementList", "Expression",
  "Term1", "Term2", "Term3", "Term4", "UnaryExpr", "cmp_op", "add_op",
  "mul_op", "unary_op", "PrimaryExpr", "Operand", "Literal", "IndexExpr",
  "ConversionExpr", "Statement", "SimpleStmt", "DeclarationStmt",
  "AssignmentStmt", "assign_op", "ExpressionStmt", "IncDecStmt", "Block",
  "$@1", "IfStmt", "ElseStmt", "Condition", "WhileStmt", "ForStmt",
  "ForClause", "InitStmt", "PostStmt", "PrintStmt", "Type", "TypeName",
  "ArrayType", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,    60,    62,    43,    45,    42,    47,
      37,    33,    40,    41,    91,    93,    59,    61,   123,   125
};
# endif

#define YYPACT_NINF (-57)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-86)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      36,   -57,   -57,   -57,   -57,   -57,   -22,     7,    28,   -17,
      32,    28,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,    88,   -57,    22,   -57,    -3,    55,    13,    19,    -1,
     -57,    71,    37,   -57,   -57,   -57,   -57,    36,    34,    40,
     -57,   -57,   -57,    68,   -57,   -57,   -57,   -57,    44,    58,
     -57,    63,    71,    71,    71,    61,   -57,   -57,    71,    61,
     -15,   -25,   -57,    36,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,   -57,    71,   -57,    71,    71,   -57,   -57,   -57,   -57,
     -57,   -57,    71,   -57,   -57,    71,   -57,   -57,   -57,    71,
     -57,    71,   -57,   -57,   -57,   -57,   -57,    38,     8,    10,
      33,    -4,   -57,    67,    60,   -57,   -57,    70,    71,    62,
      55,   103,    13,    19,    -1,    -1,   -10,    71,    71,   -57,
     -57,   102,   -57,   -57,    61,    71,   103,   -57,   -57,     0,
     103,   -57,   -57,   -16,   -57,    71,   -57,   -57
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    86,    87,    89,    88,    52,     0,     0,     0,     0,
       0,     0,    39,    40,    37,    38,    41,    35,    28,    29,
      30,     0,    69,     0,     2,    66,     6,     8,    10,    12,
      14,     0,    15,    31,    34,    32,    33,     3,     0,     0,
      53,    54,    55,     0,    47,    48,    51,    49,     0,     0,
      84,    58,     0,     0,     0,     0,    72,    73,     0,     0,
       0,     0,    85,     0,     1,    67,    68,    61,    62,    63,
      64,    65,     0,    60,     0,     0,    22,    20,    17,    18,
      19,    21,     0,    23,    24,     0,    25,    26,    27,     0,
      16,     0,     4,    45,    44,    46,    50,    56,     0,     0,
       0,     0,    80,     0,     0,    77,    36,     0,     0,     0,
       5,    59,     7,     9,    11,    13,     0,     0,     0,    82,
      83,    75,    74,    71,     0,     0,    43,    70,    42,     0,
      57,    76,    78,     0,    90,     0,    81,    79
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -57,   -57,   -27,   -20,    54,    52,    46,    -2,   100,   -57,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -56,
     -57,   -57,   -57,   -57,   -57,    -9,   -57,   123,    35,   122,
     -57,   -57,   -57,   -57,   -57,   -57,   113,   -57,   114
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    82,
      85,    89,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    74,    41,    42,    43,    63,    44,    45,    55,
      46,    47,   103,   104,   137,    48,    49,    50,    51
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    60,   102,    72,    72,    65,    66,     8,   107,    72,
      92,    67,    68,    69,    70,    71,    72,   122,   108,    72,
      52,     9,    64,    76,    77,    78,    79,    72,   106,    72,
     135,    22,    98,    99,   100,   128,   109,    86,    87,    88,
       1,     2,     3,     4,    73,   134,   101,    80,    81,    53,
     105,   119,    72,   120,   111,    83,    84,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      54,   116,    18,    19,    58,    75,   121,    20,    21,   136,
      93,    91,   117,   114,    22,   118,    94,   115,   126,    95,
      96,    97,     1,     2,     3,     4,   -85,   129,   130,    12,
      13,    14,    15,    16,    17,   133,   125,    18,    19,    22,
     124,   127,    20,    21,   117,   132,    12,    13,    14,    15,
      16,    17,    72,   131,    18,    19,   110,   112,   113,    20,
      21,    90,    57,    59,    61,    62,   123
};

static const yytype_uint8 yycheck[] =
{
       9,    21,    58,    19,    19,     8,     9,    24,    33,    19,
      37,    14,    15,    16,    17,    18,    19,    21,    43,    19,
      42,    25,     0,    10,    11,    12,    13,    19,    43,    19,
      46,    48,    52,    53,    54,    45,    63,    38,    39,    40,
       4,     5,     6,     7,    47,    45,    55,    34,    35,    42,
      59,    43,    19,    43,    74,    36,    37,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      42,    91,    36,    37,    42,    20,    43,    41,    42,   135,
      46,    44,    44,    85,    48,    47,    46,    89,   108,    21,
      46,    33,     4,     5,     6,     7,    33,   117,   118,    28,
      29,    30,    31,    32,    33,   125,    46,    36,    37,    48,
      43,    49,    41,    42,    44,   124,    28,    29,    30,    31,
      32,    33,    19,    21,    36,    37,    72,    75,    82,    41,
      42,    31,     9,    11,    21,    21,   101
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    36,    37,
      41,    42,    48,    51,    52,    53,    54,    55,    56,    57,
      58,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    73,    74,    75,    77,    78,    80,    81,    85,    86,
      87,    88,    42,    42,    42,    79,    75,    77,    42,    79,
      53,    86,    88,    76,     0,     8,     9,    14,    15,    16,
      17,    18,    19,    47,    72,    20,    10,    11,    12,    13,
      34,    35,    59,    36,    37,    60,    38,    39,    40,    61,
      58,    44,    52,    46,    46,    21,    46,    33,    53,    53,
      53,    75,    69,    82,    83,    75,    43,    33,    43,    52,
      54,    53,    55,    56,    57,    57,    53,    44,    47,    43,
      43,    43,    21,    78,    43,    46,    53,    49,    45,    53,
      53,    21,    75,    53,    45,    46,    69,    84
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    59,    59,    59,
      59,    59,    59,    60,    60,    61,    61,    61,    62,    62,
      62,    63,    63,    63,    64,    64,    64,    65,    65,    65,
      65,    65,    66,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    69,    70,    70,    70,    71,
      72,    72,    72,    72,    72,    72,    73,    74,    74,    76,
      75,    77,    78,    78,    78,    79,    79,    80,    81,    82,
      83,    84,    85,    85,    86,    86,    87,    87,    87,    87,
      88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     4,     4,     2,     2,     2,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     2,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     0,
       4,     4,     2,     2,     1,     3,     4,     3,     5,     5,
       1,     1,     4,     4,     1,     1,     1,     1,     1,     1,
       5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 134 "compiler_hw2.y"
                    {dump_symbol();}
#line 1567 "y.tab.c"
    break;

  case 5:
#line 143 "compiler_hw2.y"
                          { 
        temp1 = "a";
        temp2 = "a";
        if(!strcmp((yyvsp[0].s_val), "I") || !strcmp((yyvsp[0].s_val), "INT_LIT") || !strcmp((yyvsp[0].s_val), "int"))temp2 = "int";
        if(!strcmp(temp2, "int"))yyerror("OR");
        printf("OR\n"); 
        (yyval.s_val) = strdup("bool"); 
    }
#line 1580 "y.tab.c"
    break;

  case 7:
#line 155 "compiler_hw2.y"
                      { 
        temp1 = "a";
        temp2 = "a";
        if(!strcmp((yyvsp[-2].s_val), "I") || !strcmp((yyvsp[-2].s_val), "INT_LIT") || !strcmp((yyvsp[-2].s_val), "int"))temp1 = "int";
        if(!strcmp(temp1, "int"))yyerror("AND");
        printf("AND\n"); 
        (yyval.s_val) = strdup("bool");
    }
#line 1593 "y.tab.c"
    break;

  case 9:
#line 167 "compiler_hw2.y"
                          { printf("%s\n", (yyvsp[-1].s_val)); (yyval.s_val) = strdup("bool");}
#line 1599 "y.tab.c"
    break;

  case 11:
#line 172 "compiler_hw2.y"
                         { 
        temp1 = "a";
        temp2 = "a";
        if(!strcmp((yyvsp[-2].s_val), "I") || !strcmp((yyvsp[-2].s_val), "INT_LIT") || !strcmp((yyvsp[-2].s_val), "int"))temp1 = "int";
        if(!strcmp((yyvsp[-2].s_val), "F") || !strcmp((yyvsp[-2].s_val), "FLOAT_LIT") || !strcmp((yyvsp[-2].s_val), "float"))temp1 = "float"; 
        if(!strcmp((yyvsp[0].s_val), "I") || !strcmp((yyvsp[0].s_val), "INT_LIT") || !strcmp((yyvsp[0].s_val), "int"))temp2 = "int";
        if(!strcmp((yyvsp[0].s_val), "F") || !strcmp((yyvsp[0].s_val), "FLOAT_LIT") || !strcmp((yyvsp[0].s_val), "float"))temp2 = "float"; 
        if(strcmp(temp1, temp2))yyerror((yyvsp[-1].s_val));
        printf("%s\n", (yyvsp[-1].s_val));
    }
#line 1614 "y.tab.c"
    break;

  case 13:
#line 186 "compiler_hw2.y"
                         { 
        if(!strcmp((yyvsp[-1].s_val), "REM")){
            temp1 = "a";
            temp2 = "a";
            if(!strcmp((yyvsp[-2].s_val), "F") || !strcmp((yyvsp[-2].s_val), "FLOAT_LIT") || !strcmp((yyvsp[-2].s_val), "float"))temp1 = "float";
            if(!strcmp((yyvsp[0].s_val), "F") || !strcmp((yyvsp[0].s_val), "FLOAT_LIT") || !strcmp((yyvsp[0].s_val), "float"))temp2 = "float";
            if(!strcmp(temp1, "float") || !strcmp(temp2, "float"))yyerror((yyvsp[-1].s_val));
        }
        printf("%s\n", (yyvsp[-1].s_val));
    }
#line 1629 "y.tab.c"
    break;

  case 16:
#line 201 "compiler_hw2.y"
                         { printf("%s\n", (yyvsp[-1].s_val));}
#line 1635 "y.tab.c"
    break;

  case 17:
#line 205 "compiler_hw2.y"
          { (yyval.s_val) = strdup("EQL");}
#line 1641 "y.tab.c"
    break;

  case 18:
#line 206 "compiler_hw2.y"
          { (yyval.s_val) = strdup("NEQ");}
#line 1647 "y.tab.c"
    break;

  case 19:
#line 207 "compiler_hw2.y"
          { (yyval.s_val) = strdup("LSS");}
#line 1653 "y.tab.c"
    break;

  case 20:
#line 208 "compiler_hw2.y"
          { (yyval.s_val) = strdup("LEQ");}
#line 1659 "y.tab.c"
    break;

  case 21:
#line 209 "compiler_hw2.y"
          { (yyval.s_val) = strdup("GTR");}
#line 1665 "y.tab.c"
    break;

  case 22:
#line 210 "compiler_hw2.y"
          { (yyval.s_val) = strdup("GEQ");}
#line 1671 "y.tab.c"
    break;

  case 23:
#line 214 "compiler_hw2.y"
          { (yyval.s_val) = strdup("ADD");}
#line 1677 "y.tab.c"
    break;

  case 24:
#line 215 "compiler_hw2.y"
           { (yyval.s_val) = strdup("SUB");}
#line 1683 "y.tab.c"
    break;

  case 25:
#line 219 "compiler_hw2.y"
          { (yyval.s_val) = strdup("MUL");}
#line 1689 "y.tab.c"
    break;

  case 26:
#line 220 "compiler_hw2.y"
           { (yyval.s_val) = strdup("QUO");}
#line 1695 "y.tab.c"
    break;

  case 27:
#line 221 "compiler_hw2.y"
          { (yyval.s_val) = strdup("REM");}
#line 1701 "y.tab.c"
    break;

  case 28:
#line 225 "compiler_hw2.y"
          { (yyval.s_val) = strdup("POS");}
#line 1707 "y.tab.c"
    break;

  case 29:
#line 226 "compiler_hw2.y"
          { (yyval.s_val) = strdup("NEG");}
#line 1713 "y.tab.c"
    break;

  case 30:
#line 227 "compiler_hw2.y"
          { (yyval.s_val) = strdup("NOT");}
#line 1719 "y.tab.c"
    break;

  case 35:
#line 238 "compiler_hw2.y"
         {   
        lookup_symbol((yyvsp[0].s_val));
        int find = 0;
        for(int i = table_number; i >=0; i--){
            for(int j = 0; j < table_number_number[i]; j++){
                if(!strcmp(final_table[i].stable[j].name, (yyvsp[0].s_val)) && !find){
                    if(!strcmp(final_table[i].stable[j].type, "int"))(yyval.s_val) = "I";
                    if(!strcmp(final_table[i].stable[j].type, "float"))(yyval.s_val) = "F";
                    if(!strcmp(final_table[i].stable[j].type, "bool"))(yyval.s_val) = "bool";
                    if(!strcmp(final_table[i].stable[j].type, "string"))(yyval.s_val) = "string";
                    if(!strcmp(final_table[i].stable[j].type, "array"))(yyval.s_val) = final_table[i].stable[j].element_type;
                    find = 1;
                }
            }
        }
        if(find==0){
            t=(yyvsp[0].s_val);
            yyerror("undefined");
        }
    }
#line 1744 "y.tab.c"
    break;

  case 37:
#line 262 "compiler_hw2.y"
              { printf("INT_LIT %d\n", (yyvsp[0].i_val));  (yyval.s_val) = "INT_LIT"; }
#line 1750 "y.tab.c"
    break;

  case 38:
#line 263 "compiler_hw2.y"
                { printf("FLOAT_LIT %f\n", (yyvsp[0].f_val));  (yyval.s_val) = "FLOAT_LIT"; }
#line 1756 "y.tab.c"
    break;

  case 39:
#line 264 "compiler_hw2.y"
           { printf("TRUE\n");  (yyval.s_val) = "TRUE";}
#line 1762 "y.tab.c"
    break;

  case 40:
#line 265 "compiler_hw2.y"
            { printf("FALSE\n");  (yyval.s_val) = "FALSE";}
#line 1768 "y.tab.c"
    break;

  case 41:
#line 266 "compiler_hw2.y"
                 { printf("STRING_LIT %s\n", (yyvsp[0].s_val)); (yyval.s_val) = "string";}
#line 1774 "y.tab.c"
    break;

  case 43:
#line 274 "compiler_hw2.y"
                              {
        char temp1;
        char temp2;
        if(!strcmp((yyvsp[-2].s_val), "I") || !strcmp((yyvsp[-2].s_val), "INT_LIT") || !strcmp((yyvsp[-2].s_val), "int"))temp1 = 'I';
        if(!strcmp((yyvsp[-2].s_val), "F") || !strcmp((yyvsp[-2].s_val), "FLOAT_LIT") || !strcmp((yyvsp[-2].s_val), "float"))temp1 = 'F';
        if(!strcmp((yyvsp[0].s_val), "I") || !strcmp((yyvsp[0].s_val), "INT_LIT") || !strcmp((yyvsp[0].s_val), "int"))temp2 = 'I';
        if(!strcmp((yyvsp[0].s_val), "F") || !strcmp((yyvsp[0].s_val), "FLOAT_LIT") || !strcmp((yyvsp[0].s_val), "float"))temp2 = 'F';
        if(temp1=='I' && temp2=='F')(yyval.s_val) = "float";
        if(temp1=='I' && temp2=='F')(yyval.s_val) = "int";
        printf("%c to %c\n", temp2, temp1);                            
    }
#line 1790 "y.tab.c"
    break;

  case 56:
#line 308 "compiler_hw2.y"
              {
        bool exist = false;

        for(int i = table_number; i >=0; i--){
            for(int j = 0; j < table_number_number[i]; j++){
                if(!strcmp(final_table[i].stable[j].name, (yyvsp[0].s_val)) && final_table[i].stable[j].scopeLevel == table_number && !exist){
                    exist = true;
                }
            }
        }
        if(!exist)
            insert_symbol((yyvsp[0].s_val), (yyvsp[-1].s_val) );
        else {
            t = (yyvsp[0].s_val);
            yyerror("redeclared");
        }
    }
#line 1812 "y.tab.c"
    break;

  case 57:
#line 325 "compiler_hw2.y"
                             { 
        insert_symbol((yyvsp[-2].s_val), (yyvsp[-3].s_val));    
    }
#line 1820 "y.tab.c"
    break;

  case 59:
#line 332 "compiler_hw2.y"
                                       {
        temp1 = "a";
        temp2 = "a";
        int find = 0;
        if(!strcmp((yyvsp[-2].s_val), "I") || !strcmp((yyvsp[-2].s_val), "INT_LIT") || !strcmp((yyvsp[-2].s_val), "int"))temp1 = "int";
        if(!strcmp((yyvsp[-2].s_val), "F") || !strcmp((yyvsp[-2].s_val), "FLOAT_LIT") || !strcmp((yyvsp[-2].s_val), "float"))temp1 = "float"; 
        if(!strcmp((yyvsp[0].s_val), "I") || !strcmp((yyvsp[0].s_val), "INT_LIT") || !strcmp((yyvsp[0].s_val), "int"))temp2 = "int";
        if(!strcmp((yyvsp[0].s_val), "F") || !strcmp((yyvsp[0].s_val), "FLOAT_LIT") || !strcmp((yyvsp[0].s_val), "float"))temp2 = "float"; 

        if(!strcmp(temp1, "a")){
            for(int i = table_number; i >=0; i--){
                for(int j = 0; j < table_number_number[i]; j++){
                    if(!strcmp(final_table[i].stable[j].name, (yyvsp[0].s_val)) && !find){
                        if(!strcmp(final_table[i].stable[j].type, "int"))temp1 = "int";
                        if(!strcmp(final_table[i].stable[j].type, "float"))temp1 = "float";
                        if(!strcmp(final_table[i].stable[j].type, "bool"))temp1 = "bool";
                        if(!strcmp(final_table[i].stable[j].type, "string"))temp1 = "string";
                        if(!strcmp(final_table[i].stable[j].type, "array"))temp1 = final_table[i].stable[j].element_type;
                        find = 1;
                    }
                }
            }
        }

        if(!strcmp(temp2, "a")){
            for(int i = table_number; i >=0; i--){
                for(int j = 0; j < table_number_number[i]; j++){
                    if(!strcmp(final_table[i].stable[j].name, (yyvsp[0].s_val)) && !find){
                        if(!strcmp(final_table[i].stable[j].type, "int"))temp2 = "int";
                        if(!strcmp(final_table[i].stable[j].type, "float"))temp2 = "float";
                        if(!strcmp(final_table[i].stable[j].type, "bool"))temp2 = "bool";
                        if(!strcmp(final_table[i].stable[j].type, "string"))temp2 = "string";
                        if(!strcmp(final_table[i].stable[j].type, "array"))temp2 = final_table[i].stable[j].element_type;
                        find = 1;
                    }
                }
            }
        }

        if(strcmp(temp1, temp2))yyerror((yyvsp[-1].s_val));
        if(!strcmp((yyvsp[-1].s_val),"ADD_ASSIGN") && !strcmp((yyvsp[-2].s_val),"INT_LIT")){
            t=(yyvsp[-2].s_val);
            yyerror((yyvsp[-1].s_val));
        }
        printf("%s\n", (yyvsp[-1].s_val));
    
    }
#line 1872 "y.tab.c"
    break;

  case 60:
#line 382 "compiler_hw2.y"
          { (yyval.s_val) = strdup("ASSIGN"); }
#line 1878 "y.tab.c"
    break;

  case 61:
#line 383 "compiler_hw2.y"
                 { (yyval.s_val) = strdup("ADD_ASSIGN"); }
#line 1884 "y.tab.c"
    break;

  case 62:
#line 384 "compiler_hw2.y"
                 { (yyval.s_val) = strdup("SUB_ASSIGN"); }
#line 1890 "y.tab.c"
    break;

  case 63:
#line 385 "compiler_hw2.y"
                 { (yyval.s_val) = strdup("MUL_ASSIGN"); }
#line 1896 "y.tab.c"
    break;

  case 64:
#line 386 "compiler_hw2.y"
                 { (yyval.s_val) = strdup("QUO_ASSIGN"); }
#line 1902 "y.tab.c"
    break;

  case 65:
#line 387 "compiler_hw2.y"
                 { (yyval.s_val) = strdup("REM_ASSIGN"); }
#line 1908 "y.tab.c"
    break;

  case 67:
#line 395 "compiler_hw2.y"
                     { printf("INC\n");}
#line 1914 "y.tab.c"
    break;

  case 68:
#line 396 "compiler_hw2.y"
                     { printf("DEC\n");}
#line 1920 "y.tab.c"
    break;

  case 69:
#line 400 "compiler_hw2.y"
         { create_symbol();}
#line 1926 "y.tab.c"
    break;

  case 70:
#line 400 "compiler_hw2.y"
                                               {dump_symbol();}
#line 1932 "y.tab.c"
    break;

  case 75:
#line 414 "compiler_hw2.y"
                         {
        temp1 = (yyvsp[-1].s_val);
        temp2 = "a";     
        if(!strcmp((yyvsp[-1].s_val), "I") || !strcmp((yyvsp[-1].s_val), "INT_LIT") || !strcmp((yyvsp[-1].s_val), "int"))temp1 = "int";
        if(!strcmp((yyvsp[-1].s_val), "F") || !strcmp((yyvsp[-1].s_val), "FLOAT_LIT") || !strcmp((yyvsp[-1].s_val), "float"))temp1 = "float"; 
        if(strcmp((yyvsp[-1].s_val), "bool"))yyerror("condition");
    }
#line 1944 "y.tab.c"
    break;

  case 76:
#line 421 "compiler_hw2.y"
                                 {
        temp1 = (yyvsp[-2].s_val);
        temp2 = "a";     
        if(!strcmp((yyvsp[-2].s_val), "I") || !strcmp((yyvsp[-2].s_val), "INT_LIT") || !strcmp((yyvsp[-2].s_val), "int"))temp1 = "int";
        if(!strcmp((yyvsp[-2].s_val), "F") || !strcmp((yyvsp[-2].s_val), "FLOAT_LIT") || !strcmp((yyvsp[-2].s_val), "float"))temp1 = "float"; 
        if(strcmp((yyvsp[-2].s_val), "bool"))yyerror("condition");
    }
#line 1956 "y.tab.c"
    break;

  case 79:
#line 438 "compiler_hw2.y"
                                           {
        temp1 = (yyvsp[-2].s_val);
        temp2 = "a";     
        if(!strcmp((yyvsp[-2].s_val), "I") || !strcmp((yyvsp[-2].s_val), "INT_LIT") || !strcmp((yyvsp[-2].s_val), "int"))temp1 = "int";
        if(!strcmp((yyvsp[-2].s_val), "F") || !strcmp((yyvsp[-2].s_val), "FLOAT_LIT") || !strcmp((yyvsp[-2].s_val), "float"))temp1 = "float"; 
        if(strcmp((yyvsp[-2].s_val), "bool"))yyerror("condition");
    }
#line 1968 "y.tab.c"
    break;

  case 82:
#line 456 "compiler_hw2.y"
                               { 
        char *temp;
        temp = (yyvsp[-1].s_val);
        if(!strcmp((yyvsp[-1].s_val), "I") || !strcmp((yyvsp[-1].s_val), "INT_LIT"))temp = "int";
        if(!strcmp((yyvsp[-1].s_val), "F") || !strcmp((yyvsp[-1].s_val), "FLOAT_LIT"))temp = "float"; 
        printf("PRINT %s\n", temp);
    }
#line 1980 "y.tab.c"
    break;

  case 83:
#line 463 "compiler_hw2.y"
                                 { 
        char *temp;
        temp = (yyvsp[-1].s_val);
        if(!strcmp((yyvsp[-1].s_val), "I") || !strcmp((yyvsp[-1].s_val), "INT_LIT"))temp = "int";
        if(!strcmp((yyvsp[-1].s_val), "F") || !strcmp((yyvsp[-1].s_val), "FLOAT_LIT"))temp = "float"; 
        printf("PRINTLN %s\n", temp);
    }
#line 1992 "y.tab.c"
    break;

  case 86:
#line 478 "compiler_hw2.y"
          { (yyval.s_val) = strdup("int");}
#line 1998 "y.tab.c"
    break;

  case 87:
#line 479 "compiler_hw2.y"
            { (yyval.s_val) = strdup("float");}
#line 2004 "y.tab.c"
    break;

  case 88:
#line 480 "compiler_hw2.y"
             { (yyval.s_val) = strdup("string");}
#line 2010 "y.tab.c"
    break;

  case 89:
#line 481 "compiler_hw2.y"
           { (yyval.s_val) = strdup("bool");}
#line 2016 "y.tab.c"
    break;

  case 90:
#line 485 "compiler_hw2.y"
                                 { 
        (yyval.s_val) = strdup("array"); 
        insert_symbol((yyvsp[-3].s_val), "array");   
        strcpy(final_table[table_number].stable[table_number_number[table_number]-1].element_type, (yyvsp[-4].s_val)); 
    }
#line 2026 "y.tab.c"
    break;


#line 2030 "y.tab.c"

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
      yyerror (YY_("syntax error"));
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
#line 492 "compiler_hw2.y"


/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    yylineno = 0;
    yyparse();

	printf("Total lines: %d\n", yylineno);
    fclose(yyin);
    return 0;
}

static void create_symbol() {
    table_number++;
}

static void insert_symbol(char *id,char *type) {
    printf("> Insert {%s} into symbol table (scope level: %d)\n", id, table_number);
    final_table[table_number].stable[table_number_number[table_number]].name = id;
    final_table[table_number].stable[table_number_number[table_number]].type = type;
    final_table[table_number].stable[table_number_number[table_number]].address = address;
    final_table[table_number].stable[table_number_number[table_number]].lineno = yylineno;
    final_table[table_number].stable[table_number_number[table_number]].scopeLevel = table_number;
    if(strcmp(type, "array")){
        strcpy(final_table[table_number].stable[table_number_number[table_number]].element_type, "-");
    }
    table_number_number[table_number]++;
    address++;
}

static bool lookup_symbol( char *name) {
    int find = 0;
    for(int i = table_number; i >=0; i--){
        for(int j = 0; j < table_number_number[i]; j++){
            if(!strcmp(final_table[i].stable[j].name, name) && !find){
                printf("IDENT (name=%s, address=%d)\n", name, final_table[i].stable[j].address);
                find = 1;
            }
        }
    }
    if(find == 0)
        return false;
    else
        return true;
}

static void dump_symbol() {
    printf("> Dump symbol table (scope level: %d)\n", table_number);
    printf("%-10s%-10s%-10s%-10s%-10s%s\n",  "Index", "Name", "Type", "Address", "Lineno", "Element type");
    for(int i = 0; i < table_number_number[table_number]; i++){
        printf("%-10d%-10s%-10s%-10d%-10d%s\n",
            i, 
            final_table[table_number].stable[i].name, 
            final_table[table_number].stable[i].type, 
            final_table[table_number].stable[i].address, 
            final_table[table_number].stable[i].lineno+1, 
            final_table[table_number].stable[i].element_type
            );   
    }
    table_number_number[table_number] = 0;
    table_number--;
}
