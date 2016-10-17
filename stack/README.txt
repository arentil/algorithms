Zadanie 06 - kalkulator ONP
Marcin Żołubowski

Przy pomocy makefile:
    - kompilacja: make

    - uruchomienie kalkulatora OPN(z testami): run
    
Po uruchomieniu kalkulatora wpisać działanie w 
odwrotnej polskiej notacji na końcu ze znakiem "=". 
Np. 1 2 3 4 + * + =
Linie z dzialaniami możemy wpisywać dopóki program nie napotka pustej 
linii. Gdy to nastąpi program wypisuje wyniki w działań w tej samej
kolejności co podawanie działań.
Przykład:

4 2 5 * + 1 3 2 * + / =         
2 5 * 4 + 3 2 * 1 + / =
5 1 2 + 4 * 3 - + =
9 5 3 + 2 4 ^ - + =
**pusta linia**
2
2
14
1
