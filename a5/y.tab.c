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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string>
extern int yylineno;
extern char * yytext;
extern FILE * yyin;
extern char * last_lexeme;
extern int last_token;
extern int stop_parse;

extern void clear_tok_file();
extern int show_tokens;
extern void clear_ast_file();
extern int show_ast;

extern const char* input_filename;
const char* token_name(int tok);
int yylex(void);
[[noreturn]] void yyerror(const char *s);

#include "symtab.hh"
#include "ast.hh"

SymbolTable global_symtab(nullptr);
SymbolTable *curr_symtab = &global_symtab;

programnode *prog_root = nullptr;
Ast* root = nullptr;

Type current_decl_type;
Type currentfuncvartype;
std::vector<Type> curr_params;
std::vector<FuncParam> curr_func_params;   // formal params for current function def
Type current_func_ret_type = TYPE_VOID;    // return type of currently-parsed function
std::vector<std::string> func_decl_order;  // tracks forward-declaration order

#line 109 "y.tab.c"

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
/* "%code requires" blocks.  */
#line 39 "parser.y"

    #include <string>
    #include "ast.hh"
    #include "symtab.hh"

#line 150 "y.tab.c"

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
    VOID = 260,                    /* VOID  */
    WRITE = 261,                   /* WRITE  */
    READ = 262,                    /* READ  */
    STRING = 263,                  /* STRING  */
    BOOL = 264,                    /* BOOL  */
    RETURN = 265,                  /* RETURN  */
    IF = 266,                      /* IF  */
    ELSE = 267,                    /* ELSE  */
    WHILE = 268,                   /* WHILE  */
    DO = 269,                      /* DO  */
    PLUS = 270,                    /* PLUS  */
    MINUS = 271,                   /* MINUS  */
    MULT = 272,                    /* MULT  */
    DIV = 273,                     /* DIV  */
    ASSIGN = 274,                  /* ASSIGN  */
    SEMICOLON = 275,               /* SEMICOLON  */
    LPAREN = 276,                  /* LPAREN  */
    RPAREN = 277,                  /* RPAREN  */
    LBRACE = 278,                  /* LBRACE  */
    RBRACE = 279,                  /* RBRACE  */
    COMMA = 280,                   /* COMMA  */
    AND = 281,                     /* AND  */
    OR = 282,                      /* OR  */
    NOT = 283,                     /* NOT  */
    TERINARY = 284,                /* TERINARY  */
    COLON = 285,                   /* COLON  */
    LT = 286,                      /* LT  */
    LE = 287,                      /* LE  */
    GT = 288,                      /* GT  */
    GE = 289,                      /* GE  */
    NE = 290,                      /* NE  */
    EQ = 291,                      /* EQ  */
    INTEGER_NUMBER = 292,          /* INTEGER_NUMBER  */
    FLOAT_NUMBER = 293,            /* FLOAT_NUMBER  */
    NAME = 294,                    /* NAME  */
    STRING_LITERAL = 295,          /* STRING_LITERAL  */
    UMINUS = 296,                  /* UMINUS  */
    LOWER_THAN_ELSE = 297          /* LOWER_THAN_ELSE  */
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
#define VOID 260
#define WRITE 261
#define READ 262
#define STRING 263
#define BOOL 264
#define RETURN 265
#define IF 266
#define ELSE 267
#define WHILE 268
#define DO 269
#define PLUS 270
#define MINUS 271
#define MULT 272
#define DIV 273
#define ASSIGN 274
#define SEMICOLON 275
#define LPAREN 276
#define RPAREN 277
#define LBRACE 278
#define RBRACE 279
#define COMMA 280
#define AND 281
#define OR 282
#define NOT 283
#define TERINARY 284
#define COLON 285
#define LT 286
#define LE 287
#define GT 288
#define GE 289
#define NE 290
#define EQ 291
#define INTEGER_NUMBER 292
#define FLOAT_NUMBER 293
#define NAME 294
#define STRING_LITERAL 295
#define UMINUS 296
#define LOWER_THAN_ELSE 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 45 "parser.y"

    std::string * name;
    int value;
    double fvalue;
    Ast *ast;
    Expression_Ast *expr;
    Statement_Ast *stmt;
    Statement_List_Ast *stmt_list;
    std::vector<Expression_Ast*> *expr_list;

#line 265 "y.tab.c"

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
  YYSYMBOL_VOID = 5,                       /* VOID  */
  YYSYMBOL_WRITE = 6,                      /* WRITE  */
  YYSYMBOL_READ = 7,                       /* READ  */
  YYSYMBOL_STRING = 8,                     /* STRING  */
  YYSYMBOL_BOOL = 9,                       /* BOOL  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_DO = 14,                        /* DO  */
  YYSYMBOL_PLUS = 15,                      /* PLUS  */
  YYSYMBOL_MINUS = 16,                     /* MINUS  */
  YYSYMBOL_MULT = 17,                      /* MULT  */
  YYSYMBOL_DIV = 18,                       /* DIV  */
  YYSYMBOL_ASSIGN = 19,                    /* ASSIGN  */
  YYSYMBOL_SEMICOLON = 20,                 /* SEMICOLON  */
  YYSYMBOL_LPAREN = 21,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 22,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 23,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_NOT = 28,                       /* NOT  */
  YYSYMBOL_TERINARY = 29,                  /* TERINARY  */
  YYSYMBOL_COLON = 30,                     /* COLON  */
  YYSYMBOL_LT = 31,                        /* LT  */
  YYSYMBOL_LE = 32,                        /* LE  */
  YYSYMBOL_GT = 33,                        /* GT  */
  YYSYMBOL_GE = 34,                        /* GE  */
  YYSYMBOL_NE = 35,                        /* NE  */
  YYSYMBOL_EQ = 36,                        /* EQ  */
  YYSYMBOL_INTEGER_NUMBER = 37,            /* INTEGER_NUMBER  */
  YYSYMBOL_FLOAT_NUMBER = 38,              /* FLOAT_NUMBER  */
  YYSYMBOL_NAME = 39,                      /* NAME  */
  YYSYMBOL_STRING_LITERAL = 40,            /* STRING_LITERAL  */
  YYSYMBOL_UMINUS = 41,                    /* UMINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 42,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_global_decl_stmt_list = 45,     /* global_decl_stmt_list  */
  YYSYMBOL_funct_decl = 46,                /* funct_decl  */
  YYSYMBOL_func_def_list = 47,             /* func_def_list  */
  YYSYMBOL_func_def = 48,                  /* func_def  */
  YYSYMBOL_49_1 = 49,                      /* $@1  */
  YYSYMBOL_50_2 = 50,                      /* $@2  */
  YYSYMBOL_param_list = 51,                /* param_list  */
  YYSYMBOL_param = 52,                     /* param  */
  YYSYMBOL_stmt_list = 53,                 /* stmt_list  */
  YYSYMBOL_statement = 54,                 /* statement  */
  YYSYMBOL_named_type = 55,                /* named_type  */
  YYSYMBOL_param_type = 56,                /* param_type  */
  YYSYMBOL_var_decl_stmt = 57,             /* var_decl_stmt  */
  YYSYMBOL_var_decl_item_list = 58,        /* var_decl_item_list  */
  YYSYMBOL_local_var_decl_stmt_list = 59,  /* local_var_decl_stmt_list  */
  YYSYMBOL_print_stmt = 60,                /* print_stmt  */
  YYSYMBOL_read_stmt = 61,                 /* read_stmt  */
  YYSYMBOL_asg_stmt = 62,                  /* asg_stmt  */
  YYSYMBOL_return_stmt = 63,               /* return_stmt  */
  YYSYMBOL_func_call_expr = 64,            /* func_call_expr  */
  YYSYMBOL_call_arg_list = 65,             /* call_arg_list  */
  YYSYMBOL_call_arg_list_nonempty = 66,    /* call_arg_list_nonempty  */
  YYSYMBOL_expr = 67,                      /* expr  */
  YYSYMBOL_const_as_operand = 68,          /* const_as_operand  */
  YYSYMBOL_rel_expr = 69,                  /* rel_expr  */
  YYSYMBOL_if_stmt = 70,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 71,                /* while_stmt  */
  YYSYMBOL_do_while_stmt = 72,             /* do_while_stmt  */
  YYSYMBOL_compound_stmt = 73              /* compound_stmt  */
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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   374

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  155

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    89,    89,   102,   117,   118,   119,   120,   124,   132,
     142,   145,   152,   152,   195,   195,   236,   237,   240,   251,
     258,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     289,   290,   291,   292,   293,   297,   298,   299,   300,   304,
     308,   317,   328,   329,   333,   343,   355,   368,   373,   382,
     395,   396,   404,   410,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   438,   442,   443,   444,   448,
     449,   450,   451,   452,   453,   454,   455,   459,   464,   472,
     480,   488
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
  "VOID", "WRITE", "READ", "STRING", "BOOL", "RETURN", "IF", "ELSE",
  "WHILE", "DO", "PLUS", "MINUS", "MULT", "DIV", "ASSIGN", "SEMICOLON",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "COMMA", "AND", "OR", "NOT",
  "TERINARY", "COLON", "LT", "LE", "GT", "GE", "NE", "EQ",
  "INTEGER_NUMBER", "FLOAT_NUMBER", "NAME", "STRING_LITERAL", "UMINUS",
  "LOWER_THAN_ELSE", "$accept", "program", "global_decl_stmt_list",
  "funct_decl", "func_def_list", "func_def", "$@1", "$@2", "param_list",
  "param", "stmt_list", "statement", "named_type", "param_type",
  "var_decl_stmt", "var_decl_item_list", "local_var_decl_stmt_list",
  "print_stmt", "read_stmt", "asg_stmt", "return_stmt", "func_call_expr",
  "call_arg_list", "call_arg_list_nonempty", "expr", "const_as_operand",
  "rel_expr", "if_stmt", "while_stmt", "do_while_stmt", "compound_stmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-59)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     166,   -59,   -59,   -59,   -59,   -59,     5,   166,   -59,   166,
     -59,     4,   -59,   -59,   -59,   166,   -59,   -59,    22,    45,
      -5,    75,   350,   -59,    50,   352,   -59,   -59,   -59,   -59,
      40,    48,   -59,    61,   -59,     1,    53,   -59,   -59,    68,
      29,   -59,    80,   -59,   -59,   -59,   -59,   166,   -59,     3,
      65,   -59,   166,    46,    66,    -9,    85,    86,   103,   -59,
     -59,   -15,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,
     -59,   -59,    58,    46,    46,    46,   -59,   -59,    87,   -59,
     -59,   104,   -59,   -59,    95,   -59,   128,    46,    46,   105,
      88,    46,    46,   -59,   -59,   150,   310,    46,    46,    46,
      46,    46,   -59,    46,    46,    46,    46,    46,    46,    46,
      46,    46,   -59,   -59,   172,   194,   102,   -59,   216,   106,
     100,   282,   -59,   107,    59,    59,   -59,   -59,   310,   304,
     238,   316,   316,   316,   316,   316,   316,   103,   103,    46,
     -59,   112,    46,   -59,    46,   122,   -59,   260,   -59,   282,
     282,   103,   121,   -59,   -59
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    30,    31,    34,    32,    33,     0,     0,     7,     3,
      11,     0,     6,     1,     5,     2,     4,    10,     0,    41,
       0,     0,     0,    39,     0,     0,    35,    36,    37,    38,
       0,     0,    17,     0,    40,     0,     0,     9,    14,     0,
       0,    18,     0,    43,     8,    12,    16,    20,    43,     0,
       0,    42,    20,     0,     0,     0,     0,     0,     0,    20,
      15,     0,    19,    22,    23,    21,    28,    24,    25,    26,
      27,    41,     0,     0,     0,     0,    66,    67,    64,    68,
      63,     0,    65,    62,     0,    48,     0,     0,     0,     0,
       0,     0,    51,    13,    59,     0,    58,    51,     0,     0,
       0,     0,    44,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,    47,     0,     0,     0,    81,     0,     0,
      50,    53,    60,     0,    54,    55,    56,    57,    75,    76,
       0,    69,    70,    71,    72,    73,    74,     0,     0,     0,
      46,     0,     0,    49,     0,    77,    79,     0,    29,    52,
      61,     0,     0,    78,    80
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -59,   -59,   -59,   140,   142,    35,   -59,   -59,   125,   111,
     -34,   -58,    -7,   -59,    34,   -59,   108,   -59,   -59,   -59,
     -59,   -59,    55,   -59,   -52,   -59,   -59,   -59,   -59,   -59,
     -59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    10,    48,    43,    31,    32,
      49,    62,    11,    33,    51,    20,    47,    63,    64,    65,
      66,    80,   119,   120,   121,    82,    83,    67,    68,    69,
      70
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      89,    81,    18,    86,    91,    13,    92,    73,    18,    53,
      54,    85,    74,    55,    56,    23,    57,    58,    72,    75,
      24,    94,    95,    96,    38,    90,    59,    60,    76,    77,
      78,    79,    26,    27,    12,   114,   115,    28,    29,   118,
      50,    16,    61,    19,    17,    50,   124,   125,   126,   127,
      17,   128,   129,   130,   131,   132,   133,   134,   135,   136,
      37,    21,    73,    38,    53,    54,    22,    74,    55,    56,
      39,    57,    58,    40,    75,    42,   100,   101,    40,   145,
     146,    59,    93,    76,    77,    78,    79,   147,    44,    34,
     149,    45,   150,   153,    53,    54,    25,    61,    55,    56,
      41,    57,    58,    45,    71,    84,    87,    88,    97,    53,
      54,    59,   117,    55,    56,   112,    57,    58,   116,    98,
      99,   100,   101,   139,   102,   142,    59,    61,   141,   143,
     103,   104,   148,   105,   151,   106,   107,   108,   109,   110,
     111,   154,    61,    98,    99,   100,   101,    14,   113,    15,
      36,    46,   123,     0,   103,   104,    52,   105,     0,   106,
     107,   108,   109,   110,   111,    98,    99,   100,   101,     1,
       2,     3,   122,     0,     4,     5,   103,   104,     0,   105,
       0,   106,   107,   108,   109,   110,   111,    98,    99,   100,
     101,     0,     0,     0,   137,     0,     0,     0,   103,   104,
       0,   105,     0,   106,   107,   108,   109,   110,   111,    98,
      99,   100,   101,     0,     0,     0,   138,     0,     0,     0,
     103,   104,     0,   105,     0,   106,   107,   108,   109,   110,
     111,    98,    99,   100,   101,     0,   140,     0,     0,     0,
       0,     0,   103,   104,     0,   105,     0,   106,   107,   108,
     109,   110,   111,    98,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,   103,   104,     0,   105,   144,   106,
     107,   108,   109,   110,   111,    98,    99,   100,   101,     0,
       0,     0,   152,     0,     0,     0,   103,   104,     0,   105,
       0,   106,   107,   108,   109,   110,   111,    98,    99,   100,
     101,     0,     0,     0,     0,     0,     0,     0,   103,   104,
       0,   105,     0,   106,   107,   108,   109,   110,   111,    98,
      99,   100,   101,     0,     0,    98,    99,   100,   101,     0,
     103,    98,    99,   100,   101,   106,   107,   108,   109,   110,
     111,   106,   107,   108,   109,   110,   111,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    26,    27,     0,    28,    29,
      28,    29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,    35
};

static const yytype_int16 yycheck[] =
{
      58,    53,     9,    55,    19,     0,    21,    16,    15,     6,
       7,    20,    21,    10,    11,    20,    13,    14,    52,    28,
      25,    73,    74,    75,    23,    59,    23,    24,    37,    38,
      39,    40,     3,     4,     0,    87,    88,     8,     9,    91,
      47,     7,    39,    39,     9,    52,    98,    99,   100,   101,
      15,   103,   104,   105,   106,   107,   108,   109,   110,   111,
      20,    39,    16,    23,     6,     7,    21,    21,    10,    11,
      22,    13,    14,    25,    28,    22,    17,    18,    25,   137,
     138,    23,    24,    37,    38,    39,    40,   139,    20,    39,
     142,    23,   144,   151,     6,     7,    21,    39,    10,    11,
      39,    13,    14,    23,    39,    39,    21,    21,    21,     6,
       7,    23,    24,    10,    11,    20,    13,    14,    13,    15,
      16,    17,    18,    21,    20,    25,    23,    39,    22,    22,
      26,    27,    20,    29,    12,    31,    32,    33,    34,    35,
      36,    20,    39,    15,    16,    17,    18,     7,    20,     7,
      25,    40,    97,    -1,    26,    27,    48,    29,    -1,    31,
      32,    33,    34,    35,    36,    15,    16,    17,    18,     3,
       4,     5,    22,    -1,     8,     9,    26,    27,    -1,    29,
      -1,    31,    32,    33,    34,    35,    36,    15,    16,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    -1,    26,    27,
      -1,    29,    -1,    31,    32,    33,    34,    35,    36,    15,
      16,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      26,    27,    -1,    29,    -1,    31,    32,    33,    34,    35,
      36,    15,    16,    17,    18,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    26,    27,    -1,    29,    -1,    31,    32,    33,
      34,    35,    36,    15,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    29,    30,    31,
      32,    33,    34,    35,    36,    15,    16,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    -1,    26,    27,    -1,    29,
      -1,    31,    32,    33,    34,    35,    36,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    29,    -1,    31,    32,    33,    34,    35,    36,    15,
      16,    17,    18,    -1,    -1,    15,    16,    17,    18,    -1,
      26,    15,    16,    17,    18,    31,    32,    33,    34,    35,
      36,    31,    32,    33,    34,    35,    36,    31,    32,    33,
      34,    35,    36,     3,     4,     3,     4,    -1,     8,     9,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    22,    -1,    22
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     8,     9,    44,    45,    46,    47,
      48,    55,    57,     0,    46,    47,    57,    48,    55,    39,
      58,    39,    21,    20,    25,    21,     3,     4,     8,     9,
      22,    51,    52,    56,    39,    22,    51,    20,    23,    22,
      25,    39,    22,    50,    20,    23,    52,    59,    49,    53,
      55,    57,    59,     6,     7,    10,    11,    13,    14,    23,
      24,    39,    54,    60,    61,    62,    63,    70,    71,    72,
      73,    39,    53,    16,    21,    28,    37,    38,    39,    40,
      64,    67,    68,    69,    39,    20,    67,    21,    21,    54,
      53,    19,    21,    24,    67,    67,    67,    21,    15,    16,
      17,    18,    20,    26,    27,    29,    31,    32,    33,    34,
      35,    36,    20,    20,    67,    67,    13,    24,    67,    65,
      66,    67,    22,    65,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    22,    22,    21,
      20,    22,    25,    22,    30,    54,    54,    67,    20,    67,
      67,    12,    22,    54,    20
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    44,    45,    45,    45,    45,    46,    46,
      47,    47,    49,    48,    50,    48,    51,    51,    52,    53,
      53,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    55,    55,    56,    56,    56,    56,    57,
      58,    58,    59,    59,    60,    61,    62,    63,    63,    64,
      65,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    68,    68,    68,    69,
      69,    69,    69,    69,    69,    69,    69,    70,    70,    71,
      72,    73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     2,     2,     1,     1,     6,     5,
       2,     1,     0,    10,     0,     9,     3,     1,     2,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     2,     0,     3,     3,     4,     3,     2,     4,
       1,     0,     3,     1,     3,     3,     3,     3,     2,     2,
       3,     5,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     7,     5,
       7,     3
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
  case 2: /* program: global_decl_stmt_list func_def_list  */
#line 89 "parser.y"
                                          {
        if(!stop_parse){
            // Pass global variable list to prog_root for ASM .data section
            if(prog_root){
                std::vector<std::pair<std::string,Type>> gvars;
                for(const auto &sym : global_symtab.get_table())
                    if(sym.kind == SYM_VAR) gvars.push_back({sym.name, sym.type});
                prog_root->set_globals(gvars);
            }
            root = (yyvsp[0].ast);
        } else root = nullptr;
        (yyval.ast) = root;
    }
#line 1479 "y.tab.c"
    break;

  case 3: /* program: func_def_list  */
#line 102 "parser.y"
                    {
        if(!stop_parse){
            if(prog_root){
                std::vector<std::pair<std::string,Type>> gvars;
                for(const auto &sym : global_symtab.get_table())
                    if(sym.kind == SYM_VAR) gvars.push_back({sym.name, sym.type});
                prog_root->set_globals(gvars);
            }
            root = (yyvsp[0].ast);
        } else root = nullptr;
        (yyval.ast) = root;
    }
#line 1496 "y.tab.c"
    break;

  case 8: /* funct_decl: named_type NAME LPAREN param_list RPAREN SEMICOLON  */
#line 124 "parser.y"
                                                       {
        if(!stop_parse){
            curr_symtab->declarefunc(*(yyvsp[-4].name), current_decl_type, curr_params);
            curr_params.clear();
            curr_func_params.clear();
            func_decl_order.push_back(*(yyvsp[-4].name));
        }
    }
#line 1509 "y.tab.c"
    break;

  case 9: /* funct_decl: named_type NAME LPAREN RPAREN SEMICOLON  */
#line 132 "parser.y"
                                              {
        if(!stop_parse){
            curr_symtab->declarefunc(*(yyvsp[-3].name), current_decl_type, {});
            func_decl_order.push_back(*(yyvsp[-3].name));
        }
    }
#line 1520 "y.tab.c"
    break;

  case 10: /* func_def_list: func_def_list func_def  */
#line 142 "parser.y"
                             {
        (yyval.ast) = (yyvsp[-1].ast);
    }
#line 1528 "y.tab.c"
    break;

  case 11: /* func_def_list: func_def  */
#line 145 "parser.y"
               {
        (yyval.ast) = prog_root;
    }
#line 1536 "y.tab.c"
    break;

  case 12: /* $@1: %empty  */
#line 152 "parser.y"
                                                      {
        if(!stop_parse){
            current_func_ret_type = current_decl_type;
            curr_symtab->definefunc(*(yyvsp[-4].name), current_decl_type, curr_params);
            curr_params.clear();
            curr_symtab = new SymbolTable(&global_symtab);
            // Insert formal params into local scope
            for(auto &p : curr_func_params){
                curr_symtab->insert(p.name, p.type);
            }
        }
    }
#line 1553 "y.tab.c"
    break;

  case 13: /* func_def: named_type NAME LPAREN param_list RPAREN LBRACE $@1 local_var_decl_stmt_list stmt_list RBRACE  */
#line 164 "parser.y"
                                              {
        if(!stop_parse){
            if(current_func_ret_type != TYPE_VOID && !(yyvsp[-1].stmt_list)->has_return())
                yyerror("Missing return statement in a non-void procedure");
            FuncDefNode *fn = new FuncDefNode(*(yyvsp[-8].name), current_func_ret_type,
                                              curr_func_params, (yyvsp[-1].stmt_list));
            // Extract local variable names+types before symtab is deleted
            {
                std::vector<std::pair<std::string,Type>> lvars;
                std::set<std::string> pnames;
for(auto &p : curr_func_params) pnames.insert(p.name);

for(const auto &sym : curr_symtab->get_table())
    if(sym.kind == SYM_VAR && !pnames.count(sym.name))
        lvars.push_back({sym.name, sym.type});
fn->set_locals(lvars);


            }
            if(!prog_root){
                prog_root = new programnode();
                prog_root->set_decl_order(func_decl_order);
            }
            prog_root->add_func(fn);
            SymbolTable* old = curr_symtab;
            curr_symtab = curr_symtab->getParent();
            delete old;
            curr_func_params.clear();
        }
        (yyval.ast) = prog_root;
    }
#line 1589 "y.tab.c"
    break;

  case 14: /* $@2: %empty  */
#line 195 "parser.y"
                                           {
        if(!stop_parse){
            current_func_ret_type = current_decl_type;
            curr_symtab->definefunc(*(yyvsp[-3].name), current_decl_type, {});
            curr_symtab = new SymbolTable(&global_symtab);
        }
    }
#line 1601 "y.tab.c"
    break;

  case 15: /* func_def: named_type NAME LPAREN RPAREN LBRACE $@2 local_var_decl_stmt_list stmt_list RBRACE  */
#line 202 "parser.y"
                                              {
        if(!stop_parse){
            if(current_func_ret_type != TYPE_VOID && !(yyvsp[-1].stmt_list)->has_return())
                yyerror("Missing return statement in a non-void procedure");
            FuncDefNode *fn = new FuncDefNode(*(yyvsp[-7].name), current_func_ret_type,
                                              {}, (yyvsp[-1].stmt_list));
            // Extract local variable names+types before symtab is deleted
            {
                std::vector<std::pair<std::string,Type>> lvars;
               std::set<std::string> pnames;
for(auto &p : curr_func_params) pnames.insert(p.name);

for(const auto &sym : curr_symtab->get_table())
    if(sym.kind == SYM_VAR && !pnames.count(sym.name))
        lvars.push_back({sym.name, sym.type});
fn->set_locals(lvars);


            }
            if(!prog_root){
                prog_root = new programnode();
                prog_root->set_decl_order(func_decl_order);
            }
            prog_root->add_func(fn);
            SymbolTable* old = curr_symtab;
            curr_symtab = curr_symtab->getParent();
            delete old;
            curr_func_params.clear();
        }
        (yyval.ast) = prog_root;
    }
#line 1637 "y.tab.c"
    break;

  case 18: /* param: param_type NAME  */
#line 240 "parser.y"
                       {
    if(!stop_parse){
        FuncParam fp;
        fp.name = *(yyvsp[0].name);
        fp.type = currentfuncvartype;
        curr_func_params.push_back(fp);
    }
}
#line 1650 "y.tab.c"
    break;

  case 19: /* stmt_list: stmt_list statement  */
#line 251 "parser.y"
                          {
        if(!stop_parse){
            (yyvsp[-1].stmt_list)->append((yyvsp[0].stmt));
            (yyval.stmt_list) = (yyvsp[-1].stmt_list);
        } else { (yyval.stmt_list) = nullptr; }
    }
#line 1661 "y.tab.c"
    break;

  case 20: /* stmt_list: %empty  */
#line 258 "parser.y"
    {
        if(!stop_parse){
            (yyval.stmt_list) = new Statement_List_Ast();
        } else {
            (yyval.stmt_list) = nullptr;
        }
    }
#line 1673 "y.tab.c"
    break;

  case 21: /* statement: asg_stmt  */
#line 268 "parser.y"
                     { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1679 "y.tab.c"
    break;

  case 22: /* statement: print_stmt  */
#line 269 "parser.y"
                     { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1685 "y.tab.c"
    break;

  case 23: /* statement: read_stmt  */
#line 270 "parser.y"
                     { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1691 "y.tab.c"
    break;

  case 24: /* statement: if_stmt  */
#line 271 "parser.y"
                     { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1697 "y.tab.c"
    break;

  case 25: /* statement: while_stmt  */
#line 272 "parser.y"
                     { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1703 "y.tab.c"
    break;

  case 26: /* statement: do_while_stmt  */
#line 273 "parser.y"
                     { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1709 "y.tab.c"
    break;

  case 27: /* statement: compound_stmt  */
#line 274 "parser.y"
                     { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1715 "y.tab.c"
    break;

  case 28: /* statement: return_stmt  */
#line 275 "parser.y"
                     { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1721 "y.tab.c"
    break;

  case 29: /* statement: NAME LPAREN call_arg_list RPAREN SEMICOLON  */
#line 276 "parser.y"
                                                 {
        if(!stop_parse){
            Symbol *sym = curr_symtab->lookupFunc(*(yyvsp[-4].name));
            if(!sym) yyerror("undefined function");
            if((yyvsp[-2].expr_list)->size() != sym->params.size()) yyerror("Actual and formal parameter counts do not match");
            if(sym->type != TYPE_VOID) yyerror("Return value of a procedure ignored");
            (yyval.stmt) = new FuncCallStmt_Ast(*(yyvsp[-4].name), *(yyvsp[-2].expr_list), sym->type);
            delete (yyvsp[-2].expr_list);
        } else { (yyval.stmt) = nullptr; }
    }
#line 1736 "y.tab.c"
    break;

  case 30: /* named_type: INTEGER  */
#line 289 "parser.y"
              { current_decl_type = TYPE_INT; }
#line 1742 "y.tab.c"
    break;

  case 31: /* named_type: FLOAT  */
#line 290 "parser.y"
              { current_decl_type = TYPE_FLOAT; }
#line 1748 "y.tab.c"
    break;

  case 32: /* named_type: STRING  */
#line 291 "parser.y"
              { current_decl_type = TYPE_STRING; }
#line 1754 "y.tab.c"
    break;

  case 33: /* named_type: BOOL  */
#line 292 "parser.y"
              { current_decl_type = TYPE_BOOL; }
#line 1760 "y.tab.c"
    break;

  case 34: /* named_type: VOID  */
#line 293 "parser.y"
              { current_decl_type = TYPE_VOID; }
#line 1766 "y.tab.c"
    break;

  case 35: /* param_type: INTEGER  */
#line 297 "parser.y"
              { curr_params.push_back(TYPE_INT);    currentfuncvartype = TYPE_INT; }
#line 1772 "y.tab.c"
    break;

  case 36: /* param_type: FLOAT  */
#line 298 "parser.y"
              { curr_params.push_back(TYPE_FLOAT);  currentfuncvartype = TYPE_FLOAT; }
#line 1778 "y.tab.c"
    break;

  case 37: /* param_type: STRING  */
#line 299 "parser.y"
              { curr_params.push_back(TYPE_STRING); currentfuncvartype = TYPE_STRING; }
#line 1784 "y.tab.c"
    break;

  case 38: /* param_type: BOOL  */
#line 300 "parser.y"
              { curr_params.push_back(TYPE_BOOL);   currentfuncvartype = TYPE_BOOL; }
#line 1790 "y.tab.c"
    break;

  case 40: /* var_decl_item_list: var_decl_item_list COMMA NAME  */
#line 309 "parser.y"
    {
        if(!stop_parse){
            if(curr_symtab->lookupLocal(*(yyvsp[0].name)) != -1){
                yyerror("Var Already DECLARED!!");
            }
            curr_symtab->insert(*(yyvsp[0].name), current_decl_type);
        }
    }
#line 1803 "y.tab.c"
    break;

  case 41: /* var_decl_item_list: NAME  */
#line 317 "parser.y"
           {
        if(!stop_parse){
            if(curr_symtab->lookupLocal(*(yyvsp[0].name)) != -1){
                yyerror("Var Already DECLARED!!");
            }
            curr_symtab->insert(*(yyvsp[0].name), current_decl_type);
        }
    }
#line 1816 "y.tab.c"
    break;

  case 44: /* print_stmt: WRITE expr SEMICOLON  */
#line 333 "parser.y"
                           {
        if(!stop_parse){
            (yyval.stmt) = new Print_Ast((yyvsp[-1].expr));
        } else {
            (yyval.stmt) = nullptr;
        }
    }
#line 1828 "y.tab.c"
    break;

  case 45: /* read_stmt: READ NAME SEMICOLON  */
#line 343 "parser.y"
                          {
        if(!stop_parse){
            int idx = curr_symtab->lookup(*(yyvsp[-1].name));
            if(idx == -1) yyerror("var not Declared (not found)!!!");
            (yyval.stmt) = new Read_Ast(new Name_Ast(*(yyvsp[-1].name), curr_symtab));
        } else {
            (yyval.stmt) = nullptr;
        }
    }
#line 1842 "y.tab.c"
    break;

  case 46: /* asg_stmt: NAME ASSIGN expr SEMICOLON  */
#line 356 "parser.y"
    {
        if(!stop_parse){
            int idx = curr_symtab->lookup(*(yyvsp[-3].name));
            if(idx == -1) yyerror("var not Declared (not found)!!!");
            (yyval.stmt) = new Assignment_Ast(new Name_Ast(*(yyvsp[-3].name), curr_symtab), (yyvsp[-1].expr));
        } else {
            (yyval.stmt) = nullptr;
        }
    }
#line 1856 "y.tab.c"
    break;

  case 47: /* return_stmt: RETURN expr SEMICOLON  */
#line 368 "parser.y"
                            {
        if(!stop_parse){
            (yyval.stmt) = new Return_Ast((yyvsp[-1].expr), current_func_ret_type);
        } else { (yyval.stmt) = nullptr; }
    }
#line 1866 "y.tab.c"
    break;

  case 48: /* return_stmt: RETURN SEMICOLON  */
#line 373 "parser.y"
                       {
        if(!stop_parse){
            (yyval.stmt) = new Return_Ast(nullptr, current_func_ret_type);
        } else { (yyval.stmt) = nullptr; }
    }
#line 1876 "y.tab.c"
    break;

  case 49: /* func_call_expr: NAME LPAREN call_arg_list RPAREN  */
#line 382 "parser.y"
                                       {
        if(!stop_parse){
            Symbol *sym = curr_symtab->lookupFunc(*(yyvsp[-3].name));
            if(!sym) yyerror("undefined function");
            if((yyvsp[-1].expr_list)->size() != sym->params.size()) yyerror("Actual and formal parameter counts do not match");
            std::vector<std::pair<std::string,Type>> fps;
            (yyval.expr) = new FuncCallExpr_Ast(*(yyvsp[-3].name), *(yyvsp[-1].expr_list), sym->type, fps);
            delete (yyvsp[-1].expr_list);
        } else { (yyval.expr) = nullptr; }
    }
#line 1891 "y.tab.c"
    break;

  case 50: /* call_arg_list: call_arg_list_nonempty  */
#line 395 "parser.y"
                             { (yyval.expr_list) = (yyvsp[0].expr_list); }
#line 1897 "y.tab.c"
    break;

  case 51: /* call_arg_list: %empty  */
#line 396 "parser.y"
                  {
        if(!stop_parse){
            (yyval.expr_list) = new std::vector<Expression_Ast*>();
        } else { (yyval.expr_list) = nullptr; }
    }
#line 1907 "y.tab.c"
    break;

  case 52: /* call_arg_list_nonempty: call_arg_list_nonempty COMMA expr  */
#line 404 "parser.y"
                                        {
        if(!stop_parse){
            (yyvsp[-2].expr_list)->push_back((yyvsp[0].expr));
            (yyval.expr_list) = (yyvsp[-2].expr_list);
        } else { (yyval.expr_list) = nullptr; }
    }
#line 1918 "y.tab.c"
    break;

  case 53: /* call_arg_list_nonempty: expr  */
#line 410 "parser.y"
           {
        if(!stop_parse){
            (yyval.expr_list) = new std::vector<Expression_Ast*>();
            (yyval.expr_list)->push_back((yyvsp[0].expr));
        } else { (yyval.expr_list) = nullptr; }
    }
#line 1929 "y.tab.c"
    break;

  case 54: /* expr: expr PLUS expr  */
#line 419 "parser.y"
                      { (yyval.expr) = stop_parse ? nullptr : new Binary_Expr_Ast((yyvsp[-2].expr), OP_PLUS,  (yyvsp[0].expr)); }
#line 1935 "y.tab.c"
    break;

  case 55: /* expr: expr MINUS expr  */
#line 420 "parser.y"
                      { (yyval.expr) = stop_parse ? nullptr : new Binary_Expr_Ast((yyvsp[-2].expr), OP_MINUS, (yyvsp[0].expr)); }
#line 1941 "y.tab.c"
    break;

  case 56: /* expr: expr MULT expr  */
#line 421 "parser.y"
                      { (yyval.expr) = stop_parse ? nullptr : new Binary_Expr_Ast((yyvsp[-2].expr), OP_MULT,  (yyvsp[0].expr)); }
#line 1947 "y.tab.c"
    break;

  case 57: /* expr: expr DIV expr  */
#line 422 "parser.y"
                      { (yyval.expr) = stop_parse ? nullptr : new Binary_Expr_Ast((yyvsp[-2].expr), OP_DIV,   (yyvsp[0].expr)); }
#line 1953 "y.tab.c"
    break;

  case 58: /* expr: NOT expr  */
#line 423 "parser.y"
                      { (yyval.expr) = stop_parse ? nullptr : new Unary_Expr_Ast((yyvsp[0].expr), NOT_OP); }
#line 1959 "y.tab.c"
    break;

  case 59: /* expr: MINUS expr  */
#line 424 "parser.y"
                              { (yyval.expr) = stop_parse ? nullptr : new Unary_Expr_Ast((yyvsp[0].expr), UMINUS_OP); }
#line 1965 "y.tab.c"
    break;

  case 60: /* expr: LPAREN expr RPAREN  */
#line 425 "parser.y"
                              { (yyval.expr) = (yyvsp[-1].expr); }
#line 1971 "y.tab.c"
    break;

  case 61: /* expr: expr TERINARY expr COLON expr  */
#line 426 "parser.y"
                                    { (yyval.expr) = stop_parse ? nullptr : new ternexpr((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1977 "y.tab.c"
    break;

  case 62: /* expr: rel_expr  */
#line 427 "parser.y"
                      { (yyval.expr) = (yyvsp[0].expr); }
#line 1983 "y.tab.c"
    break;

  case 63: /* expr: func_call_expr  */
#line 428 "parser.y"
                      { (yyval.expr) = (yyvsp[0].expr); }
#line 1989 "y.tab.c"
    break;

  case 64: /* expr: NAME  */
#line 429 "parser.y"
           {
        if(stop_parse){
            (yyval.expr) = nullptr;
        } else {
            int idx = curr_symtab->lookup(*(yyvsp[0].name));
            if(idx == -1) yyerror("Undeclared variable");
            (yyval.expr) = new Name_Ast(*(yyvsp[0].name), curr_symtab);
        }
    }
#line 2003 "y.tab.c"
    break;

  case 65: /* expr: const_as_operand  */
#line 438 "parser.y"
                       { (yyval.expr) = (yyvsp[0].expr); }
#line 2009 "y.tab.c"
    break;

  case 66: /* const_as_operand: INTEGER_NUMBER  */
#line 442 "parser.y"
                      { (yyval.expr) = stop_parse ? nullptr : new Int_Const_Ast((yyvsp[0].value)); }
#line 2015 "y.tab.c"
    break;

  case 67: /* const_as_operand: FLOAT_NUMBER  */
#line 443 "parser.y"
                      { (yyval.expr) = stop_parse ? nullptr : new Float_Const_Ast((yyvsp[0].fvalue)); }
#line 2021 "y.tab.c"
    break;

  case 68: /* const_as_operand: STRING_LITERAL  */
#line 444 "parser.y"
                      { (yyval.expr) = stop_parse ? nullptr : new String_Const_Ast((yyvsp[0].name)); }
#line 2027 "y.tab.c"
    break;

  case 69: /* rel_expr: expr LT expr  */
#line 448 "parser.y"
                   { (yyval.expr) = stop_parse ? nullptr : new Relational_Expr_Ast((yyvsp[-2].expr), LT_OP, (yyvsp[0].expr)); }
#line 2033 "y.tab.c"
    break;

  case 70: /* rel_expr: expr LE expr  */
#line 449 "parser.y"
                   { (yyval.expr) = stop_parse ? nullptr : new Relational_Expr_Ast((yyvsp[-2].expr), LE_OP, (yyvsp[0].expr)); }
#line 2039 "y.tab.c"
    break;

  case 71: /* rel_expr: expr GT expr  */
#line 450 "parser.y"
                   { (yyval.expr) = stop_parse ? nullptr : new Relational_Expr_Ast((yyvsp[-2].expr), GT_OP, (yyvsp[0].expr)); }
#line 2045 "y.tab.c"
    break;

  case 72: /* rel_expr: expr GE expr  */
#line 451 "parser.y"
                   { (yyval.expr) = stop_parse ? nullptr : new Relational_Expr_Ast((yyvsp[-2].expr), GE_OP, (yyvsp[0].expr)); }
#line 2051 "y.tab.c"
    break;

  case 73: /* rel_expr: expr NE expr  */
#line 452 "parser.y"
                   { (yyval.expr) = stop_parse ? nullptr : new Relational_Expr_Ast((yyvsp[-2].expr), NE_OP, (yyvsp[0].expr)); }
#line 2057 "y.tab.c"
    break;

  case 74: /* rel_expr: expr EQ expr  */
#line 453 "parser.y"
                   { (yyval.expr) = stop_parse ? nullptr : new Relational_Expr_Ast((yyvsp[-2].expr), EQ_OP, (yyvsp[0].expr)); }
#line 2063 "y.tab.c"
    break;

  case 75: /* rel_expr: expr AND expr  */
#line 454 "parser.y"
                    { (yyval.expr) = stop_parse ? nullptr : new Relational_Expr_Ast((yyvsp[-2].expr), OP_AND, (yyvsp[0].expr)); }
#line 2069 "y.tab.c"
    break;

  case 76: /* rel_expr: expr OR expr  */
#line 455 "parser.y"
                    { (yyval.expr) = stop_parse ? nullptr : new Relational_Expr_Ast((yyvsp[-2].expr), OP_OR,  (yyvsp[0].expr)); }
#line 2075 "y.tab.c"
    break;

  case 77: /* if_stmt: IF LPAREN expr RPAREN statement  */
#line 459 "parser.y"
                                                            {
        if(!stop_parse){
            (yyval.stmt) = new If_Ast((yyvsp[-2].expr), (yyvsp[0].stmt));
        } else { (yyval.stmt) = nullptr; }
    }
#line 2085 "y.tab.c"
    break;

  case 78: /* if_stmt: IF LPAREN expr RPAREN statement ELSE statement  */
#line 464 "parser.y"
                                                     {
        if(!stop_parse){
            (yyval.stmt) = new If_Else_Ast((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt));
        } else { (yyval.stmt) = nullptr; }
    }
#line 2095 "y.tab.c"
    break;

  case 79: /* while_stmt: WHILE LPAREN expr RPAREN statement  */
#line 472 "parser.y"
                                         {
        if(!stop_parse){
            (yyval.stmt) = new While_Ast((yyvsp[-2].expr), (yyvsp[0].stmt));
        } else { (yyval.stmt) = nullptr; }
    }
#line 2105 "y.tab.c"
    break;

  case 80: /* do_while_stmt: DO statement WHILE LPAREN expr RPAREN SEMICOLON  */
#line 480 "parser.y"
                                                      {
        if(!stop_parse){
            (yyval.stmt) = new Do_While_Ast((yyvsp[-2].expr), (yyvsp[-5].stmt));
        } else { (yyval.stmt) = nullptr; }
    }
#line 2115 "y.tab.c"
    break;

  case 81: /* compound_stmt: LBRACE stmt_list RBRACE  */
#line 488 "parser.y"
                              {
        if(!stop_parse){
            (yyval.stmt) = new Compound_Stmt((yyvsp[-1].stmt_list));
        } else { (yyval.stmt) = nullptr; }
    }
#line 2125 "y.tab.c"
    break;


#line 2129 "y.tab.c"

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

#line 495 "parser.y"


const char* token_name(int tok){
    switch(tok){
        case FLOAT:          return "FLOAT";
        case INTEGER:        return "INTEGER";
        case STRING:         return "STRING";
        case BOOL:           return "BOOL";
        case VOID:           return "VOID";
        case READ:           return "READ";
        case RETURN:         return "RETURN";
        case FLOAT_NUMBER:   return "FLOAT_NUM";
        case INTEGER_NUMBER: return "INT_NUM";
        case NAME:           return "NAME";
        case STRING_LITERAL: return "STR_CONST";
        case ASSIGN:         return "ASSIGN_OP";
        case PLUS:           return "PLUS";
        case MINUS:          return "MINUS";
        case DIV:            return "DIV";
        case MULT:           return "MULT";
        case SEMICOLON:      return "SEMICOLON";
        case LPAREN:         return "LEFT_ROUND_BRACKET";
        case RPAREN:         return "RIGHT_ROUND_BRACKET";
        case LBRACE:         return "LEFT_CURLY_BRACKET";
        case RBRACE:         return "RIGHT_CURLY_BRACKET";
        case COMMA:          return "COMMA";
        case WRITE:          return "WRITE";
        case IF:             return "IF";
        case ELSE:           return "ELSE";
        case WHILE:          return "WHILE";
        case DO:             return "DO";
        case AND:            return "AND";
        case OR:             return "OR";
        case NOT:            return "NOT";
        case LT:             return "LT";
        case LE:             return "LE";
        case GT:             return "GT";
        case GE:             return "GE";
        case EQ:             return "EQ";
        case NE:             return "NE";
        case TERINARY:       return "TERNARY";
        case COLON:          return "COLON";
        default:             return "UNKNOWN";
    }
}

void yyerror(const char *s){
    if(show_tokens){
        clear_tok_file();
    }
    if(show_ast){
        clear_ast_file();
    }
    fprintf(stderr, "%s\n", s);
    fprintf(stderr, "sclp error: File: %s, Line: %d, Next Token: %s, Lexeme: \"%s\"\n",
            input_filename, yylineno, token_name(last_token), last_lexeme ? last_lexeme : "");
    if(yychar != 0 && yychar != YYEMPTY)
        fprintf(stderr, ", at '%s'", yytext);
    fprintf(stderr, "\n");
    exit(1);
}
