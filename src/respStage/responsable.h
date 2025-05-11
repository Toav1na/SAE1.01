int charger(char* nomFichier,int tab_num_etu[], int tab_ref[], float tab_note[]);
void affichage(int tab1[], int tab2[], float tab3[], int tlog, int tmax);
int decalerADroite(int tab1[], int tab2[], float tab3[], int tlog, int tmax, int inter);
int insertion(int tab1[],int tab2[],float tab3[], int *tlog,int tmax);
void sauvegarde(int tab1[],int tab2[],float tab3[], int tlog);
int recherche(int tab[],int val, int *trouve, int tlog);
void Supression(int tabEtu[], int tabRef[], float tabNoteF[], int *tlogi);
void decalerAGAuche(int tabEtu[], int tabRef[],float tabNoteF[], int *tlog, int i);

int chargerOffres(char* nomFichier, int tRefs[], int tDepts[], int isPourvu[], int nbCandidats[], int *tlogRefs, int *tlog, int tmaxRefs, int tmax);
int sauvegarderOffres(char* nomFichier, int tRefs[], int tDepts[], int isPourvu[], int nbCandidats[], int tlogRefs, int tlog);
void afficherOffres(int tRefs[], int tDepts[], int isPourvu[], int nbCandidats[], int tlog, int full);
int ajouterOffre(int tRefs[], int tDepts[], int isPourvu[], int nbCandidats[], int *tlogRefs, int *tlog, int tmax, int idOffre, int dept);
int supprimerOffre(int tRefs[], int tDepts[], int isPourvu[], int nbCandidats[], int *tlogRefs, int *tlog, int tmax, int idOffre);
int getIndexDepartement(int tRefs[], int tlog, int refToFind);
int accepterEtudiant(int tRefs[], int isPourvu[], int nbCandidats[], int *tlogRefs, int idOffre, int idEtudiant);
int rechercheOffre(int tRefs[], int offre, int tlog);

void responsableStage(int tEtudiant[],int tab_ref[],float tab_note[], int *tlog, int tRefsOffres[], int tDepts[], int isPourvu[], int nbCandidats[], int *tlogtRefs, int *tlogOffresReste, int tMaxOffres);
