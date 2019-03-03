#include <iostream>
#include <cstdlib>

#include "stack.hpp"
#include "queue.hpp"
#include "list.hpp"

using namespace std;

int main()
{
    short int choice;

    do
    {
        std::system("clear");

        cout << "Aplikacja prezentujaca zasade dzialania podstawowych struktur danych w C++." << endl << endl;

        cout << "Wybierz strukture:" << endl;
        cout << "------------------------------------------" << endl;
        cout << "1. Stos (stack)" << endl;
        cout << "2. Kolejka (queue)" << endl;
        cout << "3. Lista (list)" << endl;
        cout << "4. Drzewo binarne (binary tree)" << endl;
        cout << "5. Zakoncz program" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Wybor: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            {
                Stack stack;
                stack.run();
            }
            break;

        case 2:
            {
                Queue queue;
                queue.run();
            }
            break;

        case 3:
            {
                List list;
                list.run();
            }
            break;

        case 4:
            break;

        default:
            break;
        }
    }
    while (choice !=5);

    return 0;
}
