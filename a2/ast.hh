#pragma once 

#include<string>
#include<iostream>
#include <vector>
#include "symbol_table.hh"

#define AST_SPACE "         "
#define AST_NODE_SPACE "            "
#define AST_SUB_NODE_SPACE "               "
using namespace std;

enum rop {
    OP_LE, OP_LT, OP_GT, OP_GE, OP_NE, OP_EQ,
    OP_PLUS, OP_MINUS, OP_MULT, OP_DIV, OP_UMINUS,
    OP_AND, OP_OR
};
class Ast;

class Ast
{
protected:
	typedef enum
	{
		zero_arity = 0,
		unary_arity = 1,
		binary_arity = 2
	}Ast_Arity;

	string node_data_type;
	Ast_Arity ast_num_child;

	int lineno;

public:
	Ast();
    Ast(int line) : lineno(line) {}
	~Ast();

	virtual string get_data_type();
	virtual bool check_ast();
	virtual Symbol& get_symbol_entry();

	virtual void print(ostream & file_buffer) = 0;
};

class Assignment_Ast:public Ast
{
	Ast * lhs;
	Ast * rhs;

public:
	Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line);
	~Assignment_Ast();

	//Data_Type get_data_type();
	bool check_ast();
	void print(ostream & file_buffer);
};

class Name_Ast:public Ast
{
	const Symbol * variable_symbol_entry;

public:
	Name_Ast(const string & name, const Symbol & var_entry, int line);
	~Name_Ast();

	string get_data_type() const;
	const Symbol & get_symbol_entry() const;

	void print(ostream & file_buffer);
};

class Relational_Ast:public Ast
{
	Ast * lhs;
	Ast * rhs;
	rop rel_oper;
public:
	Relational_Ast(Ast * temp_lhs, Ast * temp_rhs, rop a, int line);

	~Relational_Ast();

	string get_data_type();

	bool check_ast();
	void print(ostream & file_buffer);
	
};

class Expression_Ast:public Ast
{
	Ast * lhs;
	Ast * rhs;
	rop rel_oper;
public:
	Expression_Ast(Ast * temp_lhs, Ast * temp_rhs, rop a, int line);
	~Expression_Ast();
	string get_data_type();
	bool check_ast();
	void print(ostream & file_buffer);
};

class Uminus_Ast : public Ast {
    Ast *operand;

public:
    Uminus_Ast(Ast *op, int line);
    ~Uminus_Ast();
    bool check_ast() override;
    void print(std::ostream &file_buffer) override;
};

class Constant_Ast : public Ast {
protected:
    int lineno;

public:
    Constant_Ast(int line) : lineno(line) {}
    virtual ~Constant_Ast() {}
};



class Int_Ast : public Constant_Ast {
    int value;

public:
    Int_Ast(int v, int line);

    bool check_ast() override;
    void print(std::ostream &out) override;
};


class Float_Ast : public Constant_Ast {
    float value;

public:
    Float_Ast(float v, int line);

    bool check_ast() override;
    void print(std::ostream &out) override;
};


class String_Ast : public Constant_Ast {
    std::string value;

public:
    String_Ast(const std::string &v, int line);

    bool check_ast() override;
    void print(std::ostream &out) override;
};


class Sequence_Ast : public Ast {
    std::vector<Ast*> stmt_list;

public:
    Sequence_Ast(std::vector<Ast*> &stmts);
    ~Sequence_Ast();

    bool check_ast() override;
    void print(std::ostream &out) override;
}; 

/* ================= */
/* Ternary AST       */
/* ================= */

class Ternary_Ast : public Ast {
    Ast *cond;
    Ast *true_expr;
    Ast *false_expr;
    int lineno;

public:
    Ternary_Ast(Ast *c, Ast *t, Ast *f, int line);
    ~Ternary_Ast();

    bool check_ast() override;
    void print(std::ostream &out) override;
};

/* ================= */
/* Logical AST       */
/* ================= */

class Logical_Ast : public Ast {
    Ast *lhs;
    Ast *rhs;
    int op;   // AND / OR
    int lineno;

public:
    Logical_Ast(Ast *l, Ast *r, int oper, int line);
    ~Logical_Ast();

    bool check_ast() override;
    void print(std::ostream &out) override;
};

class Logical_Not_Ast : public Ast {
    Ast *expr;
    int lineno;

public:
    Logical_Not_Ast(Ast *e, int line);
    ~Logical_Not_Ast();

    bool check_ast() override;
    void print(std::ostream &out) override;
};

/* ================= */
/* I/O ASTs          */
/* ================= */

class Print_Ast : public Ast {
    Ast *expr;
    int lineno;

public:
    Print_Ast(Ast *e, int line);
    ~Print_Ast();

    bool check_ast() override;
    void print(std::ostream &out) override;
};

class Read_Ast : public Ast {
    Ast *var;
    int lineno;

public:
    Read_Ast(Ast *v, int line);
    ~Read_Ast();

    bool check_ast() override;
    void print(std::ostream &out) override;
};
