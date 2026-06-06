# SAE2.1 — Visualisation météo en C++

## Présentation

Ce projet est une application graphique en C++ qui lit un fichier de données météo (`data.csv`) et affiche des graphiques interactifs de températures.

L'interface utilise la bibliothèque `LibGraph2` pour dessiner des boutons, gérer les événements clavier et souris, et afficher des graphiques personnalisés.

## Fonctionnalités

- Lecture et parsing d'un fichier CSV contenant des relevés météo.
- Affichage d'un graphique général de toutes les données disponibles.
- Affichage d'un graphique filtré par année.
- Affichage d'un graphique filtré par mois.
- Mode sombre / mode clair.
- Navigation par touches fléchées pour avancer ou reculer dans la sélection.
- Aide intégrée affichée via `F1` ou le bouton « Raccourcis ».
- Suppression du graphique actuellement affiché.

## Structure du projet

- `main.cpp` : point d'entrée de l'application, initialisation de l'interface et boucle d'événements.
- `CParsing.cpp` / `CParsing.h` : lecture et traitement des données CSV.
- `CApp.cpp` / `CApp.h` : gestion des données météo et des calculs de graphique.
- `CAffichage.cpp` / `CAffichage.h` : rendu des éléments graphiques et interaction utilisateur.
- `CBouton.cpp` / `CBouton.h` : définition des boutons interactifs.
- `CDate.cpp` / `CDate.h` : représentation des dates du relevé.
- `CReleveMeteo.cpp` / `CReleveMeteo.h` : structure des relevés météo.
- `data.csv` : jeu de données météo utilisé par l'application.

## Utilisation

1. Ouvrir la solution `SAE2.1.slnx` avec Visual Studio.
2. S'assurer que `LibGraph2` est accessible via le dossier `inc/` et les bibliothèques de `lib/`.
3. Construire le projet en mode `Debug` ou `Release`.
4. Lancer l'application.
5. Utiliser les boutons ou les raccourcis clavier pour afficher les graphiques.

## Raccourcis clavier

- `G` : affichage du graphique général.
- `A` : affichage du graphique par année.
- `M` : affichage du graphique par mois.
- `E` : effacer le graphique en cours.
- `S` : activer le mode sombre.
- `C` : activer le mode clair.
- `←` / `→` : avancer ou reculer dans la date ou le mois.
- `F1` : afficher l'aide.

## Notes

- Le fichier `data.csv` doit rester dans le même dossier que l'exécutable pour être correctement chargé.
- Les dates sont lues au format `AAAAMM` et les températures sont attendues en deuxième colonne.

---

Merci d'avoir regardé ce projet ! Amusez-vous bien avec la visualisation des données météo.
