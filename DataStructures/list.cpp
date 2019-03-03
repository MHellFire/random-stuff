#include <iostream>

#include "list.hpp"

using namespace std;

List::List()
{
}

List::~List()
{
}

void List::run()
{
    short int choice;

    do
    {
        showList();


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
            //push();
            break;

        case 2:
            //pop();
            break;

        case 3:
            //getSize();
            break;

        case 4:
            //isEmpty();
            break;

        default:
            break;
        }
    }
    while (choice != 5);
}

void List::showList()
{
    system("clear");

    cout << "---------------------------" << endl;
    cout << " ZAWARTOSC LISTY: " << endl;
    cout << "---------------------------" << endl;

    for (std::list<float>::iterator i=listData.begin(); i!=listData.end(); ++i)
        cout << *i << " ";

    cout << endl << "---------------------------" << endl << endl;
}
