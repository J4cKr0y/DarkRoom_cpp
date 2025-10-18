#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>

// Inclusion des structures de données (en supposant qu'elles sont déjà compilées)
#include "LinkedList.h"      // Liste chaînée pour les Quêtes
#include "DoublyLinkedList.h" // Liste doublement chaînée pour l'Inventaire
#include "MaxHeap.h"         // Tas Max pour la Priorité des Monstres
#include "Queue.h"           // File pour la Sélection des Personnages
#include "CharacterCreation.h"

using namespace std;

// --- 1. NOUVELLE STRUCTURE : PERSONNAGE ---

#define MAX_HP 10


Personnage* creerPersonnage(int f, int i, int r, int id, const char* nom) {
    Personnage* p = (Personnage*)malloc(sizeof(Personnage));
    if (p == NULL) { cerr << "Erreur malloc Personnage." << endl; exit(1); }
    p->id = id;
    strncpy(p->nom, nom, 30);
    p->force = f;
    p->intelligence = i;
    p->rapidite = r;
    p->hp = MAX_HP;
    return p;
}

void afficherStats(Personnage* p) {
    cout << "\n-------------------------------------" << endl;
    cout << "  PERSONNAGE ACTUEL : " << p->nom << " (ID: " << p->id << ")" << endl;
    cout << "  Force: " << p->force << " | Intelligence: " << p->intelligence << " | Rapidité: " << p->rapidite << endl;
    cout << "  HP: " << p->hp << endl;
    cout << "-------------------------------------" << endl;
}

// Tableau global pour retrouver les personnages par ID
Personnage* PersonnagePool[4] = {NULL}; 
Personnage* getPersonnageById(int id) {
    if (id >= 1 && id <= 3) return PersonnagePool[id];
    return NULL;
}

// --- 2. FONCTIONS DE LOGIQUE DU JEU ---

// Prototypes
void initialiserJeu(Node** quetes, DNode** inventaire, Queue* filePersos, Personnage* pool[]);
void executerCombat(Personnage* perso, MaxHeap* tasMonstres);
void jouerPartie();

/**
 * @brief Tente de combattre et défoncer la porte.
 * @return 1 si victoire, 0 si défaite.
 */
int executerCombatEtPorte(Personnage* perso, MaxHeap* tasMonstres) {
    cout << "\n🛡️ **COMBAT IMMINENT !** Les monstres attaquent !" << endl;
    
    // Simuler le combat en utilisant le Tas Max pour cibler le plus dangereux
    cout << "  Priorisation de la cible par Tas Max..." << endl;
    executerCombat(perso, tasMonstres);

    if (perso->hp <= 0) {
        cout << "\n💀 **DÉFAITE** : " << perso->nom << " a été submergé par les monstres." << endl;
        return 0;
    }

    cout << "\n⚔️ **VICTOIRE** : " << perso->nom << " a vaincu les monstres !" << endl;
    
    // Tenter de défoncer la porte (Test de Force)
    int seuilForce = 18;
    if (perso->force >= seuilForce) {
        cout << "💪 La porte est verrouillée, mais " << perso->nom << " a une Force de " << perso->force << " (Seuil: " << seuilForce << ")." << endl;
        cout << "🚪 **VICTOIRE** : La porte est défoncée !" << endl;
        return 1;
    } else {
        cout << "🔨 La porte est verrouillée, " << perso->nom << " n'a pas assez de Force (" << perso->force << " < " << seuilForce << ") pour la défoncer." << endl;
        cout << "💀 **DÉFAITE** : Le personnage est bloqué et épuisé." << endl;
        return 0;
    }
}


/**
 * @brief Simule le combat en utilisant le MaxHeap.
 */
void executerCombat(Personnage* perso, MaxHeap* tasMonstres) {
    int seuilForce = 15;
    int toursMax = 1; // Un seul coup par défaut
    
    if (perso->force > seuilForce) {
        // Assez fort, gagne en un coup (tourMax reste 1)
        cout << "  [Test Force] Force suffisante (" << perso->force << "). Victoire rapide assurée." << endl;
    } else {
        // Pas assez fort
        int seuilRapidite = 15;
        if (perso->rapidite > seuilRapidite) {
            toursMax = 3; // L'esquive permet de durer
            cout << "  [Test Rapidité] Force insuffisante, mais la Rapidité (" << perso->rapidite << ") permet 3 tours d'esquive." << endl;
        } else {
            // Pas fort et pas rapide
            perso->hp = 0; // Défaite immédiate
            cout << "  [Test Rapidité] Trop faible et trop lent. Massacre immédiat." << endl;
            return;
        }
    }

    int degatsTotal = 0;
    for (int tour = 1; tour <= toursMax; ++tour) {
        if (tasMonstres->size == 0) break;

        int monstreHP = extractMax(tasMonstres); // Attaque le plus dangereux
        cout << "  Tour " << tour << " : Attaque contre Monstre HP(" << monstreHP << "). Victoire du round!" << endl;
        
        // Simuler les dégâts reçus si le combat dure
        if (toursMax > 1) {
            int degats = rand() % 3 + 1; 
            perso->hp -= degats;
            degatsTotal += degats;
            cout << "    *Contre-attaque* : -" << degats << " HP. Reste HP: " << perso->hp << endl;
        }
        
        if (perso->hp <= 0) break;
    }

    if (perso->hp > 0 && tasMonstres->size == 0) {
        cout << "  Tous les monstres vaincus en " << toursMax << " tours. Dégâts subis: " << degatsTotal << "." << endl;
    }
}


/**
 * @brief Simule le déroulement complet du jeu.
 */
void jouerPartie() {
    // Initialisation
    Node* quetes = NULL;
    DNode* inventaire = NULL;
    Queue* filePersos = createQueue();
    MaxHeap* tasMonstres = createMaxHeap(5);

    initialiserJeu(&quetes, &inventaire, filePersos, PersonnagePool);

    // Ajout des monstres initiaux (HP/Dangerosité)
    insertElement(tasMonstres, 50); // Boss
    insertElement(tasMonstres, 30); // Élite
    insertElement(tasMonstres, 10); // Standard

    int maxTries = 3;
    int tentatives = 0;
    int jeuTermine = 0;

    while (filePersos->front != NULL && tentatives < maxTries && !jeuTermine) {
        tentatives++;
        int idActuel = dequeue(filePersos);
        Personnage* perso = getPersonnageById(idActuel);
        
        cout << "\n=======================================================" << endl;
        cout << "  TENTATIVE #" << tentatives << " avec le personnage : " << perso->nom << endl;
        cout << "=======================================================" << endl;
        afficherStats(perso);

        // --- DÉBUT DE LA LOGIQUE DE LA PIÈCE SANS LUMIÈRE ---
        int clefTrouvee = 0;
        int lumiereAllumee = 0;
        int monstreDechaine = 0;
        
        // Les quêtes à faire sont : 1 (Lumière), 2 (Chercher Clé), 3 (Ouvrir Porte)
        cout << "\n❓ **CHOIX** : La pièce est noire. Que faites-vous ?" << endl;
        
        // Simulation des choix
        int choix;
        cout << "  1. Allumer l'interrupteur (Quête 1)" << endl;
        cout << "  2. Chercher la clef dans le noir (Quête 2)" << endl;
        cout << "  3. Tenter d'ouvrir la porte (verrouillée)" << endl;
        cout << "  Votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1: // Allumer l'interrupteur
                deleteElement(&quetes, 1); // Quête 1 terminée
                lumiereAllumee = 1;
                cout << "\n L'interrupteur est actionné. La lumière s'allume. (Quête 1 OK)" << endl;
                break;

            case 2: // Chercher la clef dans le noir
                cout << "\n Vous cherchez la clé sans lumière..." << endl;
                if (perso->intelligence >= 15) { // Test d'Intelligence
                    clefTrouvee = 1;
                    deleteElement(&quetes, 2); // Quête 2 terminée
                    addElementD(&inventaire, 777); // Clé ajoutée à l'inventaire
                    cout << "  [Test INTEL OK] : La clé est trouvée ! (Quête 2 OK)" << endl;
                } else {
                    cout << "  [Test INTEL ÉCHEC] : Vous ne trouvez rien dans le noir ! (Intel: " << perso->intelligence << "/15)" << endl;
                    monstreDechaine = 1; // Les monstres sont attirés par le bruit de la recherche
                }
                break;

            case 3: // Tenter d'ouvrir la porte
                cout << "\n La porte est verrouillée. Il faut la clé." << endl;
                monstreDechaine = 1; // Perte de temps = Monstres arrivent
                break;
                
            default:
                cout << "\n❌ Choix invalide. Le temps s'écoule..." << endl;
                monstreDechaine = 1;
                break;
        }

        // --- GESTION DU RISQUE ET DE LA SUITE ---
        if (monstreDechaine) {
            // Le personnage a perdu du temps ou a fait du bruit
            int resultat = executerCombatEtPorte(perso, tasMonstres);
            if (resultat == 1) jeuTermine = 1;
        } else if (lumiereAllumee) {
            // Lumière OK, étape suivante : chercher la clé
            cout << "\n Il faut maintenant trouver la clé." << endl;
            if (perso->intelligence >= 10) { 
                clefTrouvee = 1;
                deleteElement(&quetes, 2);
                addElementD(&inventaire, 777);
                cout << "  [Test INTEL OK] : La clé est trouvée sous la lumière ! (Quête 2 OK)" << endl;
            } else {
                cout << "  [Test INTEL ÉCHEC] : Même avec la lumière, il ne trouve rien. (Intel: " << perso->intelligence << "/10). Le temps presse !" << endl;
                int resultat = executerCombatEtPorte(perso, tasMonstres);
                if (resultat == 1) jeuTermine = 1;
            }
        }
        
        if (clefTrouvee && !jeuTermine) {
            // Tentative d'ouvrir la porte avec la clé
            if (searchElementD(inventaire, 777)) {
                deleteElementD(&inventaire, 777); // Clé utilisée (supprimée de l'inventaire)
                deleteElement(&quetes, 3);       // Quête 3 terminée
                cout << "\n Clé trouvée dans l'inventaire (Liste Doublement Chaînée). Porte déverrouillée!" << endl;
                cout << "**VICTOIRE** : Le personnage s'échappe par la porte verrouillée !" << endl;
                jeuTermine = 1;
            }
        }


        // --- FIN DE TENTATIVE ---
        if (!jeuTermine) {
            cout << "\n🚫 **ÉCHEC DE LA TENTATIVE** : Le personnage est mis au repos." << endl;
            // Réinitialiser les HP si on le remet dans la file
            perso->hp = MAX_HP; 
            // Le personnage échoué est remis dans la file (Queue)
            enqueue(filePersos, perso->id); 
            // Réinitialiser les structures pour le prochain essai (sauf la Queue)
            freeList(&quetes);
            freeListD(&inventaire);
            quetes = NULL; inventaire = NULL;
            initialiserJeu(&quetes, &inventaire, NULL, NULL); // Réinitialiser quêtes et inventaire
        }
    }

    // --- NETTOYAGE FINAL ---
    if (!jeuTermine) {
        cout << "\n=======================================================" << endl;
        cout << "  FIN DE PARTIE : TOUS LES PERSONNAGES ONT ÉCHOUÉ." << endl;
        cout << "=======================================================" << endl;
    }
    
    freeList(&quetes);
    freeListD(&inventaire);
    freeQueue(filePersos);
    freeHeap(tasMonstres);
    for(int i = 1; i <= 3; ++i) free(PersonnagePool[i]);
}

/**
 * @brief Initialise les structures pour chaque nouvelle partie.
 */
void initialiserJeu(Node** quetes, DNode** inventaire, Queue* filePersos, Personnage* pool[]) {
    // 1. Initialiser les quêtes (Liste Chaînée)
    // Ordre logique : 1-Lumière, 2-Clé, 3-Porte
    addElement(quetes, 3); 
    addElement(quetes, 2); 
    addElement(quetes, 1);
    
    // 2. Initialiser l'inventaire (Liste Doublement Chaînée)
    addElementD(inventaire, 100); // Torche
    addElementD(inventaire, 50);  // Potion de soin
    addElementD(inventaire, 20);  // Corde

    // 3. Initialiser les Personnages si c'est le début du jeu
    if (filePersos != NULL) {
        initializeCharacterPool(pool, filePersos);
    }
}


// --- MAIN ---
int main() {
    srand(time(NULL)); // Initialisation du générateur aléatoire
    cout << "-----------------------------------------------" << endl;
    cout << "  JEU DE SURVIE DANS LA PIÈCE NOIRE" << endl;
    cout << "  (Démonstration de Structures de Données)" << endl;
    cout << "-----------------------------------------------" << endl;
    
    // Assurez-vous d'avoir compilé les .cpp et inclus les .h
    jouerPartie();
    
    return 0;
}
