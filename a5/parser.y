%{
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
%}

%code requires{
    #include <string>
    #include "ast.hh"
    #include "symtab.hh"
}

%union{
    std::string * name;
    int value;
    double fvalue;
    Ast *ast;
    Expression_Ast *expr;
    Statement_Ast *stmt;
    Statement_List_Ast *stmt_list;
    std::vector<Expression_Ast*> *expr_list;
};

%token INTEGER FLOAT VOID WRITE READ STRING BOOL RETURN
%token IF ELSE WHILE DO
%token PLUS MINUS MULT DIV ASSIGN
%token SEMICOLON LPAREN RPAREN LBRACE RBRACE COMMA
%token AND OR NOT TERINARY COLON LT LE GT GE NE EQ

%token <value> INTEGER_NUMBER
%token <fvalue> FLOAT_NUMBER
%token <name> NAME
%token <name> STRING_LITERAL

%right TERINARY COLON
%left OR
%left AND
%right NOT
%nonassoc LT LE GT GE EQ NE
%left PLUS MINUS
%left MULT DIV
%right UMINUS

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%type <expr> expr const_as_operand rel_expr func_call_expr
%type <stmt> statement asg_stmt print_stmt read_stmt if_stmt while_stmt do_while_stmt compound_stmt return_stmt
%type <stmt_list> stmt_list
%type <ast> program func_def_list func_def
%type <expr_list> call_arg_list call_arg_list_nonempty

%start program
%%

program
    : global_decl_stmt_list func_def_list {
        if(!stop_parse){
            // Pass global variable list to prog_root for ASM .data section
            if(prog_root){
                std::vector<std::pair<std::string,Type>> gvars;
                for(const auto &sym : global_symtab.get_table())
                    if(sym.kind == SYM_VAR) gvars.push_back({sym.name, sym.type});
                prog_root->set_globals(gvars);
            }
            root = $2;
        } else root = nullptr;
        $$ = root;
    }
    | func_def_list {
        if(!stop_parse){
            if(prog_root){
                std::vector<std::pair<std::string,Type>> gvars;
                for(const auto &sym : global_symtab.get_table())
                    if(sym.kind == SYM_VAR) gvars.push_back({sym.name, sym.type});
                prog_root->set_globals(gvars);
            }
            root = $1;
        } else root = nullptr;
        $$ = root;
    }
    ;

global_decl_stmt_list:
    global_decl_stmt_list var_decl_stmt
    | global_decl_stmt_list funct_decl
    | var_decl_stmt
    | funct_decl
    ;

funct_decl:
    named_type NAME LPAREN param_list RPAREN SEMICOLON {
        if(!stop_parse){
            curr_symtab->declarefunc(*$2, current_decl_type, curr_params);
            curr_params.clear();
            curr_func_params.clear();
            func_decl_order.push_back(*$2);
        }
    }
    | named_type NAME LPAREN RPAREN SEMICOLON {
        if(!stop_parse){
            curr_symtab->declarefunc(*$2, current_decl_type, {});
            func_decl_order.push_back(*$2);
        }
    }
    ;

/* ── list of function definitions (L5: multiple functions) ─────── */
func_def_list
    : func_def_list func_def {
        $$ = $1;
    }
    | func_def {
        $$ = prog_root;
    }
    ;

/* ── single function definition ─────────────────────────────────── */
func_def
    : named_type NAME LPAREN param_list RPAREN LBRACE {
        if(!stop_parse){
            current_func_ret_type = current_decl_type;
            curr_symtab->definefunc(*$2, current_decl_type, curr_params);
            curr_params.clear();
            curr_symtab = new SymbolTable(&global_symtab);
            // Insert formal params into local scope
            for(auto &p : curr_func_params){
                curr_symtab->insert(p.name, p.type);
            }
        }
    }
    local_var_decl_stmt_list stmt_list RBRACE {
        if(!stop_parse){
            if(current_func_ret_type != TYPE_VOID && !$9->has_return())
                yyerror("Missing return statement in a non-void procedure");
            FuncDefNode *fn = new FuncDefNode(*$2, current_func_ret_type,
                                              curr_func_params, $9);
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
        $$ = prog_root;
    }
    | named_type NAME LPAREN RPAREN LBRACE {
        if(!stop_parse){
            current_func_ret_type = current_decl_type;
            curr_symtab->definefunc(*$2, current_decl_type, {});
            curr_symtab = new SymbolTable(&global_symtab);
        }
    }
    local_var_decl_stmt_list stmt_list RBRACE {
        if(!stop_parse){
            if(current_func_ret_type != TYPE_VOID && !$8->has_return())
                yyerror("Missing return statement in a non-void procedure");
            FuncDefNode *fn = new FuncDefNode(*$2, current_func_ret_type,
                                              {}, $8);
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
        $$ = prog_root;
    }
    ;

param_list
    : param_list COMMA param
    | param
    ;

param: param_type NAME {
    if(!stop_parse){
        FuncParam fp;
        fp.name = *$2;
        fp.type = currentfuncvartype;
        curr_func_params.push_back(fp);
    }
}
;

stmt_list
    : stmt_list statement {
        if(!stop_parse){
            $1->append($2);
            $$ = $1;
        } else { $$ = nullptr; }
    }
    | /* empty */
    {
        if(!stop_parse){
            $$ = new Statement_List_Ast();
        } else {
            $$ = nullptr;
        }
    }
    ;

statement
    : asg_stmt       { $$ = $1; }
    | print_stmt     { $$ = $1; }
    | read_stmt      { $$ = $1; }
    | if_stmt        { $$ = $1; }
    | while_stmt     { $$ = $1; }
    | do_while_stmt  { $$ = $1; }
    | compound_stmt  { $$ = $1; }
    | return_stmt    { $$ = $1; }
    | NAME LPAREN call_arg_list RPAREN SEMICOLON {
        if(!stop_parse){
            Symbol *sym = curr_symtab->lookupFunc(*$1);
            if(!sym) yyerror("undefined function");
            if($3->size() != sym->params.size()) yyerror("Actual and formal parameter counts do not match");
            if(sym->type != TYPE_VOID) yyerror("Return value of a procedure ignored");
            $$ = new FuncCallStmt_Ast(*$1, *$3, sym->type);
            delete $3;
        } else { $$ = nullptr; }
    }
    ;

named_type
    : INTEGER { current_decl_type = TYPE_INT; }
    | FLOAT   { current_decl_type = TYPE_FLOAT; }
    | STRING  { current_decl_type = TYPE_STRING; }
    | BOOL    { current_decl_type = TYPE_BOOL; }
    | VOID    { current_decl_type = TYPE_VOID; }
    ;

param_type
    : INTEGER { curr_params.push_back(TYPE_INT);    currentfuncvartype = TYPE_INT; }
    | FLOAT   { curr_params.push_back(TYPE_FLOAT);  currentfuncvartype = TYPE_FLOAT; }
    | STRING  { curr_params.push_back(TYPE_STRING); currentfuncvartype = TYPE_STRING; }
    | BOOL    { curr_params.push_back(TYPE_BOOL);   currentfuncvartype = TYPE_BOOL; }
    ;

var_decl_stmt
    : named_type var_decl_item_list SEMICOLON
    ;

var_decl_item_list
    : var_decl_item_list COMMA NAME
    {
        if(!stop_parse){
            if(curr_symtab->lookupLocal(*$3) != -1){
                yyerror("Var Already DECLARED!!");
            }
            curr_symtab->insert(*$3, current_decl_type);
        }
    }
    | NAME {
        if(!stop_parse){
            if(curr_symtab->lookupLocal(*$1) != -1){
                yyerror("Var Already DECLARED!!");
            }
            curr_symtab->insert(*$1, current_decl_type);
        }
    }
    ;

local_var_decl_stmt_list
    : local_var_decl_stmt_list var_decl_stmt
    | /* empty */
    ;

print_stmt
    : WRITE expr SEMICOLON {
        if(!stop_parse){
            $$ = new Print_Ast($2);
        } else {
            $$ = nullptr;
        }
    }
    ;

read_stmt
    : READ NAME SEMICOLON {
        if(!stop_parse){
            int idx = curr_symtab->lookup(*$2);
            if(idx == -1) yyerror("var not Declared (not found)!!!");
            $$ = new Read_Ast(new Name_Ast(*$2, curr_symtab));
        } else {
            $$ = nullptr;
        }
    }
    ;

asg_stmt:
    NAME ASSIGN expr SEMICOLON
    {
        if(!stop_parse){
            int idx = curr_symtab->lookup(*$1);
            if(idx == -1) yyerror("var not Declared (not found)!!!");
            $$ = new Assignment_Ast(new Name_Ast(*$1, curr_symtab), $3);
        } else {
            $$ = nullptr;
        }
    };

/* ── L5: return statement ─────────────────────────────────────── */
return_stmt
    : RETURN expr SEMICOLON {
        if(!stop_parse){
            $$ = new Return_Ast($2, current_func_ret_type);
        } else { $$ = nullptr; }
    }
    | RETURN SEMICOLON {
        if(!stop_parse){
            $$ = new Return_Ast(nullptr, current_func_ret_type);
        } else { $$ = nullptr; }
    }
    ;

/* ── L5: function call as expression ────────────────────────────── */
func_call_expr
    : NAME LPAREN call_arg_list RPAREN {
        if(!stop_parse){
            Symbol *sym = curr_symtab->lookupFunc(*$1);
            if(!sym) yyerror("undefined function");
            if($3->size() != sym->params.size()) yyerror("Actual and formal parameter counts do not match");
            std::vector<std::pair<std::string,Type>> fps;
            $$ = new FuncCallExpr_Ast(*$1, *$3, sym->type, fps);
            delete $3;
        } else { $$ = nullptr; }
    }
    ;

call_arg_list
    : call_arg_list_nonempty { $$ = $1; }
    | /* empty */ {
        if(!stop_parse){
            $$ = new std::vector<Expression_Ast*>();
        } else { $$ = nullptr; }
    }
    ;

call_arg_list_nonempty
    : call_arg_list_nonempty COMMA expr {
        if(!stop_parse){
            $1->push_back($3);
            $$ = $1;
        } else { $$ = nullptr; }
    }
    | expr {
        if(!stop_parse){
            $$ = new std::vector<Expression_Ast*>();
            $$->push_back($1);
        } else { $$ = nullptr; }
    }
    ;

expr
    : expr PLUS expr  { $$ = stop_parse ? nullptr : new Binary_Expr_Ast($1, OP_PLUS,  $3); }
    | expr MINUS expr { $$ = stop_parse ? nullptr : new Binary_Expr_Ast($1, OP_MINUS, $3); }
    | expr MULT expr  { $$ = stop_parse ? nullptr : new Binary_Expr_Ast($1, OP_MULT,  $3); }
    | expr DIV expr   { $$ = stop_parse ? nullptr : new Binary_Expr_Ast($1, OP_DIV,   $3); }
    | NOT expr        { $$ = stop_parse ? nullptr : new Unary_Expr_Ast($2, NOT_OP); }
    | MINUS expr %prec UMINUS { $$ = stop_parse ? nullptr : new Unary_Expr_Ast($2, UMINUS_OP); }
    | LPAREN expr RPAREN      { $$ = $2; }
    | expr TERINARY expr COLON expr { $$ = stop_parse ? nullptr : new ternexpr($1, $3, $5); }
    | rel_expr        { $$ = $1; }
    | func_call_expr  { $$ = $1; }
    | NAME {
        if(stop_parse){
            $$ = nullptr;
        } else {
            int idx = curr_symtab->lookup(*$1);
            if(idx == -1) yyerror("Undeclared variable");
            $$ = new Name_Ast(*$1, curr_symtab);
        }
    }
    | const_as_operand { $$ = $1; }
    ;

const_as_operand
    : INTEGER_NUMBER  { $$ = stop_parse ? nullptr : new Int_Const_Ast($1); }
    | FLOAT_NUMBER    { $$ = stop_parse ? nullptr : new Float_Const_Ast($1); }
    | STRING_LITERAL  { $$ = stop_parse ? nullptr : new String_Const_Ast($1); }
    ;

rel_expr
    : expr LT expr { $$ = stop_parse ? nullptr : new Relational_Expr_Ast($1, LT_OP, $3); }
    | expr LE expr { $$ = stop_parse ? nullptr : new Relational_Expr_Ast($1, LE_OP, $3); }
    | expr GT expr { $$ = stop_parse ? nullptr : new Relational_Expr_Ast($1, GT_OP, $3); }
    | expr GE expr { $$ = stop_parse ? nullptr : new Relational_Expr_Ast($1, GE_OP, $3); }
    | expr NE expr { $$ = stop_parse ? nullptr : new Relational_Expr_Ast($1, NE_OP, $3); }
    | expr EQ expr { $$ = stop_parse ? nullptr : new Relational_Expr_Ast($1, EQ_OP, $3); }
    | expr AND expr { $$ = stop_parse ? nullptr : new Relational_Expr_Ast($1, OP_AND, $3); }
    | expr OR expr  { $$ = stop_parse ? nullptr : new Relational_Expr_Ast($1, OP_OR,  $3); }
    ;

if_stmt
    : IF LPAREN expr RPAREN statement %prec LOWER_THAN_ELSE {
        if(!stop_parse){
            $$ = new If_Ast($3, $5);
        } else { $$ = nullptr; }
    }
    | IF LPAREN expr RPAREN statement ELSE statement {
        if(!stop_parse){
            $$ = new If_Else_Ast($3, $5, $7);
        } else { $$ = nullptr; }
    }
    ;

while_stmt
    : WHILE LPAREN expr RPAREN statement {
        if(!stop_parse){
            $$ = new While_Ast($3, $5);
        } else { $$ = nullptr; }
    }
    ;

do_while_stmt
    : DO statement WHILE LPAREN expr RPAREN SEMICOLON {
        if(!stop_parse){
            $$ = new Do_While_Ast($5, $2);
        } else { $$ = nullptr; }
    }
    ;

compound_stmt
    : LBRACE stmt_list RBRACE {
        if(!stop_parse){
            $$ = new Compound_Stmt($2);
        } else { $$ = nullptr; }
    }
    ;

%%

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
