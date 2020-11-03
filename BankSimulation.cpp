#include <fstream>
#include <iostream>
#include <limits>

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

/* Prints the departue and witing queues
 * Params: The departure and waiting queues
 * Pre: The queues have been initilizes
 * Post: The queues have been printed, and are
 *        unchanged
 */
template <class ItemType>
void printQueues(QueType<ItemType>& waiting, PriorityQueue<ItemType>& departure, ofstream& outFile) {
    outFile << "Waiting queue" << endl;
    waiting.printQueue(outFile);
    outFile << "Priority queue" << endl;
    departure.printQueue(outFile);
}

/*
 * Runs a simulation with the specified parameters.
 * Params: arrivalQue = the queue of customers, numTellers = number of tellers, averageWait = int to return averageWait, outFile = file to write to
 * Pre: arrivalQue is an initlized queue of customers sorted by arrival queueue. numTellers is initialized and > 0
 *      averageWait and outFile are initialzied.
 * Post: Simulation has been ran, arrivalQue is reset to its original state.
 */
template <class ItemType>
void runSimulation(QueType<ItemType>& arrivalQue, int numTellers, double& averageWait, ofstream& outFile) {
    // Set variables
    // int counter = 0;                // counter so we can print every 5 customers
    int* tellers = new int[numTellers]();  // array of teller availiability times. 0 because all the tellers are available at start
    int timeIndex = 0;                     // Index of the earliest avaiable teller
    double totalWait = 0;
    QueType<Customer> waitingQue;
    PriorityQueue<Customer> departureQue;
    int numCustomers = arrivalQue.length();

    // Run the simulatin until all customers have been served
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
        if((departureQue.length() + waitingQue.length()) % 5 == 0) {
            outFile << "Number of Customers " << departureQue.length() + waitingQue.length() << endl;
            // print departure que and waiting que
            printQueues<Customer>(waitingQue, departureQue, outFile);
            outFile << endl;
        }
    }  // while there are customers to serve

    // Print final departure queue and average wait time
    outFile << "Final Priority/Departure Queue" << endl;
    departureQue.printQueue(outFile);
    averageWait = totalWait / numCustomers;
    outFile << "Number of tellers = " << numTellers << endl;
    outFile << "Average wait time = " << averageWait << " seconds" << endl;
    delete[] tellers;

    // Reset arrivalQueue
    while(departureQue.length() > 0) {
        // Set wait to 0 and move to arrival
        departureQue.dequeue(cus);
        cus.setWait(0);
        arrivalQue.enqueue(cus);
    }
    while(arrivalQue.length() > 0) {
        // move back to departure to sort by arrival
        arrivalQue.dequeue(cus);
        departureQue.enqueue(cus, cus.getArrival());
    }
    while(departureQue.length() > 0) {
        // move back to arrival
        departureQue.dequeue(cus);
        arrivalQue.enqueue(cus);
    }
    return;
}

int main() {
    // File io
    ifstream inFile;
    ofstream outFile;
    inFile.open("input.txt");
    outFile.open("output.txt");
    string temp;  // string used to read and store useless info from input

    // Read data from file, and enqueue customers
    QueType<Customer> arrivalQue;
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
        Customer cus(name, arrivalTime, serviceTime, 0);
        arrivalQue.enqueue(cus);
    }

    // Run  first simulation
    double averageWait = 0;
    runSimulation(arrivalQue, numTellers, averageWait, outFile);

    while(averageWait > 300 && numTellers < numeric_limits<int>::max()) {
        outFile << "============================================================" << endl;
        numTellers++;
        runSimulation(arrivalQue, numTellers, averageWait, outFile);
    }

    // Print required number of tellers
    outFile << "============================================================" << endl;
    if(averageWait > 300.0) {
        outFile << "Impossible to get average wait under 5 minutes." << endl;
    } else {
        outFile << "Number of tellers for required wait time is " << numTellers << endl;
    }

    return 0;
}