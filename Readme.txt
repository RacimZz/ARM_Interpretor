Binome : Racim ZENATI & Arris ZAIDI

🔧 Compilation avec make

▶️ Exécution
- Analyse lexicale : ./test_lexeme test/mon_fichier.s   # Analyse lexicale  
- Analyse syntaxique : ./test_syntaxe test/mon_fichier.s # Interprétation complète

📁 Structure
analyse_lexicale.c / .h → Analyse lexicale

analyse_syntaxique.c / .h → Analyse syntaxique + AST

ast_construction.c / .h → Création de l’arbre

ast_parcours.c → Interprétation + affichage

gestion_variable.c → Mémoire, étiquettes

test/ → Fichiers .s à tester

type_ast.h → Tout les types utilisé pour l'AST