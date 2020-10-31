#include <fstream>
#include <iostream>

#include "Customer.h"
#include "req/PriorityQueue.cpp"
#include "req/QueType.cpp"
using namespace std;

int main() {
    // File io
    ifstream inFile;
    ofstream outFile;
    inFile.open("input.txt");
    outFile.open("output.txt");
    string temp;  // string used to read and store useless info from input

    // Read data from file, and enqueue customers
    QueType<Customer> arrivalQue;
    PriorityQueue<Customer> waitingQue;
    PriorityQueue<Customer> departureQue;
    int numTellers;
    int numCustomers;

    inFile >> temp >> numTellers;
    inFile >> temp >> numCustomers;

    for(int i = 0; i < numCustomers; i++) {
        string name;
        int arrivalTime;
        int serviceTime;
        inFile >> name >> temp >> arrivalTime >> temp >> serviceTime;
        arrivalQue.enqueue(Customer(name, arrivalTime, serviceTime, 0));
    }

    return 0;
}