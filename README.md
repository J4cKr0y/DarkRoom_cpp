# DarkRoom_cpp

## Projet
------
Implémentation d'une séquence de jeu d'aventure textuelle en C/C++, dont la logique centrale est entièrement articulée autour des structures de données fondamentales codées avec des pointeurs "à la C". Le projet sert de démonstration fonctionnelle et thématique des listes chaînées, des files, des tas et des listes doublement chaînées.


## C'est quoi ?
------------
DarkRoom_cpp est un jeu de survie textuel par tentatives. Le joueur dispose d'une équipe de trois personnages, chacun doté de statistiques uniques (Force, Intelligence, Rapidité).

L'objectif est de s'échapper d'une pièce sombre contenant une clé cachée et deux portes (une verrouillée et une menacée par des monstres).

Chaque structure de données a un rôle critique :

- **File (Queue)** : Gère la séquence des tentatives des personnages.

- **Liste Chaînée** : Liste les Quêtes à accomplir (Allumer lumière, Trouver clé, Ouvrir porte).

- **Liste Doublement Chaînée** : Simule l'Inventaire du personnage.

- **Tas Max (Max-Heap)** : Gère la priorité d'attaque des monstres en fonction de leur dangerosité.

C'est un projet qui allie la programmation système (gestion manuelle de la mémoire avec malloc/free) et la conception de jeux.


## Technologies Utilisées
-----------------------
- **Langage**: C++(avec un accent sur les pointeurs C pour les structures de données)
- **Build System**: CMake 3.10+
- **Compilateurs**: GCC, Clang
- **Débogage**: GDB/LLDB

![C++](https://img.shields.io/badge/C++-17-blue)
![CMake](https://img.shields.io/badge/CMake-3.10+-green)
![Compiler-GCC](https://img.shields.io/badge/Compiler-GCC-orange)


## Fonctionnalités Clés
---------------------
- **Implémentation Bas Niveau**: Les structures de données sont construites à l'aide de pointeurs C (struct, malloc, free, typedef), évitant les classes C++ pour les nœuds.

- **Logique de Jeu Pilotée par les Stats**: La réussite des quêtes (trouver la clé) dépend de l'Intelligence du personnage, tandis que le combat et la force brute dépendent de la Force et de la Rapidité.

- **Gestion des Tentatives (Queue)**: Les personnages échoués sont remis en fin de file pour une tentative ultérieure, simulant une rotation d'équipe.

- **Priorisation du Combat (Max-Heap)**: Les monstres sont systématiquement attaqués dans l'ordre de leur dangerosité, dicté par l'extraction de la racine du Tas Max.

- **Architecture Modulaire**: Séparation des structures (ex: LinkedList.h) et du moteur de jeu (main.cpp).


## Architecture du Projet
------------------------
```
/DarkRoom_cpp
├── CmakeLists.txt		# Configuration CMake principale
├── main.cpp			# Moteur de jeu principal et logique
├── Personnage.h		# Définition du struct Personnage
├── include/
│   ├── LinkedList.h		# Interface Liste Chaînée (Quêtes)
│   ├── DoublyLinkedList.h	# Interface Liste Doublement Chaînée (Inventaire)
│   ├── MaxHeap.h		# Interface Tas Max (Priorité Monstres)
│   └── Queue.h			# Interface File (Rotation Personnages)
└── src/
    ├── LinkedList.cpp		# Implémentation de la Liste Chaînée
    ├── DoublyLinkedList.cpp	# Implémentation de la Liste Doublement Chaînée
    ├── MaxHeap.cpp		# Implémentation du Tas Max
    └── Queue.cpp			# Implémentation de la File
```

Cette architecture met en évidence la séparation des responsabilités : les structures de données dans include/src fournissent des services génériques, tandis que main.cpp les utilise pour implémenter la logique spécifique au jeu.


## Par quoi commencer ? 
--------------------
Vous devez compiler le projet vous-même.
**Prérequis**
- Un compilateur C++11 (ou plus récent) compatible avec les fonctions C standards (malloc, free).

- CMake 3.10 ou supérieur.

**Compilation et exécution**
1. Cloner le dépôt et organiser les fichiers comme indiqué dans l'architecture ci-dessus.
2. Configuration en mode Release (recommandé pour jouer)
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j4
```
3. Lancer le jeu
```
./build/bin/DarkRoom_cpp
```

## Documentation Complète

Le projet est accompagné d'un rapport sur les structures de données les plus communes séparés en 3 groupes :

- Structures Linéaires
- Structures Arborescentes et Graphiques
- Structures Associatives (Clé-Valeur)

Consulter la documentation complète dans le dossier Rapport/


## Roadmap et Améliorations Prévues
----------------------------------
- [ ] Interface utilisateur plus riche (ASCII art, couleurs).
- [ ] Gestion dynamique des monstres (réapprovisionnement du Tas Max après chaque combat)
- [ ] Intégration d'une structure de Set pour les effets de statut (poison, saignement) appliqués aux monstres.
- [ ] TRefonte de l'inventaire avec des objets plus complexes et des effets sur les statistiques du personnage.

### Contribuer
Les contributions sont les bienvenues, surtout celles qui améliorent la robustesse des pointeurs C et l'efficacité des opérations des structures de données. Pour contribuer :

1. Forkez le projet
2. Créez une branche feature (git checkout -b feature/amelioration-heap)
3. Committez vos changements (git commit -m 'Optimisation de la fonction heapify')
4. Pushez vers la branche (git push origin feature/amelioration-heap)
5. Ouvrez une Pull Request
