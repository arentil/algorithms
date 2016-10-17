// Marcin Zolubowski
// Zadanie 7
//  implementacja tablicy mieszającej z adresowaniem łańcuchowym


#include <iostream>
#include <string>
#include <cassert>

using namespace std;


class ListElement
{
public:
    string key;
    string value;
    ListElement * ptr_next;
};

class List
{
public:
    ListElement * ptrList;
    List();
    ~List();

    void push_back(string surname, string name);
    void remove(string surname);
    string get(string surname);
    void pop_back();
    void pop_front();
    bool empty();
    int size();
    void print();
};

const int hashMapSize = 100;
int string_to_int(string s);
void selection_sort(int * tab, int n, int choise);

class Map
{
public:
    List hashMap[hashMapSize];
    
    Map(){}
    
    void insert(string key, string value);
    void delet(string key);
    string find(string key);
    int getMaxListLen();
    int getMedianListLen();
};


int main(int argc, char ** argv)
{
    if (argv[1][0] == 't')
    {
        Map hashMap;
        assert ( hashMap.getMaxListLen() == 0);
        assert ( hashMap.getMedianListLen() == 0);
        hashMap.insert("Metcalfe","Elliot");
        hashMap.insert("Winter","Morgan");
        hashMap.insert("Savage","Rosie");
        hashMap.insert("Harper","Kate");
        hashMap.insert("Tomlinson","Gabriel");
        hashMap.insert("Bailey","Hollie");
        assert( hashMap.find("Metcalfe") == "Elliot");
        assert( hashMap.find("Winter") == "Morgan");
        assert( hashMap.find("Savage") == "Rosie");
        assert( hashMap.find("Harper") == "Kate");
        assert( hashMap.find("Tomlinson") == "Gabriel");
        assert( hashMap.find("Bailey") == "Hollie");
        assert ( hashMap.getMaxListLen() == 1);
        assert ( hashMap.getMedianListLen() == 0);
        hashMap.delet("Metcalfe");
        hashMap.delet("Winter");
        hashMap.delet("Savage");
         assert( hashMap.find("Metcalfe") == "-1");
        assert( hashMap.find("Winter") == "-1");
        assert( hashMap.find("Savage") == "-1");
        assert ( hashMap.getMaxListLen() == 1);
        assert ( hashMap.getMedianListLen() == 0);
        hashMap.delet("Harper");
        hashMap.delet("Tomlinson");
        hashMap.delet("Bailey");
        assert ( hashMap.getMaxListLen() == 0);
        assert ( hashMap.getMedianListLen() == 0);
    
        
        cout << "Wszystkie testy przeszly pomyslnie." << endl;
    }
    if (argv[1][0] == 'm')
    {
        Map hashMap;
        int n = 0;
        cin >> n;
        string kv;
        string keym;
        string valuem;
        for (int i = 0; i <= n; i++)
        {
            bool flag = false;
            getline(cin, kv);
            for (int j = 0; j < kv.length(); j++)
            {
                if ((kv[j] != ' ') && flag == false)
                {    keym += kv[j]; continue;   }
                if (kv[j] == ' ') j++;
                flag = true;
                if (flag == true)
                    valuem += kv[j];
            }
            if (!keym.empty() && !valuem.empty())
            hashMap.insert(keym, valuem);
            keym.clear();
            valuem.clear();
        }
        cout << "Dlugosc najdluzszej listy: " << hashMap.getMaxListLen()
             << "\nMediana: " << hashMap.getMedianListLen() << endl;
    }
    
    return 0;
}


int string_to_int(string s)
{
    int stringInASCII = 0;
    for(int i = 0; i < s.length(); i++)
    {stringInASCII += s[i];}
    return stringInASCII;
}

// ******************************* sortowanie ********************

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

//*************************** MAP METODY ******************************

void Map::insert(string key, string value)
{
    int index = string_to_int(key) % 100;
    this->hashMap[index].push_back(key,value);
}

void Map::delet(string key)
{
    int index = string_to_int(key) % 100;
    this->hashMap[index].remove(key);    
}

string Map::find(string key)
{
    int i = 0;
    bool ifn = false;
    int index = string_to_int(key) % 100;
    for (i = index; i < hashMapSize; i++)
    {
        if (this->hashMap[i].get(key) != "-1")
            return this->hashMap[i].get(key);
        if (i == hashMapSize-1)
            ifn = true;
    }
    if (ifn)
        for (i = 0; i < index; i++)
        {
            if (this->hashMap[i].get(key) != "-1")
                return this->hashMap[i].get(key);
        }
    cout << "Brak zadanego elementu w mapie! (-1)" << endl;
    return "-1";
}

int Map::getMaxListLen()
{
    int a = 0;
    int b = 0;
    for (int i = 0; i < hashMapSize; i++)
    {
        b = this->hashMap[i].size();
        a = (b >= a ? b : a);
    }
    return a;
}

int Map::getMedianListLen()
{
    int me = 0;
    int tabCount[hashMapSize];
    for (int i = 0; i < hashMapSize; i++)
    {
        tabCount[i] = this->hashMap[i].size();
    }
    selection_sort(tabCount, hashMapSize, 0);
    me = tabCount[hashMapSize/2];
    return me;
}
//******************* LIST METODY *********************
List::List()
{
    this->ptrList = nullptr;
}

List::~List()
{
    ListElement * temp;
    while(this->ptrList) 
    {
        temp = ptrList->ptr_next;
        delete ptrList;
        ptrList = temp;
    }
} 

void List::push_back(string surname, string name)
{
    ListElement * temp;
    
    if(this->ptrList == nullptr)
    {
        temp = new ListElement();
        temp->key = surname;
        temp->value = name;
        this->ptrList = temp;
    }
    else
    {    
        temp = this->ptrList;
        while(temp != nullptr) 
        {
            if (temp->ptr_next == nullptr)
                break;
            temp = temp->ptr_next;
        }
    temp->ptr_next = new ListElement();
    temp->ptr_next->key = surname;
    temp->ptr_next->value = name;
    temp->ptr_next->ptr_next = nullptr;
    }
}

void List::pop_front()
{
    if (this->ptrList == nullptr)
    {   cout << "Lista jest pusta!" << endl; return; }
    if (this->size() == 1)
    this->ptrList = nullptr;
    else
        this->ptrList = this->ptrList->ptr_next;
}

void List::pop_back()
{
    ListElement * temp;
    if (this->ptrList != nullptr)
    {
        if (this->size() == 1)
        {   this->ptrList = nullptr; return;    }
        
        temp = this->ptrList;
        while(temp->ptr_next->ptr_next != nullptr)
        {
            temp = temp->ptr_next;
        }
    }
    else
    {   cout << "Lista pusta!" << endl; return; }
    temp->ptr_next = nullptr;
}



bool List::empty()
{
    if (this->ptrList == nullptr)
        return true;
    else
        return false;
}

int List::size()
{
    ListElement * temp = new ListElement;
    int count = 0;
    if(this->ptrList != nullptr)
    {    
        temp = this->ptrList;
        while(temp != nullptr) 
        {
            temp = temp->ptr_next;
            count++;
        }
    }
    return count;
}

void List::remove(string surname)
{
    ListElement * temp;
    if (this->ptrList == nullptr)
    {   cout << "Lista pusta!" << endl;    return;   }
    if (this->ptrList->key == surname)
    {   this->pop_front(); return;   }
    else
    {    
        int i = 1;
        temp = this->ptrList;
        
        while(temp->ptr_next != nullptr) 
        {
            if (temp->ptr_next->key == surname)
            {
                if (i == this->size())
                    this->pop_back();
                break;
            }
            else
            {   temp = temp->ptr_next; i++; }
        }
        temp->ptr_next = temp->ptr_next->ptr_next;
    }
}

string List::get(string surname)
{
    string nam = "-1";
    ListElement * temp;
    if(this->ptrList != nullptr)
    {    
        temp = this->ptrList;
        while(temp != nullptr) 
        {
            if (temp->key == surname)
            {
                nam = temp->value;
                break;
            }
            temp = temp->ptr_next;
        }
    }
    else
    {return "-1";}
    return nam;
}

void List::print()
{    
    ListElement * temp;
    int i = 0;
    if(this->ptrList != nullptr)
    {    
        temp = this->ptrList;
        while(temp != nullptr) 
        {
            cout << "#" << i+1 
                 << " " << temp->key
                 << " " << temp->value 
                 << " " << endl;
            temp = temp->ptr_next;
            i++;
        }
    }
    else
        cout << "Lista pusta!" << endl;
}
