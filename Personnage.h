#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#define MAX_HP 10

typedef struct {
    int id;
    char nom[30];
    int force;        // Pour le combat et défoncer la porte
    int intelligence; // Pour trouver la clé sans lumière
    int rapidite;     // Pour éviter les monstres et la durée du combat
    int hp;
} Personnage;

Personnage* creerPersonnage(int f, int i, int r, int id, const char* nom);
void afficherStats(Personnage* p);

#endif
