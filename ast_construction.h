#ifndef AST_CONSTRUCTION_H
#define AST_CONSTRUCTION_H

#include "type_ast.h"
#include "gestion_variable.h"

Ast creer_valeur_int(long int val) ;

Ast creer_fonction_base(TypeFonctionBase fun_base , Ast fils_1 , Ast fils_2, Ast fils_3, Ast fils_instr_suiv) ;

Ast creer_registre(long int val);

/*Séquence pour les étiquettes*/
extern sequence seq_etiq;

/*Séquence pour les données*/
extern sequence seq_donnee;

/*Sequence pour les adresses*/
extern sequence seq_adresse;

/*Séquence pour la mémoire*/
extern seq_int memoire;

#endif // AST_CONSTRUCTION_H


