# Rédaction

_Pour chaque container, il faudra décrire grossièrement son fonctionnement ainsi que ses avantages et inconvénients. Vous pouvez illustrer les spécificité à travers des exemples où il est plus pertinent d’utiliser un container plutôt qu’un autre._

=> Les containers permettent de stocker des éléments. Les différents container cité ci dessous sont issus de la bibliothèque standard de C++. Ils sont tous différents et comportent des avantages et des inconvénients. 

## `list`

C'est une liste doublement chaînée. C'est à dire que chaque élément de la liste est associé à deux pointeurs. Un pointeur vers l'élément précédent. Et un pointeur vers l'élément suivant. Ce mode de fonctionnment nous permet ainsi d'avoir un accès simple, aux éléments en avant et en arrière de l'élément que l'on traite. Il faut ce le représenter comme une liste classique, ou chaque éléments est en ligne.

La liste permet également d'insérer des éléments en temps constant. C'est à dire que l'on peut insérer un élément n'importe où dans la liste, sans avoir à décaler les éléments. Cela est possible grâce aux pointeurs qui permettent de lier les éléments entre eux.

Cependant, la liste ne permet pas d'accéder à un élément en temps constant. En effet, pour accéder à un élément, il faut parcourir la liste jusqu'à l'élément voulu. En effet, comme dit précédamment, les éléments ne sont pas stockés les uns à la suite des autres. C'est un inconvénient de la liste, mais c'est aussi un avantage car une liste n'a pas de taille maximale, elle est dynamique.

## Exemple pour la `list`

```cpp
std::list<std::string> myList;

// Insertion d'éléments dans la liste
myList.push_back("Salut");
myList.push_back("voici");
myList.push_back("une liste");

// La facon d'on on parcours la liste (différente d'un autre container)
std::list<std::string>::iterator it;
for (it = myList.begin(); it != myList.end(); ++it) {
	std::cout << *it << " ";
}
std::cout << std::endl;

// Insertion d'un élément en début de liste
myList.push_front("Et voila, au début !");

// Affichage de la liste mise à jour
for (it = myList.begin(); it != myList.end(); ++it) {
	std::cout << *it << " ";
}
std::cout << std::endl;

// Résultat attendu :
// Salut voici une liste
// Et voila, au début ! Salut voici une liste
```
## `vector`

C'est un espace de stockage pour une séquence d'éléments. Il contient le nombre d'éléments, le dernier élement et les éléments.
C'est quelque chose qui s'empile les uns derrière les autres. Quand on veut stocker quelque chose sans vouloir trop se contraindre, on prend un vector, car c'est le fonctionnment d'un tableau "classique" dans beaucoup de langage.
Un vector est un template, il prend une classe en argument, cela prend le type d'éléments que l'on veut stocker dans le vector (ex: Int, string).
C'est un tableau dynamique, il peut grandir et rétrécir, la mémoire est allouée automatiquement.
A noter, en interne le vector stocke les éléments de manière contigue, c'est à dire que les éléments sont stockés les uns à la suite des autres en mémoire, ce qui facilite le parcours des éléments dans un for par exemple.

## Exemple pour le `vector`

```cpp
// Pour l'initialisation, 2 possibilités

vector <int> vect; // Ou vector <int> vect{1,2,3,4,5};
vect.push_back(1);

// Pour l'accès aux éléments, 2 possibilités

 vect[0] // ou vect.at(0); pour évité les erreurs de dépassement de tableau (la fameuse "segmentation fault")

// Nous pouvons également inserer des éléments à n'importe qu'elle position
vect.insert(vect.begin() + 1, 2); // Ici, nous insérons le nombre 2 à la position 1 du tableau (le 2ème élément)

// De la même manière, pour la suppression d'éléments
vect.erase(vect.begin() + 1);
```
D'autre méthode sont également disponible, comme la méthode `size()` qui permet de connaitre la taille du tableau, la méthode `empty()` qui permet de savoir si le tableau est vide ou non, la méthode `clear()` qui permet de vider le tableau, `resize()` qui permet de redimensionner le tableau, `capacity()` qui permet de connaitre la capacité du tableau, etc...

## `deque`

Signifi "double-ended queue", est une file doublement chaînée. C'est un conteneur de séquence indexé qui permet une insertion et une suppression rapides à la fois au début et à la fin. 

Son stockage est automatiquement géré par le conteneur, en fonction des besoins. Contrairement au `vector` l'expansion d'un `deque` est moins couteuse car il n'y a pas de copie des éléments existants dans un nouvel espace mémoire. Attention car généralement, son coût minimal est supérieur à celui d'un `vector`.

`deque` offre, globalement les mêmes méthodes que `vector`, à savoir `push_back()`, `push_front()`, `size()`...

## Exemple pour le `deque`

```cpp
std::deque<std::string> deque1;

// Insertion d'éléments dans la deque
deque1.push_back("Whaou mais c'est formidable ça !");

// Affichage de la deque
for (int i = 0; i < deque1.size(); i++) {
	std::cout << deque1[i] << " ";
}

// Résultat attendu :
// Whaou mais c'est formidable ça !
```
Note: Un cas d'usage judicieux pourrait être **Une liste de tâche**. En effet ce container est généralement utilisé pour des cas de file d'attente ou la gestion du premier élément ainsi que du dernier est récurrent.

## `map`
Ce container est un peu particulier, il permet de stocker des éléments de manière ordonnée. Il introduit un nouveau concept : l'association.
Chaque valeur est associée à une clé, qui est unique.
Cette clé peut être de n'importe quel type, mais elle doit être comparable (opérateur <, >, ==, !=, <=, >=).

Le conteneur map est implémenté en utilisant un arbre binaire, comme vu en TP, cela nous permet l'ors d'insertion, de suppression et de recherche d'éléments, d'avoir une complexité logarithmique ((O(log n)) dans le pire des cas).

Map est dont un container très judicieux pour stocker des données de manière ordonnée, et de pouvoir les retrouver **rapidement**, et lorsque l'index nous importe peu.

Note: Un cas d'usage judicieux pourrait être **Un annuaire**. En effet ce container est généralement utilisé pour des cas de stockage de données avec une clé unique.

## Exemple pour le `map`

```cpp
std::map<std::string, int> ageProfs;

    // Insertion d'éléments dans le map (données purement fictives, toute ressemblance avec des personnes existantes ou ayant existé serait purement fortuite)
    ages["Biri"] = 40;
    ages["Stevee"] = 28;
    ages["Cherrier"] = 48;

	// Affichage du map
	cout << "D'après quelques sondage d'approximation";

	std::map<std::string, int>::iterator it;
	for (it = ages.begin(); it != ages.end(); ++it) {
		std::cout << it->first << " a envrion " << it->second << " ans " << std::endl;
	}

	// Résultat attendu :
	// D'après quelques sondage d'approximation
	// Biri a envrion 40 ans
	// Cherrier a envrion 48 ans
	// Stevee a envrion 28 ans
```