// Marcin Zolubowski
// Zadanie Sortowanie I
// Przekazywanie argumentu: argv[1]
// Dla 1 - insertion_sort || Dla 2 - selection_sort || Dla 3 - merge_sort
// Przekazywanie argumentu: argv[2]
// Dla 0 - sortowanie malejaco || Dla 1 - sortowanie rosnaco



#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int * tempForMerge;
string showOrder(int choise);
void insertion_sort(int * tab, int n, int choise);
void selection_sort(int * tab, int n, int choise);
void merge(int * tab, int left, int mid, int right);
void merge_sort(int * tab, int left, int right);

int main(int argc, char *argv[])
{
   int whichAlgorithm = atoi(argv[1]);
   int choiseOrder = atoi(argv[2]);
   
   if (!(((whichAlgorithm >= 1) && (whichAlgorithm <= 3))))
   {
      cout << "Pierwszy argument powinien byc z zakresu [1;3]" << endl;
      exit(1);
   }
   if (!(choiseOrder == 0 || choiseOrder == 1))
   {
      cout << "Drugi argument powinien byc zerem lub jedynka." << endl;
      exit(1);
   }

   ifstream inFile;
   ofstream outFile;
   inFile.open("dane_duze.txt");
   outFile.open("wyniki.txt");

   int tablesToSort = 0;
   inFile >> tablesToSort;
   for (int i = 0; i < tablesToSort; i++)
   {
      int tabSize = 0;
        
      inFile >> tabSize;
      int tabToSort[tabSize];
      for (int j = 0; j < tabSize ; j++)
          inFile >> tabToSort[j];
      
      switch(whichAlgorithm)
      {
         case 1:
            cout << "insertion sort - sortuje zestaw " << i+1 << showOrder(choiseOrder) << endl;
            insertion_sort(tabToSort, tabSize, choiseOrder);
            cout << "Posortowany" << endl;
            break;
         case 2:
            cout << "selection sort - sortuje zestaw " << i+1 << showOrder(choiseOrder) << endl;
            selection_sort(tabToSort, tabSize, choiseOrder);
            cout << "Posortowany" << endl;
            break;
         case 3:
            cout << "merge sort - sortuje zestaw " << i+1 << showOrder(choiseOrder) << endl;
            tempForMerge = new int[tabSize];
            merge_sort(tabToSort, 0, tabSize-1);
            if (!choiseOrder)
            {
               int tmp;
               for(int k = 0; k < tabSize/2; k++)
               {
                  tmp=tabToSort[tabSize-k-1];
                  tabToSort[tabSize-k-1]=tabToSort[k];
                  tabToSort[k]=tmp;
               }
            } 
            delete [] tempForMerge;
            cout << "Posortowany" << endl;
            break;
      }
      for (int j = 0; j < tabSize; j++)
          outFile << tabToSort[j] << " ";
      outFile << endl;
      
   }
   

   inFile.close();
   outFile.close();
   cout << "Gotowe!" << endl;
   return 0;
}
// ************************* ALGORYTMY SORTUJACE ************************************
string showOrder(int choise)
{
   if (!choise)
      return " - malejaco";
   else
      return " - rosnaco";
}

void insertion_sort(int * tab, int n, int choise)
{
     int temp, j;
     for(int i=1; i<n; i++)
     {
             temp = tab[i];
             j = i-1;
 
             while(j>=0 && tab[j]>temp) 
             {
                        tab[j+1] = tab[j];
                        --j;
             }
             tab[j+1] = temp;
     }  
    if (!choise)
    {
        int tmp;
        for(int i = 0; i<n/2; i++)
        {
            tmp=tab[n-i-1];
            tab[n-i-1]=tab[i];
            tab[i]=tmp;
        }
    }   
}


void selection_sort(int * tab, int n, int choise)
{
   int minIndex, temp;
   for (int i = 0; i < n-1; i++)
   {
      minIndex = i;
      for (int j = i+1; j < n; j++)
         if (tab[j] < tab[minIndex])
            minIndex = j;
            
      if (minIndex != i)
      {
         temp = tab[i];
         tab[i] = tab[minIndex];
         tab[minIndex] = temp;  
      }
   }
   if (!choise)
   {
        int tmp;
        for(int i = 0; i<n/2; i++)
        {
            tmp=tab[n-i-1];
            tab[n-i-1]=tab[i];
            tab[i]=tmp;
        }
   }   
}


void merge(int * tab, int left, int mid, int right) 
{
   int i = left;
   int j = mid + 1;
 

   for(int i = left; i <= right; i++) 
   tempForMerge[i] = tab[i];  
 

   for(int k = left; k <= right; k++) 
      if(i <= mid)
         if(j <= right)
            if(tempForMerge[j] < tempForMerge[i])
               tab[k] = tempForMerge[j++];
            else
               tab[k] = tempForMerge[i++];
         else
            tab[k] = tempForMerge[i++];
      else
         tab[k] = tempForMerge[j++];
}
 
void merge_sort(int * tab,int left, int right)
{
  if(right <= left) return; 
 
  int mid = (right + left)/2;
 
  merge_sort(tab, left, mid); 
  merge_sort(tab, mid+1, right);
 
  merge(tab, left, mid, right);  
}

