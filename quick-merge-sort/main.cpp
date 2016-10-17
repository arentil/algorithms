#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

class ObjectsToSort
{
   public:
      int number;
      char character;
};

ObjectsToSort tabForMerge[1000];
void quickSort(ObjectsToSort * arr, int left, int right, int param);          //QUICK SORT
void merge(ObjectsToSort * arr, int left, int mid, int right, int param);
void mergeSort(ObjectsToSort * arr,int left, int right, int param);
int compareLetters(ObjectsToSort * pointer, int howMany);
int compareNumbers(ObjectsToSort * pointer, int howMany);


int main() 
{
   ifstream inFile;
   ofstream outFile;
   inFile.open("dane.txt");
   outFile.open("wyniki.txt");
   
   int sets = 0;
   inFile >> sets;
   for (int i = 0; i < sets; i++)
   {
      int howManyObjects = 0;
      inFile >> howManyObjects;
      ObjectsToSort * ptr = new ObjectsToSort[howManyObjects];
      ObjectsToSort * mergePtr = new ObjectsToSort[howManyObjects];
      for (int j = 0; j < howManyObjects; j++)
      {
         inFile >> ptr[j].number;
         mergePtr[j].number = ptr[j].number;
         inFile >> ptr[j].character;
         mergePtr[j].character = ptr[j].character;
      }
      
      
      
      for (int j = 0; j < 25; j++)
         outFile << "*";
      outFile << " ZESTAW: " << i+1 << " ";
      for (int j = 0; j < 25; j++)
         outFile << "*";
      
      outFile << "\nZestaw nieposortowany:\n";
      outFile << "Obiekt nr: |int||char|\n";
      for (int j = 0; j < howManyObjects; j++)
      {
         outFile << "\t#" << j+1;
         if (j >= 10 || j == 9)
            outFile << "\t\t";
         else if (j >= 100)
            outFile << "\t";
         else if (j < 9)
            outFile << "\t\t\t";
         outFile << ptr[j].number << "\t\t" << ptr[j].character << "\n";
      }
         
      if (!compareNumbers(mergePtr, howManyObjects))
         mergeSort(mergePtr, 0, howManyObjects-1, 0);
      if (!compareNumbers(ptr, howManyObjects))
         quickSort(ptr, 0, howManyObjects-1, 0);
      outFile << "\nZestaw posortowany po liczbach:\n";
      outFile << "QUICK SORT:\t\t\t\t\t\t\t\t\t\t\tMERGE SORT:\n";
      outFile << "Obiekt nr: |int||char|\t\t\t\t\t\t\tObiekt nr: |int||char|\n";
      for (int j = 0; j < howManyObjects; j++)
      {
         outFile << "\t#" << j+1;
         if (j >= 10 || j == 9)
            outFile << "\t\t";
         else if (j >= 100)
            outFile << "\t";
         else if (j < 9)
            outFile << "\t\t\t";
         outFile << ptr[j].number << "\t\t" << ptr[j].character;
         outFile << "\t\t\t\t\t\t\t\t";
         outFile << "\t#" << j+1;
         if (j >= 10 || j == 9)
            outFile << "\t\t";
         else if (j >= 100)
            outFile << "\t";
         else if (j < 9)
            outFile << "\t\t\t";
         outFile << mergePtr[j].number << "\t\t" << mergePtr[j].character << "\n";
      }
         
      if (!compareLetters(mergePtr, howManyObjects))
         mergeSort(mergePtr, 0, howManyObjects-1, 1);
      if (!compareLetters(ptr, howManyObjects))
         quickSort(ptr, 0, howManyObjects-1, 1);
      outFile << "\nZestaw posortowany po literach:\n";
      outFile << "QUICK SORT:\t\t\t\t\t\t\t\t\t\t\tMERGE SORT:\n";
      outFile << "Obiekt nr: |int||char|\t\t\t\t\t\t\tObiekt nr: |int||char|\n";
      for (int j = 0; j < howManyObjects; j++)
      {
         outFile << "\t#" << j+1;
         if (j >= 10 || j == 9)
            outFile << "\t\t";
         else if (j >= 100)
            outFile << "\t";
         else if (j < 9)
            outFile << "\t\t\t";
         outFile << ptr[j].number << "\t\t" << ptr[j].character;
         outFile << "\t\t\t\t\t\t\t\t";
         outFile << "\t#" << j+1;
         if (j >= 10 || j == 9)
            outFile << "\t\t";
         else if (j >= 100)
            outFile << "\t";
         else if (j < 9)
            outFile << "\t\t\t";
         outFile << mergePtr[j].number << "\t\t" << mergePtr[j].character << "\n";
      }
   }
   
   cout << "Gotowe!" << endl;
   inFile.close();
   outFile.close();
	return 0;
}
//****************** Funkcja sprawdzajaca, czy tablica jest posortowana po liczbach *******************
int compareNumbers(ObjectsToSort * pointer, int howMany)
{
   int count;
   for (int i = 0; i < howMany-1; i++)
   {
      if (pointer[i].number > pointer[i+1].number)
         return 0;
      else if (pointer[i].number == pointer[i+1].number)
         count++;
      else
         count++;
   }
   if(count == (howMany-1))
      return 1;
}
//****************** Funkcja sprawdzajaca, czy tablica jest posortowana po literach *******************
int compareLetters(ObjectsToSort * pointer, int howMany)
{
   int count;
   for (int i = 0; i < howMany-1; i++)
   {
      if (pointer[i].character > pointer[i+1].character)
         return 0;
      else if (pointer[i].character == pointer[i+1].character)
         count++;
      else
         count++;
   }
   if(count == (howMany-1))
      return 1;
}
//******************************************** QUICK SORT *****************************************
void quickSort(ObjectsToSort * arr, int left, int right, int param) 
{
   int i = left;
   int j = right;
   ObjectsToSort tmp;
   ObjectsToSort pivot = arr[(left + right) / 2];

   while (i <= j) 
   {
      if (param == 0)
      {
         while (arr[i].number < pivot.number)
            i++;
         while (arr[j].number > pivot.number)
            j--;
            if (i <= j) 
            {
               tmp = arr[i];
               arr[i] = arr[j];
               arr[j] = tmp;
               i++;
               j--;
            }
      }
      else
      {
         while (arr[i].character < pivot.character)
            i++;
         while (arr[j].character > pivot.character)
            j--;
            if (i <= j) 
            {
               tmp = arr[i];
               arr[i] = arr[j];
               arr[j] = tmp;
               i++;
               j--;
            }
      }
   }
   if (left < j)
         quickSort(arr, left, j, param);
   if (i < right)
         quickSort(arr, i, right, param);
}
//******************************************** MERGE SORT *****************************************
void merge(ObjectsToSort * arr, int left, int mid, int right, int param) 
{
   int i = left;
   int j = mid + 1;
 

   for(int i = left; i <= right; i++) 
      tabForMerge[i] = arr[i];  
 

   for(int k = left; k <= right; k++) 
      if(i <= mid)
         if(j <= right)
            if (param == 0)
            {
               if(tabForMerge[j].number < tabForMerge[i].number)
                  arr[k] = tabForMerge[j++];
               else
                  arr[k] = tabForMerge[i++];
            }
            else
            {
               if(tabForMerge[j].character < tabForMerge[i].character)
                  arr[k] = tabForMerge[j++];
               else
                  arr[k] = tabForMerge[i++];
            }  
         else
            arr[k] = tabForMerge[i++];
      else
         arr[k] = tabForMerge[j++];
}
 
void mergeSort(ObjectsToSort * arr,int left, int right, int param)
{
  if(right <= left) return; 
 
  int mid = (right + left)/2;
 
  mergeSort(arr, left, mid, param); 
  mergeSort(arr, mid+1, right, param);
 
  merge(arr, left, mid, right, param);  
}
