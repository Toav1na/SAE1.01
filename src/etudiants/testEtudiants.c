/**
 * @file testEtudiants.c
 * @author Toavina Julien
 * @brief Le programme principal pour tester les fonctions de la gestion des étudiants
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



void testLoginEtudiant(void){
    int tEtudiants[15]={0,12,13,15,16,18,19,20,25,27,28,35};
    int tlog =12;
    int tRefs[T_MAX] = {0}, tDepts[T_MAX] = {0};
    int isPourvu[T_MAX] = {0}, nbCandidats[T_MAX] = {0};
    int tlogtRefs = 0, tlogAutresOffres = 0;
    int etudiant = 999;
    chargerOffres("../resp/offres.don", tRefs, tDepts, isPourvu, nbCandidats,  &tlogtRefs, &tlogAutresOffres, T_MAX, T_MAX);
    login(tEtudiants,tlog, etudiant, nbCandidats, tRefs, &tlogtRefs, T_MAX);
}


void testPostuler(void){
    int tRefs[T_MAX] = {0}, tDepts[T_MAX] = {0};
    int isPourvu[T_MAX] = {0}, nbCandidats[T_MAX] = {0};
    int tlogtRefs = 0, tlog = 0;
    int etudiant = 999;
    int code;
    chargerOffres("../respStage/offres.don", tRefs, tDepts, isPourvu, nbCandidats,  &tlogtRefs, &tlog, T_MAX, T_MAX);
    afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    // test 1: fonctionnement normal
    // code = postuler(etudiant, 1061, nbCandidats, tRefs, &tlogtRefs, T_MAX);
    // // afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    // printf("Test 1 - fonctionnement normal: %s (code=%d)\n", code == 0 ? "PASS" : "FAIL", code);

    // test 2: offre non trouvée
    code = postuler(etudiant, 106, nbCandidats, tRefs, &tlogtRefs, T_MAX);
    // afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 2 - offre non conforme: %s (code=%d)\n", code == -2 ? "PASS" : "FAIL", code);

    // test 3: offre a déjà le nombre de candidats max
    code = postuler(etudiant, 5008, nbCandidats, tRefs, &tlogtRefs, T_MAX);
    // afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 3 - offre a déjà le nombre de candidats max: %s (code=%d)\n", code == -3 ? "PASS" : "FAIL", code);

    // test 4: Le candidat a déjà postulé à cette offre
    etudiant = 155;
    code = postuler(etudiant, 4155, nbCandidats, tRefs, &tlogtRefs, T_MAX);
    // afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 4 - Le candidat a déjà postulé à cette offre: %s (code=%d)\n", code == -4 ? "PASS" : "FAIL", code);

    // test 5: Le candidat a déjà postulé à 3 offres
    etudiant = 155;
    code = postuler(etudiant, 6049, nbCandidats, tRefs, &tlogtRefs, T_MAX);
    // afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 5 - Le candidat a déjà postulé à 3 offres: %s (code=%d)\n", code == -5 ? "PASS" : "FAIL", code);  

    // ajouter un test où le tableau devient plein  
}

void testDePostuler(void){
    int tRefs[T_MAX] = {0}, tDepts[T_MAX] = {0};
    int isPourvu[T_MAX] = {0}, nbCandidats[T_MAX] = {0};
    int tlogtRefs = 0, tlog = 0;
    int etudiant = 999;
    int code;
    chargerOffres("../respStage/offres.don", tRefs, tDepts, isPourvu, nbCandidats,  &tlogtRefs, &tlog, T_MAX, T_MAX);

    // test 1: fonctionnement normal
    code = dePostuler(101, 5008, nbCandidats, tRefs, &tlogtRefs, T_MAX);
    afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 1 - fonctionnement normal: %s (code=%d)\n", code == 0 ? "PASS" : "FAIL", code);

    // test 2: offre non trouvée
    code = dePostuler(etudiant, 106, nbCandidats, tRefs, &tlogtRefs, T_MAX);
    // afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 2 - offre non trouvée: %s (code=%d)\n", code == -1 ? "PASS" : "FAIL", code);

    // test 3: Etudiant n'ayant pas postulé à l'offre
    code = dePostuler(etudiant, 5008, nbCandidats, tRefs, &tlogtRefs, T_MAX);
    // afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 3 - Etudiant n'ayant pas postulé à l'offre: %s (code=%d)\n", code == -2 ? "PASS" : "FAIL", code);
}


void debug(void){
    int choix;
    printf("Mode debug\n");
    printf("Que voulez-vous tester?\n"
    "1. tester le login\n"
    "2. postuler en tant qu'étudiant\n"
    "3. Dépostuler en tant qu'étudiant\n");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        testLoginEtudiant();
        break;
    case 2:
        testPostuler();
        break;  
    case 3:
        testDePostuler();
        break;
    default:
        break;
    }

}


int main(void){
    debug();
    return 0;
}