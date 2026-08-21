CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

LEX  = flex
YACC = bison

TARGET = sclp
OBJS   = parser.tab.o lex.yy.o main.o symtab.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y
parser.tab.o: parser.tab.c ast.hh symtab.hh types.hh tac.hh rtl.hh
	$(CXX) $(CXXFLAGS) -c parser.tab.c
lex.yy.c: scanner.l parser.tab.h
	$(LEX) scanner.l

lex.yy.o: lex.yy.c
	$(CXX) $(CXXFLAGS) -c lex.yy.c

symtab.o: symtab.cc symtab.hh types.hh
	$(CXX) $(CXXFLAGS) -c symtab.cc
main.o: main.cpp ast.hh symtab.hh types.hh tac.hh rtl.hh
	$(CXX)	 $(CXXFLAGS) -c main.cpp



clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parser.tab.c parser.tab.h *.toks *.ast *.tac *.rtl
