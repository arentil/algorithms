Implementacja binarnego drzewa przeszukiwan
Autor: Marcin Zolubowski

Implementacja drzewa została wykonana wg Pana wytycznych oprócz
implementacji metody "node search(int x)", gdzie przekazuje dodatkowo
jako argument do metody wskaźnik do węzła od którego rozpoczne poszukiwania, 
pomogło to uprościć poszukiwania i zaimplementować go rekurencyjnie.
Zastosowałem również dodatkową metodę znajdującą następnika swojego węzła wg 
klucza względem przeszukiwania inorder. Uprościło to również nieco implementację
metody delete(node n).

Metoda "inorder-print()" została zaimplementowana iteracyjnie, zastosowałem 
do niej własne struktury - stos, oraz listę pojedynczo wiązaną do przechowania 
zawartości a następnie jej wypisania na ekran.

Kompilacja ze standardem c++11 ze względu na użycie "nullptr" np:
	g++ -std=c++11 BSTtree.cpp
	
Uruchomienie bądź jakie np:
	./a.out
