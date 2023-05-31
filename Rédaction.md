# Rédaction

Pour chaque container, il faudra décrire grossièrement son fonctionnement ainsi que ses avantages et inconvénients. Vous
pouvez illustrer les spécificité à travers des exemples où il est plus pertinent d’utiliser un
container plutôt qu’un autre.

Les containers permettent de stocker des éléments.

## list

C'est un conteneur STL qui est implenté comme une liste à double lien. Il prend en charge l'insertion et la suppression d'élèments n'importe où dans le conteneur.

## vector

C'est un espace de stockage pour une séquence d'éléments. Il contient le nombre d'éléments, le dernier élement et les éléments. C'est quelque chose qui s'empile les uns derrière les autres. Quand on veut stocker quelque chose, par défaut, on prend un vector. Un vector est un template. Il prend une classe en argument. Cela prend le type d'éléments que l'on veut stocker dans le vector (ex: Int, string, et d'une classe).
Il s'initialise de deux façons.
Soit normalement avec l'initialisateur list :

```cpp
vector <int> v1{1,2,3,4,5};
```

## deque

Deque signifie en anglais (double ended queue). Il sert à ajouter et supprimer des élèments au début et à la fin de la structure de donnée.

## map

C'est une table associative qui permet d'associer une clé à une valeur/donnée.
Map prend deux paramètres :

- le type de la clé
- le type de la valeur/donnée
  Exemple :
  On associe une map entre un entier (la valeur) et une string (la clé).
  map<int, string> map1
  ...

```

```
