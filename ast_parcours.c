
#include <stdio.h>
#include <stdlib.h>
#include "couleur.h"
#include "ast_parcours.h"
#include "type_ast.h"
#include "ast_construction.h"


/* Les registres sont stockés dans le tableau tab_reg */
long int tab_reg[16];


//La pile



/*Permet de stocker chaque instruction de l'arbre dans le tableau pour pouvoir faire des branchements*/
Ast tab_arbre[10000];
long int taille_tab_arbre=0;

/*Valeur pour la comparaison avec cmp et tst*/
long int bool_cmp=0;



#include <stdio.h>
#include "type_ast.h"
#include "couleur.h"

// Fonction récursive avec indentation et couleurs
#include <stdio.h>
#include "type_ast.h"
#include "couleur.h"
#include "gestion_variable.h" // pour seq_etiq

#include <stdio.h>
#include "type_ast.h"
#include "couleur.h"
#include "gestion_variable.h" // pour seq_etiq

const char* nom_etiquette(long int val) {
    for (long int i = 0; i < seq_etiq.taille; i++) {
        if (seq_etiq.tab_val[i] == val)
            return seq_etiq.tab_nom[i];
    }
    return NULL;
}

void afficher_arbre_indent(Ast expr, int indent, int is_last) {
    if (!expr) return;

    for (int i = 0; i < indent; i++) printf("│   ");
    printf("%s", is_last ? "└── " : "├── ");

    switch (expr->nature) {
        case FONCTION_BASE:
            jaune_gras();
            printf("[%ld] ", expr->numero_instruction);
            blanc();

            cyan_gras();
            switch (expr->instruction) {
                case N_MOV: printf("MOV"); break;
                case N_ADD: printf("ADD"); break;
                case N_SUB: printf("SUB"); break;
                case N_LDR: printf("LDR"); break;
                case N_STR: printf("STR"); break;
                case N_CMP: printf("CMP"); break;
                case N_BAL: printf("BAL"); break;
                case N_BEQ: printf("BEQ"); break;
                case N_BNE: printf("BNE"); break;
                case N_BLT: printf("BLT"); break;
                case N_BGT: printf("BGT"); break;
                case N_BL:  printf("BL");  break;
                case N_LSL: printf("LSL"); break;
                case N_LSR: printf("LSR"); break;
                case N_AND: printf("AND"); break;
                case N_ORR: printf("ORR"); break;
                case N_TST: printf("TST"); break;
                case N_FIN: printf("FIN"); break;
                case N_AFFRC: printf("AFFRC"); break;
                case N_AFFRN: printf("AFFRN"); break;
                case N_AFFAC: printf("AFFAC"); break;
                default: printf("INSTR_UNKNOWN"); break;
            }
            blanc();
            printf("\n");

            // Cas des instructions de branchement : afficher nom d’étiquette
            if (expr->instruction == N_BAL || expr->instruction == N_BEQ || expr->instruction == N_BNE ||
                expr->instruction == N_BLT || expr->instruction == N_BGT || expr->instruction == N_BL) {
                const char* nom = nom_etiquette(expr->fils1->valeur);
                for (int i = 0; i <= indent; i++) printf("│   ");
                printf("└── "); magenta_gras();
                printf("Étiquette: "); blanc();
                if (nom) printf("%s\n", nom);
                else printf("Inconnue (%ld)\n", expr->fils1->valeur);
            }
            else {
                // Affichage personnalisé pour LDR/STR avec adresse symbolique
                if (expr->instruction == N_LDR || expr->instruction == N_STR) {
                    if (expr->fils1) afficher_arbre_indent(expr->fils1, indent + 1, 0);
                    if (expr->fils2) {
                        const char* nom_adr = nom_variable(&seq_adresse, expr->fils2->valeur);
                        for (int i = 0; i < indent + 1; i++) printf("│   ");
                        printf("└── ");
                        if (nom_adr) {
                            gris();
                            printf("Adresse: %s\n", nom_adr);
                            blanc();
                        } else {
                            afficher_arbre_indent(expr->fils2, indent + 1, 1);
                        }
                    }
                }
                else {
                    if (expr->fils1) afficher_arbre_indent(expr->fils1, indent + 1, 0);
                    if (expr->fils2) afficher_arbre_indent(expr->fils2, indent + 1, 0);
                    if (expr->fils3) afficher_arbre_indent(expr->fils3, indent + 1, 1);
                }
            }

            if (expr->instr_suiv)
                afficher_arbre_indent(expr->instr_suiv, indent, 1);
            break;

        case VALEUR:
            vert();
            printf("Valeur: %ld\n", expr->valeur);
            blanc();
            break;

        case REGISTRE:
            bleu();
            printf("Registre: R%ld\n", expr->registre);
            blanc();
            break;
    }
}

void afficher_arbre(Ast racine) {
    jaune_gras(); printf("Affichage de l'arbre AST"); blanc(); printf("\n\n");
    afficher_arbre_indent(racine, 0, 1);
}



void init_registre()
{
    for(long int i=0;i<=15;i++)
    {
        tab_reg[i]=0;
    }
    tab_reg[13]=taille_memoire; //Initialisation de SP
    tab_reg[11]=taille_memoire; //Initialisation de FP
}
#include <stdio.h>

void afficher_registre()
{
    printf("\n");
    printf("╔══════════════════════════════════════╗\n");
    printf("║         État des Registres           ║\n");
    printf("╠══════════════════════════════════════╣\n");
    
    printf("║ R0  = %5ld     R1  = %5ld          ║\n", tab_reg[0], tab_reg[1]);
    printf("║ R2  = %5ld     R3  = %5ld          ║\n", tab_reg[2], tab_reg[3]);
    
    printf("╠══════════════════════════════════════╣\n");
    printf("║ R4  = %5ld     R5  = %5ld          ║\n", tab_reg[4], tab_reg[5]);
    printf("║ R6  = %5ld     R7  = %5ld          ║\n", tab_reg[6], tab_reg[7]);
    
    printf("╠══════════════════════════════════════╣\n");
    printf("║ R8  = %5ld     R9  = %5ld          ║\n", tab_reg[8], tab_reg[9]);
    printf("║ R10 = %5ld     FP  = %5ld          ║\n", tab_reg[10], tab_reg[11]);
    
    printf("╠══════════════════════════════════════╣\n");
    printf("║ R12 = %5ld     SP  = %5ld          ║\n", tab_reg[12], tab_reg[13]);
    printf("║ LR  = %5ld     PC  = %5ld          ║\n", tab_reg[14], tab_reg[15]);
    
    printf("╚══════════════════════════════════════╝\n");
    printf("\n");
    
}
Ast affectation(Ast expr)
{
    if(expr->fils2->nature==REGISTRE)
    {
        tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre];
    }
    else
    {
        tab_reg[expr->fils1->registre] = expr->fils2->valeur;
    }
    if (expr->fils1->registre==15) //Si on change PC
    {
        return tab_arbre[ tab_reg[15]-2 ]; //  tab_reg[15]-2 = lr
    }
    return expr;
}

void addition(Ast expr)
{

    if(expr->fils3==NULL)
    {
        if(expr->fils2->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] + tab_reg[expr->fils2->registre] ;
        }
        else
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] + expr->fils2->valeur ;
        }
    }
    else
    {
        if(expr->fils3->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] + tab_reg[expr->fils3->registre] ;
        }
           
        else
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] + expr->fils3->valeur ;
        }
    }
}

void soustraction(Ast expr)
{
    if(expr->fils3==NULL)
    {
        if(expr->fils2->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] - tab_reg[expr->fils2->registre] ;
        }
        else
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] - expr->fils2->valeur ;
        }
    }
    else
    {
        if(expr->fils3->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] - tab_reg[expr->fils3->registre] ;
        }
           
        else
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] - expr->fils3->valeur ;
        }
    }
}

 
void charger(Ast expr)
{
    if(expr->fils2==NULL) //On charge une adresse
    {
        tab_reg[expr->fils1->registre]=expr->fils3->valeur;
    }
    else if(expr->fils3==NULL)
    {
        if(tab_reg[expr->fils2->registre]<0 || tab_reg[expr->fils2->registre]>taille_memoire )
        {
            rouge();
            printf("Erreur (ldr) accés à l'adresse de la mémoire %ld ,à l'instruction: %ld \n",tab_reg[expr->fils2->registre],expr->numero_instruction);
            blanc();
            exit(1);
        }
        tab_reg[expr->fils1->registre]=memoire.tab[tab_reg[expr->fils2->registre]];
    }
    else
    {
        if(expr->syntaxe_str_ldr==0) //LDR reg, [reg],int
        {
            if(tab_reg[expr->fils2->registre]<0 || tab_reg[expr->fils2->registre]>taille_memoire )
            {
                rouge();
                printf("Erreur (ldr) accés à l'adresse de la mémoire %ld ,à l'instruction: %ld \n",tab_reg[expr->fils2->registre],expr->numero_instruction);
                blanc();
                exit(1);
            }
            tab_reg[expr->fils1->registre]=memoire.tab[tab_reg[expr->fils2->registre] ];
            tab_reg[expr->fils2->registre] = tab_reg[expr->fils2->registre] + expr->fils3->valeur ;
        }
        else //LDR reg, [reg,int]
        {
            if(tab_reg[expr->fils2->registre] + expr->fils3->valeur <0 || tab_reg[expr->fils2->registre] + expr->fils3->valeur >taille_memoire )
            {
                rouge();
                printf("Erreur (ldr) accés à l'adresse de la mémoire %ld ,à l'instruction: %ld \n",tab_reg[expr->fils2->registre] + expr->fils3->valeur,expr->numero_instruction);
                blanc();
                exit(1);
            }
            tab_reg[expr->fils1->registre]=memoire.tab[tab_reg[expr->fils2->registre] + expr->fils3->valeur ];
        }
    }
}


void stocker(Ast expr)
{
    if(expr->fils3==NULL)
    {
        if(tab_reg[expr->fils2->registre]<0 || tab_reg[expr->fils2->registre]>taille_memoire )
        {
            rouge();
            printf("Erreur (ldr) accés à l'adresse de la mémoire %ld ,à l'instruction: %ld \n",tab_reg[expr->fils2->registre],expr->numero_instruction);
            blanc();
            exit(1);
        }
        memoire.tab[tab_reg[expr->fils2->registre]]=tab_reg[expr->fils1->registre];
    }
    
    else
    {
        if(expr->syntaxe_str_ldr==0) //STR reg, [reg],int
        {
            if(tab_reg[expr->fils2->registre]<0 || tab_reg[expr->fils2->registre]>taille_memoire )
            {
                rouge();
                printf("Erreur (ldr) accés à l'adresse de la mémoire %ld ,à l'instruction: %ld \n",tab_reg[expr->fils2->registre],expr->numero_instruction);
                blanc();
                exit(1);
            }
            memoire.tab[tab_reg[expr->fils2->registre]]=tab_reg[expr->fils1->registre];
            tab_reg[expr->fils2->registre] = tab_reg[expr->fils2->registre] + expr->fils3->valeur ;
        }
        else //STR reg, [reg,int]
        {
            if(tab_reg[expr->fils2->registre] + expr->fils3->valeur<0 || tab_reg[expr->fils2->registre] + expr->fils3->valeur>taille_memoire )
            {
                rouge();
                printf("Erreur (ldr) accés à l'adresse de la mémoire %ld ,à l'instruction: %ld \n",tab_reg[expr->fils2->registre] + expr->fils3->valeur,expr->numero_instruction);
                blanc();
                exit(1);
            }
            memoire.tab[ tab_reg[expr->fils2->registre] + expr->fils3->valeur ] = tab_reg[expr->fils1->registre ];
        }
    }
}

void comparaison(Ast expr)
{
    if(expr->fils2->nature==VALEUR) //cmp registre, valeur_immédiate
    {
        bool_cmp=tab_reg[expr->fils1->registre] - expr->fils2->valeur;
    }
    else
    {
        bool_cmp=tab_reg[expr->fils1->registre] - tab_reg[expr->fils2->registre];
    }
}
 
Ast eval_branchement(Ast expr)
{
    if(expr->instruction==N_BAL)
        return tab_arbre[expr->fils1->valeur-1 ];
    else if(expr->instruction==N_BEQ && bool_cmp==0)
        return tab_arbre[expr->fils1->valeur -1];
    else if(expr->instruction==N_BNE && bool_cmp!=0)
        return tab_arbre[expr->fils1->valeur -1];
    else if(expr->instruction==N_BLT && bool_cmp<0)
        return tab_arbre[expr->fils1->valeur -1];
    else if(expr->instruction==N_BGT && bool_cmp>0)
        return tab_arbre[expr->fils1->valeur -1];
    else if(expr->instruction==N_BL)
    {
       // printf("test \n");
        tab_reg[14]=expr->numero_instruction +1 ;
        return tab_arbre[expr->fils1->valeur-1 ];
    }
    else
        return expr->instr_suiv;
}


void decaler_gauche(Ast expr)
{
	if(expr->fils3==NULL)
    {
        if(expr->fils2->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] << tab_reg[expr->fils2->registre] ;
        }
        else
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] << expr->fils2->valeur ;
        }
    }
    else
    {
        if(expr->fils3->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] << tab_reg[expr->fils3->registre] ;
        }
           
        else
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] << expr->fils3->valeur ;
        }
    }
}

void decaler_droite(Ast expr)
{
	if(expr->fils3==NULL)
    {
        if(expr->fils2->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] >> tab_reg[expr->fils2->registre] ;
        }
        else
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] >> expr->fils2->valeur ;
        }
    }
    else
    {
        if(expr->fils3->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] >> tab_reg[expr->fils3->registre] ;
        }
           
        else
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] >> expr->fils3->valeur ;
        }
    }
}

void et_bit_a_bit(Ast expr)
{
    if(expr->fils3==NULL)
    {
        if(expr->fils2->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] & tab_reg[expr->fils2->registre] ;
        }
        else
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] & expr->fils2->valeur ;
        }
    }
    else
    {
        if(expr->fils3->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] & tab_reg[expr->fils3->registre] ;
        }
           
        else
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] & expr->fils3->valeur ;
        }
    }
}

void ou_bit_a_bit(Ast expr)
{
    if(expr->fils3==NULL)
    {
        if(expr->fils2->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] | tab_reg[expr->fils2->registre] ;
        }
        else
        {
            tab_reg[expr->fils1->registre] =tab_reg[expr->fils1->registre] | expr->fils2->valeur ;
        }
    }
    else
    {
        if(expr->fils3->nature==REGISTRE)
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] | tab_reg[expr->fils3->registre] ;
        }
           
        else
        {
            tab_reg[expr->fils1->registre] = tab_reg[expr->fils2->registre] | expr->fils3->valeur ;
        }
    }
}

void et_bit_a_bit_bool(Ast expr)
{
    if(expr->fils2->nature==REGISTRE)
        {
            bool_cmp =tab_reg[expr->fils1->registre] & tab_reg[expr->fils2->registre] ;
        }
    else
        {
            bool_cmp =tab_reg[expr->fils1->registre] & expr->fils2->valeur ;
        }
}


void affichage_cara(Ast expr)
{
    long int val = tab_reg[expr->fils1->registre];
    if (val >= 0 && val <= 255)
        printf("%c", (char)val);
    else
        printf("[??]");  // Valeur non imprimable
}

void affichage_nombre(Ast expr)
{
    printf("%ld", tab_reg[expr->fils1->registre]);  // Utilise %ld au lieu de %c
}

void affichage_chaine_caractere(Ast expr)
{
    long int i = tab_reg[expr->fils1->registre];
    while (memoire.tab[i] != '\0')
    {
        printf("%c", (char)memoire.tab[i]);
        i++;
    }
}


void init_tab_arbre(Ast expr)
{
    if (expr!=NULL)
    {
        tab_arbre[taille_tab_arbre]=expr;
        taille_tab_arbre++;
        init_tab_arbre(expr->instr_suiv);
    }
}

void evaluation(Ast expr)
{
    while (expr !=NULL)
    {
        switch (expr->instruction)
        {
            case N_MOV:
                expr=affectation(expr);
                expr=expr->instr_suiv;
                break;
                
            case N_ADD:
                addition(expr);
                expr=expr->instr_suiv;
                break;
                        
            case N_SUB:
                soustraction(expr);
                expr=expr->instr_suiv;
                break;
                
            case N_LDR:
                charger(expr);
                expr=expr->instr_suiv;
                break;
                
            case N_STR:
                stocker(expr);
                expr=expr->instr_suiv;
                break;
             
            case N_CMP:
                comparaison(expr);
                expr=expr->instr_suiv;
                break;
                
            case N_LSL:
                decaler_gauche(expr);
                expr=expr->instr_suiv;
                break;
                
            case N_LSR:
                decaler_droite(expr);
                expr=expr->instr_suiv;
                break;
                
            case N_AND:
                et_bit_a_bit(expr);
                expr=expr->instr_suiv;
                break;
                
            case N_ORR:
                ou_bit_a_bit(expr);
                expr=expr->instr_suiv;
                break;
                
            case N_TST:
                et_bit_a_bit_bool(expr);
                expr=expr->instr_suiv;
                break;
                
            case N_AFFRC:
                affichage_cara(expr);
                expr=expr->instr_suiv;
                break;
                
            case N_AFFRN:
                affichage_nombre(expr);
                expr=expr->instr_suiv;
                break;
                
            case N_AFFAC:
                affichage_chaine_caractere(expr);
                expr=expr->instr_suiv;
                break;
            
            case N_BAL:case N_BEQ:case N_BNE:case N_BLT:case N_BGT:case N_BL:
                expr=eval_branchement(expr);
                if (expr==NULL)
                {
                    printf("BUG\n");
                }
                break;
                
            
                
            case N_FIN: //Fin du programme 
                expr=NULL;
                break;
        }
    }
    
    
}


/*
void evaluation(Ast expr)
{
    if (expr!=NULL )
    {
        switch (expr->instruction)
        {
            case N_MOV:
                expr=affectation(expr);
                evaluation(expr->instr_suiv);
                break;
                
            case N_ADD:
                addition(expr);
                evaluation(expr->instr_suiv);
                break;
                        
            case N_SUB:
                soustraction(expr);
                evaluation(expr->instr_suiv);
                break;
                
            case N_LDR:
                charger(expr);
                evaluation(expr->instr_suiv);
                break;
                
            case N_STR:
                stocker(expr);
                evaluation(expr->instr_suiv);
                break;
             
            case N_CMP:
                comparaison(expr);
                evaluation(expr->instr_suiv);
                break;
                
            case N_LSL:
                decaler_gauche(expr);
                evaluation(expr->instr_suiv);
                break;
                
            case N_LSR:
                decaler_droite(expr);
                evaluation(expr->instr_suiv);
                break;
                
            case N_AND:
                et_bit_a_bit(expr);
                evaluation(expr->instr_suiv);
                break;
                
            case N_ORR:
                ou_bit_a_bit(expr);
                evaluation(expr->instr_suiv);
                break;
                
            case N_TST:
                et_bit_a_bit_bool(expr);
                evaluation(expr->instr_suiv);
                break;
                
            case N_AFFRC:
                affichage_cara(expr);
                evaluation(expr->instr_suiv);
                break;
                
            case N_AFFRN:
                affichage_nombre(expr);
                evaluation(expr->instr_suiv);
                break;
                
            case N_AFFAC:
                affichage_chaine_caractere(expr);
                evaluation(expr->instr_suiv);
                break;
            
            case N_BAL:case N_BEQ:case N_BNE:case N_BLT:case N_BGT:case N_BL:
                expr=eval_branchement(expr);
                if (expr==NULL)
                {
                    printf("BUG\n");
                }
                evaluation(expr);
                break;
                
            
                
            case N_FIN: //Fin du programme 
                break;
        }
    }
}
*/
