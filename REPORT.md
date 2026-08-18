# SCLP Compiler Project Report

## What this is

This repo documents a compiler-construction project completed as part of IIT Bombay's **cs302 + cs316: Implementation of Programming Languages** (theory and lab) course, built on the **SCLP** framework — "A Language Processor for a **S**mall **C**-like **L**anguage" — designed by Prof. Uday Khedker.

Course page (primary source for this report): https://www.cse.iitb.ac.in/~uday/sclp-web/

**There is no source code in this repo.** The compiler was implemented and run inside the course's VM-based lab environment, and the code was not retained locally afterward. This is a write-up of what the project involved and what was built, not a code archive.

## The SCLP project

SCLP is a from-scratch compiler for a subset of C with some extensions, built incrementally across a term: rather than implementing every compiler phase for the full language up front, the language's feature set and the compiler's phases grow together, assignment by assignment. As the course site puts it, the goal is "a small well-crafted code base for a UG compiler construction class such that it can be enhanced systematically by the students."

### Source language

A subset of C, extended in places, supporting:
- **Data types**: integers, floating-point numbers, booleans, strings
- **Values**: scalars, pointers, multi-dimensional arrays
- **Control flow**: `if`/`if-else`, `while`, `do-while` (no `for`, `switch`, or `goto`)
- **Functions**: with optional parameters and return values
- **Operators**: arithmetic, relational, boolean, and ternary conditional

### Target

Compiled output is **SPIM assembly** (MIPS). SCLP also supports an interpretation mode alongside compilation, so the relationship between compiling and interpreting the same program can be observed directly.

### Compilation pipeline

The compiler builds a sequence of intermediate representations, one per phase:

1. **Scanning** (lexical analysis) → token stream
2. **Parsing** → Abstract Syntax Tree (AST)
3. **Semantic analysis** → type-checked AST + symbol tables
4. **IR generation** → Three Address Code (TAC)
5. **Instruction selection** → Register Transfer Language (RTL)
6. **Assembly emission** → SPIM assembly

### Toolchain

- **Lex/Flex** for the scanner, **Yacc/Bison** for the parser
- Implemented in **C++**, using an object-oriented design — class hierarchies for AST expression/statement nodes, TAC statements/operands, RTL statements/operands, and assembly statements/operands
- Symbol tables (global and local scope), program/procedure objects, register and instruction descriptors, and activation records for function calls
- Reference text: Aho, Lam, Sethi & Ullman, *Compilers: Principles, Techniques, and Tools*

The SCLP driver also exposes CLI flags to stop after a given phase (`--sa-scan`, `--sa-parse`, `--sa-ast`, `--sa-tac`, `--sa-rtl`) and to dump intermediate representations for inspection (`--show-tokens`, `--show-ast`, `--show-tac`, `--show-rtl`, `--show-asm`, and JSON variants of each) — useful both for debugging a given phase in isolation and for resuming from a saved IR (`--read-json-*`) without re-running earlier phases.

## Assignment structure and what was completed

The project is broken into six assignments (A1–A6), each adding both a language feature level and a compiler phase:

| Assignment | Focus | Language level | Key features | Status |
|---|---|---|---|---|
| A1 | Scanner & parser | Level 2 | Arithmetic expressions, variables, constants | ✅ Completed |
| A2 | AST generation | Level 3 | Relational and logical operators | ✅ Completed |
| A3 | TAC production | Level 3 | Three-address code generation | ✅ Completed |
| A4 | RTL generation | Level 4 | Control flow: `if`/`else`, `while`, `do-while` | ✅ Completed |
| A5 | RTL completion | Level 4 | Full RTL representation | ✅ Completed |
| A6 | Assembly output | Level 5 | Function calls, recursion, final SPIM codegen | ⬜ Not reached |

In short: the implemented compiler takes a Level-4 SCLP program (arithmetic, relational/logical/ternary expressions, and full `if`/`while`/`do-while` control flow) through scanning, parsing, AST construction, TAC generation, and all the way to a complete RTL representation. What remains beyond this point, per the course's own structure, is instruction selection tuning and SPIM assembly emission for function calls and recursion (A6, Level 5), and — beyond the assignment sequence entirely — arrays and pointers (Level 6).

## Why no code is here

The implementation ran inside the course-provided VM/lab environment for cs302/cs316, and the working copy wasn't preserved outside of it. This repository exists to record what the project covered and how far it was taken, for reference, rather than to host the compiler's source.
