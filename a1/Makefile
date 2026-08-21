CC = gcc
CFLAGS = -Wall
LEX = flex
YACC = yacc -d

TARGET = sclp

all: $(TARGET)

# yacc generates y.tab.c and y.tab.h
y.tab.c y.tab.h: a1.y
	$(YACC) a1.y

# flex uses y.tab.h
lex.yy.c: a1.l y.tab.h
	$(LEX) a1.l

# compile
$(TARGET): lex.yy.c y.tab.c
	$(CC) $(CFLAGS) lex.yy.c y.tab.c -o $(TARGET) -lfl

clean:
	rm -f lex.yy.c y.tab.c *.toks *.log y.tab.h $(TARGET)
