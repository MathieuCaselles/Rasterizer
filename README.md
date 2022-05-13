# Rasterizer

Le but de ce projet de Mastère 1 Game Programming est de rendre une scène 3D comme le tout premier jeu en 3D "Wolfenstein" en SFML.

## Rappel des étapes
1. Implémenter drawVerticalLine()
2. Implémenter drawRect()
3. Le Raycaster proprement dit : Implémenter la méthode RasterizeScene() avec de simple couleurs de mur.
4. Quels sont les performances (FPS) obtenu ? Est-ce suffisant ? Comment les améliorer ?
5. Appliquer une texture sur les murs.
  
  
  
## Quels sont les performances (FPS) obtenu ? Est-ce suffisant ? Comment les améliorer ?  
  
### 1- Analyse des performances obtenu
  
Vous pouvez trouver à la racine de ce dépôt un fichier MainV1.cpp (Ce fichier n'est pas visible depuis Visual Studio).  
Il s'agit de ma première version fonctionnelle du Raycaster avant d'entamer la question sur les performances obtenues pour pouvoir mieux comparé ce que j'ai fait avant puis après.  
  
Pour mesurer les performances, j'ai regardé quelles fonctions prenaient plus ou moins de temps à l'aide de la fonction `GetTickCount64` en procédant comme cela :

```cpp
    auto start = GetTickCount64();

    FunctionToBeTested();

    auto end = GetTickCount64();
    auto delta = (end - start) / 1000.0f;
    printf("Time FunctionToBeTested : %f s\n", delta);
```
Les performances mesurés ci-dessous ont été mesuré en mode Debug et non Release.  
  
J'ai d'abord regardé le temps que prenait une boucle de jeu. Le temps d'une boucle oscille entre 250ms et 266ms ce qui est catastrophique.  
C'est tout simplement injouable de jouer à un jeu avec 4fps seulement.  

J'ai ensuite mesuré le temps que prenait la fonction `DrawRect` et `RasterizeScene`.  
`DrawRect` se fait entre 156ms et 172ms.  
`RasterizeScene` se fait entre 78ms et 94ms. 
Je trouve ce résultat très étonnant car je pensais que tout le plus gros problème de l'optimisation était mon algorithme de recherche de mur qui est très loin d'être bien optimisé mais au final le plus gros du problème vient du parcours des pixels pour les changer de couleur.  
En effet, j'ai essayé de me coller contre un mur pour obliger la fonction `RasterizeScene` à set tous les pixels de l'écran et les performances de cette fonction sont devenu identiques à `DrawRect` en oscillant aussi antre 156ms et 172ms.  
  
Enfin j'ai mesuré `GetFirstAreaFound` que je pensais être la fonction la plus lourde dans `RasterizeScene`.  
Le résultat était entre 60ms et 80ms pour afficher tout l'écran. Et plus je me rapprochais et plus cela baissait jusqu'à atteindre 0ms si je colle un mur de face.
 
Le problème de cette fonction vient que j'ai eu comme idée de regarder dans la map toutes les cases en fonctions de la direction du Raycast obtenu avec la fonction `GetRayDir`. Par exemple si GetRayDir me retourne comme vecteur `{0.5f, 0.5f}` alors je regardais quelle était la case se trouvant en  coordonné de ma position actuelle + `(0.5f, 0.5f)`. Et je rajoute à chaque fois le vecteur de `GetRayDir` jusqu'à trouver une case contenant un mur. Pour ensuite appeler la fonction `GetImpactedWallOfArea` qui regarde précisément quelle est la coordonnée exacte du mur touché.  
Cependant cette méthode pose un problème. En effet en me déplaçant comme cela en fonction de `GetRayDir` je loupais des cases car le déplacement était trop grand. 
J'ai donc divisé le résultat obtenu par `GetRayDir` par 100 afin d'être persuadé de ne louper aucune case. Ce qui provoque en conséquence un bien plus grand nombre de boucle pour trouver une case possédant un mur.  
  
### 2- Comment améliorer ces performances ?
  
Pour le problème de changer les pixels de couleur je me suis rappelé qu'on avait vu en cours la possibilité de passer des vertex à la carte graphique afin de lui dire de remplir très rapidement une zone en triangle.  
J'ai donc regardé si SFML propose de faire cela et heureusement c'est bel est bien le cas avec des VertexArray.
J'ai donc refait ma fonction DrawRect pour remplacer une boucle de SetPixel un par un par l'ajout de vertex pour former des triangles.   
Grâce à cela je suis passé de 150ms à 0ms car le temps était désormais trop bas pour être mesuré.
J'ai mesuré ensuite le temps que prend le nouveau DrawRect si on l'appelle 100 000 fois d'affilé et cela prend seulement 30ms ! Le gain de performance est énorme.  
De plus, je l'ai retiré de la boucle de gameplay car étant donné que je n'ai plus une image à manipuler, il suffit que je dessine l'arrière plan une seul fois pour qu'il reste pendant toute la partie. Même si cela prend d'infimes performances, cela ne sert a rien de les prendres pour rien à chaque boucle.   
   
J'ai ensuite fait de même avec la fonction `DrawVerticalLine` en traçant des lignes de VertexArray et le gain de performance était aussi gros. Cependant, au vu de la dernière étape du tp à savoir rajouter une texture aux murs, j'ai préféré me passer de cette fonction pour dessiner mes murs à partir de triangles. Comme cela j'ai juste eu à rajouter les coordonnées de ma texture aux vertex pour que ça fonctionne.  
    
    
Concernant mon algorithme de recherche de murs, je l'ai totalement refait à 0 de manière bien plus claire à relire, avec moins de lignes de codes et des performances largemment au dessus.  
Il existe une formule de maths pour détecter tous les murs verticaux à la suite et tous les murs horizontaux à la suite.  
J'ai donc refais tout l'algoritme à partire de ces formules.  
La fonction `RasterizeScene` se fait désormais en 0ms avec de temps en temps un pic à 16ms. J'ai d'ailleur souvent eu dans toutes mes mesures ce pic à 16ms et je n'ai pas réussis à trouver d'où il vient.  
Je pensais que c'était à cause de la manière donc la boucle de gameplay a été faite donc je l'ai refaite à ma façon mais cela n'a rien changé.  
J'ai fait le `RasterizeScene` 100 fois d'affilé pour avoir une mesure plus précise que 0ms et cela a donné 218ms.
