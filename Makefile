# Compiler and flags
CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Wfatal-errors -fdiagnostics-color=auto -g

# Executables
EXECUTABLES = test_lexeme test_syntaxe

# Object files
OBJS_COMMON = analyse_lexicale.o lecture_caracteres.o couleur.o
OBJS_SYNTAXE = analyse_syntaxique.o ast_construction.o ast_parcours.o gestion_variable.o

# Rules
all: $(EXECUTABLES)

# Compilation des .o
analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h couleur.h
	$(CC) $(CFLAGS) -c $<

analyse_syntaxique.o: analyse_syntaxique.c analyse_syntaxique.h analyse_lexicale.h couleur.h type_ast.h ast_construction.h ast_parcours.h
	$(CC) $(CFLAGS) -c $<

lecture_caracteres.o: lecture_caracteres.c lecture_caracteres.h
	$(CC) $(CFLAGS) -c $<

couleur.o: couleur.c couleur.h
	$(CC) $(CFLAGS) -c $<

ast_construction.o: ast_construction.c type_ast.h gestion_variable.h ast_construction.h
	$(CC) $(CFLAGS) -c $<

ast_parcours.o: ast_parcours.c ast_parcours.h couleur.h type_ast.h ast_construction.h
	$(CC) $(CFLAGS) -c $<

gestion_variable.o: gestion_variable.c gestion_variable.h
	$(CC) $(CFLAGS) -c $<

test_lexeme.o: test_lexeme.c analyse_lexicale.h
	$(CC) $(CFLAGS) -c $<

test_syntaxe.o: test_syntaxe.c analyse_lexicale.h analyse_syntaxique.h
	$(CC) $(CFLAGS) -c $<

# Executables

test_lexeme: test_lexeme.o $(OBJS_COMMON)
	$(CC) $(CFLAGS) -o $@ $^

test_syntaxe: test_syntaxe.o $(OBJS_COMMON) $(OBJS_SYNTAXE)
	$(CC) $(CFLAGS) -o $@ $^

# Clean
clean:
	rm -f *.o $(EXECUTABLES)
