#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

char randAlphabet();

int main()
{
   srand(time(NULL));
   ofstream outFile;
   outFile.open("dane.txt");
   
   int sets;
   int rangeFrom;
   int rangeTo;
   cout << "Generator zestawow danych do zadania 04."
           "\nZakres losowanych liter jest niezmienny a-z." << endl;
   cout << "Ile chcesz stworzyc zestawow: ";
   cin >> sets;
   int objects[sets];
   outFile << sets << "\n";
   for (int i = 0; i < sets; i++)
   {
      cout << "Ile chcesz stworzyc obiektow w zestawie " << i+1 << ": ";
      cin >> objects[i];
      outFile << objects[i] << "\n";
      cout << "Podaj dolny zakres liczbowy losowanych liczb: ";
      cin >> rangeFrom;
      cout << "Podaj gowny zakres liczbowy losowanych liczb: ";
      cin >> rangeTo;
      for (int j = 0; j < objects[i]; j++)
      {
         outFile << rangeFrom + rand() % rangeTo-rangeFrom;
         outFile << randAlphabet();
      }
      outFile << "\n";
   }
   
   
   cout << "\n GOTOWE!" << endl;
   outFile.close();
   return 0;
}

char randAlphabet()
{
	string alphabet;
	
	for(int i = 0; i < 26; ++i) 
	{
		alphabet.push_back('a' + i);
	}
	return alphabet[rand() % 26];
}
