#include <fstream>
#include <iostream>

#include "Customer.h"
#include "req/PriorityQueue.cpp"
#include "req/QueType.cpp"
using namespace std;

/* Takes a customer and the earliest time that a teller is available, calculates wait time and sets it.
 * Params: The customer,and array of times when tellers will be available
 * Post: The customer's wait time has been updated
 */
void setCustomerWait(Customer& cus, int available) {
    // Calculate wait time, and assign it to customer
    if(cus.getArrival() >= available) {
        cus.setWait(0);
    } else {
        cus.setWait(available - cus.getArrival());
    }
}

/* Processes a customer by updating the teller array.
 * Calculates the customer's departure time, and updates the teller array accordingly.
 * Params: The array of tellers, the length of the array, the index of the earliest available teller, the customer.
 * Post: The teller array has been updated to reflect the customer's departure time,
 *       and index has been updated to the new earliest available teller
 * Won't work corectly if the array of tellers is of length 0
 */
void updateTellers(int* tellers, int len, int& index, Customer& cus) {
    // Update teller availability
    tellers[index] = cus.getDeparture();

    // Update index of earliest available teller
    index = 0;
    for(int i = 1; i < len; i++) {
        if(tellers[i] < tellers[index]) {
            index = i;
        }
    }
}

/* Prints the specified array
 * Param: arr the specified array
 * Pre: arr has been initilized and has length > 0
 * Post: arr has been printed and is unchanged
 */
void printArray(int* arr, int len) {
    for(int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <class ItemType>
void printWaiting(QueType<ItemType>& waiting) {
    cout << "Waiting queue" << endl;
    for(int i = 0; i < waiting.length(); i++) {
        Customer cus;
        waiting.dequeue(cus);
        cout << cus << endl;
        waiting.enqueue(cus);
    }
}

template <class ItemType>
void printDeparture(PriorityQueue<ItemType>& departure) {
    cout << "Departure queue" << endl;
    PriorityQueue<Customer> temp;
    Customer cus;
    while(departure.length() > 0) {
        departure.dequeue(cus);
        cout << cus << endl;
        temp.enqueue(cus, cus.getDeparture());
    }
    while(temp.length() > 0) {
        temp.dequeue(cus);
        departure.enqueue(cus, cus.getDeparture());
    }
}

/* Prints the departue and witing queues
 * Params: The departure and waiting queues
 * Pre: The queues have been initilizes
 * Post: The queues have been printed, and are
 *        unchanged
 */
template <class ItemType>
void printQueues(QueType<ItemType>& waiting, PriorityQueue<ItemType>& departure) {
    printWaiting(waiting);
    printDeparture(departure);
}

int main() {
    // File io
    ifstream inFile;
    ofstream outFile;
    inFile.open("input.txt");
    // outFile.open("output.txt");
    string temp;  // string used to read and store useless info from input

    // Read data from file, and enqueue customers
    QueType<Customer> arrivalQue;
    QueType<Customer> waitingQue;
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
        // Enqueue customer with name, arrivalTime, serviceTime.
        // Use default waitTime = 0
        // We will calculate the correctWaitTime during the simulation.
        // cout << "Name: " << name << " arrival: " << arrivalTime << " service: " << serviceTime << endl;
        Customer cus(name, arrivalTime, serviceTime, 0);
        // cout << cus << endl << endl;
        // cout << cus.getName() << " " << cus.getWait() << " " << cus.getService() << endl;
        arrivalQue.enqueue(cus);
    }
    /*
    cout << "Peek" << arrivalQue.peek() << endl;
    cout << "Arrival queue" << endl;
    for(int i = 0; i < arrivalQue.length(); i++) {
        Customer cus;
        arrivalQue.dequeue(cus);
        cout << cus.getName() << " " << cus.getWait() << " " << cus.getService() << endl;
        arrivalQue.enqueue(cus);
    }
    cout << "Departure queue" << endl;
    for(int i = 0; i < departureQue.length(); i++) {
        Customer cus;
        departureQue.dequeue(cus);
        cout << cus.getName() << " " << cus.getWait() << " " << cus.getService() << endl;
        departureQue.enqueue(cus);
    }
    cout << "====================" << endl;
    // printQueues(arrivalQue, departureQue);
    exit(0);
    */

    // Run the simulation
    // int counter = 0;                // counter so we can print every 5 customers
    int* tellers = new int[numTellers]();  // array of teller availiability times. 0 because all the tellers are available at start
    int timeIndex = 0;                     // Index of the earliest avaiable teller
    double totalWait = 0;
    cout << "Initial tellers" << endl;
    printArray(tellers, numTellers);
    Customer cus;
    while(departureQue.length() < numCustomers) {
        if(!arrivalQue.isEmpty()) {
            // If the arrival queue is not empty, then determine whether to serve the arriving customer or the waiting customer
            if(waitingQue.isEmpty() || waitingQue.peek().getArrival() + waitingQue.peek().getWait() > arrivalQue.peek().getArrival()) {
                // If there are no waiting customers, or the the waiting customer is served after the arriving customer arrives
                // Calcualate wait time for arriving customer, and enqueue to waiting or departue queue
                arrivalQue.dequeue(cus);
                setCustomerWait(cus, tellers[timeIndex]);
                totalWait = totalWait + cus.getWait();
                if(cus.getWait() == 0) {
                    // if a teller is available, instantly serve customer
                    updateTellers(tellers, numTellers, timeIndex, cus);
                    departureQue.enqueue(cus, cus.getDeparture());
                } else {
                    // else queue customer to waitQ
                    updateTellers(tellers, numTellers, timeIndex, cus);
                    waitingQue.enqueue(cus);
                }
            } else {
                // If the waiting customer will be served before a new customer arrives, serve the waiting customer
                waitingQue.dequeue(cus);
                departureQue.enqueue(cus, cus.getDeparture());
            }
        } else {
            // If the arrival que is empty, then we empty the waiting queue and serve all waiting customers
            while(!waitingQue.isEmpty()) {
                waitingQue.dequeue(cus);
                departureQue.enqueue(cus, cus.getDeparture());
            }
        }
        if((departureQue.length() + waitingQue.length()) % 1 == 0 && departureQue.length() != numCustomers) {
            cout << "Number of Customers " << departureQue.length() + waitingQue.length() << endl;
            cout << "Earliest = " << tellers[timeIndex] << endl;
            cout << "Tellers: ";
            printArray(tellers, numTellers);
            // print departure que and waiting que
            printQueues<Customer>(waitingQue, departureQue);
            cout << endl;
        }
    }  // while there are customers to server

    // Print final departure queue
    printDeparture(departureQue);
    cout << "Number of tellers = " << numTellers << endl;
    cout << "Average wait time = " << totalWait / numCustomers << " seconds" << endl;
    cout << endl;

    // print
    return 0;
}