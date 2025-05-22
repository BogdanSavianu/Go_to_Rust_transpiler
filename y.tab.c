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
#line 1 "src/translate.y"

    #define _GNU_SOURCE         /* for asprintf */
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define YYDEBUG 1

    void yyerror(const char *s);
    int yylex(void);    

    int yydebug = 1;
    int print_newline_flag = 0;
    FILE *fptr;

    struct Parameter {
        char* name;
        char* type;
    };

    struct LibMap {
        const char* go_lib;
        const char* rust_lib;
    } lib_mappings[] = {
        {"fmt", "std::io"},
        {"std", "std"}
    };

    const char* map_library(const char* go_lib) {
        char *clean_lib = strdup(go_lib);
        if (clean_lib[0] == '"') {
            clean_lib++;
            clean_lib[strlen(clean_lib)-1] = '\0';
        }
        
        for (int i = 0; lib_mappings[i].go_lib != NULL; i++) {
            if (strcmp(clean_lib, lib_mappings[i].go_lib) == 0) {
                return lib_mappings[i].rust_lib;
            }
        }
        return clean_lib;
    }

    const char* convert_type(const char* go_type) {
        if (!go_type) return "()";  // void in Rust
        if (strcmp(go_type, "int") == 0) return "i32";
        if (strcmp(go_type, "float") == 0) return "f64";
        if (strcmp(go_type, "string") == 0) return "String";
        return go_type;
    }

    char* current_block = NULL;

    char* param_list_buffer = NULL;

#line 127 "y.tab.c"

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
# define YYDEBUG 1
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
    INT = 258,                     /* INT  */
    FLOAT = 259,                   /* FLOAT  */
    STRING = 260,                  /* STRING  */
    NUMBER = 261,                  /* NUMBER  */
    DECLARE_ASSIGN = 262,          /* DECLARE_ASSIGN  */
    ASSIGN = 263,                  /* ASSIGN  */
    ID = 264,                      /* ID  */
    PACKAGE = 265,                 /* PACKAGE  */
    IMPORT = 266,                  /* IMPORT  */
    TYPE = 267,                    /* TYPE  */
    STRUCT = 268,                  /* STRUCT  */
    FUNC = 269,                    /* FUNC  */
    RETURN = 270,                  /* RETURN  */
    LBRACE = 271,                  /* LBRACE  */
    RBRACE = 272,                  /* RBRACE  */
    LPAR = 273,                    /* LPAR  */
    RPAR = 274,                    /* RPAR  */
    LSTRPAR = 275,                 /* LSTRPAR  */
    RSTRPAR = 276,                 /* RSTRPAR  */
    NEWLINE = 277                  /* NEWLINE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INT 258
#define FLOAT 259
#define STRING 260
#define NUMBER 261
#define DECLARE_ASSIGN 262
#define ASSIGN 263
#define ID 264
#define PACKAGE 265
#define IMPORT 266
#define TYPE 267
#define STRUCT 268
#define FUNC 269
#define RETURN 270
#define LBRACE 271
#define RBRACE 272
#define LPAR 273
#define RPAR 274
#define LSTRPAR 275
#define RSTRPAR 276
#define NEWLINE 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 57 "src/translate.y"

    char *str;
    char *expr;
    struct {
        char* name;
        char* type;
    } param;

#line 233 "y.tab.c"

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
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_6_ = 6,                         /* '+'  */
  YYSYMBOL_7_ = 7,                         /* '-'  */
  YYSYMBOL_8_ = 8,                         /* '*'  */
  YYSYMBOL_9_ = 9,                         /* '/'  */
  YYSYMBOL_NUMBER = 10,                    /* NUMBER  */
  YYSYMBOL_DECLARE_ASSIGN = 11,            /* DECLARE_ASSIGN  */
  YYSYMBOL_ASSIGN = 12,                    /* ASSIGN  */
  YYSYMBOL_ID = 13,                        /* ID  */
  YYSYMBOL_PACKAGE = 14,                   /* PACKAGE  */
  YYSYMBOL_IMPORT = 15,                    /* IMPORT  */
  YYSYMBOL_TYPE = 16,                      /* TYPE  */
  YYSYMBOL_STRUCT = 17,                    /* STRUCT  */
  YYSYMBOL_FUNC = 18,                      /* FUNC  */
  YYSYMBOL_RETURN = 19,                    /* RETURN  */
  YYSYMBOL_LBRACE = 20,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 21,                    /* RBRACE  */
  YYSYMBOL_LPAR = 22,                      /* LPAR  */
  YYSYMBOL_RPAR = 23,                      /* RPAR  */
  YYSYMBOL_LSTRPAR = 24,                   /* LSTRPAR  */
  YYSYMBOL_RSTRPAR = 25,                   /* RSTRPAR  */
  YYSYMBOL_NEWLINE = 26,                   /* NEWLINE  */
  YYSYMBOL_27_ = 27,                       /* ','  */
  YYSYMBOL_28_ = 28,                       /* '('  */
  YYSYMBOL_29_ = 29,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 30,                  /* $accept  */
  YYSYMBOL_program = 31,                   /* program  */
  YYSYMBOL_newlines = 32,                  /* newlines  */
  YYSYMBOL_package_decl = 33,              /* package_decl  */
  YYSYMBOL_import_decls = 34,              /* import_decls  */
  YYSYMBOL_import_decl = 35,               /* import_decl  */
  YYSYMBOL_top_lvl_decls = 36,             /* top_lvl_decls  */
  YYSYMBOL_top_lvl_decl = 37,              /* top_lvl_decl  */
  YYSYMBOL_func_decl = 38,                 /* func_decl  */
  YYSYMBOL_param_list = 39,                /* param_list  */
  YYSYMBOL_param_list_nonempty = 40,       /* param_list_nonempty  */
  YYSYMBOL_param = 41,                     /* param  */
  YYSYMBOL_type = 42,                      /* type  */
  YYSYMBOL_block = 43,                     /* block  */
  YYSYMBOL_stmt_list = 44,                 /* stmt_list  */
  YYSYMBOL_statement = 45,                 /* statement  */
  YYSYMBOL_expr_stmt = 46,                 /* expr_stmt  */
  YYSYMBOL_var_decl = 47,                  /* var_decl  */
  YYSYMBOL_struct_decl = 48,               /* struct_decl  */
  YYSYMBOL_if_stmt = 49,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 50,                /* while_stmt  */
  YYSYMBOL_for_stmt = 51,                  /* for_stmt  */
  YYSYMBOL_return_stmt = 52,               /* return_stmt  */
  YYSYMBOL_returnable = 53,                /* returnable  */
  YYSYMBOL_expr = 54,                      /* expr  */
  YYSYMBOL_arg_list = 55,                  /* arg_list  */
  YYSYMBOL_arg_list_nonempty = 56          /* arg_list_nonempty  */
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   58

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  79

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


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
      28,    29,     8,     6,    27,     7,     2,     9,     2,     2,
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
       5,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    81,    81,    85,    86,    98,   102,   103,   107,   111,
     112,   116,   117,   118,   122,   145,   146,   150,   156,   165,
     173,   174,   175,   176,   180,   189,   190,   200,   201,   202,
     203,   204,   205,   209,   213,   221,   225,   229,   233,   237,
     245,   246,   250,   255,   260,   265,   270,   275,   280,   285,
     286,   287,   291,   292,   296,   297
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT",
  "STRING", "'+'", "'-'", "'*'", "'/'", "NUMBER", "DECLARE_ASSIGN",
  "ASSIGN", "ID", "PACKAGE", "IMPORT", "TYPE", "STRUCT", "FUNC", "RETURN",
  "LBRACE", "RBRACE", "LPAR", "RPAR", "LSTRPAR", "RSTRPAR", "NEWLINE",
  "','", "'('", "')'", "$accept", "program", "newlines", "package_decl",
  "import_decls", "import_decl", "top_lvl_decls", "top_lvl_decl",
  "func_decl", "param_list", "param_list_nonempty", "param", "type",
  "block", "stmt_list", "statement", "expr_stmt", "var_decl",
  "struct_decl", "if_stmt", "while_stmt", "for_stmt", "return_stmt",
  "returnable", "expr", "arg_list", "arg_list_nonempty", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-24)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -11,     9,    15,   -24,   -24,   -24,    -1,   -24,   -24,     8,
      18,   -24,   -24,   -24,     3,    28,    33,   -24,   -24,   -24,
     -24,    14,    19,   -24,   -24,   -10,    29,    34,    14,    14,
      14,    14,    14,    14,    14,    40,    25,    22,   -24,    29,
      29,    29,    21,    26,    29,    29,    29,    29,   -24,   -24,
     -24,   -24,    40,    34,   -24,    14,    35,   -24,    29,   -24,
     -24,    -1,   -24,     7,     2,    14,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,    29,    14,   -24,    29,    29
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     3,     5,     1,     6,     4,     3,     9,
       0,     7,     3,     8,     2,     0,     0,    10,    11,    12,
      13,     0,     0,    51,    50,    49,    34,    15,     0,     0,
      52,     0,     0,     0,     0,    20,     0,    16,    17,    43,
      42,    54,     0,    53,    45,    46,    47,    48,    21,    22,
      23,    19,    20,     0,    44,     0,     0,    18,    55,     3,
      14,    25,     3,     0,    49,    40,    24,    26,    27,    29,
      30,    31,    32,    28,    33,     0,    39,    41,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -24,   -24,    -8,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,     4,     6,   -24,   -24,   -24,   -24,    -7,   -24,   -24,
     -24,   -24,   -24,   -24,   -23,   -24,   -24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     6,     3,     8,    11,    12,    17,    18,    36,
      37,    38,    51,    60,    62,    67,    68,    19,    20,    70,
      71,    72,    73,    76,    26,    42,    43
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       9,    28,    29,     1,    14,    39,    40,    41,    44,    45,
      46,    47,    23,    75,    29,     5,    15,    24,    30,    23,
      64,    16,     4,    10,    24,     7,    65,    25,    66,     7,
      30,    13,    58,     7,     7,    31,    32,    33,    34,    21,
      74,    27,    77,    48,    49,    50,    22,    35,    52,    53,
      54,    61,    78,    55,    63,    59,    69,    57,    56
};

static const yytype_int8 yycheck[] =
{
       8,    11,    12,    14,    12,    28,    29,    30,    31,    32,
      33,    34,     5,    11,    12,     0,    13,    10,    28,     5,
      13,    18,    13,    15,    10,    26,    19,    13,    21,    26,
      28,    13,    55,    26,    26,     6,     7,     8,     9,    11,
      63,    22,    65,     3,     4,     5,    13,    13,    23,    27,
      29,    59,    75,    27,    62,    20,    63,    53,    52
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    31,    33,    13,     0,    32,    26,    34,    32,
      15,    35,    36,    13,    32,    13,    18,    37,    38,    47,
      48,    11,    13,     5,    10,    13,    54,    22,    11,    12,
      28,     6,     7,     8,     9,    13,    39,    40,    41,    54,
      54,    54,    55,    56,    54,    54,    54,    54,     3,     4,
       5,    42,    23,    27,    29,    27,    42,    41,    54,    20,
      43,    32,    44,    32,    13,    19,    21,    45,    46,    47,
      49,    50,    51,    52,    54,    11,    53,    54,    54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    30,    31,    32,    32,    33,    34,    34,    35,    36,
      36,    37,    37,    37,    38,    39,    39,    40,    40,    41,
      42,    42,    42,    42,    43,    44,    44,    45,    45,    45,
      45,    45,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    53,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    55,    55,    56,    56
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     0,     2,     2,     0,     3,     2,     0,
       3,     1,     1,     1,     7,     0,     1,     1,     3,     2,
       0,     1,     1,     1,     5,     0,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     0,     0,     0,     2,
       0,     1,     3,     3,     4,     3,     3,     3,     3,     1,
       1,     1,     0,     1,     1,     3
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
  case 4: /* newlines: newlines NEWLINE  */
#line 86 "src/translate.y"
                       {
            if (print_newline_flag) {
                fprintf(fptr, "\n");
            } else {
                print_newline_flag = 1;
                break;
            }
            print_newline_flag = 0;
        }
#line 1322 "y.tab.c"
    break;

  case 5: /* package_decl: PACKAGE ID  */
#line 98 "src/translate.y"
                 {fprintf(fptr,"mod %s;\n", (yyvsp[0].str));}
#line 1328 "y.tab.c"
    break;

  case 8: /* import_decl: IMPORT ID  */
#line 107 "src/translate.y"
                {fprintf(fptr,"use %s;\n", map_library((yyvsp[0].str)));}
#line 1334 "y.tab.c"
    break;

  case 11: /* top_lvl_decl: func_decl  */
#line 116 "src/translate.y"
                { (yyval.expr) = (yyvsp[0].expr); }
#line 1340 "y.tab.c"
    break;

  case 12: /* top_lvl_decl: var_decl  */
#line 117 "src/translate.y"
               { (yyval.expr) = NULL; /* Skip top-level variable declarations */ }
#line 1346 "y.tab.c"
    break;

  case 13: /* top_lvl_decl: struct_decl  */
#line 118 "src/translate.y"
                  { (yyval.expr) = (yyvsp[0].expr); }
#line 1352 "y.tab.c"
    break;

  case 14: /* func_decl: FUNC ID LPAR param_list RPAR type block  */
#line 122 "src/translate.y"
                                              {
        char* temp;
        asprintf(&temp, "fn %s(", (yyvsp[-5].str));
        if (param_list_buffer) {
            char* temp2;
            asprintf(&temp2, "%s%s", temp, param_list_buffer);
            free(temp);
            temp = temp2;
            free(param_list_buffer);
            param_list_buffer = NULL;
        }
        fprintf(fptr, "%s) -> %s {\n", temp, convert_type((yyvsp[-1].str)));
        if (current_block) {
            fprintf(fptr, "%s", current_block);
            free(current_block);
            current_block = NULL;
        }
        fprintf(fptr, "}\n");
        (yyval.expr) = temp;
    }
#line 1377 "y.tab.c"
    break;

  case 15: /* param_list: %empty  */
#line 145 "src/translate.y"
      { param_list_buffer = strdup(""); }
#line 1383 "y.tab.c"
    break;

  case 17: /* param_list_nonempty: param  */
#line 150 "src/translate.y"
            {
        param_list_buffer = strdup((yyvsp[0].param).name);
        char* temp;
        asprintf(&temp, "%s: %s", (yyvsp[0].param).name, convert_type((yyvsp[0].param).type));
        param_list_buffer = temp;
    }
#line 1394 "y.tab.c"
    break;

  case 18: /* param_list_nonempty: param_list_nonempty ',' param  */
#line 156 "src/translate.y"
                                    {
        char* temp;
        asprintf(&temp, "%s, %s: %s", param_list_buffer, (yyvsp[0].param).name, convert_type((yyvsp[0].param).type));
        free(param_list_buffer);
        param_list_buffer = temp;
    }
#line 1405 "y.tab.c"
    break;

  case 19: /* param: ID type  */
#line 165 "src/translate.y"
              {
        (yyval.param).name = strdup((yyvsp[-1].str));
        (yyval.param).type = strdup(convert_type((yyvsp[0].str)));
        //fprintf(fptr, "%s: %s", $1, convert_type($2));
    }
#line 1415 "y.tab.c"
    break;

  case 20: /* type: %empty  */
#line 173 "src/translate.y"
                  { (yyval.str) = NULL; }
#line 1421 "y.tab.c"
    break;

  case 21: /* type: INT  */
#line 174 "src/translate.y"
          { (yyval.str) = (yyvsp[0].str); }
#line 1427 "y.tab.c"
    break;

  case 22: /* type: FLOAT  */
#line 175 "src/translate.y"
            { (yyval.str) = (yyvsp[0].str); }
#line 1433 "y.tab.c"
    break;

  case 23: /* type: STRING  */
#line 176 "src/translate.y"
             { (yyval.str) = (yyvsp[0].str); }
#line 1439 "y.tab.c"
    break;

  case 24: /* block: LBRACE newlines stmt_list newlines RBRACE  */
#line 180 "src/translate.y"
                                                {
        // Don't create new string, use what's accumulated
        if (!current_block) {
            current_block = strdup("");
        }
    }
#line 1450 "y.tab.c"
    break;

  case 25: /* stmt_list: %empty  */
#line 189 "src/translate.y"
      { current_block = strdup(""); }
#line 1456 "y.tab.c"
    break;

  case 26: /* stmt_list: stmt_list newlines statement  */
#line 190 "src/translate.y"
                                   {
        if ((yyvsp[0].expr)) {
            char* temp = current_block;
            asprintf(&current_block, "%s    %s\n", temp ? temp : "", (yyvsp[0].expr));
            free(temp);
        }
    }
#line 1468 "y.tab.c"
    break;

  case 27: /* statement: expr_stmt  */
#line 200 "src/translate.y"
                { (yyval.expr) = (yyvsp[0].expr); }
#line 1474 "y.tab.c"
    break;

  case 28: /* statement: return_stmt  */
#line 201 "src/translate.y"
                  { (yyval.expr) = (yyvsp[0].expr); }
#line 1480 "y.tab.c"
    break;

  case 29: /* statement: var_decl  */
#line 202 "src/translate.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1486 "y.tab.c"
    break;

  case 30: /* statement: if_stmt  */
#line 203 "src/translate.y"
              { (yyval.expr) = ""; }
#line 1492 "y.tab.c"
    break;

  case 31: /* statement: while_stmt  */
#line 204 "src/translate.y"
                 { (yyval.expr) = ""; }
#line 1498 "y.tab.c"
    break;

  case 32: /* statement: for_stmt  */
#line 205 "src/translate.y"
               { (yyval.expr) = ""; }
#line 1504 "y.tab.c"
    break;

  case 33: /* expr_stmt: expr  */
#line 209 "src/translate.y"
           { (yyval.expr) = (yyvsp[0].expr); }
#line 1510 "y.tab.c"
    break;

  case 34: /* var_decl: ID DECLARE_ASSIGN expr  */
#line 213 "src/translate.y"
                             {
        char* temp;
        asprintf(&temp, "let %s = %s;", (yyvsp[-2].str), (yyvsp[0].expr));
        (yyval.expr) = temp;
    }
#line 1520 "y.tab.c"
    break;

  case 35: /* struct_decl: %empty  */
#line 221 "src/translate.y"
      { (yyval.expr) = NULL; }
#line 1526 "y.tab.c"
    break;

  case 39: /* return_stmt: RETURN returnable  */
#line 237 "src/translate.y"
                        {
        char* temp;
        asprintf(&temp, "return %s;", (yyvsp[0].expr));
        (yyval.expr) = temp;
    }
#line 1536 "y.tab.c"
    break;

  case 40: /* returnable: %empty  */
#line 245 "src/translate.y"
                  { (yyval.expr) = strdup(""); }
#line 1542 "y.tab.c"
    break;

  case 41: /* returnable: expr  */
#line 246 "src/translate.y"
           { (yyval.expr) = (yyvsp[0].expr); }
#line 1548 "y.tab.c"
    break;

  case 42: /* expr: ID ASSIGN expr  */
#line 250 "src/translate.y"
                     {  
        char* temp;
        asprintf(&temp, "%s = %s;", (yyvsp[-2].str), (yyvsp[0].expr));
        (yyval.expr) = temp;
    }
#line 1558 "y.tab.c"
    break;

  case 43: /* expr: ID DECLARE_ASSIGN expr  */
#line 255 "src/translate.y"
                             { 
        char* temp;
        asprintf(&temp, "let %s = %s;", (yyvsp[-2].str), (yyvsp[0].expr));
        (yyval.expr) = temp;
    }
#line 1568 "y.tab.c"
    break;

  case 44: /* expr: ID '(' arg_list ')'  */
#line 260 "src/translate.y"
                          {
        char* temp;
        asprintf(&temp, "%s()", (yyvsp[-3].str));
        (yyval.expr) = temp;
    }
#line 1578 "y.tab.c"
    break;

  case 45: /* expr: expr '+' expr  */
#line 265 "src/translate.y"
                    { 
        char* temp;
        asprintf(&temp, "%s + %s", (yyvsp[-2].expr), (yyvsp[0].expr));
        (yyval.expr) = temp;
    }
#line 1588 "y.tab.c"
    break;

  case 46: /* expr: expr '-' expr  */
#line 270 "src/translate.y"
                    { 
        char* temp;
        asprintf(&temp, "%s - %s", (yyvsp[-2].expr), (yyvsp[0].expr));
        (yyval.expr) = temp;
    }
#line 1598 "y.tab.c"
    break;

  case 47: /* expr: expr '*' expr  */
#line 275 "src/translate.y"
                    { 
        char* temp;
        asprintf(&temp, "%s * %s", (yyvsp[-2].expr), (yyvsp[0].expr));
        (yyval.expr) = temp;
    }
#line 1608 "y.tab.c"
    break;

  case 48: /* expr: expr '/' expr  */
#line 280 "src/translate.y"
                    { 
        char* temp;
        asprintf(&temp, "%s / %s", (yyvsp[-2].expr), (yyvsp[0].expr));
        (yyval.expr) = temp;
    }
#line 1618 "y.tab.c"
    break;

  case 49: /* expr: ID  */
#line 285 "src/translate.y"
         { (yyval.expr) = (yyvsp[0].str); }
#line 1624 "y.tab.c"
    break;

  case 50: /* expr: NUMBER  */
#line 286 "src/translate.y"
             { (yyval.expr) = (yyvsp[0].str); }
#line 1630 "y.tab.c"
    break;

  case 51: /* expr: STRING  */
#line 287 "src/translate.y"
             { (yyval.expr) = (yyvsp[0].str); }
#line 1636 "y.tab.c"
    break;


#line 1640 "y.tab.c"

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

#line 299 "src/translate.y"


void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main() {
    fptr = fopen("test.rs", "w");
    yyparse();
    return 0;
}
