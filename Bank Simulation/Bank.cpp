#include <iostream>
#include "Bank.h"
using namespace std;


Queue::Queue() {
    front = nullptr;
    rear = nullptr;
}

Queue::~Queue() {
    clear();
}

void Queue::enqueue(Customer c) {
    Node* newNode = new Node;
    newNode->data = c;
    newNode->next = nullptr;

    if (rear == nullptr) {          
        front = newNode;
        rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

Customer Queue::dequeue() {
    Customer c = {0, 0, 0};
    if (front == nullptr) {
        cout << "Queue is empty.\n";
        return c;
    }
    Node* temp = front;
    c = temp->data;
    front = front->next;
    if (front == nullptr)           
        rear = nullptr;
    delete temp;
    return c;
}

bool Queue::isEmpty() {
    return front == nullptr;
}

void Queue::display() {
    if (front == nullptr) {
        cout << "empty";
        return;
    }
    Node* current = front;
    while (current != nullptr) {
        cout << current->data.id << " ";
        current = current->next;
    }
}

void Queue::clear() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
}

// ---------- BankSimulation ----------

BankSimulation::BankSimulation() {
    totalCustomers = 0;
}

int BankSimulation::arrivalGap(int id) {
    return 1 + (id * 2) % 3;
}

int BankSimulation::serviceTimeOf(int id) {
    return 2 + (id * 3) % 4;
}

void BankSimulation::run() {
    cout << "Enter number of customers: ";
    cin >> totalCustomers;

    if (totalCustomers <= 0) {
        cout << "Number of customers must be greater than 0.\n";
        return;
    }

    int clock = 0;              
    int nextId = 1;             
    int nextArrival = 0;        
    int served = 0;             
    bool busy = false;         
    int servingId = 0;          
    int finishTime = 0;         
    int idleTime = 0;           
    int endTime = 0;            
    int totalWait = 0;          

    cout << "\n--- Bank Simulation Start ---\n";

    while (served < totalCustomers) {

        if (busy && finishTime == clock) {
            cout << "Time " << clock << ": Customer " << servingId
                 << " served and leaves.\n";
            busy = false;
            served++;
            endTime = clock;
        }

        
        if (nextId <= totalCustomers && nextArrival == clock) {
            Customer c;
            c.id = nextId;
            c.arrivalTime = clock;
            c.serviceTime = serviceTimeOf(nextId);
            line.enqueue(c);

            cout << "Time " << clock << ": Customer " << c.id
                 << " arrives.   Queue: ";
            line.display();
            cout << endl;

            nextArrival = clock + arrivalGap(nextId);
            nextId++;
        }

        if (!busy && !line.isEmpty()) {
            Customer c = line.dequeue();
            busy = true;
            servingId = c.id;
            finishTime = clock + c.serviceTime;
            totalWait = totalWait + (clock - c.arrivalTime);

            cout << "Time " << clock << ": Customer " << c.id
                 << " goes to counter (waited " << (clock - c.arrivalTime)
                 << " min, service " << c.serviceTime << " min).   Queue: ";
            line.display();
            cout << endl;
        }

        if (!busy && line.isEmpty() && served < totalCustomers)
            idleTime++;

        clock++;
    }

    cout << "--- Bank Simulation End ---\n\n";
    cout << "Customers served       : " << totalCustomers << endl;
    cout << "Last customer left at  : " << endTime << " min\n";
    cout << "Total waiting time     : " << totalWait << " min\n";
    cout << "Average waiting time   : " << (double)totalWait / totalCustomers << " min\n";
    cout << "Counter idle time      : " << idleTime << " min\n";
}