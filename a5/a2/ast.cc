#include "ast.hh"

/* ------------------ Base AST ------------------ */

Ast::Ast() : ast_num_child(zero_arity), lineno(0) {}

Ast::~Ast() {}

string Ast::get_data_type() {
    return node_data_type;
}

bool Ast::check_ast() {
    return true;
}

Symbol& Ast::get_symbol_entry() {
    cerr << "Internal Error: get_symbol_entry() called on non-name AST\n";
    exit(1);
}

/* ------------------ Assignment AST ------------------ */

Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line) {
    lhs = temp_lhs;
    rhs = temp_rhs;
    lineno = line;
    ast_num_child = binary_arity;
}

Assignment_Ast::~Assignment_Ast() {}

bool Assignment_Ast::check_ast() {
    bool ok = true;

    if (!lhs->check_ast()) ok = false;
    if (!rhs->check_ast()) ok = false;

    if (lhs->get_data_type() != rhs->get_data_type()) {
        cerr << "Type Error at line " << lineno << endl;
        ok = false;
    }
    cout << "Assign LHS type: " << lhs->get_data_type()
     << " RHS type: " << rhs->get_data_type()
     << " at line " << lineno << endl;
    return ok;
}

void Assignment_Ast::print(ostream & file_buffer) {
    file_buffer << AST_SPACE << "Assignment:\n";
    file_buffer << AST_NODE_SPACE << "LHS:\n";
    lhs->print(file_buffer);
    file_buffer << AST_NODE_SPACE << "RHS:\n";
    rhs->print(file_buffer);
}

/* ------------------ Name AST ------------------ */

Name_Ast::Name_Ast(const string & name,
                   const Symbol & var_entry,
                   int line)
    : Ast(line)
{
    variable_symbol_entry = &var_entry;
    node_data_type = var_entry.type;
    ast_num_child = zero_arity;
}

Name_Ast::~Name_Ast() {}

string Name_Ast::get_data_type() const {
    return node_data_type;
}

const Symbol & Name_Ast::get_symbol_entry() const {
    return *variable_symbol_entry;
}

void Name_Ast::print(ostream & file_buffer) {
    file_buffer << AST_SPACE
                << "Name : "
                << variable_symbol_entry->name
                << " <" << variable_symbol_entry->type << ">\n";
}

/* ------------------ Relational AST ------------------ */

Relational_Ast::Relational_Ast(Ast * temp_lhs, Ast * temp_rhs, rop a, int line) {
    lhs = temp_lhs;
    rhs = temp_rhs;
    rel_oper = a;
    lineno = line;
    ast_num_child = binary_arity;
    node_data_type = "bool";
}

Relational_Ast::~Relational_Ast() {}

string Relational_Ast::get_data_type() {
    return "bool";
}

bool Relational_Ast::check_ast() {
    string lhs_type = lhs->get_data_type();
    string rhs_type = rhs->get_data_type();

    if (lhs_type != rhs_type) {
        cerr << "Type Error at line " << lineno
             << ": relational operands must have same type\n";
        return false;
    }
    return true;
}

void Relational_Ast::print(ostream & file_buffer) {
    file_buffer << AST_SPACE << "Relational Expression:\n";
    lhs->print(file_buffer);
    rhs->print(file_buffer);
}

/* ------------------ Expression AST ------------------ */

Expression_Ast::Expression_Ast(Ast * temp_lhs, Ast * temp_rhs, rop a, int line) {
    lhs = temp_lhs;
    rhs = temp_rhs;
    rel_oper = a;
    lineno = line;
    ast_num_child = binary_arity;

    // Type propagation
    node_data_type = lhs->get_data_type();
}

Expression_Ast::~Expression_Ast() {}

string Expression_Ast::get_data_type() {
    return node_data_type;
}

bool Expression_Ast::check_ast() {
    if (!lhs->check_ast()) return false;
    if (!rhs->check_ast()) return false;

    if (lhs->get_data_type() != rhs->get_data_type()) {
        cerr << "Type mismatch: left operand is " << lhs->get_data_type() << " but right operand is " << rhs->get_data_type() << endl;
        return false;
    }

    node_data_type = lhs->get_data_type();
    return true;
}

void Expression_Ast::print(ostream & file_buffer) {
    file_buffer << AST_SPACE << "Expression:\n";
    lhs->print(file_buffer);
    rhs->print(file_buffer);
}

/* ------------------ Unary Minus AST ------------------ */

Uminus_Ast::Uminus_Ast(Ast *op, int line)
{
    operand = op;
    lineno = line;
}

Uminus_Ast::~Uminus_Ast() {}

void Uminus_Ast::print(std::ostream &file_buffer)
{
    file_buffer << "(- ";
    operand->print(file_buffer);
    file_buffer << ")";
}

bool Uminus_Ast::check_ast()
{
    if (!operand->check_ast())
        return false;

    string t = operand->get_data_type();

    if (t != "int" && t != "float") {
        cerr << "Semantic Error: Unary minus applied to non-numeric type '"
             << t << "' at line " << lineno << endl;
        return false;
    }

    node_data_type = t;   // result type same as operand
    return true;
}

Int_Ast::Int_Ast(int v, int line)
    : Constant_Ast(line), value(v)
{
    node_data_type = "int";
}


bool Int_Ast::check_ast() {
    return true; // constants are always semantically valid
}

void Int_Ast::print(std::ostream &out) {
    out << "Int(" << value << ")";
}

Float_Ast::Float_Ast(float v, int line)
    : Constant_Ast(line), value(v)
{
    node_data_type = "float";
}

bool Float_Ast::check_ast() {
    return true;
}

void Float_Ast::print(std::ostream &out) {
    out << "Float(" << value << ")";
}

String_Ast::String_Ast(const std::string &v, int line)
    : Constant_Ast(line), value(v)
{
    node_data_type = "string";
}


bool String_Ast::check_ast() {
    return true;
}

void String_Ast::print(std::ostream &out) {
    out << "String(\"" << value << "\")";
}

Sequence_Ast::Sequence_Ast(std::vector<Ast*> &stmts)
    : stmt_list(stmts) {}

Sequence_Ast::~Sequence_Ast() {
    for (Ast* stmt : stmt_list) {
        delete stmt;
    }
}

bool Sequence_Ast::check_ast() {
    bool ok = true;
    for (Ast* stmt : stmt_list) {
        if (stmt && !stmt->check_ast())
            ok = false;
    }
    return ok;
}

void Sequence_Ast::print(std::ostream &out) {
    out << "{\n";
    for (Ast* stmt : stmt_list) {
        out << "  ";
        if (stmt)
            stmt->print(out);
        out << ";\n";
    }
    out << "}";
}

Ternary_Ast::Ternary_Ast(Ast *c, Ast *t, Ast *f, int line)
    : cond(c), true_expr(t), false_expr(f), lineno(line) {}

Ternary_Ast::~Ternary_Ast() {
    delete cond;
    delete true_expr;
    delete false_expr;
}

bool Ternary_Ast::check_ast() {
    if (!cond->check_ast()) return false;
    if (!true_expr->check_ast()) return false;
    if (!false_expr->check_ast()) return false;

    if (cond->get_data_type() != "bool") {
        cerr << "Ternary condition must be bool\n";
        return false;
    }

    if (true_expr->get_data_type() != false_expr->get_data_type()) {
        cerr << "Ternary branches must have same type\n";
        return false;
    }

    node_data_type = true_expr->get_data_type();
    return true;
}

void Ternary_Ast::print(std::ostream &out) {
    out << "( ";
    cond->print(out);
    out << " ? ";
    true_expr->print(out);
    out << " : ";
    false_expr->print(out);
    out << " )";
}

/* ================= */
/* Logical_Ast       */
/* ================= */

Logical_Ast::Logical_Ast(Ast *l, Ast *r, int oper, int line)
    : lhs(l), rhs(r), op(oper), lineno(line) {}

Logical_Ast::~Logical_Ast() {
    delete lhs;
    delete rhs;
}

bool Logical_Ast::check_ast() {
    if (!lhs->check_ast()) return false;
    if (!rhs->check_ast()) return false;

    if (lhs->get_data_type() != "bool" ||
        rhs->get_data_type() != "bool") {
        cerr << "Logical operands must be bool\n";
        return false;
    }

    node_data_type = "bool";
    return true;
}

void Logical_Ast::print(std::ostream &out) {
    out << "( ";
    lhs->print(out);

    if (op == OP_AND)
        out << " && ";
    else if (op == OP_OR)
        out << " || ";

    rhs->print(out);
    out << " )";
}

/* ================= */
/* Logical_Not_Ast   */
/* ================= */

Logical_Not_Ast::Logical_Not_Ast(Ast *e, int line)
    : expr(e), lineno(line) {}

Logical_Not_Ast::~Logical_Not_Ast() {
    delete expr;
}

bool Logical_Not_Ast::check_ast() {
    return expr ? expr->check_ast() : true;
}

void Logical_Not_Ast::print(std::ostream &out) {
    out << "(! ";
    expr->print(out);
    out << ")";
}

/* ================= */
/* Print_Ast         */
/* ================= */

Print_Ast::Print_Ast(Ast *e, int line)
    : expr(e), lineno(line) {}

Print_Ast::~Print_Ast() {
    delete expr;
}

bool Print_Ast::check_ast() {
    return expr ? expr->check_ast() : true;
}

void Print_Ast::print(std::ostream &out) {
    out << "print ";
    expr->print(out);
}

/* ================= */
/* Read_Ast          */
/* ================= */

Read_Ast::Read_Ast(Ast *v, int line)
    : var(v), lineno(line) {}

Read_Ast::~Read_Ast() {
    delete var;
}

bool Read_Ast::check_ast() {
    if (!var->check_ast()) return false;

    Name_Ast* name = dynamic_cast<Name_Ast*>(var);
    if (!name) {
        cerr << "Read requires variable\n";
        return false;
    }

    return true;
}

void Read_Ast::print(std::ostream &out) {
    out << "read ";
    var->print(out);
}