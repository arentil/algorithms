// Marcin Zolubowski
// przykladowe wywolanie:  ./program dane.txt wyniki.txt

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int binaryAlgorithm(int left, int right, int tabl[], int valueToFind);

int main(int argc, char *argv[])
{
    cout << "\nProgram, ktory przy pomocy wyszukiwania binarnego\n"
            "znajduje indeksy (liczone od 0) podanych\n"
            "elementow w podanych tablicach liczb calkowitych.\n"
            "W przypadku, gdy dany element nie istnieje w tablicy,\n"
            "program wpisuje -100 zamiast indeksu." << endl;
    cout << "\nPlik danych: " << argv[1]
	 << "\nPlik wyjsciowy: " << argv[2] << endl;


    ifstream inFile;
    ofstream outFile;
    inFile.open(argv[1]);
    if (!inFile.is_open())
    {
        cout << "Nie udalo sie otworzyc pliku " << argv[1] << endl;
        exit(EXIT_FAILURE);
    }
    outFile.open(argv[2]);
    if (!outFile.is_open())
    {
        cout << "Nie udalo sie otworzyc pliku " << argv[2] << endl;
        exit(EXIT_FAILURE);
    }

    int sets = 0;
    inFile >> sets;            // ilosc zestawow danych

    for (int i = 0; i < sets; i++)
    {
        int tabSize = 0;
        int tabFindSize = 0;

        // odczyt z pliku i zapis do zmiennej "tabSize" wielkosci tablicy danych
        // oraz wartosci tablicy danych "tabValues"

        inFile >> tabSize;
        int tabValues[tabSize];
        inFile >> tabValues[0];
        for (int j = 1; j < tabSize ; j++)
            inFile >> tabValues[j];

        // odczty z pliku i zapis do zmiennej "tabFindSize" wielkości tablicy liczb do wyszukania
        // oraz wartości tych liczb do tablicy "tabFindValues"

        inFile >> tabFindSize;
        int tabFindValues[tabFindSize];
        inFile >> tabFindValues[0];
        for (int k = 1; k < tabFindSize ; k++)
            inFile >> tabFindValues[k];

        for (int l = 0; l < tabFindSize; l++)
        {
            outFile << binaryAlgorithm(0, tabSize, tabValues, tabFindValues[l]) << " ";
            // zapis jednego zestawu wyszukanych indeksow liczb
        }
        outFile << endl;
    }

    inFile.close();
    outFile.close();
    cout << "\nGotowe!" << endl;
    return 0;
}

//******************** ALGORYTM BINARNY ***********************************************
int binaryAlgorithm(int left, int right, int tabl[], int valueToFind)
{
    int middle;

    while (left <= right)
    {
        middle = (left + right) / 2;

        if (tabl[middle] == valueToFind)
            return middle;

        if (tabl[middle] > valueToFind)
            right = middle - 1;
        else
            left = middle + 1;
    }
    return -100;        //jezeli nie znaleziono szukanej wartosci
}
//***************** KONIEC ALGORYTMU BINARNEGO ****************************************
