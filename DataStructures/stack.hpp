#ifndef STACK_HPP
#define STACK_HPP

#define MAX 5

class Stack
{
    public:
        Stack();
        ~Stack();

        void run();

    protected:

    private:
        int stack[MAX];
        int stackSize;

        void showStack();
        void push();
        void pop();
        void getSize();
        void isEmpty();
};

#endif // STACK_HPP
