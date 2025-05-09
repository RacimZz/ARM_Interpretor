# 💻 Mini-Projet Interpréteur Assembleur (INF404)

[![Build](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/votre-repo)
[![Langage](https://img.shields.io/badge/langage-C-blue)](https://github.com/votre-repo)
[![License](https://img.shields.io/badge/license-MIT-lightgrey)](LICENSE)

> Un mini-interpréteur écrit en C permettant d’analyser, interpréter et exécuter un langage assembleur simplifié.

---

## 🧠 Fonctionnalités

- Analyse lexicale & syntaxique d'un fichier `.s`
- Construction et affichage d’un arbre abstrait (AST)
- Gestion de la mémoire, registres et étiquettes
- Instructions supportées : `MOV`, `LDR`, `STR`, `CMP`, `BEQ`, `ADD`, `SUB`, `AFFRC`, `AFFRN`, `AFFAC`, `BAL`, `BL`, etc.
- Segments `.data` et `.text` interprétés
- Affichage formaté des registres, mémoire, chaînes et instructions

---

## 🛠️ Compilation

```bash
make
````

---

## ▶️ Exécution

```bash
./test_lexeme test/nom_fichier.s     # Affiche les lexèmes
./test_syntaxe test/nom_fichier.s    # Analyse syntaxique + exécution
```

---

## 📂 Exemple

```s
.data
msg: .ascii "Hello, World!\n"

.text
ldr r0, msg
affac r0
fin:
```

---

## 📁 Arborescence du projet

```
├── analyse_lexicale.c
├── analyse_syntaxique.c
├── ast_construction.c
├── ast_parcours.c
├── gestion_variable.c
├── test_syntaxe.c
├── test_lexeme.c
├── Makefile
└── test/
    └── exemple.s
```

---

## 📜 License

Ce projet est sous licence MIT.

