CC = g++
CFLAGS = -std=c++17
LEX = lex
YACC = bison -d

TARGET = sclp

all: $(TARGET)

lex.yy.c: a2.l 
	$(LEX) a2.l

y.tab.c y.tab.h: a2.y
	$(YACC) a2.y

$(TARGET): y.tab.c ast.cc symbol_table.cc lex.yy.c main.cc
	$(CC) $(CFLAGS) y.tab.c ast.cc symbol_table.cc lex.yy.c main.cc -o $(TARGET) -lfl

clean:
	rm -f lex.yy.c y.tab.c *.toks *.log *.ast y.tab.h $(TARGET)