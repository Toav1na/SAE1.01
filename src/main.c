/**
 * @file main.c
 * @author Toavina
 * @brief fichier principal du programme
 * @version 0.1
 * @date 2024-11-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include "main.h"
#include "respStage/responsable.h"
#include "etudiants/etudiants.h"
#include "jury/jury.h"
#define T_MAX 50

/**
 * @brief Permet à un étudiant de s'authentifier
 * 
 * @param tEtudiant Tableau contenant les numéros d'étudiant.
 * @param tlog sagit de la taille logique du tableau
 * @param etudiant représente l'identifiant de l'étudiant
 * @return renvoi un entier (1 si l'étudiant est trouvé, 0 s'il ne l'est pas)
 */
int Authentification(int tEtudiant[],int tlog, int *etudiant){
    int id, trouve=0;
    printf("quel est votre identifiant étudiant?\n");
    scanf("%d", &id);
    recherche(tEtudiant, id,&trouve,tlog);
    if (trouve==1){
        *etudiant=id;
    }
    return trouve;
}

/**
 * @brief Permet au responsable de stage de choisir ce qu'il veut faire
 * 
 * @param tEtudiant Tableau contenant les numéros d'étudiant.
 * @param tab_ref Tableau des références des offres suivies des étudiant
 * @param tab_note Tableau des notes finales des étudiants
 * @param tlog sagit de la taille logique du tableau (la meme pour chaque tableau etudiant)
 * @param tRefsOffres Tableau des références des offres de stages
 * @param tDepts Tableau des départements des offres offres
 * @param isPourvu Tableau disant si l'offre est pourvue
 * @param nbCandidats Tableau contenant le nombre des candidats pour une offre
 * @param tlogtRefs taille logique du tableau tRefs
 * @param tlogOffresReste taille logique du tableau tRefs
 * @param tMaxOffres taille physique de tRefsOffres
 * @return code de retour de la fonction
 */
int identification (int tEtudiant[],int tab_ref[],float tab_note[], int tlog, int tRefsOffres[], int tDepts[], int isPourvu[], int nbCandidats[], int tlogtRefs, int tlogOffresReste, int tMaxOffres){
    int c, trouve, etudiant;
    printf("Qui êtes-vous ?:\n\n1. étudiant\n2. Responsable Stage\n3. Membre du Jury\n4. Personne (Quitter)\n");
    scanf("%d",&c);
    switch(c){

        case 1:
            trouve=Authentification(tEtudiant,tlog, &etudiant);
            if (trouve == 0){
                printf("Numéro de Candiat introuvable§\n");
                break;
            } else {
                actionsEtudiant(etudiant, tEtudiant, tab_ref, tab_note, &tlog, tRefsOffres, tDepts, isPourvu, nbCandidats, &tlogtRefs, &tlogOffresReste, tMaxOffres);
            }
            break;
        case 2:
            printf("vous etes responsable de stage\n");
            responsableStage(tEtudiant, tab_ref, tab_note, &tlog,  tRefsOffres,  tDepts,  isPourvu, nbCandidats, &tlogtRefs, &tlogOffresReste, tMaxOffres);
            break;
        case 3:
            printf("\nVous etes un membre du jury\n");
            jury(tEtudiant,tab_ref,tab_note,tlog);
            break;
        case 4:
            printf("Fermeture imminente");
    }
    return 0;
}


int main (void){
    // variables pour les étudiants
    int tab_num_etu[T_MAX], tab_ref[T_MAX];
    float tab_note[T_MAX];

    // variables pour les offres
    int tRefsOffres[T_MAX] = {0}, tDepts[T_MAX] = {0};
    int isPourvu[T_MAX] = {0}, nbCandidats[T_MAX] = {0};
    int tlogtRefs = 0, tlogOffresReste = 0;
    int tMaxOffres = T_MAX;

    int tlog=charger("etudiants/etudiants.don" , tab_num_etu,tab_ref,tab_note);
    //!todo: pb avec tmax
    chargerOffres("respStage/offres.don", tRefsOffres, tDepts, isPourvu, nbCandidats, &tlogtRefs, &tlogOffresReste, tMaxOffres, T_MAX);
    identification(tab_num_etu,tab_ref,tab_note,tlog, tRefsOffres, tDepts, isPourvu, nbCandidats, tlogtRefs, tlogOffresReste, tMaxOffres);

    // save les fichiers
    sauvegarde(tab_num_etu,tab_ref,tab_note,tlog);
    sauvegarderOffres("respStage/offres.don", tRefsOffres, tDepts, isPourvu, nbCandidats, tlogtRefs, tlogOffresReste);
    return 0;
}
