# LISTE_TP2

## Description

Ce projet implémente une structure de données de type liste en C++ avec des fonctionnalités avancées, telles que des itérateurs personnalisés et des opérations sur les éléments de la liste. Le projet inclut également des tests unitaires utilisant GoogleTest pour valider le bon fonctionnement des différentes fonctionnalités.

## Fonctionnalités

- **Gestion des listes** : Ajout, suppression, et modification d'éléments dans une liste.
- **Itérateurs** : Itérateurs personnalisés pour parcourir les éléments de la liste.
- **Recherche** : Fonction pour rechercher un élément dans une séquence.
- **Tests unitaires** : Validation des fonctionnalités à l'aide de GoogleTest.

## Prérequis

- **CMake** : Version 3.20 ou supérieure.
- **Compilateur C++** : Supportant le standard C++23.
- **GoogleTest** : Téléchargé automatiquement via `FetchContent`.

## Installation

1. Clonez le dépôt :
   ```bash
   git clone https://github.com/kiurow590/ESIR1_PROG2_TP2.git
   cd ESIR1_PROG2_TP2
   ```

2. Configurez le projet avec CMake :
   ```bash
   cmake -S . -B cmake-build-debug
   ```

3. Compilez le projet :
   ```bash
   cmake --build cmake-build-debug
   ```

## Utilisation

### Exécuter le programme principal

Pour exécuter le programme principal :
```bash
./cmake-build-debug/LISTE
```

### Exécuter les tests

Pour exécuter les tests unitaires :
```bash
./cmake-build-debug/LISTE_test
```

## Structure du projet

- `Liste.h` : Définition de la classe `Liste` et des itérateurs.
- `main.cpp` : Point d'entrée du programme principal.
- `test/` : Contient les fichiers de tests unitaires.
- `CMakeLists.txt` : Fichier de configuration CMake.

## Dépendances

- **GoogleTest** : Utilisé pour les tests unitaires. Téléchargé automatiquement via `FetchContent`.
