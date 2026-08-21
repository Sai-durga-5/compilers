/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "a2.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>

#include "symbol_table.hh"
#include "ast.hh"

using namespace std;

extern int yylineno;
extern FILE *yyin;

int yylex(void);
int yyparse(void);
int yyerror(const char *s);

extern FILE *fp;
extern int print_tokens;

SymbolTable symtab;
Ast* ast_root = nullptr;

#line 98 "y.tab.c"

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

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INTEGER = 258,                 /* INTEGER  */
    FLOAT = 259,                   /* FLOAT  */
    STRING = 260,                  /* STRING  */
    VOID = 261,                    /* VOID  */
    BOOL = 262,                    /* BOOL  */
    READ = 263,                    /* READ  */
    PRINT = 264,                   /* PRINT  */
    PLUS = 265,                    /* PLUS  */
    MINUS = 266,                   /* MINUS  */
    MULT = 267,                    /* MULT  */
    DIV = 268,                     /* DIV  */
    LEFT_ROUND_BRACKET = 269,      /* LEFT_ROUND_BRACKET  */
    RIGHT_ROUND_BRACKET = 270,     /* RIGHT_ROUND_BRACKET  */
    LEFT_CURLY_BRACKET = 271,      /* LEFT_CURLY_BRACKET  */
    RIGHT_CURLY_BRACKET = 272,     /* RIGHT_CURLY_BRACKET  */
    ASSIGN_OP = 273,               /* ASSIGN_OP  */
    SEMICOLON = 274,               /* SEMICOLON  */
    COMMA = 275,                   /* COMMA  */
    LT = 276,                      /* LT  */
    LE = 277,                      /* LE  */
    GT = 278,                      /* GT  */
    GE = 279,                      /* GE  */
    EQ = 280,                      /* EQ  */
    NE = 281,                      /* NE  */
    NOT = 282,                     /* NOT  */
    AND = 283,                     /* AND  */
    OR = 284,                      /* OR  */
    QUESTION_MARK = 285,           /* QUESTION_MARK  */
    COLON = 286,                   /* COLON  */
    INT_VAL = 287,                 /* INT_VAL  */
    FLOAT_VAL = 288,               /* FLOAT_VAL  */
    STR_CONST = 289,               /* STR_CONST  */
    NAME = 290,                    /* NAME  */
    UMINUS = 291                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INTEGER 258
#define FLOAT 259
#define STRING 260
#define VOID 261
#define BOOL 262
#define READ 263
#define PRINT 264
#define PLUS 265
#define MINUS 266
#define MULT 267
#define DIV 268
#define LEFT_ROUND_BRACKET 269
#define RIGHT_ROUND_BRACKET 270
#define LEFT_CURLY_BRACKET 271
#define RIGHT_CURLY_BRACKET 272
#define ASSIGN_OP 273
#define SEMICOLON 274
#define COMMA 275
#define LT 276
#define LE 277
#define GT 278
#define GE 279
#define EQ 280
#define NE 281
#define NOT 282
#define AND 283
#define OR 284
#define QUESTION_MARK 285
#define COLON 286
#define INT_VAL 287
#define FLOAT_VAL 288
#define STR_CONST 289
#define NAME 290
#define UMINUS 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 31 "a2.y"

    int int_val;
    float float_val;
    char* string_val;
    std::vector<char*>* id_list;
    Ast *ast;
    std::vector<Ast*>* ast_list;

#line 232 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER = 3,                    /* INTEGER  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_VOID = 6,                       /* VOID  */
  YYSYMBOL_BOOL = 7,                       /* BOOL  */
  YYSYMBOL_READ = 8,                       /* READ  */
  YYSYMBOL_PRINT = 9,                      /* PRINT  */
  YYSYMBOL_PLUS = 10,                      /* PLUS  */
  YYSYMBOL_MINUS = 11,                     /* MINUS  */
  YYSYMBOL_MULT = 12,                      /* MULT  */
  YYSYMBOL_DIV = 13,                       /* DIV  */
  YYSYMBOL_LEFT_ROUND_BRACKET = 14,        /* LEFT_ROUND_BRACKET  */
  YYSYMBOL_RIGHT_ROUND_BRACKET = 15,       /* RIGHT_ROUND_BRACKET  */
  YYSYMBOL_LEFT_CURLY_BRACKET = 16,        /* LEFT_CURLY_BRACKET  */
  YYSYMBOL_RIGHT_CURLY_BRACKET = 17,       /* RIGHT_CURLY_BRACKET  */
  YYSYMBOL_ASSIGN_OP = 18,                 /* ASSIGN_OP  */
  YYSYMBOL_SEMICOLON = 19,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 20,                     /* COMMA  */
  YYSYMBOL_LT = 21,                        /* LT  */
  YYSYMBOL_LE = 22,                        /* LE  */
  YYSYMBOL_GT = 23,                        /* GT  */
  YYSYMBOL_GE = 24,                        /* GE  */
  YYSYMBOL_EQ = 25,                        /* EQ  */
  YYSYMBOL_NE = 26,                        /* NE  */
  YYSYMBOL_NOT = 27,                       /* NOT  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_QUESTION_MARK = 30,             /* QUESTION_MARK  */
  YYSYMBOL_COLON = 31,                     /* COLON  */
  YYSYMBOL_INT_VAL = 32,                   /* INT_VAL  */
  YYSYMBOL_FLOAT_VAL = 33,                 /* FLOAT_VAL  */
  YYSYMBOL_STR_CONST = 34,                 /* STR_CONST  */
  YYSYMBOL_NAME = 35,                      /* NAME  */
  YYSYMBOL_UMINUS = 36,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_program = 38,                   /* program  */
  YYSYMBOL_global_decl_statement_list = 39, /* global_decl_statement_list  */
  YYSYMBOL_func_decl = 40,                 /* func_decl  */
  YYSYMBOL_main_function = 41,             /* main_function  */
  YYSYMBOL_formal_param_list = 42,         /* formal_param_list  */
  YYSYMBOL_formal_param = 43,              /* formal_param  */
  YYSYMBOL_optional_local_var_decl_stmt_list = 44, /* optional_local_var_decl_stmt_list  */
  YYSYMBOL_var_decl_stmt_list = 45,        /* var_decl_stmt_list  */
  YYSYMBOL_var_decl_stmt = 46,             /* var_decl_stmt  */
  YYSYMBOL_var_decl_item_list = 47,        /* var_decl_item_list  */
  YYSYMBOL_named_type = 48,                /* named_type  */
  YYSYMBOL_statement_list = 49,            /* statement_list  */
  YYSYMBOL_statement = 50,                 /* statement  */
  YYSYMBOL_assignment_statement = 51,      /* assignment_statement  */
  YYSYMBOL_print_statement = 52,           /* print_statement  */
  YYSYMBOL_read_statement = 53,            /* read_statement  */
  YYSYMBOL_expression = 54,                /* expression  */
  YYSYMBOL_rel_expression = 55             /* rel_expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   191

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  99

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    90,    90,    91,    95,    96,    97,    98,   108,   115,
     125,   137,   156,   157,   161,   175,   176,   180,   181,   185,
     198,   203,   215,   216,   217,   218,   219,   227,   228,   232,
     233,   234,   238,   253,   260,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   299,   300,   301,
     305,   306,   307,   308,   309,   310
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INTEGER", "FLOAT",
  "STRING", "VOID", "BOOL", "READ", "PRINT", "PLUS", "MINUS", "MULT",
  "DIV", "LEFT_ROUND_BRACKET", "RIGHT_ROUND_BRACKET", "LEFT_CURLY_BRACKET",
  "RIGHT_CURLY_BRACKET", "ASSIGN_OP", "SEMICOLON", "COMMA", "LT", "LE",
  "GT", "GE", "EQ", "NE", "NOT", "AND", "OR", "QUESTION_MARK", "COLON",
  "INT_VAL", "FLOAT_VAL", "STR_CONST", "NAME", "UMINUS", "$accept",
  "program", "global_decl_statement_list", "func_decl", "main_function",
  "formal_param_list", "formal_param", "optional_local_var_decl_stmt_list",
  "var_decl_stmt_list", "var_decl_stmt", "var_decl_item_list",
  "named_type", "statement_list", "statement", "assignment_statement",
  "print_statement", "read_statement", "expression", "rel_expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-53)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      88,   -53,   -53,   -53,   -53,   -53,    14,    88,   -53,   -53,
     -53,     9,   -53,   -53,   -53,   -53,    32,   -12,    67,   -53,
      18,    13,    -9,   -53,    22,   -53,    88,   -53,    39,    88,
     -53,   -53,    88,   -53,    24,    88,   -53,   -53,    -4,   -53,
     -53,   -53,    34,    29,   -53,    57,   -53,   -53,   -53,   -53,
      25,    78,    29,    29,    29,   -53,   -53,   -53,   -53,    77,
     -53,    29,   -53,   -53,   -53,    98,   -53,    29,    29,    29,
      29,   -53,    29,    29,    29,    29,    29,    29,    29,    29,
      29,   119,   -53,   121,   121,   -53,   -53,   104,   104,   104,
     104,   167,   167,   161,    26,    55,   -53,    29,   140
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    22,    23,    25,    26,    24,     0,     0,     7,     3,
       6,     0,     1,     5,     2,     4,    21,     0,     0,    19,
       0,     0,     0,    13,     0,    20,    16,     9,     0,     0,
      14,    28,    15,    18,     0,    16,     8,    12,     0,    17,
      21,    28,     0,     0,    11,     0,    27,    29,    30,    31,
       0,     0,     0,     0,     0,    47,    48,    49,    46,     0,
      45,     0,    10,    34,    39,     0,    44,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    40,    35,    36,    37,    38,    50,    51,    52,
      53,    54,    55,    42,    43,     0,    32,     0,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -53,   -53,   -53,    97,   105,   -53,    89,    90,   -53,     3,
     -53,    12,    94,   -53,   -53,   -53,   -53,   -52,   -53
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    22,    23,    31,    32,    33,
      17,    34,    38,    46,    47,    48,    49,    59,    60
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      64,    65,    66,    10,    42,    43,    28,    19,    20,    81,
      15,    29,    11,    44,    12,    83,    84,    85,    86,    11,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    26,
      24,    45,    27,    42,    43,    39,    67,    68,    69,    70,
      52,    24,    62,    53,    16,    98,    18,    72,    73,    74,
      75,    76,    77,    25,    78,    35,    54,    30,    36,    40,
      45,    55,    56,    57,    58,    67,    68,    69,    70,    51,
       1,     2,     3,     4,     5,    61,    72,    73,    74,    75,
      76,    77,    21,    78,    79,    80,    97,    67,    68,    69,
      70,     1,     2,     3,     4,     5,    71,    63,    72,    73,
      74,    75,    76,    77,    13,    78,    79,    80,    67,    68,
      69,    70,    14,    82,    67,    68,    69,    70,    37,    72,
      73,    74,    75,    76,    77,    41,    78,    79,    80,    67,
      68,    69,    70,    69,    70,    50,     0,     0,    96,     0,
      72,    73,    74,    75,    76,    77,     0,    78,    79,    80,
      67,    68,    69,    70,     0,     0,     0,     0,     0,     0,
       0,    72,    73,    74,    75,    76,    77,     0,    78,    79,
      80,    67,    68,    69,    70,     0,     0,    67,    68,    69,
      70,     0,    72,    73,    74,    75,    76,    77,    72,    73,
      74,    75
};

static const yytype_int8 yycheck[] =
{
      52,    53,    54,     0,     8,     9,    15,    19,    20,    61,
       7,    20,     0,    17,     0,    67,    68,    69,    70,     7,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    16,
      18,    35,    19,     8,     9,    32,    10,    11,    12,    13,
      11,    29,    17,    14,    35,    97,    14,    21,    22,    23,
      24,    25,    26,    35,    28,    16,    27,    35,    19,    35,
      35,    32,    33,    34,    35,    10,    11,    12,    13,    35,
       3,     4,     5,     6,     7,    18,    21,    22,    23,    24,
      25,    26,    15,    28,    29,    30,    31,    10,    11,    12,
      13,     3,     4,     5,     6,     7,    19,    19,    21,    22,
      23,    24,    25,    26,     7,    28,    29,    30,    10,    11,
      12,    13,     7,    15,    10,    11,    12,    13,    29,    21,
      22,    23,    24,    25,    26,    35,    28,    29,    30,    10,
      11,    12,    13,    12,    13,    41,    -1,    -1,    19,    -1,
      21,    22,    23,    24,    25,    26,    -1,    28,    29,    30,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    10,    11,    12,    13,    -1,    -1,    10,    11,    12,
      13,    -1,    21,    22,    23,    24,    25,    26,    21,    22,
      23,    24
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    38,    39,    40,    41,
      46,    48,     0,    40,    41,    46,    35,    47,    14,    19,
      20,    15,    42,    43,    48,    35,    16,    19,    15,    20,
      35,    44,    45,    46,    48,    16,    19,    43,    49,    46,
      35,    44,     8,     9,    17,    35,    50,    51,    52,    53,
      49,    35,    11,    14,    27,    32,    33,    34,    35,    54,
      55,    18,    17,    19,    54,    54,    54,    10,    11,    12,
      13,    19,    21,    22,    23,    24,    25,    26,    28,    29,
      30,    54,    15,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    19,    31,    54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    39,    39,    39,    39,    40,    40,
      41,    41,    42,    42,    43,    44,    44,    45,    45,    46,
      47,    47,    48,    48,    48,    48,    48,    49,    49,    50,
      50,    50,    51,    52,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    55,    55,    55
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     2,     2,     1,     1,     6,     5,
       9,     8,     3,     1,     2,     1,     0,     2,     1,     3,
       3,     1,     1,     1,     1,     1,     1,     2,     0,     1,
       1,     1,     4,     3,     3,     3,     3,     3,     3,     2,
       3,     5,     3,     3,     2,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 8: /* func_decl: named_type NAME LEFT_ROUND_BRACKET formal_param_list RIGHT_ROUND_BRACKET SEMICOLON  */
#line 109 "a2.y"
      {
          if (!symtab.insert((yyvsp[-4].string_val), (yyvsp[-5].string_val), SymbolKind::FUNCTION, yylineno)) {
              printf("Semantic Error: redeclaration of function '%s' at line %d\n",
                     (yyvsp[-4].string_val), yylineno);
          }
      }
#line 1352 "y.tab.c"
    break;

  case 9: /* func_decl: named_type NAME LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET SEMICOLON  */
#line 116 "a2.y"
      {
          if (!symtab.insert((yyvsp[-3].string_val), (yyvsp[-4].string_val), SymbolKind::FUNCTION, yylineno)) {
              printf("Semantic Error: redeclaration of function '%s' at line %d\n",
                     (yyvsp[-3].string_val), yylineno);
          }
      }
#line 1363 "y.tab.c"
    break;

  case 10: /* main_function: named_type NAME LEFT_ROUND_BRACKET formal_param_list RIGHT_ROUND_BRACKET LEFT_CURLY_BRACKET optional_local_var_decl_stmt_list statement_list RIGHT_CURLY_BRACKET  */
#line 127 "a2.y"
      {
          if (!symtab.insert((yyvsp[-7].string_val), (yyvsp[-8].string_val), SymbolKind::FUNCTION, yylineno)) {
              printf("Semantic Error: redeclaration of function '%s' at line %d\n",
                     (yyvsp[-7].string_val), yylineno);
          }

          if (strcmp((yyvsp[-7].string_val), "main") == 0) {
              ast_root = new Sequence_Ast(*(yyvsp[-1].ast_list));
          }
      }
#line 1378 "y.tab.c"
    break;

  case 11: /* main_function: named_type NAME LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET LEFT_CURLY_BRACKET optional_local_var_decl_stmt_list statement_list RIGHT_CURLY_BRACKET  */
#line 139 "a2.y"
      {
          if (!symtab.insert((yyvsp[-6].string_val), (yyvsp[-7].string_val), SymbolKind::FUNCTION, yylineno)) {
              printf("Semantic Error: redeclaration of function '%s' at line %d\n",
                     (yyvsp[-6].string_val), yylineno);
          }

          if (strcmp((yyvsp[-6].string_val), "main") == 0) {
              ast_root = new Sequence_Ast(*(yyvsp[-1].ast_list));
          }
      }
#line 1393 "y.tab.c"
    break;

  case 14: /* formal_param: named_type NAME  */
#line 162 "a2.y"
      {
          if (!symtab.insert((yyvsp[0].string_val), (yyvsp[-1].string_val), SymbolKind::PARAMETER, yylineno)) {
              printf("Semantic Error: redeclaration of parameter '%s' at line %d\n",
                     (yyvsp[0].string_val), yylineno);
          }
      }
#line 1404 "y.tab.c"
    break;

  case 19: /* var_decl_stmt: named_type var_decl_item_list SEMICOLON  */
#line 186 "a2.y"
      {
          for (auto name : *(yyvsp[-1].id_list)) {
              if (!symtab.insert(name, (yyvsp[-2].string_val), SymbolKind::VARIABLE, yylineno)) {
                  printf("Semantic Error: redeclaration of variable '%s' at line %d\n",
                         name, yylineno);
              }
          }
          delete (yyvsp[-1].id_list);
      }
#line 1418 "y.tab.c"
    break;

  case 20: /* var_decl_item_list: var_decl_item_list COMMA NAME  */
#line 199 "a2.y"
      {
          (yyvsp[-2].id_list)->push_back((yyvsp[0].string_val));
          (yyval.id_list) = (yyvsp[-2].id_list);
      }
#line 1427 "y.tab.c"
    break;

  case 21: /* var_decl_item_list: NAME  */
#line 204 "a2.y"
      {
          (yyval.id_list) = new vector<char*>();
          (yyval.id_list)->push_back((yyvsp[0].string_val));
      }
#line 1436 "y.tab.c"
    break;

  case 22: /* named_type: INTEGER  */
#line 215 "a2.y"
              { (yyval.string_val) = strdup("int"); }
#line 1442 "y.tab.c"
    break;

  case 23: /* named_type: FLOAT  */
#line 216 "a2.y"
              { (yyval.string_val) = strdup("float"); }
#line 1448 "y.tab.c"
    break;

  case 24: /* named_type: BOOL  */
#line 217 "a2.y"
              { (yyval.string_val) = strdup("bool"); }
#line 1454 "y.tab.c"
    break;

  case 25: /* named_type: STRING  */
#line 218 "a2.y"
              { (yyval.string_val) = strdup("string"); }
#line 1460 "y.tab.c"
    break;

  case 26: /* named_type: VOID  */
#line 219 "a2.y"
              { (yyval.string_val) = strdup("void"); }
#line 1466 "y.tab.c"
    break;

  case 27: /* statement_list: statement_list statement  */
#line 227 "a2.y"
                               {(yyvsp[-1].ast_list)->push_back((yyvsp[0].ast)); (yyval.ast_list) = (yyvsp[-1].ast_list);}
#line 1472 "y.tab.c"
    break;

  case 28: /* statement_list: %empty  */
#line 228 "a2.y"
                               {(yyval.ast_list) = new vector<Ast*>();}
#line 1478 "y.tab.c"
    break;

  case 29: /* statement: assignment_statement  */
#line 232 "a2.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1484 "y.tab.c"
    break;

  case 30: /* statement: print_statement  */
#line 233 "a2.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1490 "y.tab.c"
    break;

  case 31: /* statement: read_statement  */
#line 234 "a2.y"
                           { (yyval.ast) = (yyvsp[0].ast); }
#line 1496 "y.tab.c"
    break;

  case 32: /* assignment_statement: NAME ASSIGN_OP expression SEMICOLON  */
#line 239 "a2.y"
    {
        Symbol* sym = symtab.lookup((yyvsp[-3].string_val));
        if (!sym) {
            printf("Semantic Error: undeclared variable '%s' at line %d\n",
                    (yyvsp[-3].string_val), yylineno);
            (yyval.ast) = nullptr;
        } else {
            Ast* lhs = new Name_Ast(string((yyvsp[-3].string_val)), *sym, yylineno);
            (yyval.ast) = new Assignment_Ast(lhs, (yyvsp[-1].ast), yylineno);
        }
    }
#line 1512 "y.tab.c"
    break;

  case 33: /* print_statement: PRINT expression SEMICOLON  */
#line 254 "a2.y"
      {
          (yyval.ast) = new Print_Ast((yyvsp[-1].ast), yylineno);
      }
#line 1520 "y.tab.c"
    break;

  case 34: /* read_statement: READ NAME SEMICOLON  */
#line 261 "a2.y"
      {
          Symbol* sym = symtab.lookup((yyvsp[-1].string_val));
          if (!sym) {
              printf("Semantic Error: undeclared variable '%s' at line %d\n",
                     (yyvsp[-1].string_val), yylineno);
              (yyval.ast) = nullptr;
          } else {
              (yyval.ast) = new Read_Ast(new Name_Ast(string((yyvsp[-1].string_val)), *sym, yylineno), yylineno);
          }
      }
#line 1535 "y.tab.c"
    break;

  case 35: /* expression: expression PLUS expression  */
#line 278 "a2.y"
                                                             {(yyval.ast) = new Expression_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_PLUS, yylineno);}
#line 1541 "y.tab.c"
    break;

  case 36: /* expression: expression MINUS expression  */
#line 279 "a2.y"
                                                             {(yyval.ast) = new Expression_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_MINUS, yylineno);}
#line 1547 "y.tab.c"
    break;

  case 37: /* expression: expression MULT expression  */
#line 280 "a2.y"
                                                             {(yyval.ast) = new Expression_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_MULT, yylineno);}
#line 1553 "y.tab.c"
    break;

  case 38: /* expression: expression DIV expression  */
#line 281 "a2.y"
                                                             {(yyval.ast) = new Expression_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_DIV, yylineno);}
#line 1559 "y.tab.c"
    break;

  case 39: /* expression: MINUS expression  */
#line 282 "a2.y"
                                                             {(yyval.ast) = new Uminus_Ast((yyvsp[0].ast), yylineno);}
#line 1565 "y.tab.c"
    break;

  case 40: /* expression: LEFT_ROUND_BRACKET expression RIGHT_ROUND_BRACKET  */
#line 283 "a2.y"
                                                             {(yyval.ast) = (yyvsp[-1].ast);}
#line 1571 "y.tab.c"
    break;

  case 41: /* expression: expression QUESTION_MARK expression COLON expression  */
#line 284 "a2.y"
                                                             {(yyval.ast) = new Ternary_Ast((yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast), yylineno);}
#line 1577 "y.tab.c"
    break;

  case 42: /* expression: expression AND expression  */
#line 285 "a2.y"
                                                             {(yyval.ast) = new Logical_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_AND, yylineno);}
#line 1583 "y.tab.c"
    break;

  case 43: /* expression: expression OR expression  */
#line 286 "a2.y"
                                                             {(yyval.ast) = new Logical_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_OR, yylineno);}
#line 1589 "y.tab.c"
    break;

  case 44: /* expression: NOT expression  */
#line 287 "a2.y"
                                                             {(yyval.ast) = new Logical_Not_Ast((yyvsp[0].ast), yylineno);}
#line 1595 "y.tab.c"
    break;

  case 46: /* expression: NAME  */
#line 289 "a2.y"
           {
        const Symbol* sym = symtab.lookup((yyvsp[0].string_val));
        if (!sym) {
            printf("Semantic Error: undeclared variable '%s' at line %d\n",
                    (yyvsp[0].string_val), yylineno);
            (yyval.ast) = nullptr;
        } else {
            (yyval.ast) = new Name_Ast(string((yyvsp[0].string_val)), *sym, yylineno);
        }
    }
#line 1610 "y.tab.c"
    break;

  case 47: /* expression: INT_VAL  */
#line 299 "a2.y"
              { (yyval.ast) = new Int_Ast((yyvsp[0].int_val), yylineno);}
#line 1616 "y.tab.c"
    break;

  case 48: /* expression: FLOAT_VAL  */
#line 300 "a2.y"
                {(yyval.ast) = new Float_Ast((yyvsp[0].float_val), yylineno);}
#line 1622 "y.tab.c"
    break;

  case 49: /* expression: STR_CONST  */
#line 301 "a2.y"
                {(yyval.ast) = new String_Ast(std::string((yyvsp[0].string_val)), yylineno);}
#line 1628 "y.tab.c"
    break;

  case 50: /* rel_expression: expression LT expression  */
#line 305 "a2.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_LT, yylineno);}
#line 1634 "y.tab.c"
    break;

  case 51: /* rel_expression: expression LE expression  */
#line 306 "a2.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_LE, yylineno);}
#line 1640 "y.tab.c"
    break;

  case 52: /* rel_expression: expression GT expression  */
#line 307 "a2.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_GT, yylineno);}
#line 1646 "y.tab.c"
    break;

  case 53: /* rel_expression: expression GE expression  */
#line 308 "a2.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_GE, yylineno);}
#line 1652 "y.tab.c"
    break;

  case 54: /* rel_expression: expression EQ expression  */
#line 309 "a2.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_EQ, yylineno);}
#line 1658 "y.tab.c"
    break;

  case 55: /* rel_expression: expression NE expression  */
#line 310 "a2.y"
                               {(yyval.ast) = new Relational_Ast((yyvsp[-2].ast), (yyvsp[0].ast), OP_NE, yylineno);}
#line 1664 "y.tab.c"
    break;


#line 1668 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 313 "a2.y"


/* ================= */
/* Driver & errors   */
/* ================= */

