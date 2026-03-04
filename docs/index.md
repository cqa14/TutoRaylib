# Tuto raylib

## Introduction

Dans la vie courante, il est rare d'interagir avec un programme directement par le terminal. Les interfaces graphiques offrent de nouvelles possibilités d'affichage ainsi qu'une expérience utilisateur plus agréable. Ce document vise à donner un aperçu de [raylib](https://www.raylib.com), une bibliothèque permettant de créer des interfaces graphiques en C++.

> raylib est à l'origine une bibliothèque C, pensée pour programmer des jeux vidéo. Elle a l'avantage d'être relativement simple à utiliser, et d'avoir été portée dans de nombreux langages et sur toutes les plateformes. Son origine en C fait que certains exemples de la documentation doivent être quelque peu adaptés pour être dans un style plus proche du C++.

> Il existe de nombreuses autres bibliothèques permettant de créer des interfaces graphiques, comme [Qt](https://qt.io/), [GLFW](https://www.glfw.org/), [OGRE](https://www.ogre3d.org/), [wxWidgets](https://www.wxwidgets.org/), ou encore [SDL](https://www.libsdl.org/), qui ont chacune leurs avantages et inconvénients, donc il ne faut surtout pas hésiter à regarder s'il y en a une semblant plus adaptée à un projet particulier.

Le document structuré comme suit :

1. Nous verrons un [exemple simple de création d'une fenêtre], avec un texte et une figure en 2D.
2. Nous modulariserons le code afin de séparer le contenu à afficher et la manière de l'afficher, et présenterons du même coup un [exemple de dessin 3D].
3. On complexifiera un peu l'affichage en [ajoutant plusieurs objets], ainsi que la possibilité de déplacer la caméra.
4. Le [quatrième exemple] montrera comment rendre l'affichage interactif, avec la souris et le clavier, ainsi que des boutons.
5. Le [cinquième exemple] montrera comment faire évoluer le dessin en fonction du temps.
6. Finalement, le [dernier exemple] montrera comment afficher un modèle 3D plus complexe.

### Quelques concepts préalables

Quand on utilise une bibliothèque graphique, il faut bien comprendre son comportement :

- il y a celles qui utilisent une approche de dessin séquentielle : on dessine un objet, puis un autre, et ainsi de suite ;
- et il y a celles événementielles, dont raylib : l'idée est d'avoir une boucle infinie qui va attendre des évènements ; cela peut être un clic de souris, une touche de clavier ou même un simple délais d'attente ; lorsque qu'un évènement se produit, on le traite, puis on retourne à la boucle infinie d'attente.

Il faut donc programmer _avant_ cette boucle toutes les fonctions qui vont être associées à des évènements, puis initialiser tout ce qu'il faut (fenêtres de dessin, boutons, variables, ...) avant de lancer la boucle principale.

En général, on structure celle-ci de la manière suivante :

1. gestion des évènements ;
2. évolution du système (évènements liés au temps ; on peut donc le voir comme un cas particulier du 1.) ;
3. dessin de la nouvelle image.

Ce sont ces étapes qui seront détaillées dans la suite de ce document.

[exemple simple de création d'une fenêtre]: exemples/1.md
[exemple de dessin 3D]: exemples/2.md
[ajoutant plusieurs objets]: exemples/3.md
[quatrième exemple]: exemples/4.md
[cinquième exemple]: exemples/5.md
[dernier exemple]: exemples/6.md
