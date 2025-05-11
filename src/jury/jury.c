/**
 * @file jury.c
 * @author Toavina
 * @brief Fichier contenant les fonctions pour les jurys 
 * @version 1.0
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include "jury.h"
#include "../respStage/responsable.h"
#define T_MAX 50


/**
 * @brief Menu permetant au jury de choisir une action
 * 
 * @param tab_num_etu Tableau contenant les numéros d'étudiant.
 * @param tab_ref Tableau des références des offres suivies des étudiant
 * @param tab_note Tableau des notes finales des étudiants
 * @param tlog taille logique des fichiers
 */
void jury(int tab_num_etu[],int tab_ref[],float tab_note[], int tlog) {
    int choix,stop=0;
    while (1){ 
        printf("\n--- Menu Jury ---\n");
        printf("1. Noter un stage\n");
        printf("2. Afficher les notes par ordre décroissant\n");
        printf("3. Retour au menu principal\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                affichage(tab_num_etu,tab_ref,tab_note,tlog,T_MAX);
                noter_stages(tab_num_etu,tab_ref,tab_note,tlog);
                // sauvegarde(tab_num_etu,tab_ref,tab_note,tlog);
                break;
            case 2:
                afficher_notes_decroissantes(tab_num_etu,tab_ref,tab_note);
                break;
            case 3:
                printf("Retour au menu principal...\n");
                stop =1;
                break;
            default:
                printf("Option non valide, veuillez réessayer.\n");
        }
        if (stop==1){
            break;
        }
    }
}
/**
 * @brief Fonction permettant au jury d'entrer + calculer la moyenne des trois notes
 * 
 * @param tabetu Tableau contenant les numéros d'étudiant.
 * @param tab_note Tableau des notes finales des étudiants
 * @param tlog taille logique des fichiers
 * @return la note_finale (moyenne des trois notes)
 */
float noter_stages(int tabetu[],int tab_ref[],float tab_note[],int tlog){
    int num, index= 0, trouve=0;
    float note_entreprise, note_rapport, note_soutenance, note_finale;
    printf("Entrez le numéro d'étudiant à noter : ");
    scanf("%d", &num);
    index=recherche(tabetu,num,&trouve,tlog);
    if (trouve == 0) {
        printf("Étudiant non trouvé\n");
        return 0;
    }
    if (tab_ref[index]== -1){
        printf("Stage non atribué\n");
        return 0;
    }
    // Entrée des notes
    printf("Entrez la note d'entreprise (coeff 2) : ");
    scanf("%f", &note_entreprise);
    printf("Entrez la note de rapport (coeff 1) : ");
    scanf("%f", &note_rapport);
    printf("Entrez la note de soutenance (coeff 1) : ");
    scanf("%f", &note_soutenance);

    // Calcul de la note finale
    note_finale = (note_entreprise * 2 + note_rapport + note_soutenance) / 4;
    tab_note[index] = note_finale;
    printf("Note finale pour l'étudiant %d : %.2f\n", tabetu[index], note_finale);
    return note_finale;
}
/**
 * @brief Permet d'afficher les notes des étudiants(qui ont une note différente de -1) dans l'ordre décroissant
 * 
 * @param tab_num_etu Tableau contenant les numéros d'étudiant.
 * @param tab_ref Tableau des références des offres suivies des étudiant
 * @param tab_note Tableau des notes finales des étudiants
 */
void afficher_notes_decroissantes(int tab_num_etu[], int tab_ref[], float tab_note[]) {
    int tlog = charger("etudiants/etudiants.don", tab_num_etu, tab_ref, tab_note);
    int i,j;
    // Tri par sélection des trois tableaux en même temps
    for (i = 0; i < tlog ; i++) {
        for (j = i + 1; j < tlog; j++) {
            if (tab_note[i] < tab_note[j]) {
                // Réorganisation des notes
                int temp_note = tab_note[i];
                tab_note[i] = tab_note[j];
                tab_note[j] = temp_note;
                // Réorganisation des numéros d'étudiants
                int temp_num = tab_num_etu[i];
                tab_num_etu[i] = tab_num_etu[j];
                tab_num_etu[j] = temp_num;
                // Réorganisation des références
                int temp_ref = tab_ref[i];
                tab_ref[i] = tab_ref[j];
                tab_ref[j] = temp_ref;
            }
        }
    }
    printf("\n--- Notes des étudiants par ordre décroissant ---\n");
    for (i = 0; i < tlog; i++) {
        // N'afficher que les étudiants ayant une note différente de -1
        if (tab_note[i] != -1) {
            printf("Étudiant %d - Référence de stage %d - Note Finale : %.2f\n",
                   tab_num_etu[i], tab_ref[i], tab_note[i]);
        }
    }
}