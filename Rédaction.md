# Rédaction

Pour chaque container, il faudra décrire grossièrement son fonctionnement ainsi que ses avantages et inconvénients. Vous
pouvez illustrer les spécificité à travers des exemples où il est plus pertinent d’utiliser un
container plutôt qu’un autre.

Les containers permettent de stocker des éléments.

## list

...

## vector

C'est un espace de stockage pour une séquence d'éléments. Il contient le nombre d'éléments, le dernier élement et les éléments. C'est quelque chose qui s'empile les uns derrière les autres. Quand on veut stocker quelque chose, par défaut, on prend un vector. Un vector est un template. Il prend une classe en argument. Cela prend le type d'éléments que l'on veut stocker dans le vector (ex: Int, string, et d'une classe).
Il s'initialise de deux façons.
Soit normalement avec l'initialisateur list :

```cpp
vector <int> v1{1,2,3,4,5};
```

Soit les méthodes du template vector :
v1.push_back("int 1");

## deque

...

## map

C'est une association clé-valeur.
Exemple :
On associe une map entre un entier et une string.
map<int, string> map1
...
