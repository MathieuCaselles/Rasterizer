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
  
Vous pouvez trouver à  la racine de ce dépôt un fichier MainV1.cpp (Ce fichier n'est pas visible depuis Visual Studio).  
Il s'agit de ma première version fonctionnelle du Raycaster avant d'entamer la question sur les performances obtenu pour pouvoir mieux comparé ce que j'ai fait avant puis après.  
  
Pour mesurer les performances, j'ai regardé quelles fonctions prennaient plus ou moins de temps à l'aide de la fonction `GetTickCount64` en procédant comme cela:

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
  
Enfin j'ai mesuré les 3 fonctions que je pensais être les plus lourde dans `RasterizeScene` à savoir `GetFirstAreaFound`, `GetImpactedWallOfArea` et `DrawVerticalLine`.  
Mais le résulat me montré un temps égal à 0ms.
Sauf pour DrawVerticalLine lorsqu'il devait dessiner une ligne en plein écran qui était aussi à 0ms 99% du temps mais qui de temps en temps montait à 1.6ms ce qui montre encore une fois que le plus gros problème de performances est la gestion des pixels.  
Cependant je peux encore optimisé la fonction `GetFirstAreaFound` qui est pour moi beaucoup trop lourde. 
En effet j'ai eu comme idée de regarder dans la maps toutes les cases en fonctions de la direction du Raycast obtenu avec la fonction `GetRayDir`. Par exemple si GetRayDir me retourne comme vecteur `{0.5f, 0.5f}` alors je regardé quelle était la case se trouvant en  coordonné de ma position actuelle + `(0.5f, 0.5f)`. Et je rajoute à chaque fois le vecteur de `GetRayDir` jusqu'a trouvé une case contenant un mur. Pour ensuite appelé la fonction `GetImpactedWallOfArea` qui regarde précisément quelle est la coordonnée exacte du mur touché.  
Cependant cette méthode pose un problème. En effet en me déplaçant comme cela en fonction de `GetRayDir` je loupais des cases car le déplacement était trop grand. 
J'ai donc divisé le résultat obtenu par `GetRayDir` par 100 afin d'être persuadé de ne louper aucune case. Ce qui provoque en conséquence un bien plus grand nombre de boucle pour trouver une case possédant un mur.  
  
### 2- Comment améliorer ces performances ?

Concernant mon algorithme de recherche de murs, je pense qu'il faut entièrement refaire l'algoritme à 0 et trouver un moyen de pourvoir détecter directement la prochaine intersection d'une case depuis le point de départ ou depuis la case regardé précedemment.   
Cela réduirait drastiquement le nombre de boucle car une boucle permettrait de trouver à coup sûr la prochaine casé à vérifié en ayant en plus déjà l'emplacement du prochain mur touché s'il y a un mur.  
Cela serait bien plus performant que de se déplacer très légèrement en boucle dans la direction du raycast jusqu'à atterir à l'intérieur d'une case possédant un mur pour ensuite calculer où le mur a été touché en fonction du raycast.   

J'ai aussi pensé à mettre en place un upscale en divisant la définition par 2 ou 3. Pour ensuite dessiner des rectanges verticaux de quelques pixels de largeurs  au lieu de dessiner des lignes d'un pixel ce qui réduirait grandement le nombre de raycast à effectuer.  
Cependant cela ne résoudrait pas le problème de remplissage de pixel qui est largement le plus gros problème de performances et cela rendrait en contre partit un rendu avec un effet d'escalier.

Concernant le remplissage de pixel, 