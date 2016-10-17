// Marcin Zolubowski
// Kalkulator ONP

#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include "stack.hpp"

using namespace std;

int solveRPN(Stack stackRPN, string c);

int main()
{
    Stack stack;
    
    assert( stack.isEmpty() );
    stack.print();

    stack.push(9);
    stack.push(8);
    stack.push(7);
    stack.print();

    stack.push(3); 
    stack.push(2);
    stack.push(1);
    assert( stack.isEmpty() == false );
    stack.print();

    assert(stack.pop() != 9);
    assert(stack.pop() == 2);
    stack.print();

    assert(stack.pop() == 3);
    assert((stack.pop() + stack.pop()) == 15);
    stack.print();
    
    stack.push(9);
    assert((stack.pop() * stack.pop()) == 81);
    stack.print();
    
    stack.push(20);
    stack.push(25);
    assert((stack.pop() - stack.pop()) == 5);
    stack.print();
    
    stack.push(10);
    stack.push(5);
    assert((pow(stack.pop(), stack.pop())) == 100000 );
    stack.print();
    
    stack.push(4);
    stack.push(20);
    assert((stack.pop() / stack.pop()) == 5);
    stack.print();
    assert(stack.isEmpty());
    stack.print();

    cout << "Wszystkie testy przeszly pomyslnie." << endl;

    Stack resultStack;
    string stringRPN;
    int count = 0;
    
    cout << "Podaj dzialania, na koncu linii \"=\". Zakoncz wczytywanie pusta linia:" << endl;
    getline(cin, stringRPN);
    while (!stringRPN.empty())
    {
        if (stack.isEmpty())
            resultStack.push(solveRPN(stack, stringRPN));
        else
            cout << "Uwaga! Stos nie jest pusty! Zle dzialanie!" << endl;
        count++;
        getline(cin, stringRPN);
    }
    int * resultTab = new int[count];
    for(int i = count-1; i >= 0; i--)
    {
        resultTab[i] = resultStack.pop();
    }
    for (int i = 0; i < count; i++)
        cout << resultTab[i] << endl;

    return 0;
}


int solveRPN(Stack stackRPN, string c)
{
        
    int a1,a2;
    int node = 0;
    int x = 0;
    
    while (true)
    {
        string temp;
        
        if (c[node] == '=')
            break;
        while (c[node] != ' ')
        {temp += c[node]; node++;}
        node++;
        
        if (temp == "+")
        {a1 = stackRPN.pop();    a2 = stackRPN.pop();    stackRPN.push(a2+a1);}
        else if (temp == "-")
        {a1 = stackRPN.pop(); a2 = stackRPN.pop(); stackRPN.push(a2-a1);}
        else if (temp == "*")
        {a1 = stackRPN.pop(); a2 = stackRPN.pop(); stackRPN.push(a2*a1);}
        else if (temp == "/")
        {a1 = stackRPN.pop(); a2 = stackRPN.pop(); stackRPN.push(a2/a1);}
        else if (temp == "^")
        {a1 = stackRPN.pop(); a2 = stackRPN.pop(); stackRPN.push(pow(a2,a1));}
        else if (temp == "~")
        {stackRPN.push(-(stackRPN.pop()));}
        else
        {stackRPN.push(stoi(temp));}
    }
    x = stackRPN.pop();
    if (stackRPN.isEmpty())
        return x;
    else
    {cout << "Za malo operatorow! (404)" << endl; return 404;}
}