#include "../include/CharacterCreation.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

// Définition de la fonction de création du personnage
void createCustomCharacter(Personnage* pool[], int id) {
    char nom[30];
    int force, intelligence, rapidite;
    
    cout << "\n--- Création du Personnage #" << id << " ---" << endl;
    cout << "Entrez le nom : ";
    cin.ignore(); // Vider le buffer
    cin.getline(nom, 30);

    // Collecte des statistiques (avec validation simple)
    auto getStat = [](const char* statName) -> int {
        int stat;
        do {
            cout << "Entrez " << statName << " (entre 1 et 20) : ";
            cin >> stat;
        } while (stat < 1 || stat > 20 || cin.fail());
        return stat;
    };

    force = getStat("Force");
    intelligence = getStat("Intelligence");
    rapidite = getStat("Rapidité");

    // Crée et stocke le personnage dans le pool
    pool[id] = creerPersonnage(force, intelligence, rapidite, id, nom);
    cout << "✅ Personnage " << nom << " créé !" << endl;
}

// Fonction principale pour initialiser les personnages (custom ou par défaut)
void initializeCharacterPool(Personnage* pool[], Queue* filePersos) {
    int choix = 0;

    cout << "\n==============================================" << endl;
    cout << "  MODULE DE CRÉATION DE PERSONNAGES" << endl;
    cout << "==============================================" << endl;
    cout << "Voulez-vous créer vos propres personnages (1) ou utiliser l'équipe par défaut (2) ? ";
    cin >> choix;

    bool custom = (choix == 1);
    
    // Boucle de création pour 3 personnages
    for (int i = 1; i <= 3; ++i) {
        // Libère la mémoire s'il y avait un ancien personnage (pour la sécurité)
        if (pool[i] != NULL) free(pool[i]);

        if (custom) {
            // Création personnalisée
            createCustomCharacter(pool, i);
        } else {
            // Création par défaut (le plan de secours)
            if (i == 1) pool[i] = creerPersonnage(18, 8, 12, 1, "Gronk (Fort)");
            if (i == 2) pool[i] = creerPersonnage(10, 15, 10, 2, "Zelia (Intelligente)");
            if (i == 3) pool[i] = creerPersonnage(8, 8, 22, 3, "Kylian (Rapide)");
            cout << "✅ Personnage par défaut #" << i << " (" << pool[i]->nom << ") créé." << endl;
        }

        // Ajouter l'ID du personnage à la File d'attente
        enqueue(filePersos, pool[i]->id);
    }
}
