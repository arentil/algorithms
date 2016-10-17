//Marcin Zolubowski
//Lista implementowana tablicowo

#include <iostream>
#include <cassert>

using namespace std;

const int tabSize = 100000;

class List
{
    int tabList[tabSize];
    int nullPtrNode;
    
public:
    List()
    {
        for (int i = 0; i < tabSize; i++)
        {
            this->tabList[i] = 0;
        }
        this->nullPtrNode = 0;
    }
    
    void push_front(int x);
    void push_back(int x);
    int pop_front();
    int pop_back();
    bool empty();
    int size();
    void remove(int i);
    void insert(int x, int i);
    int index_of(int x);
    int get(int i);
    void print();
};

//********************* MAIN *****************************************************

int main()
{
    List list;
    
    assert( list.size() == 0 );
    assert( list.empty() );
    list.print();

    list.push_back(9);
    list.push_back(8);
    list.push_back(7);
    assert( list.size()==3 );
    list.print();

    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    assert( list.size()==6 );
    list.print();

    list.remove(10);
    list.remove(-3);
    assert( list.size()==6 );
    assert( list.index_of(9)==3 );

    list.remove( list.index_of(9) );
    assert( list.index_of(9)==-1 );
    list.print();
    assert( list.size()==5 );

    list.insert(100, 2);
    assert(list.index_of(100) == 2);
    assert(list.get(2) == 100);
    list.print();

    assert( list.pop_front() == 1 );
    assert( list.pop_front() == 2 );
    assert( list.pop_back() == 7 );
    assert( list.pop_back() == 8 );
    assert( list.size() == 2 );
    list.print();

    assert( list.pop_front() == 100 );
    list.remove(0);
    assert( list.empty() );
    list.print();
    cout << "Wszystkie testy pomyslnie zakonczone." << endl;
    return 0;
}

//******************* METODY KLASY LIST *******************************************

void List::push_front(int x)
{
    if (this->nullPtrNode == tabSize)
    { cout << "Lista pelna!" << endl; return;   }
    
    this->nullPtrNode++;
    for (int i = this->nullPtrNode-1; i >= 0; i--)
    {
        this->tabList[i+1] = this->tabList[i];
    }
    this->tabList[0] = x;
}

void List::push_back(int x)
{
    if (this->nullPtrNode == tabSize)
    { cout << "Lista pelna!" << endl; return;   }
    
    this->nullPtrNode++;
    this->tabList[this->nullPtrNode-1] = x;
}

int List::pop_front()
{
    if(this->nullPtrNode == 0)
    { cout << "Lista pusta!" << endl; return -1;}
    else if(this->nullPtrNode == tabSize)
    { cout << "Lista pelna!" << endl; return -1;}
    
    int temp = this->tabList[0];
    for (int i = 0; i < this->nullPtrNode; i++)
    {
        this->tabList[i] = this->tabList[i+1];
    }
    this->nullPtrNode--;
    return temp;
}

int List::pop_back()
{
    if(this->nullPtrNode == 0)
    { cout << "Lista pusta!" << endl; return -1;}

    this->nullPtrNode--;
    return this->tabList[this->nullPtrNode];
}

bool List::empty()
{
    if (this->nullPtrNode == 0)
        return true;
    else
        return false;
}

int List::size()
{
    return this->nullPtrNode;
}

void List::remove(int i)
{
    if (this->nullPtrNode == 0)
    { cout << "Lista pusta!" << endl; return;}
    if (i < 0 || i >= nullPtrNode)
    { cout << "Indeks poza zakresem!" << endl; return;  }
    
    for (int j = i; j < this->nullPtrNode; j++)
        this->tabList[j] = this->tabList[j+1];
    this->nullPtrNode--;
}

void List::insert(int x, int i)
{
    if (i < 0 || i > this->nullPtrNode)
    { cout << "Indeks poza zakresem!" << endl; return;}
    if(this->nullPtrNode == tabSize)
    { cout << "Lista pelna!" << endl; return;   }

    this->nullPtrNode++;
    for (int j = this->nullPtrNode-1; j >= i; j--)
    {
        this->tabList[j+1] = this->tabList[j];
    }
    this->tabList[i] = x;
}    

int List::index_of(int x)
{
    for (int i = 0; i < this->nullPtrNode; i++)
    {
        if (this->tabList[i] == x)
            return i;
    }
    return -1;
        
}

int List::get(int i)
{
    if (i < 0 || i >= this->nullPtrNode)
    {   cout << "Indeks poza zakresem!" << endl; return -1; }
    return this->tabList[i];
}

void List::print()
{
    cout << "Lista:\n";
    if (this->nullPtrNode != 0)
    {
        for (int i = 0; i < this->nullPtrNode; i++)
        {
            cout << "#" << i << ": " << this->tabList[i] << endl;
        }
    }
    else
    {   cout << "Lista jest pusta!" << endl; return; }
}
