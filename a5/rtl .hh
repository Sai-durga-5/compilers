#ifndef RTL_HH
#define RTL_HH

#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstdio>
#include "tac.hh"

extern FILE *rtlfile;

// ═══════════════════════════════════════════════════════════════════
//  RTL STATEMENTS
// ═══════════════════════════════════════════════════════════════════

class RTL_Stmt {
public:
    virtual void print() const = 0;
    virtual ~RTL_Stmt() {}
};

class Compute_RTL_Stmt : public RTL_Stmt {
    std::string dst, lhs, op, rhs;
    bool is_dbl;

    static bool is_freg(const std::string &r) { return !r.empty() && r[0] == 'f'; }

    std::string map_op(const std::string& o) const {
        std::string suffix = is_dbl ? ".d" : "";
        if(o == "+")  return "add" + suffix;
        if(o == "-")  return "sub" + suffix;
        if(o == "*")  return "mul" + suffix;
        if(o == "/")  return "div" + suffix;
        if(o == "==") return "seq" + suffix;
        if(o == "!=") return "sne" + suffix;
        if(o == "<")  return "slt" + suffix;
        if(o == "<=") return "sle" + suffix;
        if(o == ">")  return "sgt" + suffix;
        if(o == ">=") return "sge" + suffix;
        if(o == "&&") return "and";
        if(o == "||") return "or";
        return o;
    }
public:
    Compute_RTL_Stmt(const std::string &d, const std::string &l,
                     const std::string &o, const std::string &r)
        : dst(d), lhs(l), op(o), rhs(r), is_dbl(is_freg(d)) {}

    void print() const override {
        fprintf(rtlfile, "    %-10s%s <- %s , %s\n",
                (map_op(op) + ":").c_str(), dst.c_str(), lhs.c_str(), rhs.c_str());
    }
};

class Move_RTL_Stmt : public RTL_Stmt {
    std::string dst, op, src;
public:
    Move_RTL_Stmt(const std::string &d, const std::string &o, const std::string &s)
        : dst(d), op(o), src(s) {}
    void print() const override {
        if(op == "!")
            fprintf(rtlfile, "    %-10s%s <- %s\n", "not:", dst.c_str(), src.c_str());
        else if(op == "-"){
            bool dbl = (!dst.empty() && dst[0] == 'f');
            fprintf(rtlfile, "    %-10s%s <- %s\n", dbl ? "uminus.d:" : "uminus:", dst.c_str(), src.c_str());
        }
        else if(op.empty()){
            bool dbl = (!dst.empty() && dst[0] == 'f');
            fprintf(rtlfile, "    %-10s%s <- %s\n", dbl ? "move.d:" : "move:", dst.c_str(), src.c_str());
        }
        else
            fprintf(rtlfile, "    %-10s%s <- %s\n", (op+":").c_str(), dst.c_str(), src.c_str());
    }
};

class Load_RTL_Stmt : public RTL_Stmt {
    std::string dst_reg, var_name;
    bool is_dbl;
public:
    Load_RTL_Stmt(const std::string &d, const std::string &v)
        : dst_reg(d), var_name(v), is_dbl(!d.empty() && d[0] == 'f') {}
    void print() const override {
        fprintf(rtlfile, "    %-10s%s <- %s\n",
                is_dbl ? "load.d:" : "load:", dst_reg.c_str(), var_name.c_str());
    }
};

class ILoad_RTL_Stmt : public RTL_Stmt {
    std::string dst_reg, imm;
    bool is_dbl;
public:
    ILoad_RTL_Stmt(const std::string &d, const std::string &i)
        : dst_reg(d), imm(i), is_dbl(!d.empty() && d[0] == 'f') {}
    void print() const override {
        fprintf(rtlfile, "    %-10s%s <- %s\n",
                is_dbl ? "iLoad.d:" : "iLoad:", dst_reg.c_str(), imm.c_str());
    }
};

class Store_RTL_Stmt : public RTL_Stmt {
    std::string var_name, src_reg;
    bool is_dbl;
public:
    Store_RTL_Stmt(const std::string &v, const std::string &s)
        : var_name(v), src_reg(s), is_dbl(!s.empty() && s[0] == 'f') {}
    void print() const override {
        fprintf(rtlfile, "    %-10s%s <- %s\n",
                is_dbl ? "store.d:" : "store:", var_name.c_str(), src_reg.c_str());
    }
};

class LoadAddr_RTL_Stmt : public RTL_Stmt {
    std::string dst_reg, label;
public:
    LoadAddr_RTL_Stmt(const std::string &d, const std::string &l)
        : dst_reg(d), label(l) {}
    void print() const override {
        fprintf(rtlfile, "    %-10s%s <- %s\n", "load_addr:", dst_reg.c_str(), label.c_str());
    }
};

class Label_RTL_Stmt : public RTL_Stmt {
    std::string label;
public:
    Label_RTL_Stmt(const std::string &l) : label(l) {}
    void print() const override { fprintf(rtlfile, "\n%s:\n", label.c_str()); }
};

class Control_Flow_RTL_Stmt : public RTL_Stmt {};

class Goto_RTL_Stmt : public Control_Flow_RTL_Stmt {
    std::string label;
public:
    Goto_RTL_Stmt(const std::string &l) : label(l) {}
    void print() const override {
        fprintf(rtlfile, "    %-10s%s\n", "goto:", label.c_str());
    }
};

class If_Goto_RTL_Stmt : public Control_Flow_RTL_Stmt {
    std::string reg, label;
public:
    If_Goto_RTL_Stmt(const std::string &r, const std::string &l)
        : reg(r), label(l) {}
    void print() const override {
        fprintf(rtlfile, "    %-10s%s , %s\n", "bgtz:", reg.c_str(), label.c_str());
    }
};

class Write_RTL_Stmt : public RTL_Stmt {
public:
    Write_RTL_Stmt() {}
    void print() const override { fprintf(rtlfile, "    write\n"); }
};

class Read_RTL_Stmt : public RTL_Stmt {
    std::string var_name;
public:
    Read_RTL_Stmt(const std::string &v) : var_name(v) {}
    void print() const override {
        if(var_name.empty())
            fprintf(rtlfile, "    read\n");
        else
            fprintf(rtlfile, "    %-10s%s\n", "read:", var_name.c_str());
    }
};

// ── L5: call and return RTL statements ───────────────────────────────────────

class Call_RTL_Stmt : public RTL_Stmt {
    std::string fname;
    std::string dst_reg;  // empty = void, else "v1" or "f0"
public:
    Call_RTL_Stmt(const std::string &fn, const std::string &dst = "")
        : fname(fn), dst_reg(dst) {}
    void print() const override {
        if(dst_reg.empty())
            fprintf(rtlfile, "    call %s_\n", fname.c_str());
        else
            fprintf(rtlfile, "    %s = call %s_\n", dst_reg.c_str(), fname.c_str());
    }
};

class Push_RTL_Stmt : public RTL_Stmt {
    std::string reg;
public:
    Push_RTL_Stmt(const std::string &r) : reg(r) {}
    void print() const override {
        fprintf(rtlfile, "    push:     %s\n", reg.c_str());
    }
};

class Pop_RTL_Stmt : public RTL_Stmt {
public:
    Pop_RTL_Stmt() {}
    void print() const override {
        fprintf(rtlfile, "    pop\n");
    }
};

class Return_RTL_Stmt : public RTL_Stmt {
    std::string reg;   // empty = void return
public:
    Return_RTL_Stmt(const std::string &r = "") : reg(r) {}
    void print() const override {
        if(reg.empty())
            fprintf(rtlfile, "    return\n");
        else
            fprintf(rtlfile, "    return  %s\n", reg.c_str());
    }
};

// ═══════════════════════════════════════════════════════════════════
//  RTL STATEMENTS  (float-specific)
// ═══════════════════════════════════════════════════════════════════

class FloatCmp_RTL_Stmt : public RTL_Stmt {
    std::string op, lhs, rhs;
public:
    FloatCmp_RTL_Stmt(const std::string &o, const std::string &l, const std::string &r)
        : op(o), lhs(l), rhs(r) {}
    void print() const override {
        fprintf(rtlfile, "    %-10s%s , %s\n", (op+":").c_str(), rhs.c_str(),lhs.c_str());
    }
};

class MoveZero_RTL_Stmt : public RTL_Stmt {
    std::string dst;
public:
    MoveZero_RTL_Stmt(const std::string &d) : dst(d) {}
    void print() const override {
        fprintf(rtlfile, "    %-10s%s <- zero\n", "move:", dst.c_str());
    }
};

class MovF_RTL_Stmt : public RTL_Stmt {
    std::string dst, src;
    int cc;
public:
    MovF_RTL_Stmt(const std::string &d, const std::string &s, int c)
        : dst(d), src(s), cc(c) {}
    void print() const override {
        fprintf(rtlfile, "    %-10s%s <- %s , %d\n",
                "movf:", dst.c_str(), src.c_str(), cc);
    }
};
class MovT_RTL_Stmt : public RTL_Stmt {
    std::string dst, src;
    int cc;
public:    MovT_RTL_Stmt(const std::string &d, const std::string &s, int c)
        : dst(d), src(s), cc(c) {}
    void print() const override {
        fprintf(rtlfile, "    %-10s%s <- %s , %d\n",
                "movt:", dst.c_str(), src.c_str(), cc);
    }
};

// ═══════════════════════════════════════════════════════════════════
//  REGISTER ALLOCATOR
// ═══════════════════════════════════════════════════════════════════

class RegAlloc {
    std::set<std::string>             used_int_regs;
    std::set<std::string>             used_float_regs;
    std::vector<std::string>          static_str;
    std::map<std::string,std::string> temp_map;
    std::map<std::string,std::string> float_temp_map;
    std::vector<RTL_Stmt*>            insns;

    std::string get_int_reg(){
        if(used_int_regs.find("v0") == used_int_regs.end()){
            used_int_regs.insert("v0");
            return "v0";
        }
        int cnt = 0;
        while(true){
            std::string reg = "t" + std::to_string(cnt);
            if(used_int_regs.find(reg) == used_int_regs.end()){
                used_int_regs.insert(reg);
                return reg;
            }
            cnt++;
        }
    }

    std::string get_float_reg(){
        int cnt = 2;
        while(true){
            std::string reg = "f" + std::to_string(cnt);
            if(used_float_regs.find(reg) == used_float_regs.end()){
                used_float_regs.insert(reg);
                return reg;
            }
            cnt += 2;
        }
    }

    int get_int_reg(const std::string &r){
        if(used_int_regs.find(r) == used_int_regs.end()){
            used_int_regs.insert(r);
            return 0;
        }
        return -1;
    }

    int get_float_reg(const std::string &r){
        if(used_float_regs.find(r) == used_float_regs.end()){
            used_float_regs.insert(r);
            return 0;
        }
        return -1;
    }

    void free_int_reg(const std::string &r)   { used_int_regs.erase(r); }
    void free_float_reg(const std::string &r) { used_float_regs.erase(r); }

public:
    RegAlloc() {}
    ~RegAlloc(){ for(auto *s : insns) delete s; }

    std::string get_straddr_reg(const std::string &s){
        auto it = std::find(static_str.begin(), static_str.end(), s);
        if(it == static_str.end()){
            static_str.push_back(s);
            it = static_str.end() - 1;
        }
        return "_str_" + std::to_string(it - static_str.begin());
    }

    void emit_rtl(RTL_Stmt *s){ insns.push_back(s); }
    void flush(){
        for(auto *s : insns){ s->print(); delete s; }
        insns.clear();
    }

    std::string resolve(TAC_Opd *opd){
        if(opd->is_temp()){
            if(opd->is_float()){
                auto it = float_temp_map.find(opd->to_string());
                if(it != float_temp_map.end()) return it->second;
            } else {
                auto it = temp_map.find(opd->to_string());
                if(it != temp_map.end()) return it->second;
            }
        }
        std::string r = opd->is_float() ? get_float_reg() : get_int_reg();
        if(opd->is_variable())
            emit_rtl(new Load_RTL_Stmt(r, opd->to_string()));
        else if(opd->is_string()){
            std::string lbl = get_straddr_reg(opd->to_string());
            emit_rtl(new LoadAddr_RTL_Stmt(r, lbl));
        } else
            emit_rtl(new ILoad_RTL_Stmt(r, opd->to_string()));
        return r;
    }

    std::string alloc_dst(TAC_Opd *opd){
        std::string r = opd->is_float() ? get_float_reg() : get_int_reg();
        if(opd->is_temp()){
            if(opd->is_float()) float_temp_map[opd->to_string()] = r;
            else                temp_map[opd->to_string()] = r;
        }
        return r;
    }

    void free_input(TAC_Opd *opd, const std::string &reg){
        if(opd->is_temp()){
            if(opd->is_float()) float_temp_map.erase(opd->to_string());
            else                temp_map.erase(opd->to_string());
        }
        if(opd->is_float()) free_float_reg(reg);
        else                free_int_reg(reg);
    }

    void store_var(TAC_Opd *opd, const std::string &reg){
        emit_rtl(new Store_RTL_Stmt(opd->to_string(), reg));
        if(opd->is_float()) free_float_reg(reg);
        else                free_int_reg(reg);
    }

    void remap_temp(TAC_Opd *src, TAC_Opd *dst, const std::string &reg){
        if(src->is_float()){
            if(src->is_temp()) float_temp_map.erase(src->to_string());
            if(dst->is_temp()) float_temp_map[dst->to_string()] = reg;
        } else {
            if(src->is_temp()) temp_map.erase(src->to_string());
            if(dst->is_temp()) temp_map[dst->to_string()] = reg;
        }
    }

    void unmap_temp(TAC_Opd *opd){
        if(opd->is_float()) float_temp_map.erase(opd->to_string());
        else                temp_map.erase(opd->to_string());
    }

    std::string next_str_label(const std::string &val){
        return get_straddr_reg(val);
    }

    std::string emit_float_cmp(const std::string &op,
                                const std::string &freg_lhs,
                                const std::string &freg_rhs,
                                TAC_Opd *dst_opd)
    {
        std::string fcmp_op;
        bool invert = false;
        if     (op == ">") { fcmp_op = "sle.d"; invert = true; }
        else if(op == ">=") { fcmp_op = "slt.d"; invert = true; }
        else if(op == "<")  fcmp_op = "slt.d";
        else if(op == "<=") fcmp_op = "sle.d";
        else if(op == "==") fcmp_op = "seq.d";
        else if(op == "!=") {fcmp_op = "seq.d"; invert = true;}
        else                fcmp_op = op + ".d";
        

        emit_rtl(new FloatCmp_RTL_Stmt(fcmp_op, freg_rhs, freg_lhs));
        get_int_reg("v0");
        std::string dst_reg = alloc_dst(dst_opd);
        emit_rtl(new ILoad_RTL_Stmt("v0", "1"));
        emit_rtl(new MoveZero_RTL_Stmt(dst_reg));
        if(invert)
        emit_rtl(new MovF_RTL_Stmt(dst_reg, "v0", 0));
        else    emit_rtl(new MovT_RTL_Stmt(dst_reg, "v0", 0));
        free_int_reg("v0");
        return dst_reg;
    }

    // For call with return value: the result is in v0 after the call.
    // We need to store it into a dst temp or variable.
    void emit_call_result(TAC_Opd *dst, bool is_float_ret){
        // After call + move.d/move, result is in f2 (float) or v0 (int).
        if(dst->is_variable()){
            std::string src_reg = is_float_ret ? "f2" : "v0";
            emit_rtl(new Store_RTL_Stmt(dst->to_string(), src_reg));
        } else {
            std::string src_reg = is_float_ret ? "f2" : "v0";
            if(is_float_ret) float_temp_map[dst->to_string()] = src_reg;
            else             temp_map[dst->to_string()] = src_reg;
        }
    }
};

// ═══════════════════════════════════════════════════════════════════
//  gen_rtl() BODIES for each TAC_Stmt subclass
// ═══════════════════════════════════════════════════════════════════

inline void Compute_TAC_Stmt::gen_rtl(RegAlloc &ra){
    if(op2){
        bool is_float_op = op1->is_float() || op2->is_float();
        bool is_relop    = (op == ">" || op == ">=" || op == "<" ||
                            op == "<=" || op == "==" || op == "!=");

        if(is_float_op && is_relop){
            std::string r_left  = ra.resolve(op1);
            std::string r_right = ra.resolve(op2);
            ra.emit_float_cmp(op, r_left, r_right, dst);
            ra.free_input(op1, r_left);
            ra.free_input(op2, r_right);
        } else {
            std::string r_left  = ra.resolve(op1);
            std::string r_dst   = ra.alloc_dst(dst);
            std::string r_right = ra.resolve(op2);
            ra.emit_rtl(new Compute_RTL_Stmt(r_dst, r_left, op, r_right));
            if(dst->is_variable()) ra.store_var(dst, r_dst);
            ra.free_input(op1, r_left);
            ra.free_input(op2, r_right);
        }
    } else {
        std::string r_src = ra.resolve(op1);
        std::string r_dst = ra.alloc_dst(dst);
        ra.emit_rtl(new Move_RTL_Stmt(r_dst, op, r_src));
        if(dst->is_variable()) ra.store_var(dst, r_dst);
        ra.free_input(op1, r_src);
    }
}

inline void Asgn_TAC_Stmt::gen_rtl(RegAlloc &ra){
    std::string r_src = ra.resolve(rhs);
    if(lhs->is_variable()){
        ra.store_var(lhs, r_src);
        if(rhs->is_temp()) ra.unmap_temp(rhs);
    } else {
        ra.remap_temp(rhs, lhs, r_src);
    }
}

inline void Label_TAC_Stmt::gen_rtl(RegAlloc &ra){
    ra.emit_rtl(new Label_RTL_Stmt(label));
}

inline void Goto_TAC_Stmt::gen_rtl(RegAlloc &ra){
    ra.emit_rtl(new Goto_RTL_Stmt(label));
}

inline void If_Goto_TAC_Stmt::gen_rtl(RegAlloc &ra){
    std::string r = ra.resolve(cond);
    ra.emit_rtl(new If_Goto_RTL_Stmt(r, label));
    ra.free_input(cond, r);
}

inline void Write_TAC_Stmt::gen_rtl(RegAlloc &ra){
    if(src->is_string()){
        ra.emit_rtl(new ILoad_RTL_Stmt("v0", "4"));
        if(src->is_variable()){
            ra.emit_rtl(new Load_RTL_Stmt("a0", src->to_string()));
        } else {
            std::string lbl = ra.next_str_label(src->to_string());
            ra.emit_rtl(new LoadAddr_RTL_Stmt("a0", lbl));
        }
        ra.emit_rtl(new Write_RTL_Stmt());
    } else if(src->is_float()){
        ra.emit_rtl(new ILoad_RTL_Stmt("v0", "3"));
        if(src->is_variable()){
            ra.emit_rtl(new Load_RTL_Stmt("f12", src->to_string()));
        } else if(src->is_temp()){
            std::string r = ra.resolve(src);
            ra.emit_rtl(new Move_RTL_Stmt("f12", "", r));
            ra.free_input(src, r);
        } else {
            ra.emit_rtl(new ILoad_RTL_Stmt("f12", src->to_string()));
        }
        ra.emit_rtl(new Write_RTL_Stmt());
    } else {
        ra.emit_rtl(new ILoad_RTL_Stmt("v0", "1"));
        if(src->is_variable()){
            ra.emit_rtl(new Load_RTL_Stmt("a0", src->to_string()));
        } else if(src->is_temp()){
            std::string r = ra.resolve(src);
            ra.emit_rtl(new Move_RTL_Stmt("a0", "", r));
            ra.free_input(src, r);
        } else {
            ra.emit_rtl(new ILoad_RTL_Stmt("a0", src->to_string()));
        }
        ra.emit_rtl(new Write_RTL_Stmt());
    }
}

inline void Read_TAC_Stmt::gen_rtl(RegAlloc &ra){
    if(dst->is_float()){
        ra.emit_rtl(new ILoad_RTL_Stmt("v0", "7"));
        ra.emit_rtl(new Read_RTL_Stmt(""));
        ra.emit_rtl(new Store_RTL_Stmt(dst->to_string(), "f0"));
    } else {
        ra.emit_rtl(new ILoad_RTL_Stmt("v0", "5"));
        ra.emit_rtl(new Read_RTL_Stmt(""));
        ra.emit_rtl(new Store_RTL_Stmt(dst->to_string(), "v0"));
    }
}

// L5: Call — push args, v1=call fname_, pop args, move result
inline void Call_TAC_Stmt::gen_rtl(RegAlloc &ra){
    // Push arguments right-to-left onto the stack
    for(int i = (int)args.size() - 1; i >= 0; i--){
        auto *arg = args[i];
        if(arg->is_float()){
            if(arg->is_temp()){
                std::string r = ra.resolve(arg);
                ra.free_input(arg, r);
                ra.emit_rtl(new Push_RTL_Stmt(r));
            } else {
                if(arg->is_variable())
                    ra.emit_rtl(new Load_RTL_Stmt("f2", arg->to_string()));
                else
                    ra.emit_rtl(new ILoad_RTL_Stmt("f2", arg->to_string()));
                ra.emit_rtl(new Push_RTL_Stmt("f2"));
            }
        } else {
            if(arg->is_temp()){
                std::string r = ra.resolve(arg);
                ra.free_input(arg, r);
                ra.emit_rtl(new Push_RTL_Stmt(r));
            } else {
                if(arg->is_variable())
                    ra.emit_rtl(new Load_RTL_Stmt("v0", arg->to_string()));
                else
                    ra.emit_rtl(new ILoad_RTL_Stmt("v0", arg->to_string()));
                ra.emit_rtl(new Push_RTL_Stmt("v0"));
            }
        }
    }

    // Emit call — with or without return value
    if(dst){
        bool is_float_ret = (ret_type == TYPE_FLOAT);
        std::string ret_reg = is_float_ret ? "f0" : "v1";
        ra.emit_rtl(new Call_RTL_Stmt(fname, ret_reg));
        // Pop args
        for(size_t i = 0; i < args.size(); i++)
            ra.emit_rtl(new Pop_RTL_Stmt());
        if(is_float_ret){
            // move.d: f2 <- f0 ; store.d: dst <- f2
            ra.emit_rtl(new Move_RTL_Stmt("f2", "", "f0"));
            if(dst->is_variable())
                ra.emit_rtl(new Store_RTL_Stmt(dst->to_string(), "f2"));
            else
                ra.emit_call_result(dst, true);
        } else {
            // move: v0 <- v1 ; store: dst <- v0
            ra.emit_rtl(new Move_RTL_Stmt("v0", "", "v1"));
            if(dst->is_variable())
                ra.emit_rtl(new Store_RTL_Stmt(dst->to_string(), "v0"));
            else
                ra.emit_call_result(dst, false);
        }
    } else {
        ra.emit_rtl(new Call_RTL_Stmt(fname, ""));
        for(size_t i = 0; i < args.size(); i++)
            ra.emit_rtl(new Pop_RTL_Stmt());
    }
}

// L5: Return — load result into v0/f0 then emit return reg
inline void Return_TAC_Stmt::gen_rtl(RegAlloc &ra){
    if(val){
        if(val->is_float()){
            if(val->is_variable())
                ra.emit_rtl(new Load_RTL_Stmt("f0", val->to_string()));
            else if(val->is_temp()){
                std::string r = ra.resolve(val);
                ra.emit_rtl(new Move_RTL_Stmt("f0", "", r));
                ra.free_input(val, r);
            } else
                ra.emit_rtl(new ILoad_RTL_Stmt("f0", val->to_string()));
            ra.emit_rtl(new Return_RTL_Stmt("f0"));
        } else {
            if(val->is_variable())
                ra.emit_rtl(new Load_RTL_Stmt("v1", val->to_string()));
            else if(val->is_temp()){
                std::string r = ra.resolve(val);
                ra.emit_rtl(new Move_RTL_Stmt("v1", "", r));
                ra.free_input(val, r);
            } else
                ra.emit_rtl(new ILoad_RTL_Stmt("v1", val->to_string()));
            ra.emit_rtl(new Return_RTL_Stmt("v1"));
        }
    } else {
        ra.emit_rtl(new Return_RTL_Stmt(""));
    }
}

inline void emit_rtl_for(const TACResult &tac){
    RegAlloc ra;
    for(auto *insn : tac.insns){
        insn->gen_rtl(ra);
        ra.flush();
    }
}

inline void emit_rtl_for(const TACResult &tac, RegAlloc &ra){
    for(auto *insn : tac.insns){
        insn->gen_rtl(ra);
        ra.flush();
    }
}

#endif // RTL_HH
