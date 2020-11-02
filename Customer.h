#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <ostream>
#include <string>
using namespace std;

class Customer {
   public:
    // Class constructors
    Customer();                                                                             // Default constructor, uses placeholder vars
    Customer(const string& name, const int& arrival, const int& service, const int& wait);  // Param constructor, gets name, arrival, service, and wait as params

    // No destructor, the default destructor should work

    // get methods
    string getName() const;
    int getArrival() const;
    int getService() const;
    int getWait() const;
    int getDeparture() const;

    // set methods
    void setName(const string&);
    void setArrival(const int&);
    void setService(const int&);
    void setWait(const int&);

    // Stream overload
    friend ostream& operator<<(ostream& out, const Customer& stu);

   private:
    string name;
    int arrival;
    int service;
    int wait;
};

#endif