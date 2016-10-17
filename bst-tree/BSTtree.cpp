// Marcin Zolubowski
// Implementacja binarnego drzewa przeszukan


#include <iostream>
#include <string>
using namespace std;


class ListElement
{
public:
    int element;
    ListElement *ptr_next;
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
		while(this->ptrList) 
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

class Node
{
public:
    int key;
    Node * parent;
    Node * left;
    Node * right;
    
    Node(int a) : key(a)
    {
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};


class BstTree
{
public:
    Node * root;
    
    BstTree()
    {
        this->root = nullptr;
    }
    
    void insert(int number);
    Node * search(Node * node, int x);
    void delete_node(Node * node);
    int minimum();
    int maximum();
    void inorder_print();
    
    Node * successor(Node * node); 
    //szukanie nastepnika inorder pomocniczo do delete_node
};


int main()
{
    char letter = 'a';
    int number;
    string in;
    string num;
    
    cout << "Program z implementacja drzewa BST." << endl;
    cout << "Podaj komende w postaci \"litera + liczba\": " << endl;

    
    getline(cin, in);
    letter = in[0];
    if (in.size() > 1)
    {
        for (int i = 2; i < in.size(); i++)
        num += in[i];
        number = stoi(num);
    }
    
    BstTree bst;
    while (letter != 'q')
    {
        switch(letter)
        {
            case 'w':
                bst.insert(number);
                break;
            case 'u':
                bst.delete_node(bst.search(bst.root,number));
                break;
            case 'M':
                cout << "Max: " << bst.maximum() << endl;
                break;
            case 'm':
                cout << "Min: " << bst.minimum() << endl;
                break;
            case 'i':
                bst.inorder_print();
                break;
            default:
                cout << "Wpisales zla komende." << endl;
                break;
        }
        
        num.clear();
        getline(cin, in);
        letter = in[0];
        if (in.size() > 1)
        {
            for (int i = 2; i < in.size(); i++)
                num += in[i];
            number = stoi(num);
        }
    }
    cout << "Koncze program..." << endl;
    
    return 0;
}

// ******************* BstTree METHODS **********************

void BstTree::insert(int number)
{
    Node * exist = this->search(this->root, number);
    if (exist != nullptr)
        return;
    
    Node * newNode = new Node(number);
    Node * x = this->root;
    Node * y = nullptr;
    
    while (x != nullptr)
    {
        y = x;
        if (newNode->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    
    newNode->parent = y;
    
    if (y == nullptr)
        this->root = newNode;
    else
    {
        if (newNode->key < y->key)
            y->left = newNode;
        else
            y->right = newNode;
    }
}

Node * BstTree::search(Node * node, int x)
{
    Node * temp = node;
    if (temp == nullptr || temp->key == x)
        return temp;
    if (x < temp->key)
        return search(temp->left,x);
    return search(temp->right,x);
}

void BstTree::delete_node(Node * node)
{
    if (node == nullptr)
        return;
    Node * x = nullptr;
    Node * y = nullptr;
    if ((node->left == nullptr) || (node->right == nullptr))
        y = node;
    else
        y = successor(node);
    
    if (y->left != nullptr)
        x = y->left;
    else
        x = y->right;
    
    if (x != nullptr)
        x->parent = y->parent;
    if (y->parent == nullptr)
        this->root = x;
    else
    {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    if (y != node)
        node->key = y->key;
}

int BstTree::minimum()
{
    Node * temp = this->root;
    while (temp->left != nullptr)
    {
        temp = temp->left;
    }
    return temp->key;
}

int BstTree::maximum()
{
    Node * temp = this->root;
    while (temp->right != nullptr)
    {
        temp = temp->right;
    }
    return temp->key;
}

void BstTree::inorder_print()
{
    Stack stack;
    List list;
    int tempKey;
    Node * temp = this->root;
    if (temp == nullptr)
    {   cout << "BST is empty." << endl; return; }
    
    while (!stack.isEmpty() || temp != nullptr)
    {
        if (temp != nullptr)
        {
            stack.push(temp->key);
            temp = temp->left;
        }
        else
        {
            tempKey = stack.pop();
            list.push_back(tempKey);
            temp = this->search(this->root, tempKey);
            temp = temp->right;
        }
    }
    cout << "BST Tree inorder content:" << endl;
    list.print();
}



Node * BstTree::successor(Node * node)
{
    Node * temp = node;
    if (temp->right != nullptr)
    {
        temp = temp->right;
        while (temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp;
    }
    
    Node * node_tmp = temp->parent;
    while (node_tmp != nullptr && node_tmp->left != temp)
    {
        temp = node_tmp;
        node_tmp = node_tmp->parent;
    }
    return node_tmp;
}


// ------- POMOCNICZE STRUKTURY --------------
//*********************** Stack METHODS *************************
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

// ************************* List(linked) METHODS *********************
void List::push_front(int x)
{
    ListElement * temp = new ListElement;
    if (this->ptrList == nullptr)
        temp->ptr_next = nullptr;
    else
        temp->ptr_next = this->ptrList;
    
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
    }
    else
    {   cout << "Lista pusta! (-1)" << endl; return -1; }
    x = temp->ptr_next->element;
    temp->ptr_next = nullptr;
    return x;
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
		temp->ptr_next=tempNew;
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
    if(this->ptrList != nullptr)
    {    
        temp = this->ptrList;
        while(temp != nullptr) 
        {
            cout << temp->element;
            if (temp->ptr_next != nullptr)
                cout << " ";
            i++;
            temp = temp->ptr_next;
        }
    }
    cout << endl;
}
