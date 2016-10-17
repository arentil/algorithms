//Marcin Zolubowski
//Lista podwojnie wiazana

#include <iostream>
#include <cassert>

using namespace std;


class ListElement
{
public:
    int element;
    ListElement * ptr_next;
    ListElement * ptr_back;
};

class List
{
public:
    ListElement * ptrList;
    List()
    {
        this->ptrList = nullptr;
    }
    
    ~List()
    {
        ListElement * temp;
		while(this->ptrList != nullptr) 
        {
			temp = ptrList->ptr_next;
			delete ptrList;
			ptrList = temp;
        }
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
    list.print();
    assert( list.empty() );
    list.print();
    cout << "Wszystkie testy pomyslnie zakonczone." << endl;

    return 0;
}

//******************* METODY KLASY LIST ******************

void List::push_front(int x)
{
    ListElement * temp = new ListElement;
    if (this->ptrList == nullptr)
    {
        temp->ptr_next = nullptr;
        temp->ptr_back = nullptr;
    }
    else
    {
        temp->ptr_next = this->ptrList;
        this->ptrList->ptr_back = temp;
    }
    
    temp->element = x;
    this->ptrList = temp;
}

void List::push_back(int x)
{
    ListElement * temp;
    if(this->ptrList != nullptr)
    {    
        temp = this->ptrList;
        while(temp != nullptr) 
        {
            if (temp->ptr_next == nullptr)
                break;
            temp = temp->ptr_next;
        }
    temp->ptr_next = new ListElement;
    temp->ptr_next->element = x;
    temp->ptr_next->ptr_next = nullptr;
    temp->ptr_next->ptr_back = temp;
    }
    else
        this->push_front(x);
    

}

int List::pop_front()
{
    if (this->ptrList == nullptr)
    {   cout << "Lista jest pusta! (-1)" << endl; return -1; }
    int x = this->ptrList->element;
    this->ptrList = this->ptrList->ptr_next;
    return x;
}

int List::pop_back()
{
    ListElement * temp;
    int x = 0;
    if (this->ptrList != nullptr)
    {
        temp = this->ptrList;
        while(temp->ptr_next->ptr_next != nullptr)
        {
            temp = temp->ptr_next;
        }
    x = temp->ptr_next->element;
    temp->ptr_next = nullptr;
    return x;
    }
    else
    {   cout << "Lista pusta! (-1)" << endl; return -1; }
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

void List::remove(int i)
{
    ListElement * temp;
    if (i > size() || i < 0 || this->ptrList == nullptr)
    {   cout << "Zadano zly indeks!" << endl;    return;   }
    if (i == 0)
        this->pop_front();
    else if (i == this->size())
        this->pop_back();
    else
    {    
        temp = this->ptrList;
        for(int j = 0; j < i-1; j++) 
        {		         
            temp = temp->ptr_next;
        } 
	    temp->ptr_next = temp->ptr_next->ptr_next;
        temp->ptr_back = temp;
    }
}

void List::insert(int x, int i)
{
	ListElement * temp;
	ListElement * tempNew;
	tempNew = new ListElement; 
	tempNew->element =x ;
	temp = this->ptrList;
	if(i > this->size()) return;	
	if(i < 0) return;
	if(i > 0) 
    {
		for(int j = 1; j < i; j++) 
        {
			temp=temp->ptr_next;
		}		
		tempNew->ptr_next=temp->ptr_next;
		temp->ptr_next = tempNew;
        temp->ptr_next->ptr_back = tempNew;
        tempNew->ptr_back = temp;
        
    }
}

int List::index_of(int x)
{
    ListElement * temp;
    int i = 0;
    if(this->ptrList != nullptr)
    {
        temp = this->ptrList;
        while(temp != nullptr) 
        {
            if (temp->element == x)
                return i;
            temp = temp->ptr_next;
            i++;
        }
        return -1;
    }
}

int List::get(int i)
{
    ListElement * temp = this->ptrList;
    if (i > size() || i <= 0 || this->ptrList == nullptr)
    {   cout << "Zadano zly indeks!" << endl;    return -1;   }
    int j = 0;
    if (i == 0)
        return temp->element;
    if(this->ptrList != nullptr)
    {    
        temp = this->ptrList;
        while (temp != nullptr)
        {
            temp = temp->ptr_next;
            j++;
            if (j == i)
            return temp->element;
        }
        return -1;
    }
}

void List::print()
{    
    ListElement * temp;
    int i = 0;
    cout << "\nLista podwojnie wiazana:" << endl;
    if(this->ptrList != nullptr)
    {    
        temp = this->ptrList;
        while(temp != nullptr) 
        {
            cout << "#" << i+1 << ": " << temp->element << " " << endl;
            i++;
            temp = temp->ptr_next;
        }
    }
}