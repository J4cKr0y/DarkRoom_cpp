cmake_minimum_required(VERSION 3.10)
project(GameDataStructures C CXX)

# Inclure les dossiers pour les headers
include_directories(include .) # Assure que Personnage.h et CharacterCreation.h sont trouvés

# Définir la cible et les sources
add_executable(
    game_app
    main.cpp
    src/LinkedList.cpp
    src/DoublyLinkedList.cpp
    src/MaxHeap.cpp
    src/Queue.cpp
    src/CharacterCreation.cpp 
)

# Configuration de base pour C++11 (pour std::cout, etc.)
target_compile_features(game_app PRIVATE cxx_std_11)
