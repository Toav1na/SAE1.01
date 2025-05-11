int rechercheEtu(int tab[], int val, int tlog, int *trouve);

void login(int tEdudiants[], int tlog, int etudiant, int nbCandidats[], int tRefs[], int *tlogRefs, int tmaxRefs);

int postuler(int etudiant,int idOffre, int nbCandidats[], int tRefs[], int *tlogRefs, int tmaxRefs);
int dePostuler(int etudiant,int idOffre, int nbCandidats[], int tRefs[], int *tlogRefs, int tmaxRefs);
int saisiePostuler (int etudiant, int nbCandidats[], int tRefs[], int *tlogRefs, int tmaxRefs);
int saisieDePostuler (int etudiant, int nbCandidats[], int tRefs[], int *tlogRefs, int tmaxRefs);

void actionsEtudiant(int etudiant, int tEtudiant[],int tab_ref[],float tab_note[], int *tlog, int tRefsOffres[], int tDepts[], int isPourvu[], int nbCandidats[], int *tlogtRefs, int *tlogOffresReste, int tMaxOffres);