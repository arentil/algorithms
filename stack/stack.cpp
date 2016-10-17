#include <iostream>
#include "stack.hpp"

using namespace std;



Stack::Stack()
{
    this->ptrStack = nullptr;
}

Stack::~Stack()
{
    StackElement * temp;
    while(this->ptrStack != nullptr) 
    {
        temp = ptrStack->ptr_next;
        delete ptrStack;
        ptrStack = temp;
    }
}

void Stack::push(int x)
{
    StackElement * temp = new StackElement;
    if (this->isEmpty())
        temp->ptr_next = nullptr;
    else
        temp->ptr_next = this->ptrStack;
    
    temp->number = x;
    this->ptrStack = temp;
} 

int Stack::pop()
{
    int temp;
    if (this->ptrStack == nullptr)
    {   cout << "Stack empty!(-1)" << endl; return -1;  }
    else
    {
        temp = this->ptrStack->number;
        this->ptrStack = this->ptrStack->ptr_next;
        return temp;
    }
}

bool Stack::isEmpty()
{
    if (this->ptrStack == nullptr)
        return true;
    else
        return false;
}

void Stack::print()
{
    StackElement * temp;
    int i = 0;
    if(this->ptrStack != nullptr)
    {    
        temp = this->ptrStack;
        while(temp != nullptr) 
        {
            cout << "#" << i+1 << " " << temp->number << " " << endl;
            i++;
            temp = temp->ptr_next;
        }
    }
    else
        return;
    cout << endl;
}

