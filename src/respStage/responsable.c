/**
 * @file responsable.c
 * @authors Julien & Toavina
 * @brief Fichier contenant les fonctions pour la gestion des responsables de stage
 * @version 1.0
 * @date 2024-11-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include "responsable.h"
#define T_MAX 50


/**
 * @brief Permet de charger le fichier contenant tout les étudiants
 * 
 * @param nomFichier chemin vers le fichier contenant tout les étudiants
 * @param tab_num_etu Tableau contenant les numéros d'étudiant.
 * @param tab_ref Tableau des références des offres suivies des étudiant
 * @param tab_note Tableau des notes finales des étudiants
 * @return la taille physique de tout les tableaux
 */
int charger(char* nomFichier,int tab_num_etu[], int tab_ref[], float tab_note[])
{
    int i = 0, num_etu, ref_stage;
    float note_finale;
    FILE *f = fopen(nomFichier, "r");
    if (f == NULL)
    {
        perror("Erreur lors de l'ouverture");
    }
    while (fscanf(f, "%d  %d  %f", &num_etu, &ref_stage, &note_finale) == 3)
    {
        tab_num_etu[i] = num_etu;
        tab_ref[i] = ref_stage;
        tab_note[i] = note_finale;
        i++;
    }
    fclose(f);
    return i;
}
/**
 * @brief Affiche les données des étudians contenues dans les tableaux
 * 
 * @param tab1 Tableau contenant les numéros d'étudiant.
 * @param tab2 Tableau des références des offres suivies des étudiant
 * @param tab3 Tableau des notes finales des étudiants
 * @param tlog taille logique des tableaux
 * @param tmax taille physique des tableaux
 */
void affichage(int tab1[], int tab2[], float tab3[], int tlog, int tmax)
{
    printf("N°Etudiant\tRéférence Stage\tNote Finale\n");
    if (tlog > tmax)
    {
        printf("\n ! Erreur, taille insuffisante ! \n");
        return;
    }
    for (int i = 0; i < tlog; i++)
    {
        printf("%d\t\t%d\t\t\t%f\n", tab1[i], tab2[i], tab3[i]);
    }
}
/**
 * @brief Rechercher l'id de l'étudiant
 * 
 * @param tabEtudiant Tableau contenant les numéros d'étudiant
 * @param val id de l'étudiant à rechercher
 * @param trouve variable indiquant si l'étudiant à été trouvé ou non
 * @param tlog taille logique du tableau tabEtudiant
 * @return index de la position de l'étudiant dans le son tableau
 */
int recherche(int tabEtudiant[],int val, int *trouve, int tlog){
    int i=0;
    *trouve = 0;
    while (i < tlog) {
        if (val == tabEtudiant[i]){
            *trouve = 1;
            return i;
        }
        if (val < tabEtudiant[i]){
            *trouve = 0;
            return i;
        }
        i++;
    }
    return i;
}
/**
 * @brief Permet de Décaler d'un cran vers la droite toutes les valeurs dans les tableaux
 * 
 * @param tab1 Tableau contenant les numéros d'étudiant.
 * @param tab2 Tableau des références des offres suivies des étudiant
 * @param tab3 Tableau des notes finales des étudiants
 * @param tlog taille logique des tableaux
 * @param tmax Taille physique des Tableaux
 * @param inter index de la position de l'étudiant dans le son tableau
 * @return nouvelle taille logique des tableaux(tlog + 1)
 */
int decalerADroite(int tab1[], int tab2[], float tab3[], int tlog, int tmax, int inter)
{
    if (tlog + 1 > tmax)
    {
        printf("Erreur, plus assez de place dans la tableau\n");
        return -1;
    }
    for (int i = tlog; inter <= i; i--)
    {
        tab1[i + 1] = tab1[i];
        tab2[i + 1] = tab2[i];
        tab3[i + 1] = tab3[i];
    }

    return tlog + 1;
}
/**
 * @brief Permet d'insérer un nouvel étudiant, sa référence de stage(celui pour lequel il a été accepté) et sa note finale
 * 
 * @param tab1 Tableau contenant les numéros d'étudiant.
 * @param tab2 Tableau des références des offres suivies des étudiant
 * @param tab3 Tableau des notes finales des étudiants
 * @param tlog taille logique des tableaux
 * @param tmax Taille physique des Tableaux
 * @return nouvelle taille logique des tableaux
 */
int insertion(int tab1[], int tab2[], float tab3[], int *tlog, int tmax)
{
    int numetudiant, Refstage;
    float noteF;
    int trouve = 0, indice, newtlog;
    printf("Selectionnez le N° de l'étudiant que vous voulez ajouter: \n");
    scanf("%d", &numetudiant);
    indice = recherche(tab1, numetudiant, &trouve, *tlog);
    while (trouve == 1)
    {
        printf("L'étudiant %d existe déjà ! Réessayez.\n", numetudiant);
        scanf("%d", &numetudiant);
        indice = recherche(tab1, numetudiant, &trouve, *tlog);
    }
    printf("Saisir la Référence Stage: \n");
    scanf("%d", &Refstage);
    printf("Saisir la Note Finale\n");
    scanf("%f", &noteF);
    printf("%d", *tlog);
    newtlog = decalerADroite(tab1, tab2, tab3, *tlog, tmax, indice);
    tab1[indice] = numetudiant;
    tab2[indice] = Refstage;
    tab3[indice] = noteF;
    return newtlog;
}

/**
 * @brief Permet de sauvegarder les données contenues dans les tableaux dans le fichier étudiant.
 * 
 * @param tabEtu Tableau contenant les numéros d'étudiant.
 * @param tabRef Tableau des références des offres suivies des étudiant
 * @param tabNoteF Tableau des notes finales des étudiants
 * @param tlog taille logique des tableaux
 */
void sauvegarde(int tabEtu[],int tabRef[],float tabNoteF[], int tlog){
    int i=0;
    FILE *f = fopen("etudiants/etudiants.don", "w");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier (fichier manquant)");
        return ;
    }  
    for (i=0; i<tlog; i++){
        fprintf(f,"%d\t%d\t%f\n", tabEtu[i], tabRef[i], tabNoteF[i]);
    }
    fclose(f);
    printf("Fichié sauvegardé!\n");
}
/**
 * @brief Permet de Décaler d'un cran vers la gauche toutes les valeurs dans les tableaux
 * 
 * @param tabEtu Tableau contenant les numéros d'étudiant.
 * @param tabRef Tableau des références des offres suivies des étudiant
 * @param tabNoteF Tableau des notes finales des étudiants
 * @param tlog taille logique des tableaux
 * @param i index de la position de l'étudiant dans le son tableau
 */

void decalerAGAuche(int tabEtu[], int tabRef[],float tabNoteF[], int *tlog, int i){
    while (i <= *tlog - 1){
        tabEtu[i] = tabEtu[i + 1];
        tabRef[i] = tabRef[i + 1];
        tabNoteF[i] = tabNoteF[i + 1];
        i++;
    }
    *tlog = *tlog - 1;
}
/**
 * @brief Permet de supprimer un étudiant présent dans les tableaux
 * 
 * @param tabEtu Tableau contenant les numéros d'étudiant.
 * @param tabRef Tableau des références des offres suivies des étudiant
 * @param tabNoteF Tableau des notes finales des étudiants
 * @param tlogi taille logique des tableaux
 */
void Supression(int tabEtu[], int tabRef[], float tabNoteF[], int *tlogi)
{
    int etudiant;
    int trouve, i;
    printf("quel étudiant voulez-vous supprimer ?\n");
    scanf("%d", &etudiant);
    i = recherche(tabEtu, etudiant, &trouve, *tlogi);
    while (trouve == 0)
    {
        printf("Cette matière n'existe pas, réssayez!\n");
        scanf("%d", &etudiant);
        i = recherche(tabEtu, etudiant, &trouve, *tlogi);
    }
    decalerAGAuche(tabEtu, tabRef, tabNoteF, tlogi, i);
}

/**
 * @brief Charge un fichier type offres dans les tableaux appropriés
 *
 * @param nomFichier Le nom du fichier qu'on veut importer (oui c'est théoriquement une chaine de caractère, mais je voulais des dossiers séparés)
 * @param tRefs Tableau des références des offres, suivies des étudiant, pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param tDepts Tableau des départements des offres offres
 * @param isPourvu Tableau disant si l'offre est pourvue
 * @param nbCandidats Tableau contenant le nombre des candidats pour une offre
 * @param tlogRefs taille logique du tableau tRefs
 * @param tlog taille logique des autre tableaux
 * @param tmaxRefs taille physique de tRefs
 * @param tmax taille physique des autres tableaux
 * @return code de retour de la fonction
 */
int chargerOffres(char* nomFichier, int tRefs[], int tDepts[], int isPourvu[], int nbCandidats[], int *tlogRefs, int *tlog, int tmaxRefs, int tmax)
{
    FILE *f = fopen(nomFichier, "r");
    if (f == NULL)
    {
        printf("Erreur fichier lors de l'ouverture\n");
        return -1;
    }
    int i = 0, k = 0;
    fscanf(f, "%d%d", &tRefs[i+k], &tDepts[i]);
    fscanf(f, "%d", &isPourvu[i]);
    fscanf(f, "%d", &nbCandidats[i]);
    int nbCandidatsActu = nbCandidats[i];
    if (nbCandidats > 0)
    {
        for (int j = 0; j < nbCandidatsActu; j++)
        {
            k = k + 1;
            fscanf(f, "%d", &tRefs[i + k]);
        }
    }
    if (isPourvu[i] == 1){
        k = k + 1;
        fscanf(f, "%d", &tRefs[i + k]);
    }
    i=i+1;
    while (!feof(f))
    {
        fscanf(f, "%d%d", &tRefs[i+k], &tDepts[i]);
        fscanf(f, "%d", &isPourvu[i]);
        fscanf(f, "%d", &nbCandidats[i]);
        nbCandidatsActu = nbCandidats[i];
        if (nbCandidats > 0)
        {
            for (int j = 0; j < nbCandidatsActu; j++)
            {
                k = k + 1;
                fscanf(f, "%d", &tRefs[i + k]);
            }
        }
        if (isPourvu[i] == 1){
            k = k + 1;
        fscanf(f, "%d", &tRefs[i + k]);
    }
        i=i+1;
    }
    fclose(f);
    *tlog = i;
    *tlogRefs = i + k;
    return 0;
}
/**
 * @brief Sauvegarde les offres dans un fichier
 * 
 * @param nomFichier Le nom du fichier qu'on veut importer (oui c'est théoriquement une chaine de caractère, mais je voulais des dossiers séparés)
 * @param tRefs Tableau des références des offres, suivies des étudiant, pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param tDepts Tableau des départements des offres offres
 * @param isPourvu Tableau disant si l'offre est pourvue
 * @param nbCandidats Tableau contenant le nombre des candidats pour une offre
 * @param tlog taille logique des tableaux tDept, isPourvu, nbCandidats, il sont les plus petits
 * @return int code de retour de la fonction
 */
int sauvegarderOffres(char* nomFichier, int tRefs[], int tDepts[], int isPourvu[], int nbCandidats[], int tlogRefs, int tlog) {
    FILE *f = fopen(nomFichier, "w");
    int tref = 0;
    
    if (f == NULL) {
        printf("Erreur fichier lors de l'ouverture\n");
        return -1;
    }
    
    for (int i = 0; i < tlog; i++) {
        if (tRefs[i + tref] >= 1000) {
            fprintf(f, "%d\t%d\n", tRefs[i + tref], tDepts[i]);
            fprintf(f, "%d\n", isPourvu[i]);
            fprintf(f, "%d\n", nbCandidats[i]);
            
            if (nbCandidats[i] > 0) {
                for (int j = 0; j < nbCandidats[i]; j++) {
                    fprintf(f, "%d\n", tRefs[i + tref + j + 1]);
                    tref = tref + 1;
                }
            }
            if (isPourvu[i] == 1) {
                fprintf(f, "%d\n", tRefs[i + tref]);
                tref = tref + 1;
            }
        }
    }
    fclose(f);
    return 0;
}


//! TODO refaire la fonction
/**
 * @brief Affiche toutes les offres chargées
 *
 * @param tRefs Tableau des références des offres, suivies des étudiant. Pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param tDepts Tableau des départements des offres offres
 * @param isPourvu Tableau disant si l'offre est pourvue
 * @param nbCandidats Tableau contenant le nombre des candidats pour une offre
 * @param tlog taille logique du tableau tRefs
 * @param full si =0 affichage des offres, sinon affichage des etudiants candidats en plus
 */
void afficherOffres(int tRefs[], int tDepts[], int isPourvu[], int nbCandidats[], int tlog, int full){
    printf("Tag Offre\tDépartement\tisPourvu\tnbCandidats\n");
    if (full ==0){
        for (int i =0; i< tlog; i++){
            if (tRefs[i]>=1000){
                printf("%d\t\t%d\t\t%d\t\t%d\n", tRefs[i], tDepts[i], isPourvu[i], nbCandidats[i]);
            }
        }
    }
    else{
        // j est un compteur pour les étudiants
        int j = 0;
        for (int i =0; i< tlog; i++){
            if (tRefs[i]>=1000){
                printf("%d\t\t%d\t\t%d\t\t%d\n", tRefs[i], tDepts[i-j], isPourvu[i-j], nbCandidats[i-j]);
            }
            else{
                printf("Etudiant postulant pour cette offre");
                printf("%d\t\n", tRefs[i]);
                j = j + 1;
            }
        }
    }
}

/**
 * @brief Ajoute une offre dans le tableau de offres
 *
 * @param tRefs Tableau des références des offres, suivies des étudiant, pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param tDepts Tableau des départements des offres offres
 * @param isPourvu Tableau disant si l'offre est pourvue
 * @param nbCandidats Tableau contenant le nombre des candidats pour une offre
 * @param tlogRefs taille logique du tableau tRefs
 * @param tlog taille logique des autres tableaux
 * @param tmax taille phyisique du tableau tRefs
 * @param idOffre référence de l'offre à ajouter (4chiffres)
 * @param dept département à ajouter
 *
 * @return code de retour de la fonction
 */
int ajouterOffre(int tRefs[], int tDepts[], int isPourvu[], int nbCandidats[], int *tlogRefs, int *tlog, int tmax, int idOffre, int dept)
{
    // check si le tableau est plein
    if ((*tlogRefs + 1) > tmax)
    {
        return -1;
    }
    // check si le département est correct
    if (dept <= 0 || dept > 95)
    {
        return -2;
    }
    // check si l'offre est correcte
    if (!(idOffre >= 1000) && !(idOffre < 10000))
    {
        return -3;
    }
    // check si l'offre est déjà dans le tableau
    int trouve = rechercheOffre(tRefs, idOffre, *tlogRefs);
    if (trouve != -1)
    {
        return -4;
    }
    // ajout
    tRefs[*tlogRefs] = idOffre;
    tDepts[*tlogRefs] = dept;   
    isPourvu[*tlogRefs] = 0;    
    nbCandidats[*tlogRefs] = 0; 
    *tlog = *tlog + 1;
    *tlogRefs = *tlogRefs + 1; 
    return 0;
}
/**
 * @brief Supprime une offre du tableau des offres et les étudiants y postulant
 * 
 * @param tRefs Tableau des références des offres, suivies des étudiant, pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param tDepts Tableau des départements des offres offres
 * @param isPourvu Tableau disant si l'offre est pourvue
 * @param nbCandidats Tableau contenant le nombre des candidats pour une offre
 * @param tlogRefs taille logique du tableau tRefs
 * @param tlog taille logique des autres tableaux
 * @param tmax taille phyisique du tableau tRefs
 * @param idOffre référence de l'offre à ajouter (4chiffres)
 * 
 * @return int (code de retour de la fonction)
 */
int supprimerOffre(int tRefs[], int tDepts[], int isPourvu[], int nbCandidats[], int *tlogRefs, int *tlog, int tmax, int idOffre){
    int nbCandidatsActu = 0, pourvu = 0, clock, indexTrouve= -1;
    // check si le tableau est vide
    if (tlogRefs == 0){
        return -1;
    }
    // check si l'offre est correcte
    if (!(idOffre >= 1000) && !(idOffre < 10000))
    {
        return -2;
    }
    // check si l'offre est dans le tableau
    int trouve = rechercheOffre(tRefs, idOffre, *tlogRefs);
    if (trouve == -1)
    {
        return -3;
    }
    // check si le département est dans le tableau
    indexTrouve = getIndexDepartement(tRefs, *tlogRefs, idOffre);
    if (indexTrouve == -1)
    {
        return -4;
    }
    printf("indexTrouve: %d\n", indexTrouve);
    nbCandidatsActu = nbCandidats[indexTrouve];
    pourvu = isPourvu[indexTrouve];
    printf("nbCandidatsActu: %d\n", nbCandidatsActu);
    printf("pourvu: %d\n", pourvu);
    clock = pourvu + nbCandidatsActu+1;
    printf("clock: %d\n", clock);
    while (clock > 0){
        for (int i = trouve; i < *tlogRefs; i++){
            tRefs[i] = tRefs[i + 1];
        }
        clock = clock - 1;
        *tlogRefs = *tlogRefs - 1; 
        // printf("tlogRefs: %d\n", *tlogRefs);
        // printf("clock: %d\n", clock);
    }
    for (int i = trouve; i < *tlog; i++){
        tDepts[i] = tDepts[i + 1];
        isPourvu[i] = isPourvu[i + 1];
        nbCandidats[i] = nbCandidats[i + 1];
    }
    *tlog = *tlog - 1;
    return 0;
}

/**
 * @brief retourne l'index des départements d'une offre (fonctionne aussi pour isPourvu, nbCandidats)
 * 
 * @param tRefs Tableau des références des offres, suivies des étudiant, pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param tlog taille phyisique du tableau tRefs
 * @param refToFind idOffre à rechercher
 * 
 * @return int -1 si non trouvé, index du département sinon
 */
int getIndexDepartement(int tRefs[], int tlog, int refToFind) {
    int indexDept = 0;
    
    for (int i = 0; i < tlog; i++) {
        if (tRefs[i] >= 1000) {  
            if (tRefs[i] == refToFind) {
                return indexDept;
            }
            indexDept++;
        }
    }
    return -1; 
}
/**
 * @brief Accepte un étudiant pour une offre de stage
 * 
 * @param tRefs Tableau des références des offres, suivies des étudiant, pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param isPourvu Tableau disant si l'offre est pourvue
 * @param nbCandidats Tableau contenant le nombre des candidats pour une offre
 * @param tlogRefs taille logique du tableau tRefs
 * @param idOffre référence de l'offre à ajouter (4chiffres)
 * @param idEtudiant id de l'étudiant à pourvoir (3chiffres)
 * @return int négatif si erreur, 0 si tout est bon
 */

// On vient de voir que la fonction ne modifie pas les listes ETUDIANT GLHF ;(
int accepterEtudiant(int tRefs[], int isPourvu[], int nbCandidats[], int *tlogRefs, int idOffre, int idEtudiant){
    int vrai =0, indexOffre = 0;

    // check si l'offre est correct
    if (idOffre < 1000 || idOffre >= 10000){
        return -1;
    }
    // check si l'offre n'est pas dans le tableau
    int trouve = rechercheOffre(tRefs, idOffre, *tlogRefs);
    if (trouve == -1){
        return -2;
    }
    // check si l'offre est déjà pourvue
    indexOffre = getIndexDepartement(tRefs,*tlogRefs, idOffre);
    if (isPourvu[indexOffre] == 1){
        return -3;
    }
    // check si l'étudiant est correct
    if (idEtudiant < 100 || idEtudiant >= 1000){
        return -4;
    }
    // check si l'étudiant est dans la liste des candidats
    for (int i = trouve+1; i < trouve+nbCandidats[indexOffre]+1; i++){
        if (tRefs[i] == idEtudiant){
            vrai = 1;
        }
    }
    if (vrai == 0){
        return -5;
    }
    // check si l'offre a des candidats
    if ( nbCandidats[indexOffre] == 0){
        return -6;
    }
    // si l'offre a plus d'un candidat
    if (nbCandidats[indexOffre] >1){
        int i = trouve+1;
        while(nbCandidats[indexOffre] > 1){
            if (tRefs[i] != idEtudiant){
                for (int j = i; j < *tlogRefs; j++){
                    tRefs[j] = tRefs[j+1];
                }
                nbCandidats[indexOffre] = nbCandidats[indexOffre] - 1;
                *tlogRefs = *tlogRefs - 1;
            }
            else{
                i++;
            }
        }
    }
    // plus de candidats donc pourvu donc nbCandidats[indexOffre] = 0
    nbCandidats[indexOffre] = nbCandidats[indexOffre] - 1;
    isPourvu[indexOffre] = 1;
    
    return 0;
}


/**
 * @brief Recherche une offre ou un étudiant et retourne
 * l'index où il apparait ou -1 si non trouve
 *
 * @param tRefs Tableau des références des offres, suivies des étudiant, pour avoir le nombre d'offres, utiliser `lenOffres`
 * @param idOffre valeur à recharcher dans le tableau
 * @param tlog taille logique du tableau tRefs
 * 
 * @return int
 */
int rechercheOffre(int tRefs[], int offre, int tlog)
{
    for (int i = 0; i < tlog; i++)
    {
        if (offre == tRefs[i])
        {
            return i;
        }
    }
    return -1;
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
 */
void responsableStage(int tEtudiant[],int tab_ref[],float tab_note[], int *tlog, int tRefsOffres[], int tDepts[], int isPourvu[], int nbCandidats[], int *tlogtRefs, int *tlogOffresReste, int tMaxOffres){
    int choix, idOffre, idEtudiant, dept, retour;
    int stop =0;
    // affichage(tEtudiant,tab_ref,tab_note,tlog,T_MAX);
    while (1){   
        printf("Que souhaitez vous faire?\n"
        "1. Ajouter un étudiant\n"
        "2. Supprimer un étudiant\n"
        "3. accepter un étudiant pour une offre\n"
        "4. ajouter une offre\n"
        "5. supprimer une offre\n"
        "6. Voir les offres\n"
        "7. Ne rien faire\n");

        scanf("%d", &choix);
        switch (choix)
        {
            case 1:
                *tlog=insertion(tEtudiant,tab_ref,tab_note,tlog,T_MAX);
                // affichage(tEtudiant,tab_ref,tab_note,*tlog,T_MAX);
                // sauvegarde(tEtudiant,tab_ref,tab_note,*tlog);
                break;
            
            case 2: 
                Supression(tEtudiant, tab_ref, tab_note, tlog);
                affichage(tEtudiant,tab_ref,tab_note,*tlog,T_MAX);
                break;
            case 3:
                
                printf("Saisir l'offre pour laquelle vous voulez accepter un étudiant\n");
                scanf("%d", &idOffre);
                printf("Saisir l'étudiant que vous voulez accepter\n");
                scanf("%d", &idEtudiant);
                retour = accepterEtudiant(tRefsOffres, isPourvu, nbCandidats, tlogtRefs, idOffre, idEtudiant);
                if (retour == 0){
                    printf("Etudiant accepté\n");
                }
                else if (retour == -1){
                    printf("Offre non conforme\n");
                }
                else if (retour == -2){
                    printf("Offre non trouvée\n");
                }
                else if (retour == -3){
                    printf("Offre déjà pourvue\n");
                }
                else if (retour == -4){
                    printf("Etudiant non conforme\n");
                }
                else if (retour == -5){
                    printf("Etudiant non trouvé\n");
                }
                else if (retour == -6){
                    printf("Offre sans candidats\n");
                }
                afficherOffres(tRefsOffres, tDepts, isPourvu, nbCandidats, *tlogtRefs, 1);
                break;
            case 4:
                printf("Saisir l'offre à ajouter\n");
                scanf("%d", &idOffre);
                printf("Saisir le département de l'offre\n");
                scanf("%d", &dept);
                retour = ajouterOffre(tRefsOffres, tDepts, isPourvu, nbCandidats, tlogtRefs, tlogOffresReste, tMaxOffres, idOffre, dept);
                if (retour == 0){
                    printf("Offre ajoutée\n");
                }
                else if (retour == -1){
                    printf("Plus de place dans le tableau\n");
                }
                else if (retour == -2){
                    printf("Département non conforme\n");
                }
                else if (retour == -3){
                    printf("Offre non conforme\n");
                }
                else if (retour == -4){
                    printf("Offre déjà existante\n");
                }
                afficherOffres(tRefsOffres, tDepts, isPourvu, nbCandidats, *tlogtRefs, 0);
                break;
            case 5:
                printf("Saisir l'offre à supprimer\n");
                scanf("%d", &idOffre);
                retour = supprimerOffre(tRefsOffres, tDepts, isPourvu, nbCandidats, tlogtRefs, tlogOffresReste, tMaxOffres, idOffre);
                if (retour == 0){
                    printf("Offre supprimée\n");
                }
                else if (retour == -1){
                    printf("Tableau vide\n");
                }
                else if (retour == -2){
                    printf("Offre non conforme\n");
                }
                else if (retour == -3){
                    printf("Offre non trouvée\n");
                }
                else if (retour == -4){
                    printf("Département non trouvé\n");
                }
                afficherOffres(tRefsOffres, tDepts, isPourvu, nbCandidats, *tlogtRefs, 0);
                break;
            case 6 : 
                afficherOffres(tRefsOffres, tDepts, isPourvu, nbCandidats, *tlogtRefs, 0);
                break;
            case 7:
                break;
                stop = 1;
            default:
                break;
        }
        if (stop == 1){
            break;
        }
    }
}
