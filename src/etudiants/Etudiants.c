/**
 * @file Etudiants.c
 * @author Toavina Julien
 * @brief Fichier contenant les fonctions pour la gestion des étudiants
 * @version 0.1
 * @date 2024-11-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "etudiants.h"
#include "../respStage/responsable.h"
#define T_MAX 50


//login
// void login(int tEdudiants[], int tlog, int etudiant, int nbCandidats[], int tRefs[], int *tlogRefs, int tmaxRefs){
//     int id, trouve;
//     printf("quel est votre identifiant étudiant?\n");
//     scanf("%d", &id);
//     recherche(tEdudiants, id, &trouve, tlog);
//     if (trouve==1){
//         actionsEtudiant( etudiant, nbCandidats, tRefs, tlogRefs, tmaxRefs);
//     }
//     else{
//         printf("Cet étudiant (%d) n'a pas l'air d'exister, réssayez\n", id);
//     }
// }

//postuler stage
/**
 * @brief Permet à un étudiant de postuler à une offre de stage
 * 
 * @param etudiant int représentant l'identifiant de l'étudiant
 * @param idOffre référence de l'offre où l'étudiant veut postuler (4chiffres)
 * @param nbCandidats Tableau contenant le nombre des candidats pour une offre
 * @param tRefs Tableau des références des offres, suivies des étudiant, pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param tlogRefs taille logique du tableau tRefs
 * @param tmaxRefs taille physique des autres tableaux
 * 
 * @return int 
 */
int postuler(int etudiant,int idOffre, int nbCandidats[], int tRefs[], int *tlogRefs, int tmaxRefs){
    //On a déjà contrôlé la saisie de l'offre et de l'étudiant dans login et saisiePostuler respectivement
    // afficherOffres(tRefs, tRefs, tRefs, nbCandidats, *tlogRefs, 1);
    int trouve;
    // check si le tableau est plein
    if (*tlogRefs >= tmaxRefs){
        // printf("Le tableau est plein, impossible d'ajouter une offre\n");
        return -1;
    }
    // check si l'offre existe pas
    trouve = rechercheOffre(tRefs, idOffre, *tlogRefs);
    if (trouve == -1){
        // printf("Aucune offre ne correspond à votre recherche\n");
        return -2;
    }
    // check si l'offre a le nombre de candidats max
    if (nbCandidats[getIndexDepartement(tRefs, *tlogRefs, idOffre)] ==3){
        // printf("Cette offre est pleine\n");
        return -3;
    }
    // check si l'étudiant a déjà postulé
    
    int nbCandidatsActu = nbCandidats[getIndexDepartement(tRefs, *tlogRefs, idOffre)];
    for (int i = trouve + 1; i < trouve + 1 + nbCandidatsActu; i++){
        if (tRefs[i] == etudiant){
            // printf("Vous avez déjà postulé à cette offre\n");
            return -4;
        }
    }
    // check si l'étudiant a postulé à 3 offres
    int nbOffres = 0;
    for (int i = 0; i < *tlogRefs; i++){
        if (tRefs[i] == etudiant){
            nbOffres++;
        }
    }
    if (nbOffres == 3){
        // printf("Vous avez déjà postulé à 3 offres, veuillez supprimer une de vos postulations pour postuler à cette offre\n");
        return -5;
    }

    // ajout de l'étudiant
    for (int i = *tlogRefs; i > trouve + 1; i--){
        tRefs[i] = tRefs[i-1];
    }
    tRefs[trouve + 1] = etudiant;
    nbCandidats[getIndexDepartement(tRefs, *tlogRefs, idOffre)]++;

    *tlogRefs = *tlogRefs + 1;
    return 0;
}

/**
 * @brief Demmande à l'étudiant de saisir l'offre à laquelle il veut postuler
 * 
 * @param etudiant int représentant l'identifiant de l'étudiant
 * @param nbCandidats Tableau contenant le nombre des candidats pour une offre
 * @param tRefs Tableau des références des offres, suivies des étudiant, pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param tlogRefs taille logique du tableau tRefs
 * @param tmaxRefs taille physique des autres tableaux
 */
int saisiePostuler (int etudiant, int nbCandidats[], int tRefs[], int *tlogRefs, int tmaxRefs){
    int idOffre, trouve, codeRetour;
    printf("Quelle est la référence de l'offre à laquelle vous voulez postuler?\n");
    scanf("%d", &idOffre);
    trouve = rechercheOffre(tRefs, idOffre, *tlogRefs);
    if (trouve == -1){
        printf("Aucune offre ne correspond à votre recherche\n");
        return 0;
    }
    else{
        codeRetour = postuler(etudiant, idOffre, nbCandidats, tRefs, tlogRefs, tmaxRefs);
    }
    return codeRetour;
}


/** 
 * @brief Permet à un étudiant de se retirer d'une offre de stage
 * 
 * @param etudiant int représentant l'identifiant de l'étudiant
 * @param idOffre référence de l'offre où l'étudiant veut postuler (4chiffres)
 * @param nbCandidats Tableau contenant le nombre des candidats pour une offre
 * @param tRefs Tableau des références des offres, suivies des étudiant, pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param tlogRefs taille logique du tableau tRefs
 * @param tmaxRefs taille physique des autres tableaux
 * @return int 
 */

//!TODO enlever tmaxRefs car non utilisé
int dePostuler(int etudiant, int idOffre, int nbCandidats[], int tRefs[], int *tlogRefs, int tmaxRefs){
    //On a déjà contrôlé la saisie de l'offre et de l'étudiant dans login et saisiePostuler respectivement
    int trouve;
    // check si l'offre existe pas
    trouve = rechercheOffre(tRefs, idOffre, *tlogRefs);
    if (trouve == -1){
        return -1;
    }
    // check si l'étudiant a postulé
    for (int i = trouve+1; i < trouve+nbCandidats[getIndexDepartement(tRefs, *tlogRefs, idOffre)]; i++){
        if (tRefs[i] == etudiant){
            // suppression de l'étudiant
            for (int j = i; j < *tlogRefs; j++){
                tRefs[j] = tRefs[j+1];
            }
            nbCandidats[getIndexDepartement(tRefs, *tlogRefs, idOffre)] --;
            *tlogRefs = *tlogRefs - 1;
            return 0;
        }
    }
    // l'étudiant n'a pas postulé
    return -2;
}

/**
 * @brief Demmande à l'étudiant de saisir l'offre à laquelle il veut se retirer
 * 
 * @param etudiant int représentant l'identifiant de l'étudiant
 * @param nbCandidats Tableau contenant le nombre des candidats pour une offre
 * @param tRefs Tableau des références des offres, suivies des étudiant, pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param tlogRefs taille logique du tableau tRefs
 * @param tmaxRefs taille physique des autres tableaux
 */
int saisieDePostuler (int etudiant, int nbCandidats[], int tRefs[], int *tlogRefs, int tmaxRefs){
    int idOffre, trouve, codeRetour;
    printf("Quelle est la référence de l'offre à laquelle vous voulez vous retirer?\n");
    scanf("%d", &idOffre);
    trouve = rechercheOffre(tRefs, idOffre, *tlogRefs);
    if (trouve == -1){
        printf("Aucune offre ne correspond à votre recherche\n");
        return 0;
    }
    else{
        codeRetour = dePostuler(etudiant, idOffre, nbCandidats, tRefs, tlogRefs, tmaxRefs);
    }
    return codeRetour;
}


// actions choisir
void actionsEtudiant(int etudiant, int tEtudiant[],int tab_ref[],float tab_note[], int *tlog, int tRefsOffres[], int tDepts[], int isPourvu[], int nbCandidats[], int *tlogtRefs, int *tlogOffresReste, int tMaxOffres){
    int stop;
    while (1)
    {    
        int choix;
        printf("Menu des choix Etudiant:\n");
        printf("1. postuler dans une formation\n");
        printf("2. Retirer sa candidature pour un stage\n");
        printf("3. Afficher les offres de stage\n");
        printf("4. Revenir au menu principal (choix par défaut)\n\n");
        printf("Tapez votre choix\n");
        scanf("%d", &choix);
        switch (choix){
            case 1:
                saisiePostuler(etudiant, nbCandidats, tRefsOffres, tlogtRefs, tMaxOffres);
                break;
            case 2:
                saisieDePostuler(etudiant, nbCandidats, tRefsOffres, tlogtRefs, tMaxOffres);
                break;
            case 3:
                afficherOffres(tRefsOffres, tDepts, isPourvu, nbCandidats, *tlogtRefs, 1);
                break;
            case 4:
                stop=1;
                break;
            default:
                stop=1;
                break;
        }
        if (stop==1){
            break;
        }
    }
}

//recherche étudiant
int rechercheEtu(int tab[], int val, int tlog, int *trouve){
    int i;
    *trouve=0;
    for ( i =0; i<=tlog; i++){
        if (val==tab[i]){
            *trouve=1;
            return i;
        }
        else if (val > tab[i]){
            return i;
        }
    }
    return i;
}
