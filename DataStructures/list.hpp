#ifndef LIST_HPP
#define LIST_HPP

#include <list>

class List
{
    public:
        List();
        ~List();

        void run();

    protected:

    private:
        std::list <float> listData;

        void showList();
};

#endif // LIST_HPP
