#ifndef AST_HH
#define AST_HH

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "types.hh"
#include "symtab.hh"
// #include "rtl.hh"     // rtl.hh already includes tac.hh
#include "asm.hh"
using namespace std;
extern FILE *astfile;
extern int show_ast;

extern void yyerror(const char *s);
inline void sem_error(const std::string &msg){ yyerror(msg.c_str()); }
inline void sem_error(const char *msg)       { yyerror(msg); }

inline std::string type_to_string(Type t){
    switch(t){
        case TYPE_INT:    return "int";
        case TYPE_FLOAT:  return "float";
        case TYPE_STRING: return "string";
        case TYPE_BOOL:   return "bool";
        case TYPE_VOID:   return "void";
        default:          return "error";
    }
}

class Ast {
public:
    virtual void print(int indent = 0) = 0;
    virtual TACResult gen_tac() { return TACResult(); }
    virtual ~Ast() {}
};

inline void do_indent(int n){
    for(int i = 0; i < n; i++) fprintf(astfile, " ");
}

class Expression_Ast : public Ast {
protected:
    Type type;
public:
    Type getType() const { return type; }
    virtual bool closes_own_rhs() const { return false; }
};

// ── leaf nodes ────────────────────────────────────────────────────────────────

class Int_Const_Ast : public Expression_Ast {
    int value;
public:
    Int_Const_Ast(int v) : value(v) { type = TYPE_INT; }
    void print(int) override {
        fprintf(astfile, "Num : %d<int>", value);
    }
    TACResult gen_tac() override {
        TACResult r;
        r.result = new Int_TAC_Opd(value);
        return r;
    }
};

class Float_Const_Ast : public Expression_Ast {
    double value;
public:
    Float_Const_Ast(double v) : value(v) { type = TYPE_FLOAT; }
    void print(int) override {
        fprintf(astfile, "Num : %.2f<float>", value);
    }
    TACResult gen_tac() override {
        TACResult r;
        r.result = new Float_TAC_Opd(value);
        return r;
    }
};

class String_Const_Ast : public Expression_Ast {
    string value;
public:
    String_Const_Ast(std::string *v) : value(*v) { type = TYPE_STRING; }
    void print(int) override {
        fprintf(astfile, "String : %s<string>", value.c_str());
    }
    TACResult gen_tac() override {
        TACResult r;
        r.result = new String_TAC_Opd(value);
        return r;
    }
};

class Name_Ast : public Expression_Ast {
    string name;
public:
    Name_Ast(const std::string &n, SymbolTable *symtab) : name(n) {
        type = symtab->lookupType(n);
    }
    void print(int) override {
        fprintf(astfile, "Name : %s_<%s>", name.c_str(), type_to_string(type).c_str());
    }
    TACResult gen_tac() override {
        TACResult r;
        r.result = new Variable_TAC_Opd(name, type);
        return r;
    }
};

// ── binary arithmetic ─────────────────────────────────────────────────────────

enum BinaryOp { OP_PLUS, OP_MINUS, OP_MULT, OP_DIV };

inline const string opToStr(BinaryOp op){
    switch(op){
        case OP_PLUS:  return "Plus";
        case OP_MINUS: return "Minus";
        case OP_MULT:  return "Mult";
        case OP_DIV:   return "Div";
        default:       return "Unknown";
    }
}

class Binary_Expr_Ast : public Expression_Ast {
    Expression_Ast *lhs, *rhs;
    BinaryOp op;
public:
    Binary_Expr_Ast(Expression_Ast *l, BinaryOp o, Expression_Ast *r)
        : lhs(l), rhs(r), op(o)
    {
        if(lhs->getType() != TYPE_INT && lhs->getType() != TYPE_FLOAT)
            sem_error(std::string("wrong type of operand to ") + opToStr(op));
        if(lhs->getType() != rhs->getType())
            sem_error(std::string("type mismatch on both sides of ") + opToStr(op));
        type = lhs->getType();
    }
    void print(int indent_lvl) override {
        fprintf(astfile, "\n");
        do_indent(indent_lvl);
        fprintf(astfile, "Arith: %s<%s>\n", opToStr(op).c_str(), type_to_string(type).c_str());

        do_indent(indent_lvl + 1);
        fprintf(astfile, "L_Opd (");
        lhs->print(indent_lvl + 3);
        fprintf(astfile, ")\n");

        do_indent(indent_lvl + 1);
        fprintf(astfile, "R_Opd (");
        rhs->print(indent_lvl + 3);
        fprintf(astfile, ")");
    }
    TACResult gen_tac() override {
        TACResult r;
        TACResult lr = lhs->gen_tac();
        TACResult rr = rhs->gen_tac();
        r.append(lr);
        r.append(rr);
        std::string op_str;
        switch(op){
            case OP_PLUS:  op_str = "+";  break;
            case OP_MINUS: op_str = "-";  break;
            case OP_MULT:  op_str = "*";  break;
            case OP_DIV:   op_str = "/";  break;
        }
        std::string tname = fresh_temp();
        TAC_Opd* dst = new Temp_TAC_Opd(tname, type);
        r.emit(new Compute_TAC_Stmt(dst, lr.result, op_str, rr.result));
        r.result = dst;
        return r;
    }
};

// ── relational / logical ──────────────────────────────────────────────────────

enum RelOp { LT_OP, LE_OP, GT_OP, GE_OP, EQ_OP, NE_OP, OP_AND, OP_OR };

inline const string RelOpToStr(RelOp op){
    switch(op){
        case LT_OP:  return "LT";
        case LE_OP:  return "LE";
        case GT_OP:  return "GT";
        case GE_OP:  return "GE";
        case EQ_OP:  return "EQ";
        case NE_OP:  return "NE";
        case OP_AND: return "AND";
        case OP_OR:  return "OR";
        default:     return "Unknown";
    }
}

class Relational_Expr_Ast : public Expression_Ast {
    Expression_Ast *lhs, *rhs;
    RelOp op;
public:
    Relational_Expr_Ast(Expression_Ast *l, RelOp o, Expression_Ast *r)
        : lhs(l), rhs(r), op(o)
    {
        if(op == OP_AND || op == OP_OR){
            if(lhs->getType() != TYPE_BOOL)
                sem_error(std::string("wrong type of operand to ") + RelOpToStr(op));
            if(lhs->getType() != rhs->getType())
                sem_error(std::string("type mismatch on both sides of ") + RelOpToStr(op));
        } else {
            if(lhs->getType() != TYPE_INT && lhs->getType() != TYPE_FLOAT)
                sem_error(std::string("wrong type of operand to ") + RelOpToStr(op));
            if(lhs->getType() != rhs->getType())
                sem_error(std::string("type mismatch on both sides of ") + RelOpToStr(op));
        }
        type = TYPE_BOOL;
    }
    void print(int indent_lvl) override {
        fprintf(astfile, "\n");
        do_indent(indent_lvl);
        fprintf(astfile, "Condition: %s<bool>\n", RelOpToStr(op).c_str());

        do_indent(indent_lvl + 1);
        fprintf(astfile, "L_Opd (");
        lhs->print(indent_lvl + 3);
        fprintf(astfile, ")\n");

        do_indent(indent_lvl + 1);
        fprintf(astfile, "R_Opd (");
        rhs->print(indent_lvl + 3);
        fprintf(astfile, ")");
    }
    TACResult gen_tac() override {
        TACResult r;
        TACResult lr = lhs->gen_tac();
        TACResult rr = rhs->gen_tac();
        r.append(lr);
        r.append(rr);
        std::string op_str;
        switch(op){
            case LT_OP:  op_str = "<";  break;
            case LE_OP:  op_str = "<="; break;
            case GT_OP:  op_str = ">";  break;
            case GE_OP:  op_str = ">="; break;
            case EQ_OP:  op_str = "=="; break;
            case NE_OP:  op_str = "!="; break;
            case OP_AND: op_str = "&&"; break;
            case OP_OR:  op_str = "||"; break;
        }
        std::string tname = fresh_temp();
        TAC_Opd* dst = new Temp_TAC_Opd(tname, TYPE_BOOL);
        r.emit(new Compute_TAC_Stmt(dst, lr.result, op_str, rr.result));
        r.result = dst;
        return r;
    }
};

// ── unary ─────────────────────────────────────────────────────────────────────

enum UnaryOp { UMINUS_OP, NOT_OP };

class Unary_Expr_Ast : public Expression_Ast {
    Expression_Ast *operand;
    UnaryOp op;
public:
    Unary_Expr_Ast(Expression_Ast *l, UnaryOp o)
        : operand(l), op(o)
    {
        if(op == UMINUS_OP){
            if(operand->getType() != TYPE_INT && operand->getType() != TYPE_FLOAT)
                sem_error("UMinus operand must be int or float");
            type = operand->getType();
        } else {
            if(operand->getType() != TYPE_BOOL)
                sem_error("NOT operand must be bool");
            type = TYPE_BOOL;
        }
    }
    void print(int indent_lvl) override {
        if(op == UMINUS_OP){
            fprintf(astfile, "\n");
            do_indent(indent_lvl);
            fprintf(astfile, "Arith: Uminus<%s>\n", type_to_string(type).c_str());
            do_indent(indent_lvl + 1);
            fprintf(astfile, "L_Opd (");
            operand->print(indent_lvl + 3);
            fprintf(astfile, ")");
        } else {
            fprintf(astfile, "\n");
            do_indent(indent_lvl);
            fprintf(astfile, "Condition: NOT<bool>\n");
            do_indent(indent_lvl + 1);
            fprintf(astfile, "L_Opd (");
            operand->print(indent_lvl + 3);
            fprintf(astfile, ")");
        }
    }
    TACResult gen_tac() override {
        TACResult r;
        TACResult or_ = operand->gen_tac();
        r.append(or_);
        std::string tname = fresh_temp();
        TAC_Opd* dst = new Temp_TAC_Opd(tname, type);
        std::string op_str = (op == UMINUS_OP) ? "-" : "!";
        r.emit(new Compute_TAC_Stmt(dst, or_.result, op_str, nullptr));
        r.result = dst;
        return r;
    }
};

// ── ternary ───────────────────────────────────────────────────────────────────

class ternexpr : public Expression_Ast {
    Expression_Ast *cond, *tpart, *fpart;
public:
    ternexpr(Expression_Ast *c, Expression_Ast *t, Expression_Ast *f)
        : cond(c), tpart(t), fpart(f)
    {
        if(cond->getType() != TYPE_BOOL)
            sem_error("wrong type of condition in ternary expr");
        if(tpart->getType() != fpart->getType())
            sem_error("type mismatch of true and false parts in ternary expr");
        type = tpart->getType();
    }
    ~ternexpr() {}

    bool closes_own_rhs() const override { return true; }

    void print(int indent_lvl) override {
        cond->print(indent_lvl);
        fprintf(astfile, "\n");

        do_indent(indent_lvl - 2);
        fprintf(astfile, "True_Part (");
        tpart->print(indent_lvl);
        fprintf(astfile, ")\n");

        do_indent(indent_lvl - 2);
        fprintf(astfile, "False_Part (");
        fpart->print(indent_lvl);
        fprintf(astfile, ")");
    }

    TACResult gen_tac() override {
        TACResult r;
        TACResult cr = cond->gen_tac();
        std::string lfalse = fresh_label();
        std::string lend   = fresh_label();
        std::string sname  = fresh_stemp();
        TAC_Opd* dst = new Temp_TAC_Opd(sname, type);
        TACResult tr = tpart->gen_tac();
        TACResult fr = fpart->gen_tac();
        std::string neg_name = fresh_temp();
        TAC_Opd* neg_dst = new Temp_TAC_Opd(neg_name, TYPE_BOOL);
        r.append(cr);
        r.emit(new Compute_TAC_Stmt(neg_dst, cr.result, "!", nullptr));
        r.emit(new If_Goto_TAC_Stmt(neg_dst, lfalse));
        r.append(tr);
        r.emit(new Asgn_TAC_Stmt(dst, tr.result));
        r.emit(new Goto_TAC_Stmt(lend));
        r.emit(new Label_TAC_Stmt(lfalse));
        r.append(fr);
        r.emit(new Asgn_TAC_Stmt(dst, fr.result));
        r.emit(new Label_TAC_Stmt(lend));
        r.result = dst;
        return r;
    }
};

// ── L5: function call as expression ──────────────────────────────────────────

class FuncCallExpr_Ast : public Expression_Ast {
    std::string fname;
    std::vector<Expression_Ast*> args;
    // for AST print: formal param names from symtab
    std::vector<std::pair<std::string,Type>> formal_params;
public:
    FuncCallExpr_Ast(const std::string &fn, const std::vector<Expression_Ast*> &a,
                     Type ret, const std::vector<std::pair<std::string,Type>> &fps)
        : fname(fn), args(a), formal_params(fps)
    {
        type = ret;
    }

    void print(int indent_lvl) override {
        fprintf(astfile, "\n");
        do_indent(indent_lvl + 4);
        fprintf(astfile, "FN CALL: %s_ (", fname.c_str());
        if(args.empty()){
            fprintf(astfile, " )");
        } else {
            fprintf(astfile, "\n");
            for(size_t i = 0; i < args.size(); i++){
                do_indent(indent_lvl + 4);
                args[i]->print(0);
                if(i + 1 < args.size())
                    fprintf(astfile, "\n");
                else
                    fprintf(astfile, ")");
            }
        }
    }

    TACResult gen_tac() override {
        TACResult r;
        std::vector<TAC_Opd*> arg_opds;
         std::string tname = fresh_temp();
        TAC_Opd* dst = new Temp_TAC_Opd(tname, type);
       
        for(auto *a : args){
            TACResult ar = a->gen_tac();
            r.append(ar);
            arg_opds.push_back(ar.result);
        }
        // Result temp allocated after args (matches reference numbering)
        r.emit(new Call_TAC_Stmt(fname, arg_opds, dst, type));
        r.result = dst;
        return r;
    }
};

// ── statements ────────────────────────────────────────────────────────────────

class Statement_Ast : public Ast {
public:
    virtual bool has_return() const { return false; }
};

class Assignment_Ast : public Statement_Ast {
    Name_Ast *lhs;
    Expression_Ast *rhs;
public:
    Assignment_Ast(Name_Ast *l, Expression_Ast *r) : lhs(l), rhs(r) {
        if(lhs->getType() != rhs->getType())
            sem_error("type mismatch in assignment");
    }
    void print(int indent_lvl) override {
        do_indent(indent_lvl);
        fprintf(astfile, "Asgn:\n");

        do_indent(indent_lvl + 1);
        fprintf(astfile, "LHS (");
        lhs->print(0);
        fprintf(astfile, ")\n");

        do_indent(indent_lvl + 1);
        fprintf(astfile, "RHS (");
        rhs->print(indent_lvl + 3);
        fprintf(astfile, ")");
    }
    TACResult gen_tac() override {
        TACResult r;
        TACResult rr = rhs->gen_tac();
        r.append(rr);
        TACResult lr = lhs->gen_tac();
        r.emit(new Asgn_TAC_Stmt(lr.result, rr.result));
        return r;
    }
};

class Print_Ast : public Statement_Ast {
    Expression_Ast *expr;
public:
    Print_Ast(Expression_Ast *e) : expr(e) {
        if(expr->getType() == TYPE_BOOL)
            sem_error("A bool is not allowed in write");
    }
    void print(int indent_lvl) override {
        do_indent(indent_lvl);
        fprintf(astfile, "Write: ");
        expr->print(0);
    }
    TACResult gen_tac() override {
        TACResult r;
        TACResult er = expr->gen_tac();
        r.append(er);
        r.emit(TACInsn::write_insn(er.result));
        return r;
    }
};

class Read_Ast : public Statement_Ast {
    Expression_Ast *expr;
public:
    Read_Ast(Expression_Ast *e) : expr(e) {
        if(expr->getType() != TYPE_INT && expr->getType() != TYPE_FLOAT)
            sem_error("only int and float variables are allowed in read");
    }
    void print(int indent_lvl) override {
        do_indent(indent_lvl);
        fprintf(astfile, "Read: ");
        expr->print(0);
    }
    TACResult gen_tac() override {
        TACResult r;
        TACResult er = expr->gen_tac();
        r.emit(TACInsn::read_insn(er.result));
        return r;
    }
};

// ── L5: function call as statement ───────────────────────────────────────────

class FuncCallStmt_Ast : public Statement_Ast {
    std::string fname;
    std::vector<Expression_Ast*> args;
    Type ret_type;
public:
    FuncCallStmt_Ast(const std::string &fn, const std::vector<Expression_Ast*> &a, Type rt)
        : fname(fn), args(a), ret_type(rt) {}

    void print(int indent_lvl) override {
        fprintf(astfile, "\n");
        do_indent(indent_lvl);
        fprintf(astfile, "FN CALL: %s_ (", fname.c_str());
        if(args.empty()){
            fprintf(astfile, " )");
        } else {
            fprintf(astfile, "\n");
            for(size_t i = 0; i < args.size(); i++){
                do_indent(indent_lvl + 4);
                args[i]->print(0);
                if(i + 1 < args.size())
                    fprintf(astfile, "\n");
                else
                    fprintf(astfile, ")");
            }
        }
    }

    TACResult gen_tac() override {
        TACResult r;
        std::vector<TAC_Opd*> arg_opds;
        for(auto *a : args){
            TACResult ar = a->gen_tac();
            r.append(ar);
            arg_opds.push_back(ar.result);
        }
        // void call: dst = nullptr
        r.emit(new Call_TAC_Stmt(fname, arg_opds, nullptr, ret_type));
        return r;
    }
};

// ── L5: return statement ─────────────────────────────────────────────────────

class Return_Ast : public Statement_Ast {
    Expression_Ast *expr;  // nullptr for void
    Type func_ret_type;
public:
    Return_Ast(Expression_Ast *e, Type frt) : expr(e), func_ret_type(frt) {
        if(expr && expr->getType() != func_ret_type)
            sem_error("return type mismatch");
        if(!expr && func_ret_type != TYPE_VOID)
            sem_error("non-void function must return a value");
    }
    bool has_return() const override { return true; }
    bool has_expr() const { return expr != nullptr; }
    void print(int indent_lvl) override {
        do_indent(indent_lvl);
        fprintf(astfile, "Return: ");
        if(expr) expr->print(indent_lvl + 2);
        else      fprintf(astfile, "<void>");
    }
    TACResult gen_tac() override {
        TACResult r;
        if(expr){
            TACResult er = expr->gen_tac();
            r.append(er);
            TAC_Opd* dst = new Temp_TAC_Opd(func_ret_stemp(), func_ret_type);
            r.emit(new Asgn_TAC_Stmt(dst, er.result));
            r.emit(new Goto_TAC_Stmt(func_exit_label()));
        } else {
            // void return — only emit goto if there's an exit label
            if(!func_exit_label().empty())
                r.emit(new Goto_TAC_Stmt(func_exit_label()));
        }
        return r;
    }
};

class Statement_List_Ast : public Statement_Ast {
public:
    std::vector<Statement_Ast *> stmts;
    void append(Statement_Ast *ast) { stmts.push_back(ast); }
    bool empty() const { return stmts.empty(); }
    bool has_return() const override {
        for(auto *s : stmts)
            if(s->has_return()) return true;
        return false;
    }
    void print(int indent_lvl = 0) override {
        for(size_t i = 0; i < stmts.size(); i++){
            stmts[i]->print(indent_lvl);
            fprintf(astfile, "\n");
        }
    }
    TACResult gen_tac() override {
        TACResult r;
        for(auto s : stmts){
            TACResult sr = s->gen_tac();
            r.append(sr);
        }
        return r;
    }
};

// ── control flow ──────────────────────────────────────────────────────────────

class If_Ast : public Statement_Ast {
    Expression_Ast *cond;
    Statement_Ast  *then_s;
public:
    If_Ast(Expression_Ast *c, Statement_Ast *t) : cond(c), then_s(t) {
        if(cond->getType() != TYPE_BOOL)
            sem_error("condition in if must be bool");
    }
    void print(int indent_lvl) override {
        do_indent(indent_lvl);
        fprintf(astfile, "If:\n");
        do_indent(indent_lvl + 4);
        fprintf(astfile, "Condition (");
        cond->print(indent_lvl + 6);
        fprintf(astfile, ")\n");
        do_indent(indent_lvl + 4);
        fprintf(astfile, "Then (\n");
        then_s->print(indent_lvl + 8);
        fprintf(astfile, ")");
    }
    TACResult gen_tac() override {
        TACResult r;
        TACResult cr = cond->gen_tac();
        TACResult tr = then_s->gen_tac();      // body first
        std::string lend = fresh_label();      // label after body
        std::string neg_name = fresh_temp();
        TAC_Opd* neg_dst = new Temp_TAC_Opd(neg_name, TYPE_BOOL);
        r.append(cr);
        r.emit(TACInsn::unary(neg_dst, "!", cr.result));
        r.emit(TACInsn::if_goto(neg_dst, lend));
        r.append(tr);
        r.emit(TACInsn::go_to(lend));
        r.emit(TACInsn::label_def(lend));
        return r;
    }
    bool has_return() const override { return then_s->has_return(); }
};

class If_Else_Ast : public Statement_Ast {
    Expression_Ast *cond;
    Statement_Ast  *then_s, *else_s;
public:
    If_Else_Ast(Expression_Ast *c, Statement_Ast *t, Statement_Ast *e)
        : cond(c), then_s(t), else_s(e)
    {
        if(cond->getType() != TYPE_BOOL)
            sem_error("condition in if-else must be bool");
    }
    void print(int indent_lvl) override {
        do_indent(indent_lvl);
        fprintf(astfile, "If:\n");
        do_indent(indent_lvl + 4);
        fprintf(astfile, "Condition (");
        cond->print(indent_lvl + 6);
        fprintf(astfile, ")\n");
        do_indent(indent_lvl + 4);
        fprintf(astfile, "Then (\n");
        then_s->print(indent_lvl + 8);
        fprintf(astfile, ")\n");
        do_indent(indent_lvl + 4);
        fprintf(astfile, "Else (\n");
        else_s->print(indent_lvl + 8);
        fprintf(astfile, ")");
    }
    TACResult gen_tac() override {
        TACResult r;
        TACResult cr = cond->gen_tac();
        TACResult tr = then_s->gen_tac();
        std::string neg_name = fresh_temp();   // neg_temp FIRST
        std::string lend  = fresh_label();     // then labels
        std::string lelse = fresh_label();
        TAC_Opd* neg_dst = new Temp_TAC_Opd(neg_name, TYPE_BOOL);
        TACResult er = else_s->gen_tac();
        r.append(cr);
        r.emit(TACInsn::unary(neg_dst, "!", cr.result));
        r.emit(TACInsn::if_goto(neg_dst, lelse));
        r.append(tr);
        r.emit(TACInsn::go_to(lend));
        r.emit(TACInsn::label_def(lelse));
        r.append(er);
        r.emit(TACInsn::label_def(lend));
        return r;
    }
    bool has_return() const override {
        return then_s->has_return() && else_s->has_return();
    }
};

class While_Ast : public Statement_Ast {
    Expression_Ast *cond;
    Statement_Ast  *body;
public:
    While_Ast(Expression_Ast *c, Statement_Ast *b) : cond(c), body(b) {
        if(cond->getType() != TYPE_BOOL)
            sem_error("condition in while must be bool");
    }
    void print(int indent_lvl) override {
        do_indent(indent_lvl);
        fprintf(astfile, "While:\n");
        do_indent(indent_lvl + 4);
        fprintf(astfile, "Condition (");
        cond->print(indent_lvl + 6);
        fprintf(astfile, ")\n");
        do_indent(indent_lvl + 4);
        fprintf(astfile, "Body (\n");
        body->print(indent_lvl + 8);
        fprintf(astfile, ")");
    }
    TACResult gen_tac() override {
        TACResult r;
        TACResult cr = cond->gen_tac();
        TACResult br = body->gen_tac();        // body first
        std::string lstart = fresh_label();    // labels after body
        std::string lend   = fresh_label();
        std::string neg_name = fresh_temp();
        TAC_Opd* neg_dst = new Temp_TAC_Opd(neg_name, TYPE_BOOL);
        r.emit(TACInsn::label_def(lstart));
        r.append(cr);
        r.emit(TACInsn::unary(neg_dst, "!", cr.result));
        r.emit(TACInsn::if_goto(neg_dst, lend));
        r.append(br);
        r.emit(TACInsn::go_to(lstart));
        r.emit(TACInsn::label_def(lend));
        return r;
    }
};

class Do_While_Ast : public Statement_Ast {
    Expression_Ast *cond;
    Statement_Ast  *body;
public:
    Do_While_Ast(Expression_Ast *c, Statement_Ast *b) : cond(c), body(b) {
        if(cond->getType() != TYPE_BOOL)
            sem_error("condition in do-while must be bool");
    }
    void print(int indent_lvl) override {
        do_indent(indent_lvl);
        fprintf(astfile, "Do:\n");
        do_indent(indent_lvl + 4);
        fprintf(astfile, "Body (\n");
        body->print(indent_lvl + 8);
        fprintf(astfile, ")\n");
        do_indent(indent_lvl + 4);
        fprintf(astfile, "While Condition (");
        cond->print(indent_lvl + 6);
        fprintf(astfile, ")");
    }
    TACResult gen_tac() override {
        TACResult r;
        TACResult br = body->gen_tac();
        TACResult cr = cond->gen_tac();
        std::string lstart = fresh_label();
        r.emit(TACInsn::label_def(lstart));
        r.append(br);
        r.append(cr);
        r.emit(TACInsn::if_goto(cr.result, lstart));
        return r;
    }
};

class Compound_Stmt : public Statement_Ast {
    Statement_List_Ast *stmts;
public:
    Compound_Stmt(Statement_List_Ast *st) : stmts(st) {}
    void print(int indent) override {
        bool first = true;
        for(auto s : stmts->stmts) {
            if(!first) fprintf(astfile, "\n");
            s->print(indent);
            first = false;
        }
    }
    bool has_return() const override { return stmts->has_return(); }
    TACResult gen_tac() override { return stmts->gen_tac(); }
};

// ═══════════════════════════════════════════════════════════════════
//  L5: per-function node (replaces the single programnode from L4)
// ═══════════════════════════════════════════════════════════════════

struct FuncParam {
    std::string name;
    Type        type;
};

// One procedure definition
class FuncDefNode : public Ast {
    std::string fname;
    Type        ret_type;
    std::vector<FuncParam> params;
    Statement_List_Ast    *body;
    // local variables (declared inside this function, excluding params), in order
    std::vector<std::pair<std::string,Type>> local_vars_;
public:
    FuncDefNode(const std::string &fn, Type rt,
                const std::vector<FuncParam> &ps, Statement_List_Ast *b)
        : fname(fn), ret_type(rt), params(ps), body(b) {}

    // Called from parser before the local symtab is deleted.
    // 'locals' should contain only declared local variables (not params, not funcs).
    void set_locals(const std::vector<std::pair<std::string,Type>> &locals) {
        local_vars_ = locals;
    }

    const std::string &get_name() const { return fname; }
    Type get_ret_type() const { return ret_type; }
    Statement_List_Ast* get_body() const { return body; }
    const std::vector<FuncParam>& get_params() const { return params; }
    const std::vector<std::pair<std::string,Type>>& get_local_vars() const { return local_vars_; }

    // ── AST print ──────────────────────────────────────────────────
    void print(int = 0) override {
        std::string pname = (fname == "main") ? fname : fname + "_";
        fprintf(astfile, "**PROCEDURE: %s\n", pname.c_str());
        fprintf(astfile, "        Return Type: <%s>\n", type_to_string(ret_type).c_str());
        fprintf(astfile, "        Formal Parameters:\n");
        for(const auto &p : params)
            fprintf(astfile, "                %s_  Type:<%s>\n",
                    p.name.c_str(), type_to_string(p.type).c_str());
        fprintf(astfile, "**BEGIN: Abstract Syntax Tree\n");
        body->print(8);
        fprintf(astfile, "**END: Abstract Syntax Tree\n");
    }

    // ── TAC print ──────────────────────────────────────────────────
    void print_tac(){
        if(body->empty()) return;
        reset_tac_counters();
        std::string pname = (fname == "main") ? fname : fname + "_";
        fprintf(tacfile, "**PROCEDURE: %s\n", pname.c_str());
        fprintf(tacfile, "**BEGIN: Three Address Code Statements\n");
        if(ret_type != TYPE_VOID){
            func_ret_stemp()  = fresh_stemp();
            func_exit_label() = fresh_label();
        } else {
            func_ret_stemp()  = "";
            func_exit_label() = "";   // no exit label for void
        }
        func_ret_type_g() = ret_type;
        TACResult r = body->gen_tac();
        // Epilogue only for non-void functions
        if(ret_type != TYPE_VOID){
            r.emit(new Label_TAC_Stmt(func_exit_label()));
            TAC_Opd* sv = new Temp_TAC_Opd(func_ret_stemp(), ret_type);
            r.emit(new Return_TAC_Stmt(sv));
        }
        for(const auto &insn : r.insns)
            insn->print();
        fprintf(tacfile, "**END: Three Address Code Statements\n");
    }

    // ── ASM print ──────────────────────────────────────────────────
    // global_vars: pre-built AsmVarInfo map for the whole program
    // str_lits:    pre-ordered string literals for .data (shared)
    void print_asm(const std::map<std::string, AsmVarInfo> &global_vars,
                   const std::vector<std::string>           &str_lits)
    {
        if (body->empty() && local_vars_.empty()) return;
        reset_tac_counters();

        if (ret_type != TYPE_VOID) {
            func_ret_stemp()  = fresh_stemp();
            func_exit_label() = fresh_label();
        } else {
            func_ret_stemp()  = "";
            func_exit_label() = "";
        }
        func_ret_type_g() = ret_type;

        TACResult r = body->gen_tac();
        if (ret_type != TYPE_VOID) {
            r.emit(new Label_TAC_Stmt(func_exit_label()));
            r.emit(new Return_TAC_Stmt(
                new Temp_TAC_Opd(func_ret_stemp(), ret_type)));
        }

        // Build param list for emit_asm_func
        std::vector<std::pair<std::string,Type>> param_list;
        for (auto &p : params)
            param_list.push_back({p.name, p.type});

        emit_asm_func(fname, ret_type,
                      local_vars_, param_list,
                      global_vars, str_lits,
                      r.insns);
    }

    // ── RTL print ──────────────────────────────────────────────────
    void print_rtl(){
        if(body->empty()) return;
        reset_tac_counters();
        std::string pname = (fname == "main") ? fname : fname + "_";
        fprintf(rtlfile, "**PROCEDURE: %s\n", pname.c_str());
        fprintf(rtlfile, "**BEGIN: RTL Statements\n");
        if(ret_type != TYPE_VOID){
            func_ret_stemp()  = fresh_stemp();
            func_exit_label() = fresh_label();
        } else {
            func_ret_stemp()  = "";
            func_exit_label() = "";   // no exit label for void
        }
        func_ret_type_g() = ret_type;
        TACResult r = body->gen_tac();
        // Epilogue only for non-void functions
        if(ret_type != TYPE_VOID){
            r.emit(new Label_TAC_Stmt(func_exit_label()));
            TAC_Opd* sv = new Temp_TAC_Opd(func_ret_stemp(), ret_type);
            r.emit(new Return_TAC_Stmt(sv));
        }
        emit_rtl_for(r);
        fprintf(rtlfile, "**END: RTL Statements\n");
    }
};

// ── program root: list of FuncDefNode ────────────────────────────────────────

class programnode : public Ast {
    std::vector<FuncDefNode*> funcs;
    std::vector<std::string>  decl_order_;
    // global variables in declaration order: (name without trailing _, type)
    std::vector<std::pair<std::string,Type>> global_vars_;
public:
    programnode() {}
    void add_func(FuncDefNode *f){ funcs.push_back(f); }
    void set_decl_order(const std::vector<std::string> &order){ decl_order_ = order; }

    // Called from parser with the global symbol table's VAR entries (in order)
    void set_globals(const std::vector<std::pair<std::string,Type>> &gvars) {
        global_vars_ = gvars;
    }

    std::vector<FuncDefNode*> sorted_funcs() const {
        std::vector<FuncDefNode*> result = funcs;
        std::sort(result.begin(), result.end(), [](FuncDefNode *a, FuncDefNode *b){
            std::string na = (a->get_name() == "main") ? "main" : a->get_name() + "_";
            std::string nb = (b->get_name() == "main") ? "main" : b->get_name() + "_";
            return na < nb;
        });
        return result;
    }

    void print(int = 0) override {
        for(auto *f : sorted_funcs()) f->print(0);
    }

    // Build alloc_order: declared functions first, then definition-only
    std::vector<FuncDefNode*> build_alloc_order() const {
        std::vector<FuncDefNode*> order;
        for(const auto &dname : decl_order_)
            for(auto *f : funcs)
                if(f->get_name() == dname){ order.push_back(f); break; }
        for(auto *f : funcs){
            bool declared = false;
            for(const auto &d : decl_order_) if(f->get_name()==d){declared=true;break;}
            if(!declared) order.push_back(f);
        }
        return order;
    }

    void print_tac(){
        auto alloc_order = build_alloc_order();

        // Phase 1: pre-reserve exit labels for non-void functions that have
        //          value returns, in alloc_order. Labels are 0,1,2,...
        label_ctr() = 0;
        std::map<std::string,int>    exit_label_num;   // function name → label number
        std::map<std::string,std::string> ret_stp;
        std::map<std::string,Type>   ret_typ;
        int reserved = 0;
        for(auto *f : alloc_order){
            if(f->get_body()->empty()) continue;
            ret_typ[f->get_name()] = f->get_ret_type();
            if(f->get_ret_type() != TYPE_VOID){
                // reserve a label number for this function's exit
                exit_label_num[f->get_name()] = reserved++;
                ret_stp[f->get_name()] = "stemp0";
            } else {
                exit_label_num[f->get_name()] = -1;
                ret_stp[f->get_name()] = "";
            }
        }

        // Phase 2: generate body TAC in sorted order.
        // label_ctr starts at 'reserved' so body labels don't clash.
        label_ctr() = reserved;
        std::vector<std::pair<std::string, std::vector<TAC_Stmt*>>> stored;
        for(auto *f : sorted_funcs()){
            if(f->get_body()->empty()) continue;
            reset_tac_counters();  // resets temp+stemp to 0
            int elbl = exit_label_num.count(f->get_name()) ? exit_label_num[f->get_name()] : -1;
            if(elbl >= 0){
                func_ret_stemp() = fresh_stemp(); // reserves stemp0; body gets stemp1+
            } else {
                func_ret_stemp() = "";
            }
            func_exit_label() = (elbl >= 0) ? ("Label" + std::to_string(elbl)) : "";
            func_ret_type_g() = ret_typ[f->get_name()];
            TACResult r = f->get_body()->gen_tac();
            if(elbl >= 0){
                r.emit(new Label_TAC_Stmt("Label" + std::to_string(elbl)));
                r.emit(new Return_TAC_Stmt(new Temp_TAC_Opd(func_ret_stemp(), f->get_ret_type())));
            }
            stored.push_back({f->get_name(), r.insns});
        }

        // Phase 3: print in sorted order
        for(auto &p : stored){
            FuncDefNode *f = nullptr;
            for(auto *fn : funcs) if(fn->get_name()==p.first){f=fn;break;}
            if(!f) continue;
            std::string pname = (f->get_name()=="main")?"main":f->get_name()+"_";
            fprintf(tacfile,"**PROCEDURE: %s\n",pname.c_str());
            fprintf(tacfile,"**BEGIN: Three Address Code Statements\n");
            for(auto *insn : p.second) insn->print();
            fprintf(tacfile,"**END: Three Address Code Statements\n");
        }
    }

    void print_rtl(){
        auto alloc_order = build_alloc_order();

        label_ctr() = 0;
        std::map<std::string,int>    exit_label_num;
        std::map<std::string,std::string> ret_stp;
        std::map<std::string,Type>   ret_typ;
        int reserved = 0;
        for(auto *f : alloc_order){
            if(f->get_body()->empty()) continue;
            ret_typ[f->get_name()] = f->get_ret_type();
            if(f->get_ret_type() != TYPE_VOID){
                exit_label_num[f->get_name()] = reserved++;
                ret_stp[f->get_name()] = "stemp0";
            } else {
                exit_label_num[f->get_name()] = -1;
                ret_stp[f->get_name()] = "";
            }
        }
        // Also register void functions not in alloc_order (e.g. main)
        for(auto *f : funcs){
            if(ret_typ.find(f->get_name()) == ret_typ.end()){
                ret_typ[f->get_name()] = f->get_ret_type();
                exit_label_num[f->get_name()] = -1;
                ret_stp[f->get_name()] = "";
            }
        }

        label_ctr() = reserved;
        std::vector<std::pair<std::string, std::vector<TAC_Stmt*>>> stored;
        for(auto *f : sorted_funcs()){
            if(f->get_body()->empty()) continue;
            reset_tac_counters();
            int elbl = exit_label_num.count(f->get_name()) ? exit_label_num[f->get_name()] : -1;
            if(elbl >= 0){
                func_ret_stemp() = fresh_stemp(); // reserves stemp0; body gets stemp1+
            } else {
                func_ret_stemp() = "";
            }
            func_exit_label() = (elbl >= 0) ? ("Label" + std::to_string(elbl)) : "";
            func_ret_type_g() = ret_typ[f->get_name()];
            TACResult r = f->get_body()->gen_tac();
            if(elbl >= 0){
                r.emit(new Label_TAC_Stmt("Label" + std::to_string(elbl)));
                r.emit(new Return_TAC_Stmt(new Temp_TAC_Opd(func_ret_stemp(), f->get_ret_type())));
            }
            stored.push_back({f->get_name(), r.insns});
        }

        // Build name→insns map for lookup
        std::map<std::string, std::vector<TAC_Stmt*>*> insns_map;
        for(auto &p : stored) insns_map[p.first] = &p.second;

        // Pre-register string literals in TAC instruction order, in alloc_order
        RegAlloc shared_ra;
        for(auto *f : alloc_order){
            auto it = insns_map.find(f->get_name());
            if(it == insns_map.end()) continue;
            for(auto *insn : *it->second){
                Write_TAC_Stmt *wr = dynamic_cast<Write_TAC_Stmt*>(insn);
                if(wr && wr->src && wr->src->is_string() && !wr->src->is_variable())
                    shared_ra.get_straddr_reg(wr->src->to_string());
                Asgn_TAC_Stmt *asgn = dynamic_cast<Asgn_TAC_Stmt*>(insn);
                if(asgn && asgn->rhs && asgn->rhs->is_string() && !asgn->rhs->is_variable())
                    shared_ra.get_straddr_reg(asgn->rhs->to_string());
            }
        }

        for(auto &p : stored){
            FuncDefNode *f = nullptr;
            for(auto *fn : funcs) if(fn->get_name()==p.first){f=fn;break;}
            if(!f) continue;
            std::string pname = (f->get_name()=="main")?"main":f->get_name()+"_";
            fprintf(rtlfile,"**PROCEDURE: %s\n",pname.c_str());
            fprintf(rtlfile,"**BEGIN: RTL Statements\n");
            TACResult tr; tr.insns = p.second;
            emit_rtl_for(tr, shared_ra);
            fprintf(rtlfile,"**END: RTL Statements\n");
        }
    }

    // ── ASM (SPIM) print ───────────────────────────────────────────
    void print_asm() {
        auto alloc_order = build_alloc_order();

        // ── Phase 1: build global var map (name_ → AsmVarInfo) ──
        std::map<std::string, AsmVarInfo> gmap;
        for (auto &v : global_vars_) {
            bool flt = (v.second == TYPE_FLOAT);
            AsmVarInfo vi{true, 0, flt};
            gmap[v.first + "_"] = vi;
        }

        // ── Phase 2: collect all string literals across all functions
        //    in alloc_order (same order as .data will list them) ──
        // We do a dry-run TAC gen just to collect strings.
        // Simpler: scan all functions' TAC after generating it.
        // We'll collect strings per-function below and merge.

        // ── Phase 3: reserve label counters (same as print_tac) ──
        label_ctr() = 0;
        std::map<std::string,int>  exit_label_num;
        std::map<std::string,Type> ret_typ;
        int reserved = 0;
        for (auto *f : alloc_order) {
if (f->get_body()->empty() && f->get_local_vars().empty()) continue;

            ret_typ[f->get_name()] = f->get_ret_type();
            if (f->get_ret_type() != TYPE_VOID)
                exit_label_num[f->get_name()] = reserved++;
            else
                exit_label_num[f->get_name()] = -1;
        }
        for (auto *f : funcs) {
            if (ret_typ.find(f->get_name()) == ret_typ.end()) {
                ret_typ[f->get_name()] = f->get_ret_type();
                exit_label_num[f->get_name()] = -1;
            }
        }

        // ── Phase 4: generate TAC for each function in sorted order ──
        label_ctr() = reserved;
        std::vector<std::pair<std::string, std::vector<TAC_Stmt*>>> stored;
        for (auto *f : sorted_funcs()) {
            if (f->get_body()->empty() && f->get_local_vars().empty()) continue;

            reset_tac_counters();
            int elbl = exit_label_num.count(f->get_name())
                     ? exit_label_num[f->get_name()] : -1;
            if (elbl >= 0) {
                func_ret_stemp()  = fresh_stemp();
            } else {
                func_ret_stemp()  = "";
            }
            func_exit_label() = (elbl >= 0)
                ? ("Label" + std::to_string(elbl)) : "";
            func_ret_type_g() = ret_typ[f->get_name()];
            TACResult r = f->get_body()->gen_tac();
            if (elbl >= 0) {
                r.emit(new Label_TAC_Stmt("Label" + std::to_string(elbl)));
                r.emit(new Return_TAC_Stmt(
                    new Temp_TAC_Opd(func_ret_stemp(), f->get_ret_type())));
            }
            stored.push_back({f->get_name(), r.insns});
        }

        // ── Phase 5: collect all string literals in alloc_order ──
        // We need to scan the stored TAC in alloc_order for string literals.
        std::vector<std::string> all_strs;
        std::map<std::string, std::vector<TAC_Stmt*>*> insns_map;
        for (auto &p : stored) insns_map[p.first] = &p.second;

        auto collect_str_from_opd = [&](TAC_Opd *opd) {
            if (!opd) return;
            if (opd->is_string() && !opd->is_variable()) {
                std::string s = opd->to_string();
                if (std::find(all_strs.begin(), all_strs.end(), s) == all_strs.end())
                    all_strs.push_back(s);
            }
        };
        for (auto *f : alloc_order) {
            auto it = insns_map.find(f->get_name());
            if (it == insns_map.end()) continue;
            for (auto *insn : *it->second) {
                if (auto *w = dynamic_cast<Write_TAC_Stmt*>(insn))
                    collect_str_from_opd(w->src);
                if (auto *a = dynamic_cast<Asgn_TAC_Stmt*>(insn))
                    collect_str_from_opd(a->rhs);
                if (auto *c = dynamic_cast<Compute_TAC_Stmt*>(insn)) {
                    collect_str_from_opd(c->op1);
                    collect_str_from_opd(c->op2);
                }
            }
        }

        // ── Phase 6: emit .data section ──────────────────────────
        bool has_data = !global_vars_.empty() || !all_strs.empty();
        if (has_data) {
            fprintf(asmfile, ".data\n");
            // Global variables
            for (auto &v : global_vars_) {
                bool flt = (v.second == TYPE_FLOAT);
                if (flt)
                    fprintf(asmfile, "%s_:\t.double 0.0\n", v.first.c_str());
                else
                    fprintf(asmfile, "%s_:\t.word 0\n", v.first.c_str());
            }
            // String literals
            for (size_t i = 0; i < all_strs.size(); i++)
                fprintf(asmfile, "_str_%zu:\t.asciiz %s\n", i, all_strs[i].c_str());
        }

        // ── Phase 7: emit each function in sorted order ───────────
        for (auto &p : stored) {
            FuncDefNode *f = nullptr;
            for (auto *fn : funcs)
                if (fn->get_name() == p.first) { f = fn; break; }
            if (!f) continue;

            // Build param list
            std::vector<std::pair<std::string,Type>> param_list;
            // FuncDefNode exposes params via get_params()
            for (auto &fp : f->get_params())
                param_list.push_back({fp.name, fp.type});

            emit_asm_func(f->get_name(), f->get_ret_type(),
                          f->get_local_vars(), param_list,
                          gmap, all_strs, p.second);
        }
    }
};

#endif // AST_HH
