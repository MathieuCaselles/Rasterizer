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

J'ai d'abord regardé le temps que prenait une boucle de jeu. Le temps d'une boucle oscille entre 25ms et 26.6ms ce qui est catastrophique.  
C'est tout simplement injouable de jouer à un jeu avec 4fps seulement.  

J'ai ensuite mesuré le temps que prenait la fonction `DrawRect` et `RasterizeScene`.  
`DrawRect` se fait entre 15.6ms et 17.2ms.  
`RasterizeScene` se fait entre 7.8ms et 9.4ms. 
Je trouve ce résultat très étonnant car je pensais que tout le plus gros problème de l'optimisation était mon algorithme de recherche de mur qui est très loin d'être bien optimisé mais au final le plus gros du problème vient du parcours des pixels pour les changer de couleur.  
En effet, j'ai essayé de me coller contre un mur pour obliger la fonction `RasterizeScene` à set tous les pixels de l'écran et les performances de cette fonction sont devenu identiques à `DrawRect` en oscillant aussi antre 15.6ms et 17.2ms.  
  
Enfin j'ai mesuré `GetFirstAreaFound` que je pensais être la fonction la plus lourde dans `RasterizeScene`.  
Le résultat était entre 6ms et 8ms pour afficher tout l'écran. Et plus je me rapprochais et plus cela baissait jusqu'à atteindre 0ms si je colle un mur de face.
 
Le problème de cette fonction vient que j'ai eu comme idée de regarder dans la map toutes les cases en fonctions de la direction du Raycast obtenu avec la fonction `GetRayDir`. Par exemple si GetRayDir me retourne comme vecteur `{0.5f, 0.5f}` alors je regardais quelle était la case se trouvant en  coordonné de ma position actuelle + `(0.5f, 0.5f)`. Et je rajoute à chaque fois le vecteur de `GetRayDir` jusqu'à trouver une case contenant un mur. Pour ensuite appeler la fonction `GetImpactedWallOfArea` qui regarde précisément quelle est la coordonnée exacte du mur touché.  
Cependant cette méthode pose un problème. En effet en me déplaçant comme cela en fonction de `GetRayDir` je loupais des cases car le déplacement était trop grand. 
J'ai donc divisé le résultat obtenu par `GetRayDir` par 100 afin d'être persuadé de ne louper aucune case. Ce qui provoque en conséquence un bien plus grand nombre de boucle pour trouver une case possédant un mur.  
  
### 2- Comment améliorer ces performances ?
  
Pour le problème de changer les pixels de couleur je me suis rappelé qu'on avait vu en cours la possibilité de passer des vertex à la carte graphique afin de lui dire de remplir très rapidement une zone en triangle.  
J'ai donc regardé si SFML propose de faire cela et heureusement c'est bel est bien le cas avec des VertexArray.
J'ai donc refait ma fonction DrawRect pour remplacer une boucle de SetPixel un par un par l'ajout de vertex pour former des triangles.   
Grâce à cela je suis passé de 15ms à 0ms car le temps était désormais trop bas pour être mesuré.
J'ai mesuré ensuite le temps que prend le nouveau DrawRect si on l'appelle 100 000 fois d'affilé et cela prend seulement 3ms ! Le gain de performance est énorme.   
   
J'ai ensuite fait de même avec la fonction `DrawVerticalLine` en traçant des lignes de VertexArray et le gain de performance était aussi gros. Cependant, au vu de la dernière étape du tp à savoir rajouter une texture aux murs, j'ai préféré me passer de cette fonction pour dessiner mes murs à partir de triangles. Comme cela j'ai juste eu à rajouter les coordonnées de ma texture aux vertex pour que ça fonctionne.  
    
    
Concernant mon algorithme de recherche de murs, je pense qu'il faut entièrement refaire l'algorithme à 0 et trouver un moyen de pourvoir détecter directement la prochaine intersection d'une case depuis le point de départ ou depuis la case regardé précédemment.     
Cela réduirait drastiquement le nombre de boucle car une boucle permettrait de trouver à coup sûr la prochaine case à vérifier en ayant en plus déjà l'emplacement du prochain mur touché s'il y a un mur.    
Cela serait bien plus performant que de se déplacer très légèrement en boucle dans la direction du raycast jusqu'à atterrir à l'intérieur d'une case possédant un mur pour ensuite calculer où le mur a été touché en fonction du raycast.  
C'est le seul algorithme que je n'ai malheureusement pas optimisé par manque de temps ce qui est assez frustrant.
Surtout que je pense que j'avais déjà une bonne base de recherche avec mon algorithme pour détecter la collision avec un mur dans une case.  