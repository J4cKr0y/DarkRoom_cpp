# TP9-Structure de données

## A. Structures Linéaires
Ces structures stockent les données de manière séquentielle, où chaque élément est connecté à l'élément suivant et/ou précédent.
### 1. Tableau (Array)

#### Définition
Une collection d'éléments stockés dans des emplacements mémoire contigus. L'accès aux éléments se fait par un index.
#### Cas d’utilisation pertinent
Stockage de données de taille fixe, accès aléatoire rapide (O(1)) aux éléments, implémentation d'autres structures (tables de hachage, piles, queues).
#### Pseudo algorithme / Exemple
Accéder à l'élément i : ELEMENT = TABLEAU[i]

### 2. Liste chaînée (Linked List)

#### Définition
Une collection d'éléments (nœuds) où chaque nœud contient la donnée et une référence (pointeur) vers le nœud suivant.
#### Cas d’utilisation pertinent
Implémenter des structures comme les piles et les queues, gestion de listes où les insertions/suppressions sont fréquentes (car O(1)).
#### Pseudo algorithme / Exemple
NOUVEAU_NOEUD.suivant = TETE; TETE = NOUVEAU_NOEUD

### 3. Liste doublement chaînée (Double Linked List)

#### Définition
Une liste chaînée où chaque nœud possède deux références : une vers le nœud précédent et une vers le nœud suivant.
#### Cas d’utilisation pertinent
Construction de l'historique d'un navigateur web (pour les boutons "Précédent" et "Suivant"), implémentation du cache LRU (Least Recently Used).
#### Pseudo algorithme / Exemple
X.precedent.suivant = X.suivant; X.suivant.precedent = X.precedent

### 4. Queue

#### Définition
Une structure LIFO (Last-In, First-Out). Le dernier élément inséré est le premier à être retiré.
#### Cas d’utilisation pertinent
Gestion de la mémoire lors de l'appel de fonctions (pile d'appel), mécanismes "Annuler" (Undo) dans les éditeurs, vérification de l'équilibrage des parenthèses.
#### Pseudo algorithme / Exemple
PUSH(élément) (ajouter); POP() (retirer le dernier)

### 5. Queue de priorité (Priority Queue)

#### Définition
Une structure similaire à une Queue mais où chaque élément a une priorité. L'élément avec la plus haute priorité est toujours retiré en premier.
#### Cas d’utilisation pertinent
Planification de tâches critiques dans les systèmes d'exploitation, algorithmes de recherche de chemin (Dijkstra, Prim).
#### Pseudo algorithme / Exemple
INSERER(élément, priorité); EXTRAIRE_MAX() (retirer l'élément de plus haute priorité). Souvent implémentée avec un Tas.

## B. Structures Arborescentes et Graphiques

Ces structures stockent les données de manière non linéaire, représentant des relations hiérarchiques ou des connexions entre des éléments.

### 1. Arbre (Tree)

#### Définition
Une structure de données hiérarchique composée de nœuds connectés par des arêtes, sans cycles.
#### Cas d’utilisation pertinent
Modélisation des systèmes de fichiers (répertoires et sous-répertoires), parsing de code (Abstract Syntax Trees - AST).
#### Pseudo algorithme / Exemple
VISITER(Racine); PARCOURIR(Enfants)

### 2. Arbre Binaire (Binary Tree)

#### Définition
Un type d'arbre où chaque nœud a au maximum deux enfants, appelés enfant gauche et enfant droit.
#### Cas d’utilisation pertinent
Représentation d'expressions mathématiques, base pour les arbres de recherche binaires.
#### Pseudo algorithme / Exemple
NOEUD(Valeur, Enfant_Gauche, Enfant_Droit)

### 3. Arbre Binaire de Recherche (Binary Search Tree - BST)

#### Définition
Un arbre binaire où, pour chaque nœud, toutes les clés de son sous-arbre gauche sont inférieures à sa clé, et toutes les clés de son sous-arbre droit sont supérieures.
#### Cas d’utilisation pertinent
Implémentation de dictionnaires ou de structures de tri dynamiques, permettant une recherche efficace (O(logn) en moyenne).
#### Pseudo algorithme / Exemple
Recherche : SI (Clé < Nœud.Clé) RECHERCHER(Nœud.Gauche) SINON RECHERCHER(Nœud.Droit)

### 4. Arbre Équilibré (Balanced Tree)

#### Définition
Une catégorie de BST (comme AVL, Arbre Rouge-Noir) qui s'auto-ajuste pour garantir que la hauteur reste minimale, assurant des opérations O(logn) dans le pire des cas.
#### Cas d’utilisation pertinent
Implémentation des collections Set et Map dans de nombreux langages pour garantir la performance.
#### Pseudo algorithme / Exemple
Après insertion : SI (Déséquilibré) FAIRE ROTATION_SIMPLE ou ROTATION_DOUBLE

### 5. Tas (Heap)

#### Définition
Un arbre binaire complet qui satisfait la propriété de tas : la clé du nœud parent est toujours supérieure (Max-Heap) ou inférieure (Min-Heap) aux clés de ses enfants.
#### Cas d’utilisation pertinent
Implémentation efficace de la Queue de Priorité, algorithme de tri par tas (Heapsort).
#### Pseudo algorithme / Exemple
Insertion : AJOUTER_FIN; TANT QUE (enfant > parent) ECHANGER

### 6. Arbre de Préfixes (Trie / Prefix Tree)

#### Définition
Un arbre utilisé pour stocker et récupérer des données associatives où les clés sont généralement des chaînes de caractères. Les chemins d'un nœud à l'autre représentent des préfixes.
#### Cas d’utilisation pertinent
Suggestion automatique de mots (autocomplétion), vérification orthographique, recherche de mots dans un dictionnaire.
#### Pseudo algorithme / Exemple
Recherche : Parcourir l'arbre caractère par caractère de la clé, en suivant les arêtes correspondantes.

### 7. Graphe (Graph)

#### Définition
Une collection de nœuds (sommets) et de connexions (arêtes) entre ces nœuds.
#### Cas d’utilisation pertinent
Modélisation de réseaux sociaux, de cartes routières (GPS), de dépendances entre tâches (gestion de projet).
#### Pseudo algorithme / Exemple
Algorithmes : Dijkstra (plus court chemin), BFS/DFS (parcours), Kruskal/Prim (arbre couvrant minimal).

## C. Structures Associatives (Clé-Valeur)
Ces structures stockent les données sous forme de paires clé-valeur, permettant de récupérer une valeur rapidement en utilisant sa clé.
### 1. Table de Hachage / Carte (Hash Table / Map / Dictionary)

#### Définition
Une structure qui utilise une fonction de hachage pour convertir une clé en un index de tableau (appelé bucket ou slot) où la valeur correspondante est stockée.
#### Cas d’utilisation pertinent
Stockage de configuration (clé = nom du paramètre, valeur = valeur), indexation rapide de données, implémentation des Set.
#### Pseudo algorithme / Exemple
Insertion : INDEX = FONCTION_HACHAGE(Clé); TABLE[INDEX] = Valeur

### 2. Set (Ensemble)

#### Définition
Une collection non ordonnée d'éléments uniques. Les doublons ne sont pas autorisés.
#### Cas d’utilisation pertinent
Vérification rapide de l'existence d'un élément (appartenance), suppression de doublons dans une liste, opérations ensemblistes (union, intersection).
#### Pseudo algorithme / Exemple
Appartenance : EST_PRESENT = TABLE_HACHAGE.RECHERCHER(Élément) (très rapide, O(1) en moyenne).


## Conclusion 
L'exploration de ces structures fondamentales, du simple Tableau linéaire au complexe Graphe non linéaire, révèle l'architecture essentielle de tout logiciel performant. 
Chaque structure, qu'il s'agisse de la discipline du Stack (Pile) et de la Queue (File), de l'efficacité hiérarchique des Arbres Binaires de Recherche, ou de la rapidité d'accès des Tables de Hachage, répond à un problème de performance spécifique.
Le choix d'une structure de données appropriée détermine directement la complexité temporelle et spatiale d'un algorithme. 
Dans des domaines allant des systèmes d'exploitation (où les Heaps (Tas) et les Queues de Priorité gèrent les tâches critiques) aux applications web modernes (où les Maps et les Sets optimisent l'accès aux données), ces structures ne sont pas de simples abstractions, mais les piliers invisibles de l'informatique efficace.
 Comprendre leurs forces et leurs faiblesses permet de concevoir des solutions robustes, rapides et évolutives.
