/**
 * @file testresp.c
 * @author Julien
 * @brief Le programme principal pour tester les fonctions de la gestion des responsables de stage
 * @version 0.1
 * @date 2024-11-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include "responsable.h"
#define T_MAX 50

void testChargementOffres(void){
    int tRefs[T_MAX]={0}, tDepts[T_MAX]={0}, isPourvu[T_MAX]={0}, nbCandidats[T_MAX]={0}, tlogtRefs, tlog;
    chargerOffres("offres.don", tRefs, tDepts, isPourvu, nbCandidats,  &tlogtRefs, &tlog, T_MAX, T_MAX);
    printf("tlogRefs: %d\n", tlogtRefs);
    printf("tlog: %d\n", tlog);
    afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 0);
}

void testSauvegardeOffres(void){
    int tRefs[T_MAX]={0}, tDepts[T_MAX]={0}, isPourvu[T_MAX]={0}, nbCandidats[T_MAX]={0}, tlogtRefs, tlog;
    chargerOffres("offres.don", tRefs, tDepts, isPourvu, nbCandidats,  &tlogtRefs, &tlog, T_MAX, T_MAX);
    printf("tlogRefs: %d\n", tlogtRefs);
    printf("tlog: %d\n", tlog);
    afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    ajouterOffre(tRefs, tDepts, isPourvu, nbCandidats, &tlogtRefs, &tlog, T_MAX, 5000, 69);
    sauvegarderOffres("TESTSAVEoffres.exe", tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, tlog);
}

void testAjouterOffre(void) {
    int tRefs[T_MAX] = {0}, tDepts[T_MAX] = {0};
    int isPourvu[T_MAX] = {0}, nbCandidats[T_MAX] = {0};
    int tlogtRefs = 0, tlog = 0;
    chargerOffres("offres.don", tRefs, tDepts, isPourvu, nbCandidats,  &tlogtRefs, &tlog, T_MAX, T_MAX);
    printf("tlogRefs: %d\n", tlogtRefs);
    printf("tlog: %d\n", tlog);
    // ajouts de tests avec string demander au prof si ça pass
    // Test 1: fonctionnement normal
    int code = ajouterOffre(tRefs, tDepts, isPourvu, nbCandidats, 
                           &tlogtRefs, &tlog, T_MAX, 5000, 69);

    printf("tlogRefs: %d\n", tlogtRefs);
    printf("tlog: %d\n", tlog);
    
    printf("Test 1 - fonctionnement normal: %s (code=%d)\n", 
           code == 0 ? "PASS" : "FAIL", code);
    
    // test 1.1, ajout d'une autre offre 
    code = ajouterOffre(tRefs, tDepts, isPourvu, nbCandidats, &tlogtRefs, &tlog, T_MAX, 6000, 70);
    printf("Test 1.1 - fonctionnement normal: %s (code=%d)\n",
    code == 0 ? "PASS" : "FAIL", code);

    afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 0);
    afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);



    // Test 2: offre déjà existante
    code = ajouterOffre(tRefs, tDepts, isPourvu, nbCandidats,
                       &tlogtRefs, &tlog, T_MAX, 5000, 69);
    printf("Test 2 - offre déjà existante: %s (code=%d)\n",
           code == -4 ? "PASS" : "FAIL", code);
    
    // Test 3: Département invalide
    code = ajouterOffre(tRefs, tDepts, isPourvu, nbCandidats,
                       &tlogtRefs, &tlog, T_MAX, 5001, 96);
    printf("Test 3 - Département invalide: %s (code=%d)\n",
           code == -2 ? "PASS" : "FAIL", code);
}

void testSuppressionOffre(void){
    int tRefs[T_MAX] = {0}, tDepts[T_MAX] = {0};
    int isPourvu[T_MAX] = {0}, nbCandidats[T_MAX] = {0};
    int tlogtRefs = 0, tlog = 0;
    int code;
    chargerOffres("offres.don", tRefs, tDepts, isPourvu, nbCandidats,  &tlogtRefs, &tlog, T_MAX, T_MAX);
    printf("tlogRefs: %d\n", tlogtRefs);
    printf("tlog: %d\n", tlog);
    afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    // Test 1: fonctionnement normal avec une offre avec 2 candidats
    code =supprimerOffre(tRefs, tDepts, isPourvu, nbCandidats, &tlogtRefs, &tlog, T_MAX, 5008);
    // printf("tlogRefs: %d\n", tlogtRefs);
    // printf("tlog: %d\n", tlog);
    // afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 1 - fonctionnement normal avec une offre avec 2 candidats: %s (code=%d)\n", code == 0 ? "PASS" : "FAIL", code);

    // Test 2: fonctionnement normal avec une offre promue
    code =supprimerOffre(tRefs, tDepts, isPourvu, nbCandidats, &tlogtRefs, &tlog, T_MAX, 5143);
    // printf("tlogRefs: %d\n", tlogtRefs);
    // printf("tlog: %d\n", tlog);
    // afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 2 - fonctionnement normal avec une offre promue: %s (code=%d)\n", code == 0 ? "PASS" : "FAIL", code);

    // Test 3: offre non trouvée
    code =supprimerOffre(tRefs, tDepts, isPourvu, nbCandidats, &tlogtRefs, &tlog, T_MAX, 5000);
    // printf("tlogRefs: %d\n", tlogtRefs);
    // printf("tlog: %d\n", tlog);
    // afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 3 - offre non trouvée: %s (code=%d)\n", code == -3 ? "PASS" : "FAIL", code);

    // Test 4: offre non conforme
    code =supprimerOffre(tRefs, tDepts, isPourvu, nbCandidats, &tlogtRefs, &tlog, T_MAX, 500);
    // printf("tlogRefs: %d\n", tlogtRefs);
    // printf("tlog: %d\n", tlog);
    // afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 4 - offre non conforme: %s (code=%d)\n", code == -2 ? "PASS" : "FAIL", code);

    //!TODO ajouter test getIndexDepartement renvoie -1
}

void testAccepterEtudiant(void){
    int tRefs[T_MAX]={0}, tDepts[T_MAX]={0}, isPourvu[T_MAX]={0}, nbCandidats[T_MAX]={0}, tlogtRefs, tlog;
    chargerOffres("offres.don", tRefs, tDepts, isPourvu, nbCandidats,  &tlogtRefs, &tlog, T_MAX, T_MAX);
    printf("tlogRefs: %d\n", tlogtRefs);
    printf("tlog: %d\n", tlog);
    int code;
    // Test 1: fonctionnement normal
    code = accepterEtudiant(tRefs, isPourvu, nbCandidats, &tlogtRefs, 5008, 101);
    afficherOffres(tRefs, tDepts, isPourvu, nbCandidats, tlogtRefs, 1);
    printf("Test 1 - fonctionnement normal: %s (code=%d)\n", code == 0 ? "PASS" : "FAIL", code);
    // Test 2: offre non conforme
    code = accepterEtudiant(tRefs, isPourvu, nbCandidats, &tlogtRefs, 50080, 101);
    printf("Test 2 - offre non conforme: %s (code=%d)\n", code == -1 ? "PASS" : "FAIL", code);
    // Test 3: offre non trouvée
    code = accepterEtudiant(tRefs, isPourvu, nbCandidats, &tlogtRefs, 5000, 101);
    printf("Test 3 - offre non trouvée: %s (code=%d)\n", code == -2 ? "PASS" : "FAIL", code);
    // Test 4: offre déjà pourvue
    code = accepterEtudiant(tRefs, isPourvu, nbCandidats, &tlogtRefs, 5143, 101);
    printf("Test 4 - offre déjà pourvue: %s (code=%d)\n", code == -3 ? "PASS" : "FAIL", code);
    // Test 5: étudiant non conforme
    code = accepterEtudiant(tRefs, isPourvu, nbCandidats, &tlogtRefs, 5008, 1010);
    printf("Test 5 - étudiant non conforme: %s (code=%d)\n", code == -4 ? "PASS" : "FAIL", code);
    // Test 6: étudiant pas dans la liste des candidats
    code = accepterEtudiant(tRefs, isPourvu, nbCandidats, &tlogtRefs, 5008, 100);
    printf("Test 6 - étudiant pas dans la liste des candidats: %s (code=%d)\n", code == -5 ? "PASS" : "FAIL", code);
    // Test 7: offre sans candidats
    code = accepterEtudiant(tRefs, isPourvu, nbCandidats, &tlogtRefs, 2548, 101);
    printf("Test 7 - offre sans candidats: %s (code=%d)\n", code == -6 ? "PASS" : "FAIL", code);


}
void testRechercher(void){
    int tRefs[T_MAX]={0}, tDepts[T_MAX]={0}, isPourvu[T_MAX]={0}, nbCandidats[T_MAX]={0}, tlogtRefs, tlog;
    chargerOffres("offres.don", tRefs, tDepts, isPourvu, nbCandidats,  &tlogtRefs, &tlog, T_MAX, T_MAX);
    printf("tlogRefs: %d\n", tlogtRefs);
    printf("tlog: %d\n", tlog);
    int res =rechercheOffre(tRefs,5008,tlogtRefs);
    printf("resultat: %d. Exepected -> 0\n", res);
    res =rechercheOffre(tRefs,5000,tlogtRefs);
    printf("resultat: %d. Exepected -> -1\n", res);
    res =rechercheOffre(tRefs,4155,tlogtRefs);
    printf("resultat: %d. Exepected -> 3\n", res);
}

void debug(void){
    int choix;
    printf("Que souhaitez vous faire?\n"
    "1. Tester le chargement des offres\n"
    "2. tester l'ajout d'une offre\n"
    "3. Ne rien faire\n"
    "4. Tester la fonction recherche\n"
    "5. Tester la suppression d'une offre\n"
    "6. Tester l'acceptation d'un etudiant pour une offre\n"
    "7. Tester la sauvegarde des offres\n"
    );
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        testChargementOffres();
        break;
    case 2:
        testAjouterOffre();
        break;
    case 3:
        break;
    case 4:
        testRechercher();
        break;
    case 5:
        testSuppressionOffre();
        break;
    case 6:
        testAccepterEtudiant();
        break;
    case 7:
        testSauvegardeOffres();
        break;
    default:
        break;
    }
}


int main (void){
    debug();
    return 0;
}