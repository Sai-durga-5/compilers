#ifndef TAC_HH
#define TAC_HH

#include <string>
#include <vector>
#include <cstdio>
#include "types.hh"

extern FILE *tacfile;

class RegAlloc;

// ═══════════════════════════════════════════════════════════════════
//  OPERANDS
// ═══════════════════════════════════════════════════════════════════

class TAC_Opd {
public:
    virtual std::string to_string() = 0;
    virtual bool is_temp()     const { return false; }
    virtual bool is_variable() const { return false; }
    virtual bool is_float()    const { return false; }
    virtual bool is_string()   const { return false; }
    virtual ~TAC_Opd() {}
};

class Variable_TAC_Opd : public TAC_Opd {
    std::string name;
    Type type;
public:
    Variable_TAC_Opd(std::string n, Type t = TYPE_INT) : name(n + "_"), type(t) {}
    std::string to_string() override { return name; }
    bool is_variable() const override { return true; }
    bool is_float()    const override { return type == TYPE_FLOAT; }
    bool is_string()   const override { return type == TYPE_STRING; }
};

class Temp_TAC_Opd : public TAC_Opd {
    std::string name;
    Type type;
public:
    Temp_TAC_Opd(std::string n, Type t = TYPE_INT) : name(n), type(t) {}
    std::string to_string() override { return name; }

    bool is_temp() const override {
        return name.rfind("stemp", 0) != 0;
    }

    bool is_variable() const override {
        return name.rfind("stemp", 0) == 0;
    }

    bool is_float() const override { return type == TYPE_FLOAT; }
};

class Int_TAC_Opd : public TAC_Opd {
    int val;
public:
    Int_TAC_Opd(int v) : val(v) {}
    std::string to_string() override { return std::to_string(val); }
};

class Float_TAC_Opd : public TAC_Opd {
    double val;
public:
    Float_TAC_Opd(double v) : val(v) {}
    std::string to_string() override {
        char buf[32]; snprintf(buf, sizeof(buf), "%.2f", val); return buf;
    }
    bool is_float() const override { return true; }
};

class String_TAC_Opd : public TAC_Opd {
    std::string val;
public:
    String_TAC_Opd(std::string v) : val(v) {}
    std::string to_string() override { return val; }
    bool is_string() const override { return true; }
};

// ═══════════════════════════════════════════════════════════════════
//  STATEMENTS
// ═══════════════════════════════════════════════════════════════════

class TAC_Stmt {
public:
    virtual void print()             = 0;
    virtual void gen_rtl(RegAlloc &) = 0;
    virtual ~TAC_Stmt() {}
};

class Asgn_TAC_Stmt : public TAC_Stmt {
public:
    TAC_Opd *lhs, *rhs;
    Asgn_TAC_Stmt(TAC_Opd *l, TAC_Opd *r) : lhs(l), rhs(r) {}
    TAC_Opd* get_rhs() const { return rhs; }

    void print() override {
        fprintf(tacfile, "    %s = %s\n",
                lhs->to_string().c_str(), rhs->to_string().c_str());
    }
    void gen_rtl(RegAlloc &ra) override;
};

class Compute_TAC_Stmt : public TAC_Stmt {
public:
    TAC_Opd    *dst, *op1, *op2;
    std::string op;

    Compute_TAC_Stmt(TAC_Opd *d, TAC_Opd *a, std::string o, TAC_Opd *b)
        : dst(d), op1(a), op2(b), op(o) {}

    void print() override {
        if(op2)
            fprintf(tacfile, "    %s = %s %s %s\n",
                    dst->to_string().c_str(), op1->to_string().c_str(),
                    op.c_str(), op2->to_string().c_str());
        else
            fprintf(tacfile, "    %s = %s %s\n",
                    dst->to_string().c_str(), op.c_str(),
                    op1->to_string().c_str());
    }
    void gen_rtl(RegAlloc &ra) override;
};

class Label_TAC_Stmt : public TAC_Stmt {
public:
    std::string label;
    Label_TAC_Stmt(std::string l) : label(l) {}

    void print() override { fprintf(tacfile, "%s:\n", label.c_str()); }
    void gen_rtl(RegAlloc &ra) override;
};

class Goto_TAC_Stmt : public TAC_Stmt {
public:
    std::string label;
    Goto_TAC_Stmt(std::string l) : label(l) {}

    void print() override { fprintf(tacfile, "    goto %s\n", label.c_str()); }
    void gen_rtl(RegAlloc &ra) override;
};

class If_Goto_TAC_Stmt : public TAC_Stmt {
public:
    TAC_Opd    *cond;
    std::string label;
    If_Goto_TAC_Stmt(TAC_Opd *c, std::string l) : cond(c), label(l) {}

    void print() override {
        fprintf(tacfile, "    if(%s) goto %s\n",
                cond->to_string().c_str(), label.c_str());
    }
    void gen_rtl(RegAlloc &ra) override;
};

class Write_TAC_Stmt : public TAC_Stmt {
public:
    TAC_Opd *src;
    Write_TAC_Stmt(TAC_Opd *s) : src(s) {}
    TAC_Opd* get_src() const { return src; }

    void print() override {
        fprintf(tacfile, "    write %s\n", src->to_string().c_str());
    }
    void gen_rtl(RegAlloc &ra) override;
};

class Read_TAC_Stmt : public TAC_Stmt {
public:
    TAC_Opd *dst;
    Read_TAC_Stmt(TAC_Opd *d) : dst(d) {}

    void print() override {
        fprintf(tacfile, "    read %s\n", dst->to_string().c_str());
    }
    void gen_rtl(RegAlloc &ra) override;
};

// ── L5: function call as statement ────────────────────────────────────────────
// Prints: "    fname(arg1, arg2, ...)\n"  or  "    fname()\n"
class Call_TAC_Stmt : public TAC_Stmt {
public:
    std::string fname;
    std::vector<TAC_Opd*> args;
    TAC_Opd *dst;        // nullptr if void call (statement), else temp holding result
    Type     ret_type;

    Call_TAC_Stmt(const std::string &fn, const std::vector<TAC_Opd*> &a,
                  TAC_Opd *d, Type rt)
        : fname(fn), args(a), dst(d), ret_type(rt) {}

    void print() override {
        // Build arg string
        std::string argstr;
        for(size_t i = 0; i < args.size(); i++){
            if(i) argstr += ", ";
            argstr += args[i]->to_string();
        }
        if(dst){
            fprintf(tacfile, "    %s = %s_(%s)\n",
                    dst->to_string().c_str(), fname.c_str(), argstr.c_str());
        } else {
            fprintf(tacfile, "    %s_(%s)\n", fname.c_str(), argstr.c_str());
        }
    }
    void gen_rtl(RegAlloc &ra) override;
};

// ── L5: return statement ──────────────────────────────────────────────────────
class Return_TAC_Stmt : public TAC_Stmt {
public:
    TAC_Opd *val;   // nullptr for void return
    Return_TAC_Stmt(TAC_Opd *v) : val(v) {}

    void print() override {
        if(val)
            fprintf(tacfile, "    return %s\n", val->to_string().c_str());
        else
            fprintf(tacfile, "    return\n");
    }
    void gen_rtl(RegAlloc &ra) override;
};

// ═══════════════════════════════════════════════════════════════════
//  RESULT
// ═══════════════════════════════════════════════════════════════════

struct TACResult {
    std::vector<TAC_Stmt*> insns;
    TAC_Opd *result = nullptr;

    void append(const TACResult &o){
        insns.insert(insns.end(), o.insns.begin(), o.insns.end());
    }
    void emit(TAC_Stmt *stmt){ insns.push_back(stmt); }
};

// ═══════════════════════════════════════════════════════════════════
//  COUNTERS
// ═══════════════════════════════════════════════════════════════════

inline int &temp_ctr()  { static int c = 0; return c; }
inline int &label_ctr() { static int c = 0; return c; }
inline int &stemp_ctr() { static int c = 0; return c; }

inline std::string fresh_temp()  { return "temp"  + std::to_string(temp_ctr()++);  }
inline std::string fresh_stemp() { return "stemp" + std::to_string(stemp_ctr()++); }
inline std::string fresh_label() { return "Label" + std::to_string(label_ctr()++); }

inline void reset_tac_counters(){
    temp_ctr() = 0; stemp_ctr() = 0;
    // label_ctr is NOT reset — labels are globally unique across functions
}

// ── Per-function exit label and return stemp (shared by all returns) ──────────
inline std::string &func_exit_label() { static std::string s; return s; }
inline std::string &func_ret_stemp()  { static std::string s; return s; }
inline Type        &func_ret_type_g() { static Type t = TYPE_VOID; return t; }

// ═══════════════════════════════════════════════════════════════════
//  FACTORY
// ═══════════════════════════════════════════════════════════════════

struct TACInsn {
    static TAC_Stmt* write_insn(TAC_Opd *src)                              { return new Write_TAC_Stmt(src); }
    static TAC_Stmt* read_insn (TAC_Opd *dst)                              { return new Read_TAC_Stmt(dst);  }
    static TAC_Stmt* unary(TAC_Opd *dst, const std::string &op, TAC_Opd *src)
                                                                            { return new Compute_TAC_Stmt(dst, src, op, nullptr); }
    static TAC_Stmt* if_goto(TAC_Opd *cond, const std::string &lbl)        { return new If_Goto_TAC_Stmt(cond, lbl); }
    static TAC_Stmt* go_to(const std::string &lbl)                         { return new Goto_TAC_Stmt(lbl);  }
    static TAC_Stmt* label_def(const std::string &lbl)                     { return new Label_TAC_Stmt(lbl); }
};

#endif // TAC_HH
