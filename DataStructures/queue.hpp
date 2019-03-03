#ifndef QUEUE_HPP
#define QUEUE_HPP

#define MAX 5

class Queue
{
    public:
        Queue();
        ~Queue();

        void run();

    protected:

    private:
        int queue[MAX];
        int queueSize;
        int front, rear;

        void showQueue();
        void push();
        void pop();
        void getSize();
        void isEmpty();
};

#endif // QUEUE_HPP
