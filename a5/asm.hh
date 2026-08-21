#ifndef ASM_HH
#define ASM_HH

#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstdio>
#include "tac.hh"
#include "types.hh"

extern FILE *asmfile;

// ═══════════════════════════════════════════════════════════════════
//  VARIABLE INFO
// ═══════════════════════════════════════════════════════════════════

struct AsmVarInfo {
    bool is_global;
    int  offset;     // locals: negative $fp offset; params: positive; globals: 0 (use name)
    bool is_float;
};

// ═══════════════════════════════════════════════════════════════════
//  ASM CONTEXT  (per-function)
// ═══════════════════════════════════════════════════════════════════

class AsmCtx {
public:
    std::map<std::string, AsmVarInfo> var_map;    // varname_ → info
    std::map<std::string, std::string> temp_reg;  // tempN → register holding it
    std::vector<std::string> str_lits;            // ordered string literals
    std::string epilogue_label;                   // "epilogue_fname_" or "epilogue_main"

    std::set<std::string> used_int;
    std::set<std::string> used_flt;

    std::string alloc_int() {
        static const char* pool[] = {
            "v0","t0","t1","t2","t3","t4","t5","t6","t7","t8","t9"
        };
        for (auto r : pool)
            if (!used_int.count(r)) { used_int.insert(r); return r; }
        return "t9";
    }
    std::string alloc_flt() {
        for (int i = 2; i <= 30; i += 2) {
            std::string r = "f" + std::to_string(i);
            if (!used_flt.count(r)) { used_flt.insert(r); return r; }
        }
        return "f2";
    }
    void free_int(const std::string &r) { used_int.erase(r); }
    void free_flt(const std::string &r) { used_flt.erase(r); }

    // Register or index a string literal and return its label
    std::string str_label(const std::string &val) {
        auto it = std::find(str_lits.begin(), str_lits.end(), val);
        if (it == str_lits.end()) {
            str_lits.push_back(val);
            it = str_lits.end() - 1;
        }
        return "_str_" + std::to_string(it - str_lits.begin());
    }

    // Load opd into a register, emitting load instruction if needed.
    // Returns the register name. Call free_opd() when done.
    std::string resolve(TAC_Opd *opd, bool &allocated) {
        allocated = false;
        // Already in a register?
        if (opd->is_temp()) {
            auto it = temp_reg.find(opd->to_string());
            if (it != temp_reg.end()) {
                // Ensure the register is marked as in-use so alloc won't hand it out again
                if (opd->is_float()) used_flt.insert(it->second);
                else                 used_int.insert(it->second);
                return it->second;
            }
        }

        bool flt = opd->is_float();
        std::string r = flt ? alloc_flt() : alloc_int();
        allocated = true;

        if (opd->is_variable()) {
            auto it = var_map.find(opd->to_string());
            if (it != var_map.end()) {
                AsmVarInfo &vi = it->second;
                if (vi.is_global) {
                    fprintf(asmfile, flt
                        ? "\tl.d $%s, %s\t\t \n"
                        : "\tlw $%s, %s\t\t \n",
                        r.c_str(), opd->to_string().c_str());
                } else {
                    fprintf(asmfile, flt
                        ? "\tl.d $%s, %d($fp)\t\t \n"
                        : "\tlw $%s, %d($fp)\t\t \n",
                        r.c_str(), vi.offset );
                }
            }
        } else if (opd->is_string()) {
            std::string lbl = str_label(opd->to_string());
            fprintf(asmfile, "\tla $%s, %s\t\t \n",
                    r.c_str(), lbl.c_str());
        } else {
            // Immediate constant
            fprintf(asmfile, flt
                ? "\tli.d $%s, %s\t\t \n"
                : "\tli $%s, %s\t\t \n",
                r.c_str(), opd->to_string().c_str());
        }

        if (opd->is_temp())
            temp_reg[opd->to_string()] = r;
        return r;
    }

    // Store result register r into dst, emitting store if dst is a variable.
    void store_dst(TAC_Opd *dst, const std::string &r) {
        if (dst->is_variable()) {
            auto it = var_map.find(dst->to_string());
            if (it != var_map.end()) {
                AsmVarInfo &vi = it->second;
                if (vi.is_global) {
                    fprintf(asmfile, vi.is_float
                        ? "\ts.d $%s, %s\t\t \n"
                        : "\tsw $%s, %s\t\t \n",
                        r.c_str(), dst->to_string().c_str());
                } else {
                    fprintf(asmfile, vi.is_float
                        ? "\ts.d $%s, %d($fp)\t\t \n"
                        : "\tsw $%s, %d($fp)\t\t \n",
                        r.c_str(), vi.offset);
                }
            }
            // Variable is now in memory — free the register
            if (dst->is_float()) free_flt(r); else free_int(r);
        } else if (dst->is_temp()) {
            // Keep in register — mark it as in-use so alloc won't hand it out again
            temp_reg[dst->to_string()] = r;
            if (dst->is_float()) used_flt.insert(r);
            else                 used_int.insert(r);
        }
    }

    // Free the register used by opd (after we are done consuming it as a source)
    void free_opd(TAC_Opd *opd, const std::string &r) {
        if (opd->is_temp()) temp_reg.erase(opd->to_string());
        if (opd->is_float()) free_flt(r); else free_int(r);
    }
};

// ═══════════════════════════════════════════════════════════════════
//  INSTRUCTION EMISSION HELPERS
// ═══════════════════════════════════════════════════════════════════

static inline std::string spim_arith(const std::string &op, bool flt) {
    std::string s = flt ? ".d" : "";
    if (op == "+") return "add" + s;
    if (op == "-") return "sub" + s;
    if (op == "*") return "mul" + s;
    if (op == "/") return "div" + s;
    if (op == "&&") return "and";
    if (op == "||") return "or";
    return op;
}

static inline std::string spim_relop(const std::string &op) {
    if (op == "<")  return "slt";
    if (op == "<=") return "sle";
    if (op == ">")  return "sgt";
    if (op == ">=") return "sge";
    if (op == "==") return "seq";
    if (op == "!=") return "sne";
    return op;
}

// ─── Compute ───────────────────────────────────────────────────────
static void emit_compute(Compute_TAC_Stmt *s, AsmCtx &ctx) {
    bool flt    = s->op1->is_float() || (s->op2 && s->op2->is_float());
    bool is_rel = (s->op=="<"||s->op=="<="||s->op==">"||s->op==">="||
                   s->op=="=="||s->op=="!=");

    // ── Unary ──
    if (!s->op2) {
        bool a; std::string r1 = ctx.resolve(s->op1, a);
        std::string rd = flt ? ctx.alloc_flt() : ctx.alloc_int();
        if (s->op == "!") {
            fprintf(asmfile, "\txori $%s, $%s, 1\t\t \n",
                    rd.c_str(), r1.c_str());
        } else { // uminus
            fprintf(asmfile, flt
                ? "\tneg.d $%s, $%s\t\t \n"
                : "\tneg $%s, $%s\t\t \n",
                rd.c_str(), r1.c_str());
        }
        ctx.free_opd(s->op1, r1);
        ctx.store_dst(s->dst, rd);
        return;
    }

    // ── Integer relational ──
    if (!flt && is_rel) {
    bool a1; std::string r1 = ctx.resolve(s->op1, a1);
    std::string rd = ctx.alloc_int();   // ← move this here
    bool a2; std::string r2 = ctx.resolve(s->op2, a2);
    fprintf(asmfile, "\t%s $%s, $%s, $%s\t\t \n",
                spim_relop(s->op).c_str(),
                rd.c_str(), r1.c_str(), r2.c_str()
                );
        ctx.free_opd(s->op1, r1);
        ctx.free_opd(s->op2, r2);
        ctx.store_dst(s->dst, rd);
        return;
    }

    // ── Float relational ──
    // ── Float relational ──
if (flt && is_rel) {
    bool a1; std::string r1 = ctx.resolve(s->op1, a1);
    bool a2; std::string r2 = ctx.resolve(s->op2, a2);
    std::string fcmp; bool invert = false;
    if      (s->op == "<")  { fcmp = "c.lt.d"; }
    else if (s->op == "<=") { fcmp = "c.le.d"; }
    else if (s->op == ">")  { fcmp = "c.le.d"; invert = true; }
    else if (s->op == ">=") { fcmp = "c.lt.d"; invert = true; }
    else if (s->op == "==") { fcmp = "c.eq.d"; }
    else                    { fcmp = "c.eq.d"; invert = true; }

    fprintf(asmfile, "\t%s $%s, $%s\n", fcmp.c_str(), r1.c_str(), r2.c_str());

    std::string rd = ctx.alloc_int();
    std::string rt = ctx.alloc_int();          // extra temp
    fprintf(asmfile, "\tli $%s, 1\n", rd.c_str());
    fprintf(asmfile, "\tmove $%s, $zero\n", rt.c_str());

    if(invert) fprintf(asmfile, "\tmovf $%s, $%s, 0\n", rt.c_str(), rd.c_str());
    else
    fprintf(asmfile, "\tmovt $%s, $%s, 0\n", rt.c_str(), rd.c_str());
    ctx.free_int(rd);                          // rd done, rt has the result

    ctx.free_opd(s->op1, r1);
    ctx.free_opd(s->op2, r2);
    ctx.store_dst(s->dst, rt);
    return;
}

    // ── Binary arithmetic ──
    bool a1; std::string r1 = ctx.resolve(s->op1, a1);
    std::string rd = flt ? ctx.alloc_flt() : ctx.alloc_int();
    bool a2; std::string r2 = ctx.resolve(s->op2, a2);
    fprintf(asmfile, "\t%s $%s, $%s, $%s\t\t \n",
            spim_arith(s->op, flt).c_str(),
            rd.c_str(), r1.c_str(), r2.c_str());
    ctx.free_opd(s->op1, r1);
    ctx.free_opd(s->op2, r2);
    ctx.store_dst(s->dst, rd);
}

// ─── Assignment ────────────────────────────────────────────────────
static void emit_asgn(Asgn_TAC_Stmt *s, AsmCtx &ctx) {
    bool a; std::string r = ctx.resolve(s->rhs, a);
    ctx.store_dst(s->lhs, r);
    // rhs temp was consumed into a variable — remove its register mapping
    if (s->rhs->is_temp() && s->lhs->is_variable())
        ctx.temp_reg.erase(s->rhs->to_string());
}

// ─── Label ─────────────────────────────────────────────────────────
static void emit_label(Label_TAC_Stmt *s, AsmCtx &) {
    fprintf(asmfile, "%s:\n", s->label.c_str());
}

// ─── Goto ──────────────────────────────────────────────────────────
static void emit_goto(Goto_TAC_Stmt *s, AsmCtx &) {
    fprintf(asmfile, "\tj %s\n", s->label.c_str());
}

// ─── If-Goto ───────────────────────────────────────────────────────
static void emit_if_goto(If_Goto_TAC_Stmt *s, AsmCtx &ctx) {
    bool a; std::string r = ctx.resolve(s->cond, a);
    fprintf(asmfile, "\tbgtz $%s, %s\n", r.c_str(), s->label.c_str());
    ctx.free_opd(s->cond, r);
}

// ─── Write ─────────────────────────────────────────────────────────
static void emit_write(Write_TAC_Stmt *s, AsmCtx &ctx) {
    if (s->src->is_string()) {
        fprintf(asmfile,
            "\tli $v0, 4\t\t \n");
        if (s->src->is_variable()) {
            auto it = ctx.var_map.find(s->src->to_string());
            if (it != ctx.var_map.end()) {
                if (it->second.is_global)
                    fprintf(asmfile, "\tlw $a0, %s\t\t \n",
                            s->src->to_string().c_str());
                else
                    fprintf(asmfile, "\tlw $a0, %d($fp)\t\t \n",
                            it->second.offset);
            }
        } else {
            std::string lbl = ctx.str_label(s->src->to_string());
            fprintf(asmfile, "\tla $a0, %s\t\t \n",
                    lbl.c_str());
        }
        fprintf(asmfile, "\tsyscall\n");

    } else if (s->src->is_float()) {
        fprintf(asmfile,
            "\tli $v0, 3\t\t \n");
        if (s->src->is_variable()) {
            auto it = ctx.var_map.find(s->src->to_string());
            if (it != ctx.var_map.end()) {
                if (it->second.is_global)
                    fprintf(asmfile, "\tl.d $f12, %s\t\t \n",
                            s->src->to_string().c_str());
                else
                    fprintf(asmfile, "\tl.d $f12, %d($fp)\t\t \n",
                            it->second.offset);
            }
        } else if (s->src->is_temp()) {
            bool a; std::string r = ctx.resolve(s->src, a);
            fprintf(asmfile, "\tmov.d $f12, $%s\n", r.c_str());
            ctx.free_opd(s->src, r);
        } else {
            fprintf(asmfile, "\tli.d $f12, %s\t\t \n",
                    s->src->to_string().c_str());
        }
        fprintf(asmfile, "\tsyscall\n");

    } else {
        // integer / bool
        fprintf(asmfile,
            "\tli $v0, 1\t\t \n");
        if (s->src->is_variable()) {
            auto it = ctx.var_map.find(s->src->to_string());
            if (it != ctx.var_map.end()) {
                if (it->second.is_global)
                    fprintf(asmfile, "\tlw $a0, %s\t\t \n",
                            s->src->to_string().c_str());
                else
                    fprintf(asmfile, "\tlw $a0, %d($fp)\t\t \n",
                            it->second.offset);
            }
        } else if (s->src->is_temp()) {
            bool a; std::string r = ctx.resolve(s->src, a);
            fprintf(asmfile, "\tmove $a0, $%s\t\t \n",
                    r.c_str());
            ctx.free_opd(s->src, r);
        } else {
            fprintf(asmfile, "\tli $a0, %s\t\t \n",
                    s->src->to_string().c_str());
        }
        fprintf(asmfile, "\tsyscall\n");
    }
}

// ─── Read ──────────────────────────────────────────────────────────
static void emit_read(Read_TAC_Stmt *s, AsmCtx &ctx) {
    auto it = ctx.var_map.find(s->dst->to_string());
    if (s->dst->is_float()) {
        fprintf(asmfile,
            "\tli $v0, 7\t\t \n");
        fprintf(asmfile, "\tsyscall\n");
        if (it != ctx.var_map.end()) {
            if (it->second.is_global)
                fprintf(asmfile, "\ts.d $f0, %s\t\t \n",
                        s->dst->to_string().c_str());
            else
                fprintf(asmfile, "\ts.d $f0, %d($fp)\t\t \n",
                        it->second.offset);
        }
    } else {
        fprintf(asmfile,
            "\tli $v0, 5\t\t \n");
        fprintf(asmfile, "\tsyscall\n");
        if (it != ctx.var_map.end()) {
            if (it->second.is_global)
                fprintf(asmfile, "\tsw $v0, %s\t\t \n",
                        s->dst->to_string().c_str());
            else
                fprintf(asmfile, "\tsw $v0, %d($fp)\t\t \n",
                        it->second.offset);
        }
    }
}
static void emit_call(Call_TAC_Stmt *s, AsmCtx &ctx) {
    for (int i = (int)s->args.size() - 1; i >= 0; i--) {
        TAC_Opd *arg = s->args[i];
        bool flt = arg->is_float();

        if (arg->is_variable()) {
            auto it = ctx.var_map.find(arg->to_string());
            if (it != ctx.var_map.end()) {
                if (flt) {
                    if (it->second.is_global)
                        fprintf(asmfile, "\tl.d $f2, %s\t\t \n",
                                arg->to_string().c_str());
                    else
                        fprintf(asmfile, "\tl.d $f2, %d($fp)\t\t \n",
                                it->second.offset);
                    fprintf(asmfile, "\ts.d $f2, -4($sp)\t\t \n");
                    fprintf(asmfile, "\tsub $sp, $sp, 8\t\t \n");
                    continue;
                }
                if (it->second.is_global)
                    fprintf(asmfile, "\tlw $v0, %s\t\t \n",
                            arg->to_string().c_str());
                else
                    fprintf(asmfile, "\tlw $v0, %d($fp)\t\t \n",
                            it->second.offset);
            }
        } else if (arg->is_temp()) {
            bool a; std::string r = ctx.resolve(arg, a);
            if (flt) {
                fprintf(asmfile, "\ts.d $%s, -4($sp)\t\t \n", r.c_str());
                fprintf(asmfile, "\tsub $sp, $sp, 8\t\t \n");
                ctx.free_opd(arg, r);
                continue;
            }
            fprintf(asmfile, "\tsw $%s, 0($sp)\t\t \n", r.c_str());
            ctx.free_opd(arg, r);
            fprintf(asmfile, "\tsub $sp, $sp, 4\t\t \n");
            continue;
        } else {
            // immediate
            if (flt) {
                fprintf(asmfile, "\tli.d $f2, %s\n", arg->to_string().c_str());
                fprintf(asmfile, "\ts.d $f2, -4($sp)\t\t \n");
                fprintf(asmfile, "\tsub $sp, $sp, 8\t\t \n");
                continue;
            }
            fprintf(asmfile, "\tli $v0, %s\t\t \n",
                    arg->to_string().c_str());
        }
        fprintf(asmfile, "\tsw $v0, 0($sp)\t\t \n");
        fprintf(asmfile, "\tsub $sp, $sp, 4\t\t \n");
    }

    fprintf(asmfile, "\tjal %s_\n", s->fname.c_str());

    // Pop args — float args used 8 bytes, int args used 4
    for (auto *arg : s->args) {
        int sz = arg->is_float() ? 8 : 4;
        fprintf(asmfile, "\tadd $sp, $sp, %d\t\t \n", sz);
    }

    if (s->dst) {
        bool flt_ret = (s->ret_type == TYPE_FLOAT);
        if (flt_ret) {
            fprintf(asmfile, "\tmov.d $f2, $f0\t\t \n");
            if (s->dst->is_variable()) {
                auto it = ctx.var_map.find(s->dst->to_string());
                if (it != ctx.var_map.end()) {
                    if (it->second.is_global)
                        fprintf(asmfile, "\ts.d $f2, %s\t\t \n",
                                s->dst->to_string().c_str());
                    else
                        fprintf(asmfile, "\ts.d $f2, %d($fp)\t\t \n",
                                it->second.offset);
                }
            } else {
                ctx.temp_reg[s->dst->to_string()] = "f2";
                ctx.used_flt.insert("f2");
            }
        } else {
            fprintf(asmfile,
                "\tmove $v0, $v1\t\t \n");
            if (s->dst->is_variable()) {
                auto it = ctx.var_map.find(s->dst->to_string());
                if (it != ctx.var_map.end()) {
                    if (it->second.is_global)
                        fprintf(asmfile, "\tsw $v0, %s\t\t \n",
                                s->dst->to_string().c_str());
                    else
                        fprintf(asmfile, "\tsw $v0, %d($fp)\t\t \n",
                                it->second.offset);
                }
            } else {
                ctx.temp_reg[s->dst->to_string()] = "v0";
                ctx.used_int.insert("v0");
            }
        }
    }
}
// ─── Return ────────────────────────────────────────────────────────
// TAC emits: stemp0 = value; goto ExitLabel; ... ExitLabel: return stemp0
// In ASM:  the Goto emits "j LabelN", and Return_TAC_Stmt emits:
//   lw $v1, stemp_offset($fp)
//   j epilogue_fname_
static void emit_return(Return_TAC_Stmt *s, AsmCtx &ctx) {
    if (!s->val) return; // void — no action needed here

    bool flt = s->val->is_float();
    if (flt) {
       if (s->val->is_variable()) {
    auto it = ctx.var_map.find(s->val->to_string());
    if (it != ctx.var_map.end()) {
        if (it->second.is_global)
            fprintf(asmfile, "\tl.d $f0, %s\n", s->val->to_string().c_str());
        else
            fprintf(asmfile, "\tl.d $f0, %d($fp)\n", it->second.offset);
    }
} else {
    bool a; std::string r = ctx.resolve(s->val, a);
    fprintf(asmfile, "\tmov.d $f0, $%s\n", r.c_str());
    ctx.free_opd(s->val, r);
}
fprintf(asmfile, "\tj %s\n", ctx.epilogue_label.c_str());
} else {
        if (s->val->is_variable()) {
            auto it = ctx.var_map.find(s->val->to_string());
            if (it != ctx.var_map.end()) {
                if (it->second.is_global)
                    fprintf(asmfile,
                        "\tlw $v1, %s\t\t \n",
                        s->val->to_string().c_str());
                else
                    fprintf(asmfile,
                        "\tlw $v1, %d($fp)\t\t \n",
                        it->second.offset);
            }
        } else if (s->val->is_temp()) {
            bool a; std::string r = ctx.resolve(s->val, a);
            fprintf(asmfile, "\tmove $v1, $%s\n", r.c_str());
            ctx.free_opd(s->val, r);
        } else {
            fprintf(asmfile, "\tli $v1, %s\n", s->val->to_string().c_str());
        }
        fprintf(asmfile, "\tj %s\n", ctx.epilogue_label.c_str());
    }
}

// ═══════════════════════════════════════════════════════════════════
//  MAIN ENTRY: emit full SPIM for one function
// ═══════════════════════════════════════════════════════════════════

// local_vars : declared locals in order — (name WITHOUT trailing _, type)
// params     : formal params in order  — (name WITHOUT trailing _, type)
// global_vars: pre-built map for entire program (name WITH trailing _)
// str_lits   : pre-ordered string literals for .data (shared across functions)
// insns      : TAC instruction list for this function
static void emit_asm_func(
    const std::string                              &fname,
    [[maybe_unused]] Type                            ret_type,
    const std::vector<std::pair<std::string,Type>> &local_vars,
    const std::vector<std::pair<std::string,Type>> &params,
    const std::map<std::string, AsmVarInfo>        &global_vars,
    const std::vector<std::string>                 &str_lits,
    const std::vector<TAC_Stmt*>                   &insns)
{
    std::string pname = (fname == "main") ? "main" : fname + "_";
    std::string epi   = "epilogue_" + pname;

    // ── Scan TAC for stemp names AND their types ──────────────────
    // Use a map keyed by stemp NUMBER so they are always in numeric order
    // (stemp0 < stemp1 < stemp2). This is critical: ternary gen_tac() calls
    // fresh_stemp() for the OUTER ternary first, so stemp0 is the outermost
    // result slot and must get the lowest (first-assigned) $fp offset.
    std::map<int, std::pair<std::string,Type>> stemp_map;
    auto check_opd = [&](TAC_Opd *opd) {
        if (!opd) return;
        std::string n = opd->to_string();
        if (n.rfind("stemp", 0) == 0) {
            int num = std::stoi(n.substr(5));
            if (!stemp_map.count(num))
                stemp_map[num] = {n, opd->is_float() ? TYPE_FLOAT : TYPE_INT};
        }
    };
    for (auto *insn : insns) {
        if (auto *a  = dynamic_cast<Asgn_TAC_Stmt*>(insn))    { check_opd(a->lhs);  check_opd(a->rhs); }
        if (auto *c  = dynamic_cast<Compute_TAC_Stmt*>(insn)) { check_opd(c->dst);  check_opd(c->op1); check_opd(c->op2); }
        if (auto *r  = dynamic_cast<Return_TAC_Stmt*>(insn))  { check_opd(r->val); }
        if (auto *ig = dynamic_cast<If_Goto_TAC_Stmt*>(insn)) { check_opd(ig->cond); }
        if (auto *ca = dynamic_cast<Call_TAC_Stmt*>(insn))    { check_opd(ca->dst); }
    }
    // Flatten into vector sorted by stemp number (stemp0 first)
    std::vector<std::pair<std::string,Type>> stemps;
    for (auto &kv : stemp_map) stemps.push_back(kv.second);

    // ── Assign local offsets ──────────────────────────────────────
    // Layout (for void): locals first (in decl order), then stemps.
    // Layout (for non-void): stemps first (stemp0 closest to fp), then locals.
    // Offset formula: off -= size (4 for int/bool/string, 8 for float), loc = off.
    // This correctly places floats at 8-byte-aligned negative offsets.
    std::map<std::string, AsmVarInfo> loc_map;
    int off = -4;

    auto assign_var = [&](const std::string &key, Type t, bool is_flt) {
        int sz = is_flt ? 8 : 4;
        off -= (sz - 4);   // extra 4 bytes for float (total = 8), 0 for int
        loc_map[key] = AsmVarInfo{false, off, is_flt};
        off -= 4;
    };

    if (ret_type == TYPE_VOID) {
        // void: locals first (in decl order), then all stemps
        for (auto &v : local_vars)
            assign_var(v.first + "_", v.second, v.second == TYPE_FLOAT);
        for (auto &st : stemps)
            assign_var(st.first, st.second, st.second == TYPE_FLOAT);
    } else {
        // non-void: stemp0 (return slot) first, then locals, then stemp1+
        // stemp0 is always the function return temp (allocated by print_asm before body).
        // stemp1, stemp2, ... are body-generated (ternary etc.) and go after locals.
        if (!stemps.empty())
            assign_var(stemps[0].first, stemps[0].second, stemps[0].second == TYPE_FLOAT);
        for (auto &v : local_vars)
            assign_var(v.first + "_", v.second, v.second == TYPE_FLOAT);
        for (size_t i = 1; i < stemps.size(); i++)
            assign_var(stemps[i].first, stemps[i].second, stemps[i].second == TYPE_FLOAT);
    }

    // frame_size = bytes used by locals+stemps + 8 (for saved $ra and $fp)
    int local_bytes = (-4) - off;
    int frame_size  = local_bytes + 8;
    if (frame_size < 8) frame_size = 8;

    // ── Assign param offsets (positive, starting at 8($fp)) ───────
    std::map<std::string, AsmVarInfo> param_map;
    int poff = 8;
    for (auto &p : params) {
        bool flt = (p.second == TYPE_FLOAT);
        param_map[p.first + "_"] = AsmVarInfo{false, poff, flt};
        poff += (flt ? 8 : 4);
    }

    // ── .text header + prologue ───────────────────────────────────
    fprintf(asmfile,
        "\t.text\t\t\t \n");
    fprintf(asmfile,
        "\t.globl %s\t\t \n",
        pname.c_str());
    if (fname == "main")
        fprintf(asmfile,
            "%s:\t\t\t\t \n",
            pname.c_str());
    else
        fprintf(asmfile,
            "%s:\t\t\t\t \n",
            pname.c_str());

    fprintf(asmfile, " \n");
    fprintf(asmfile, "\tsw $ra, 0($sp)\t\t \n");
    fprintf(asmfile, "\tsw $fp, -4($sp)\t\t \n");
    fprintf(asmfile, "\tsub $fp, $sp, 4\t\t \n");
    fprintf(asmfile, "\tsub $sp, $sp, %d\t \n", frame_size);
    fprintf(asmfile, " \n");

    // ── Build AsmCtx ─────────────────────────────────────────────
    AsmCtx ctx;
    ctx.epilogue_label = epi;
    ctx.str_lits       = str_lits;
    for (auto &kv : global_vars) ctx.var_map[kv.first] = kv.second;
    for (auto &kv : loc_map)     ctx.var_map[kv.first] = kv.second;
    for (auto &kv : param_map)   ctx.var_map[kv.first] = kv.second;

    // ── Emit body ─────────────────────────────────────────────────
    for (auto *insn : insns) {
        if (auto *s = dynamic_cast<Compute_TAC_Stmt*>(insn))  { emit_compute(s, ctx);  continue; }
        if (auto *s = dynamic_cast<Asgn_TAC_Stmt*>(insn))     { emit_asgn(s, ctx);     continue; }
        if (auto *s = dynamic_cast<Label_TAC_Stmt*>(insn))    { emit_label(s, ctx);    continue; }
        if (auto *s = dynamic_cast<Goto_TAC_Stmt*>(insn))     { emit_goto(s, ctx);     continue; }
        if (auto *s = dynamic_cast<If_Goto_TAC_Stmt*>(insn))  { emit_if_goto(s, ctx);  continue; }
        if (auto *s = dynamic_cast<Write_TAC_Stmt*>(insn))    { emit_write(s, ctx);    continue; }
        if (auto *s = dynamic_cast<Read_TAC_Stmt*>(insn))     { emit_read(s, ctx);     continue; }
        if (auto *s = dynamic_cast<Call_TAC_Stmt*>(insn))     { emit_call(s, ctx);     continue; }
        if (auto *s = dynamic_cast<Return_TAC_Stmt*>(insn))   { emit_return(s, ctx);   continue; }
    }

    // ── Epilogue ──────────────────────────────────────────────────
    fprintf(asmfile, "%s:\n", epi.c_str());
    fprintf(asmfile,
        "\tadd $sp, $sp, %d\t \n",
        frame_size);
    fprintf(asmfile, "\tlw $fp, -4($sp)\t\t \n");
    fprintf(asmfile, "\tlw $ra, 0($sp)\t\t \n");
    fprintf(asmfile, "\tjr $ra\t\t\t \n");
    fprintf(asmfile, " \n");
}
#endif // ASM_HH
