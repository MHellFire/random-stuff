#include <iostream>
#include <unistd.h>
#include "stack.hpp"

using namespace std;
Stack::Stack()
{
    stackSize = 0;
}

Stack::~Stack()
{
}

void Stack::run(void)
{
    short int choice;

    do
    {
        showStack();

        cout << "MENU GLOWNE STOSU:" << endl;
        cout << "------------------------------------------" << endl;
        cout << "1. PUSH (dodaje element na szczyt stosu)" << endl;
        cout << "2. POP (usuwa element ze szczytu stosu)" << endl;
        cout << "3. SIZE (ile elementow na stosie?)" << endl;
        cout << "4. EMPTY (czy stos jest pusty?)" << endl;
        cout << "5. Wyjscie" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Wybor: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            push();
            break;

        case 2:
            pop();
            break;

        case 3:
            getSize();
            break;

        case 4:
            isEmpty();
            break;

        default:
            break;
        }
    }
    while (choice != 5);
}

void Stack::showStack()
{
    system("clear");

    cout << "----------------" << endl;
    cout << "ZAWARTOSC STOSU:" << endl;
    cout << "----------------" << endl;

    if (stackSize == 0)
        cout << "pusty" << endl;
    else
        for (int i=stackSize-1; i>=0; i--)
            cout << stack[i] << endl;

    cout << "----------------" << endl << endl;
}

void Stack::push()
{
    if (stackSize>=MAX)
    {
        cout << endl << "Stos pelny!";
        cout << flush;
        sleep(1);
    }
    else
    {
        cout << endl << "PUSH (jaka liczbe polozyc na stosie): ";

        cin >> stack[stackSize++];
    }
}

void Stack::pop()
{
    if (stackSize>0)
    {
        cout << endl << "POP (liczba zostanie usunieta ze stosu): " << stack[--stackSize];
        cout << flush;
        sleep(2);
    }
    else
    {
        cout << endl << "Stos pusty!";
        cout << flush;
        sleep(1);
    }
}

void Stack::getSize()
{
    cout << endl << "Liczba elementow na stosie: " << stackSize;

    cout << flush;
    sleep(2);
}

void Stack::isEmpty()
{
    if (stackSize == 0)
        cout << endl << "EMPTY (stos pusty?) ->  TRUE";
    else
        cout << endl << "EMPTY (stos pusty?) ->  FALSE";

    cout << flush;
    sleep(2);
}
