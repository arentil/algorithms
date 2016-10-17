#ifndef stack_hpp
#define stack_hpp

class StackElement
{
public:
    int number;
    StackElement *ptr_next;
};

class Stack
{
    StackElement *ptrStack;
public:
    Stack();
    ~Stack();
    void push(int x);
    int pop();
    bool isEmpty();
    void print();
};

#endif