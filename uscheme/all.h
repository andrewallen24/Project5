/* {\Tt all.h} for \uscheme S318a */
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __GNUC__
#define __noreturn __attribute__((noreturn))
#else
#define __noreturn
#endif

/* early type definitions for \uscheme S309c */
typedef struct Valuelist *Valuelist;     // list of Value
/* type definitions for \uscheme (generated by a script) */
typedef struct Lambda Lambda; 
typedef struct Value Value;
typedef enum { SYM, NUM, BOOLV, NIL, PAIR, CLOSURE, PRIMITIVE } Valuealt;

/* type definitions for \uscheme (generated by a script) */
typedef struct Def *Def;
typedef enum { VAL, EXP, DEFINE, DEFS } Defalt; 
typedef struct Exp *Exp;
typedef enum {
    LITERAL, VAR, SET, IFX, WHILEX, BEGIN, APPLY, LETX, LAMBDAX
} Expalt;

typedef struct XDef *XDef;
typedef enum { DEF, USE, TEST } XDefalt; 
typedef struct UnitTest *UnitTest;
typedef enum { CHECK_EXPECT, CHECK_ASSERT, CHECK_ERROR } UnitTestalt;

/* type definitions for \uscheme 145b */
typedef enum Letkeyword { LET, LETSTAR, LETREC } Letkeyword;
/* type definitions for \uscheme 152b */
typedef Value (Primitive)(Exp e, int tag, Valuelist vs);
/* type definitions for \uscheme 153a */
typedef struct Env *Env;
/* type definitions for \uscheme S309b */
typedef struct UnitTestlist  *UnitTestlist;  // list of UnitTest 
typedef struct Explist  *Explist;            // list of Exp 
typedef struct Deflist  *Deflist;            // list of Def    /*OMIT*/
/* type definitions for \uscheme S312c */
enum {
  #define xx(NAME, TAG, FUNCTION) TAG,
  #include "prim.h"
  #undef xx
  UNUSED_TAG
};
/* shared type definitions 43a */
typedef struct Name *Name;
typedef struct Namelist *Namelist;   // list of Name
/* shared type definitions (generated by a script) */
typedef struct Par *Par;
typedef enum { ATOM, LIST } Paralt; 
/* shared type definitions S197a */
typedef struct ParserState *ParserState;
typedef struct ParsingContext *ParsingContext;
/* shared type definitions S197d */
typedef enum ParserResult {
  PARSED,            // some input was parsed without any errors
  INPUT_EXHAUSTED,   // there aren't enough inputs
  INPUT_LEFTOVER,    // there are too many inputs
  BAD_INPUT,         // an input wasn't what it should have been
  STOP_PARSING       // all the inputs have been parsed; it's time to stop
} ParserResult;
/* shared type definitions S197e */
typedef ParserResult (*ShiftFun)(ParserState);
/* shared type definitions S201d */
typedef struct ParserRow *ParserTable;
/* shared type definitions S209a */
enum Sugar {
  CAND, COR,    // short-circuit Boolean operators

  WHILESTAR, DO_WHILE, FOR,     // bonus loop forms

  WHEN, UNLESS,       // single-sided conditionals

  RECORD,             // record-type definition

  COND                // McCarthy's conditional from Lisp

};
/* shared type definitions S165a */
typedef struct Linestream *Linestream;
/* shared type definitions S168c */
typedef struct Parlist *Parlist; /* list of Par */
/* shared type definitions S168d */
typedef struct Parstream *Parstream;
/* shared type definitions S174a */
typedef struct Printbuf *Printbuf;
/* shared type definitions S177a */
/* definition of [[va_list_box]] S177b */
typedef struct va_list_box {
  va_list ap;
} va_list_box;
typedef void Printer(Printbuf output, va_list_box *args);
/* shared type definitions S293a */
typedef struct XDefstream *XDefstream;
/* shared type definitions S293d */
typedef enum Prompts { NOT_PROMPTING, PROMPTING } Prompts;
/* shared type definitions S293f */
typedef enum Echo { NOT_ECHOING, ECHOING } Echo;
/* shared type definitions S293h */
typedef struct Sourceloc *Sourceloc;
/* shared type definitions S294a */
typedef enum ErrorFormat { WITH_LOCATIONS, WITHOUT_LOCATIONS } ErrorFormat;
/* shared type definitions S300e */
typedef enum TestResult { TEST_PASSED, TEST_FAILED } TestResult;

/* structure definitions for \uscheme (generated by a script) */
struct Lambda { Namelist formals; Exp body; }; 
struct Value {
    Valuealt alt;
    union {
        Name sym;
        int32_t num;
        bool boolv;
        struct { Value *car; Value *cdr; } pair;
        struct { Lambda lambda; Env env; } closure;
        struct { int tag; Primitive *function; } primitive;
    } ;
};

/* structure definitions for \uscheme (generated by a script) */
struct Def {
    Defalt alt;
    union {
        struct { Name name; Exp exp; } val;
        Exp exp;
        struct { Name name; Lambda lambda; } define;
        Deflist defs;
    } ;
};

struct Exp {
    Expalt alt;
    union {
        Value literal;
        Name var;
        struct { Name name; Exp exp; } set;
        struct { Exp cond; Exp truex; Exp falsex; } ifx;
        struct { Exp cond; Exp body; } whilex;
        Explist begin;
        struct { Exp fn; Explist actuals; } apply;
        struct { Letkeyword let; Namelist xs; Explist es; Exp body; } letx;
        Lambda lambdax;
    } ;
};

struct XDef { XDefalt alt; union { Def def; Name use; UnitTest test; } ; };

struct UnitTest {
    UnitTestalt alt;
    union {
        struct { Exp check; Exp expect; } check_expect;
        Exp check_assert;
        Exp check_error;
    } ;
};

/* structure definitions for \uscheme (generated by a script) */
struct Parlist {
   Par hd;
   struct Parlist *tl;
};

struct Namelist {
   Name hd;
   struct Namelist *tl;
};

struct UnitTestlist {
   UnitTest hd;
   struct UnitTestlist *tl;
};

struct Explist {
   Exp hd;
   struct Explist *tl;
};

struct Deflist {
   Def    /*OMIT*/ hd;
   struct Deflist *tl;
};

struct Valuelist {
   Value hd;
   struct Valuelist *tl;
};

/* structure definitions for \uscheme S322a */
struct Component {
    Exp exp;
    Explist exps;
    Name name;
    Namelist names;
    Value value;
    /* fields of \uscheme\ [[Component]] added in exercises S324d */
    /* if implementing COND, add a question-answer field here */
    /* fields of \uscheme\ [[Component]] added in exercises S636g */
    // for COND:
    struct qa_pairs { Explist questions; Explist answers; } qa_pairs;
};
/* shared structure definitions (generated by a script) */
struct Par { Paralt alt; union { Name atom; Parlist list; } ; }; 
/* shared structure definitions S196b */
#define MAXCOMPS 4 // max # of components in any syntactic form
struct ParserState {
    int nparsed;       // number of components parsed so far
    struct Component components[MAXCOMPS];  // those components
    Parlist input;     // the part of the input not yet parsed

    struct ParsingContext {   // context of this parse
        Par par;       // the original thing being parsed
        struct Sourceloc {
            int line;                // current line number
            const char *sourcename;  // where the line came from
        } *source;
        Name name;     // a keyword, or name of a function being defined
    } context;
};
/* shared structure definitions S201a */
struct ParserRow {
    const char *keyword;
    int code;
    ShiftFun *shifts;  // points to array of shift functions
};
/* shared structure definitions S166a */
struct Linestream {
    char *buf;               // holds the last line read
    int bufsize;             // size of buf

    struct Sourceloc source; // where the last line came from
    FILE *fin;               // non-NULL if filelines
    const char *s;           // non-NULL if stringlines
};

/* function prototypes for \uscheme (generated by a script) */
Lambda mkLambda(Namelist formals, Exp body);
Value mkSym(Name sym);
Value mkNum(int32_t num);
Value mkBoolv(bool boolv);
Value mkNil(void);
Value mkPair(Value *car, Value *cdr);
Value mkClosure(Lambda lambda, Env env);
Value mkPrimitive(int tag, Primitive *function);
/* function prototypes for \uscheme (generated by a script) */
Def mkVal(Name name, Exp exp);
Def mkExp(Exp exp);
Def mkDefine(Name name, Lambda lambda);
Def mkDefs(Deflist defs);
struct Def mkValStruct(Name name, Exp exp);
struct Def mkExpStruct(Exp exp);
struct Def mkDefineStruct(Name name, Lambda lambda);
struct Def mkDefsStruct(Deflist defs);
Exp mkLiteral(Value literal);
Exp mkVar(Name var);
Exp mkSet(Name name, Exp exp);
Exp mkIfx(Exp cond, Exp truex, Exp falsex);
Exp mkWhilex(Exp cond, Exp body);
Exp mkBegin(Explist begin);
Exp mkApply(Exp fn, Explist actuals);
Exp mkLetx(Letkeyword let, Namelist xs, Explist es, Exp body);
Exp mkLambdax(Lambda lambdax);
struct Exp mkLiteralStruct(Value literal);
struct Exp mkVarStruct(Name var);
struct Exp mkSetStruct(Name name, Exp exp);
struct Exp mkIfxStruct(Exp cond, Exp truex, Exp falsex);
struct Exp mkWhilexStruct(Exp cond, Exp body);
struct Exp mkBeginStruct(Explist begin);
struct Exp mkApplyStruct(Exp fn, Explist actuals);
struct Exp mkLetxStruct(Letkeyword let, Namelist xs, Explist es, Exp body);
struct Exp mkLambdaxStruct(Lambda lambdax);
XDef mkDef(Def def);
XDef mkUse(Name use);
XDef mkTest(UnitTest test);
struct XDef mkDefStruct(Def def);
struct XDef mkUseStruct(Name use);
struct XDef mkTestStruct(UnitTest test);
UnitTest mkCheckExpect(Exp check, Exp expect);
UnitTest mkCheckAssert(Exp check_assert);
UnitTest mkCheckError(Exp check_error);
struct UnitTest mkCheckExpectStruct(Exp check, Exp expect);
struct UnitTest mkCheckAssertStruct(Exp check_assert);
struct UnitTest mkCheckErrorStruct(Exp check_error);
/* function prototypes for \uscheme (generated by a script) */
int     lengthPL(Parlist ps);
Par     nthPL   (Parlist ps, unsigned n);
Parlist mkPL    (Par p, Parlist ps);
Parlist popPL   (Parlist ps);
Printer printparlist;

int      lengthNL(Namelist ns);
Name     nthNL   (Namelist ns, unsigned n);
Namelist mkNL    (Name n, Namelist ns);
Namelist popNL   (Namelist ns);
Printer  printnamelist;

int          lengthUL(UnitTestlist us);
UnitTest     nthUL   (UnitTestlist us, unsigned n);
UnitTestlist mkUL    (UnitTest u, UnitTestlist us);
UnitTestlist popUL   (UnitTestlist us);
Printer      printunittestlist;

int     lengthEL(Explist es);
Exp     nthEL   (Explist es, unsigned n);
Explist mkEL    (Exp e, Explist es);
Explist popEL   (Explist es);
Printer printexplist;

int     lengthDL(Deflist ds);
Def    /*OMIT*/ nthDL   (Deflist ds, unsigned n);
Deflist mkDL    (Def    /*OMIT*/ d, Deflist ds);
Deflist popDL   (Deflist ds);
Printer printdeflist;

int       lengthVL(Valuelist vs);
Value     nthVL   (Valuelist vs, unsigned n);
Valuelist mkVL    (Value v, Valuelist vs);
Valuelist popVL   (Valuelist vs);
Printer   printvaluelist;

/* function prototypes for \uscheme 153b */
Value *find(Name name, Env env);
/* function prototypes for \uscheme 153c */
Env bindalloc    (Name name,   Value v,      Env env);
Env bindalloclist(Namelist xs, Valuelist vs, Env env);
/* function prototypes for \uscheme 154a */
Value *allocate(Value v);
/* function prototypes for \uscheme 154b */
extern Value truev, falsev;
/* function prototypes for \uscheme 154c */
bool istrue(Value v);
/* function prototypes for \uscheme 154d */
Value unspecified(void);
/* function prototypes for \uscheme 155a */
Value eval   (Exp e, Env rho);
Env   evaldef(Def d, Env rho, Echo echo);
/* function prototypes for \uscheme ((elided)) (THIS CAN'T HAPPEN -- claimed code was not used) */
Exp desugarLetStar(Namelist xs, Explist es, Exp body);
Exp desugarLet    (Namelist xs, Explist es, Exp body);
/* function prototypes for \uscheme S309d */
void initallocate(Env *globals);
/* function prototypes for \uscheme S309e */
void initvalue(void);
/* function prototypes for \uscheme S310a */
void readevalprint(XDefstream xdefs, Env *envp, Echo echo);
/* function prototypes for \uscheme S310c */
void addprimitives(Env *envp);
/* function prototypes for \uscheme S310d */
void printenv    (Printbuf, va_list_box*);
void printvalue  (Printbuf, va_list_box*);
void printexp    (Printbuf, va_list_box*);
void printdef    (Printbuf, va_list_box*);
void printlambda (Printbuf, va_list_box*);
/* function prototypes for \uscheme S311d */
void process_tests(UnitTestlist tests, Env rho);
/* function prototypes for \uscheme S313c */
Value cons(Value v, Value w);

/*prob two*/
Value list(Valuelist args);


Value equalatoms(Value v, Value w);
/* function prototypes for \uscheme S325c */
Value parsesx(Par p, Sourceloc source);
struct Component parseletbindings(ParsingContext context, Parlist input);
/* function prototypes for \uscheme S333a */
int number_of_good_tests(UnitTestlist tests, Env rho);
/* function prototypes for \uscheme S333c */
TestResult test_result(UnitTest t, Env rho);
/* function prototypes for \uscheme S335g */
bool equalpairs(Value v, Value w);
/* function prototypes for \uscheme S336a */
Exp testexp(Exp);
/* function prototypes for \uscheme S337a */
Name namecat(Name n1, Name n2);
/* function prototypes for \uscheme S635g */
Exp desugarAnd(Explist args);
/* function prototypes for \uscheme S635i */
Namelist freevars(Exp e, Namelist bound, Namelist free);
/* function prototypes for \uscheme S636d */
Exp desugarOr(Explist args);
/* function prototypes for \uscheme S636i */
Exp desugarCond(Explist questions, Explist answers);
/* function prototypes for \uscheme S638f */
Deflist desugarRecord(Name recname, Namelist fieldnames);
/* shared function prototypes 43b */
Name strtoname(const char *s);
const char *nametostr(Name x);
/* shared function prototypes 46b */
void print (const char *fmt, ...);  // print to standard output
void fprint(FILE *output, const char *fmt, ...);  // print to given file
/* shared function prototypes 47a */
__noreturn // OMIT
void runerror (const char *fmt, ...);
extern jmp_buf errorjmp;        // longjmp here on error
/* shared function prototypes 47b */
__noreturn // OMIT
void synerror (Sourceloc src, const char *fmt, ...);
/* shared function prototypes 47c */
void checkargc(Exp e, int expected, int actual);
/* shared function prototypes (generated by a script) */
Par mkAtom(Name atom);
Par mkList(Parlist list);
struct Par mkAtomStruct(Name atom);
struct Par mkListStruct(Parlist list);
/* shared function prototypes S192a */
Exp  parseexp (Par p, Sourceloc source);
XDef parsexdef(Par p, Sourceloc source);
/* shared function prototypes S192b */
Exp exp_of_atom(Sourceloc loc, Name atom);
/* shared function prototypes S195a */
Exp  reduce_to_exp (int alt, struct Component *components);
XDef reduce_to_xdef(int alt, struct Component *components);
/* shared function prototypes S197c */
struct ParserState mkParserState(Par p, Sourceloc source);
/* shared function prototypes S197f */
ParserResult sExp     (ParserState state);  // shift 1 input into Exp
ParserResult sExps    (ParserState state);  // shift all inputs into Explist
ParserResult sName    (ParserState state);  // shift 1 input into Name
ParserResult sNamelist(ParserState state);  // shift 1 input into Namelist
/* shared function prototypes S198b */
void halfshift(ParserState state); // advance input, check for room in output
/* shared function prototypes S198e */
Explist parseexplist(Parlist p, Sourceloc source);
/* shared function prototypes S199b */
Name parsename(Par p, ParsingContext context);
/* shared function prototypes S200a */
ParserResult stop(ParserState state);
/* shared function prototypes S200c */
ParserResult setcontextname(ParserState state);
/* shared function prototypes S200f */
ParserResult sLocals(ParserState state);
                 // shift locals if [locals x y z ...]
/* shared function prototypes S201c */
void rowparse(struct ParserRow *table, ParserState s);
__noreturn /* OMIT */
void usage_error(int alt, ParserResult r, ParsingContext context);
/* shared function prototypes S202a */
struct ParserRow *tableparse(ParserState state, ParserTable t);
/* shared function prototypes S205b */
ParserResult use_exp_parser(ParserState state);
/* shared function prototypes S208c */
int code_of_name(Name n);
/* shared function prototypes S208d */
void check_exp_duplicates(Sourceloc source, Exp e);
void check_def_duplicates(Sourceloc source, Def d);
/* shared function prototypes S165b */
char *getline_(Linestream r, const char *prompt);
/* shared function prototypes S165c */
Linestream stringlines(const char *stringname, const char *s);
Linestream filelines  (const char *filename,   FILE *fin);
/* shared function prototypes S168e */
Parstream parstream(Linestream lines, Prompts prompts);
Par       getpar   (Parstream r);
Sourceloc parsource(Parstream pars);
/* shared function prototypes S169a */
extern bool read_tick_as_quote;
/* shared function prototypes S174b */
Printbuf printbuf(void);
void freebuf(Printbuf *);
/* shared function prototypes S174c */
void bufput(Printbuf, char);
void bufputs(Printbuf, const char*);
void bufreset(Printbuf);
/* shared function prototypes S174d */
char *bufcopy(Printbuf);
void fwritebuf(Printbuf buf, FILE *output);
/* shared function prototypes S176d */
void print (const char *fmt, ...);                  // print to standard output
void fprint(FILE *output, const char *fmt, ...);    // print to given file
void bprint(Printbuf output, const char *fmt, ...); // print to given buffer
/* shared function prototypes S176e */
void installprinter(unsigned char specifier, Printer *take_and_print);
/* shared function prototypes S177c */
void vbprint(Printbuf output, const char *fmt, va_list_box *box);
/* shared function prototypes S179c */
Printer printpercent, printstring, printdecimal, printchar, printname, 
        printpointer;
/* shared function prototypes S180e */
Printer printpar;
/* shared function prototypes S181a */
typedef enum ErrorMode { NORMAL, TESTING } ErrorMode;
void set_error_mode(ErrorMode mode);
extern jmp_buf testjmp;    // if error occurs during a test, longjmp here
extern Printbuf errorbuf;  // if error occurs during a test, message is here
/* shared function prototypes S184a */
__noreturn // OMIT
void othererror (const char *fmt, ...);
/* shared function prototypes S184d */
Name duplicatename(Namelist names);
/* shared function prototypes S186a */
extern int  checkoverflow(int limit);
extern void reset_overflow_check(void);
/* shared function prototypes S187b */
extern void checkarith(char operation, int32_t n, int32_t m, int precision);
/* shared function prototypes S188a */
void fprint_utf8(FILE *output, unsigned code_point);
void print_utf8 (unsigned u);
/* shared function prototypes S293b */
XDef getxdef(XDefstream xdefs);
/* shared function prototypes S293c */
XDefstream stringxdefs(const char *stringname, const char *input);
XDefstream filexdefs  (const char *filename, FILE *input, Prompts prompts);
/* shared function prototypes S293g */
void installprinter(unsigned char c, Printer *take_and_print);
/* shared function prototypes S294b */
void set_toplevel_error_format(ErrorFormat format);
/* shared function prototypes S300c */
void report_test_results(int npassed, int ntests);
/* shared function prototypes S304d */
Printer printexp, printdef, printvalue, printfun;
/* shared function prototypes S312b */
Primitive arith, binary, unary, someArgs;
/* shared function prototypes S322c */
ParserResult sSexp    (ParserState state);
ParserResult sBindings(ParserState state);
/* shared function prototypes S324j */
void extendSyntax(void);

/* macro definitions used in parsing S195d */
#define ANEXP(ALT)  (  0+(ALT))
#define ADEF(ALT)   (100+(ALT))
#define ATEST(ALT)  (200+(ALT))
#define ANXDEF(ALT) (300+(ALT))
#define ALET(ALT)   (400+(ALT))
#define SUGAR(CODE) (500+(CODE))
#define LATER       1000
#define EXERCISE    1001
/* declarations of globals used in lexical analysis and parsing S202e */
extern struct ParserRow exptable[];
extern struct ParserRow xdeftable[];
/* declarations of globals used in lexical analysis and parsing S206b */
extern struct Usage {
    int code;             // codes for form in reduce_to_exp or reduce_to_xdef
    const char *expected; // shows the expected usage of the identified form
} usage_table[];
