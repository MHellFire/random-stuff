#include <iostream>
#include <unistd.h>

#include "queue.hpp"

using namespace std;
Queue::Queue()
{
    queueSize = 0;
    front = 0;
    rear = 0;
}

Queue::~Queue()
{
}

void Queue::run()
{
    short int choice;

    do
    {
        showQueue();

        cout << "glowa=" << front << "   ogon=" << rear << "   ile=" << queueSize << endl << endl;

        cout << "MENU GLOWNE KOLEJKI:" << endl;
        cout << "------------------------------------------" << endl;
        cout << "1. PUSH (dodaje element na koniec kolejki)" << endl;
        cout << "2. POP (usuwa element z poczatku kolejki)" << endl;
        cout << "3. SIZE (ile elementow na kolejce?)" << endl;
        cout << "4. EMPTY (czy kolejka jest pusty?)" << endl;
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

void Queue::showQueue()
{
    system("clear");

    cout << "------------------" << endl;
    cout << "ZAWARTOSC KOLEJKI:" << endl;
    cout << "------------------" << endl;

    if (queueSize == 0)
        cout << "pusta";
    else
    {
        int j;

        for (int i=0; i<queueSize; ++i)
        {
            front+i>=5 ? j=front+i-5 : j=front+i;
            cout << queue[j] << " ";
        }
    }

    cout << endl << "-----------------" << endl << endl;
}

void Queue::push()
{
    if (queueSize >= MAX)
    {
        cout << endl << "Kolejka pelna!";
        cout << flush;
        sleep(1);
    }
    else
    {
        cout << endl << "PUSH (jaka liczbe wstawic do kolejki): ";

        cin >> queue[rear];

        rear = (rear+1)%5;
        queueSize++;
    }

}

void Queue::pop()
{
    if (queueSize>0)
    {
        cout << endl << "POP (liczba zostanie usunieta z kolejki): " << queue[front];
        front = (front+1)%5;
        queueSize--;
        cout << flush;
        sleep(2);
    }
    else
    {
        cout << endl << "Kolejka jest pusta!";
        cout << flush;
        sleep(1);
    }
}

void Queue::getSize()
{
    cout << endl << "Liczba elementow kolejce: " << queueSize;

    cout << flush;
    sleep(2);
}

void Queue::isEmpty()
{
    if (queueSize == 0)
        cout << endl << "EMPTY (kolejka pusta?) ->  TRUE";
    else
        cout << endl << "EMPTY (kolejka pusta?) ->  FALSE";

    cout << flush;
    sleep(2);
}
