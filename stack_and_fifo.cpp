//Kamil W³odarczyk
#include <iostream>

using namespace std;

enum class EXCEPTION_CODE
{
    arrayEmpty,
};

void seeExceptions(EXCEPTION_CODE error)
{
    switch (error) {
    case EXCEPTION_CODE::arrayEmpty:
        std::cerr << "Lista jest pusta!" << std::endl;
        break;
    default:
        std::cerr << "Nieznany blad!";
        break;
    }
}

//Zadanie 6.1
class ArrayStack {
private:
    int* items;
    int capacity;        //pojemnoœæ stosu
    int sp;                //wierzcho³ek stosu
public:
    ArrayStack(int c)    //tworzy pusty stos o pojemnoœci c
    {
        items = new int[c];
        capacity = c;
        sp = -1;
    }
    bool empty()        //sprawdza czy stos jest pusty
    {
        if (sp == -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool full()     //sprawdza czy stos jest pelny
    {
        if (sp == capacity-1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool push(int x)        //dodaje element na szczyt stosu
    {
        if (full())
        {
            return false;
        }
        else
        {
            sp++;
            items[sp] = x;
            return true;
        }
    }
    int top()            //zwraca dan¹ ze stosu
    {
        if (empty())
        {
            throw EXCEPTION_CODE::arrayEmpty;
        }
        return items[sp];
    }
    bool pop()            //usuwa dan¹ ze stosu
    {
        if (empty())
        {
            return false;
        }
        else
        {
            items[sp] = NULL;
            sp--;
            return true;
        }
    }
    void clear()        //usuwa stos
    {
        if (empty())
        {
            throw EXCEPTION_CODE::arrayEmpty;
        }
        delete[]items;
        items = new int[capacity];
        sp = -1;
    }
    friend std::ostream& operator<<(std::ostream& out, ArrayStack& s);    //wyœwietla ca³¹ zawartoœæ stosu
    ~ArrayStack()
    {
        delete[]items;
    }
};
ostream& operator<< (ostream& out, ArrayStack& l)
{
    for (int i = 0; i <= l.sp; i++)
    {
        out << l.items[i] << ' ';
    }
    return out;
}

//Zadanie 6.2
class Element {
private:
    int v;
    Element* next;
public:
    Element(int x, Element* next)
    {
        this->setNext(next);
        v = x;
    }
    int getValue()
    {
        return v;
    }
    Element* getNext()
    {
        return next;
    }
    void setNext(Element* p)
    {
        next = p;
    }
};

class LinkedStack {
private:
    Element* sp;
public:
    LinkedStack()        //tworzy pusty stos
    {
        sp = NULL;
    }
    bool empty()        //sprawdza czy stos jest pusty
    {
        if (sp)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    void push(int x)        //dodaje element na szczyt stosu
    {
        Element* tmp = new Element(x, sp);
        sp = tmp;
    }
    int top()            //zwraca dan¹ ze stosu
    {
        if (empty())
        {
            throw EXCEPTION_CODE::arrayEmpty;
        }
        return sp->getValue();
    }    
    bool pop()           //usuwa element ze stosu
    {
        if (empty())
        {
            return false;
        }
        else
        {
            sp = sp->getNext();
            return true;
        }
    }
    void clear()        //usuwa stos
    {
        while (!empty())
        {
            pop();
        }
    }
    friend std::ostream& operator<<(std::ostream& out, LinkedStack* s); //wyœwietla zawartoœæ ca³ego stosu
    ~LinkedStack()
    {
        clear();
        delete sp;
    }
};
ostream& operator<< (ostream& out, LinkedStack* s)
{
    LinkedStack* tmp = new LinkedStack(*s);
    while (!tmp->empty())
    {
        out << tmp->top() << ' ';
        tmp->pop();
    }
    return out;
}

//Zadanie 6.3
class ArrayFifo {
private:
    int* items;
    int capacity;            //pojemnoœæ kolejki
    int size;                //rozmiar kolejki (liczba elementów w kolejce)
    int head;
    int tail;
public:
    ArrayFifo(int c)        //tworzy pust¹ kolejkê o pojemnoœci c
    {
        items = new int[c];
        capacity = c;
        size = 0;
        head = 0;
        tail = -1;
        for (int i = 0; i < capacity; i++)
        {
            items[i] = NULL;
        }
    }
    bool empty()        //sprawdza czy kolejka jest pusta
    {
        if (size == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool full()     //sprawdza czy kolejka jest pelna
    {
        if (size == capacity)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool enqueue(int x)     //dodaje element do kolejki
    {
        if (full())
        {
            return false;
        }
        if (tail == capacity-1)
        {
            items[0] = x;
        }
        else
        {
            items[tail + 1] = x;
            tail++;
        }
        size++;
        return true;
    }
    int peek()      //zwraca wartosc pierwszego elementu w kolejce
    {
        if (empty())
        {
            throw EXCEPTION_CODE::arrayEmpty;
        }
        return items[head];
    }
    bool dequeue()        //usuwa dan¹ z kolejki
    {
        if (empty())
        {
            return false;
        }
        items[head] = NULL;
        if (head == capacity - 1)
        {
            head = 0;
        }
        else
        {
            head++;
        }
        size--;
        return true;
    }
    void clear()        //usuwa kolejke
    {
        if (empty())
        {
            throw EXCEPTION_CODE::arrayEmpty;
        }
        delete[]items;
        items = new int[capacity];
        size = 0;
        head = 0;
        tail = -1;
        for (int i = 0; i < capacity; i++)
        {
            items[i] = NULL;
        }
    }
    friend std::ostream& operator<<(std::ostream& out, ArrayFifo& f);    //wyœwietla zawartoœæ kolejki (od head do tail)
    ~ArrayFifo()
    {
        delete[]items;
    }
};
ostream& operator<< (ostream& out, ArrayFifo& f)
{
    int counter = -1;
    for (int i = f.head; i < (f.head + f.size); i++)
    {
        counter = i % f.capacity;
        if (f.items[counter] != NULL)
        {
            out << f.items[counter] << ' ';
        }
    }

    return out;
}

//Zadanie 6.4
class LinkedFifo {
private:
    Element* head;
    Element* tail;
public:
    LinkedFifo()        //tworzy pusta kolejke
    {
        head = NULL;
        tail = NULL;
    }
    Element* getHead()  //zwraca head
    {
        return head;
    }
    bool empty()    //sprawdza czy kolejka jest pusta
    {
        if (head)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    void enqueue(int x)     //dodaje element do kolejki
    {
        Element* tmp = new Element(x, NULL);
        if (empty())
        {
            head = tmp;
        }
        else
        {
            tail->setNext(tmp);
        }
        tail=tmp;
    }
    int peek()                //zwraca dan¹ z kolejki
    {
        if (empty())
        {
            throw EXCEPTION_CODE::arrayEmpty;
        }
        else
        {
            return head->getValue();
        }
    }
    bool dequeue()            //usuwa dan¹ z kolejki
    {
        if (empty())
        {
            return false;
        }
        else
        {
            Element* tmp = head;
            head = head->getNext();
            delete tmp;
            return true;
        }
    }
    void clear()        //usuwa kolejke
    {
        if (empty())
        {
            throw EXCEPTION_CODE::arrayEmpty;
        }
        while (!empty())
        {
            dequeue();
        }
    }
    friend std::ostream& operator<<(std::ostream& out, LinkedFifo* f);    //wyœwietla zawartoœæ kolejki (od head do tail)
    ~LinkedFifo()
    {
        clear();
        delete head;
        delete tail;
    }
};
ostream& operator<< (ostream& out, LinkedFifo* f)
{
    Element* tmp = f->getHead();
    while (tmp)
    {
        out << tmp->getValue() << ' ';
        tmp = tmp->getNext();
    }
    return out;
}

int main()
{
    try
    {
        //Zadanie 6.1 - test
        
        cout << endl << "Zadanie 6.1 - test" << endl;
        ArrayStack s(6);
        cout << endl << "empty(): 1 - " << s.empty();                                       //sprawdza dzialanie metody empty()
        cout << endl << "pop(): 0 - " << s.pop();                                           //sprawdza dzialanie metody pop()
        cout << endl << "push(4): 4 - "; s.push(4); cout << " " << s;                       //sprawdza dzialanie metody push()
        cout << endl << "push(1): 4 1 - "; s.push(1); cout << " " << s;                     //sprawdza dzialanie metody push()
        cout << endl << "push(5): 4 1 5 - "; s.push(5); cout << " " << s;                   //sprawdza dzialanie metody push()
        cout << endl << "push(2): 4 1 5 2 - "; s.push(2); cout << " " << s;                 //sprawdza dzialanie metody push()
        cout << endl << "push(7): 4 1 5 2 7 - "; s.push(7); cout << " " << s;               //sprawdza dzialanie metody push()
        cout << endl << "push(6): 4 1 5 2 7 6 - "; s.push(6); cout << " " << s;             //sprawdza dzialanie metody push()
        cout << endl << "full(): 1 - " << s.full();                                         //sprawdza dzialanie metody full()
        cout << endl << "push(4): 0 - " << s.push(4);                                       //sprawdza dzialanie metody push()
        cout << endl << "pop(): 4 1 5 2 7 - "; s.pop(); cout << " " << s;                   //sprawdza dzialanie metody pop()
        cout << endl << "top(): 7 - " << s.top();                                           //sprawdza dzialanie metody top()
        cout << endl << "clear(), empty(): 1 - "; s.clear(); cout << s.empty();             //sprawdza dzialanie metody clear() oraz empty()
        

        //Zadanie 6.2 - test
        
        cout << endl << "Zadanie 6.2 - test" << endl;
        LinkedStack* s1 = new LinkedStack();
        cout << endl << "empty(): 1 - " << s1->empty();                                      //sprawdza dzialanie metody empty()
        cout << endl << "pop(): 0 - " << s1->pop();                                          //sprawdza dzialanie metody pop()
        cout << endl << "push(4): 4 - "; s1->push(4); cout << " " << s1;                      //sprawdza dzialanie metody push()
        cout << endl << "push(1): 1 4 - "; s1->push(1); cout << " " << s1;                    //sprawdza dzialanie metody push()
        cout << endl << "push(5): 5 1 4 - "; s1->push(5); cout << " " << s1;                  //sprawdza dzialanie metody push()
        cout << endl << "push(2): 2 5 1 4 - "; s1->push(2); cout << " " << s1;                //sprawdza dzialanie metody push()
        cout << endl << "push(7): 7 2 5 1 4 - "; s1->push(7); cout << " " << s1;              //sprawdza dzialanie metody push()
        cout << endl << "push(6): 6 7 2 5 1 4 - "; s1->push(6); cout << " " << s1;            //sprawdza dzialanie metody push()
        cout << endl << "empty(): 0 - " << s1->empty();                                      //sprawdza dzialanie metody empty()
        cout << endl << "pop(): 7 2 5 1 4 - "; s1->pop(); cout << " " << s1;                  //sprawdza dzialanie metody pop()
        cout << endl << "top(): 7 - " << s1->top();                                          //sprawdza dzialanie metody top()
        cout << endl << "clear(), empty(): 1 - "; s1->clear(); cout << s1->empty();           //sprawdza dzialanie metody clear() oraz empty()
        

        //Zadanie 6.3 - test
        
        cout << endl << "Zadanie 6.3 - test" << endl;
        ArrayFifo f(6);
        cout << endl << "empty(): 1 - " << f.empty();                                       //sprawdza dzialanie metody empty()
        cout << endl << "dequeue(): 0 - " << f.dequeue();                                   //sprawdza dzialanie metody dequeue()
        cout << endl << "enqueue(4): 4 - "; f.enqueue(4); cout << f;                        //sprawdza dzialanie metody enqueue()
        cout << endl << "enqueue(1): 4 1 - "; f.enqueue(1); cout << f;                      //sprawdza dzialanie metody enqueue()
        cout << endl << "enqueue(5): 4 1 5 - "; f.enqueue(5); cout << f;                    //sprawdza dzialanie metody enqueue()
        cout << endl << "enqueue(2): 4 1 5 2 - "; f.enqueue(2); cout << f;                  //sprawdza dzialanie metody enqueue()
        cout << endl << "enqueue(7): 4 1 5 2 7 - "; f.enqueue(7); cout << f;                //sprawdza dzialanie metody enqueue()
        cout << endl << "enqueue(6): 4 1 5 2 7 6 - "; f.enqueue(6); cout << f;              //sprawdza dzialanie metody enqueue()
        cout << endl << "full(): 1 - " << f.full();                                         //sprawdza dzialanie metody full()
        cout << endl << "enqueue(4): 0 - " << f.enqueue(4);                                 //sprawdza dzialanie metody enqueue()
        cout << endl << "dequeue(): 1 5 2 7 6 - "; f.dequeue(); cout << f;                  //sprawdza dzialanie metody dequeue()
        cout << endl << "peek(): 1 - " << f.peek();                                         //sprawdza dzialanie metody peek()
        cout << endl << "clear(), empty(): 1 - "; f.clear(); cout << f.empty();             //sprawdza dzialanie metody clear() oraz empty()
        

        //Zadanie 6.4 - test
        
        cout << endl << "Zadanie 6.4 - test" << endl;
        LinkedFifo* f1 = new LinkedFifo();
        cout << endl << "empty(): 1 - " << f1->empty();                                      //sprawdza dzialanie metody empty()
        cout << endl << "dequeue(): 0 - " << f1->dequeue();                                  //sprawdza dzialanie metody dequeue()
        cout << endl << "enqueue(4): 4 - "; f1->enqueue(4); cout << f1;                       //sprawdza dzialanie metody enqueue()
        cout << endl << "enqueue(1): 4 1 - "; f1->enqueue(1); cout << f1;                     //sprawdza dzialanie metody enqueue()
        cout << endl << "enqueue(5): 4 1 5 - "; f1->enqueue(5); cout << f1;                   //sprawdza dzialanie metody enqueue()
        cout << endl << "enqueue(2): 4 1 5 2 - "; f1->enqueue(2); cout << f1;                 //sprawdza dzialanie metody enqueue()
        cout << endl << "enqueue(7): 4 1 5 2 7 - "; f1->enqueue(7); cout << f1;               //sprawdza dzialanie metody enqueue()
        cout << endl << "enqueue(6): 4 1 5 2 7 6 - "; f1->enqueue(6); cout << f1;             //sprawdza dzialanie metody enqueue()
        cout << endl << "dequeue(): 1 5 2 7 6 - "; f1->dequeue(); cout << f1;                 //sprawdza dzialanie metody dequeue()
        cout << endl << "peek(): 1 - " << f1->peek();                                        //sprawdza dzialanie metody peek()
        cout << endl << "clear(), empty(): 1 - "; f1->clear(); cout << f1->empty();           //sprawdza dzialanie metody clear() oraz empty()
        cout << endl << "dequeue(): 0 - " << f1->dequeue();                                  //sprawdza dzialanie metody dequeue()
    }
    catch (EXCEPTION_CODE error)
    {
        seeExceptions(error);
    }
    return 0;
}