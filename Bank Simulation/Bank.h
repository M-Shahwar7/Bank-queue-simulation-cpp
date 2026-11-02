#ifndef BANK_H
#define BANK_H

struct Customer {
    int id;
    int arrivalTime;
    int serviceTime;
};

struct Node {
    Customer data;
    Node* next;
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue();
    ~Queue();

    void enqueue(Customer c);
    Customer dequeue();
    bool isEmpty();
    void display();
    void clear();
};


class BankSimulation {
private:
    Queue line;
    int totalCustomers;

    int arrivalGap(int id);
    int serviceTimeOf(int id);

public:
    BankSimulation();
    void run();
};

#endif