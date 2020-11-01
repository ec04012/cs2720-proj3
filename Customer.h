#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <ostream>
#include <string>
using namespace std;

class Customer {
   public:
    // Class constructors
    Customer();                                                       // Default constructor, uses placeholder vars
    Customer(string const &, int const &, int const &, int const &);  // Param constructor, gets name, arrival, service, and wait as params

    // No destructor, the default destructor should work

    // get methods
    string getName() const;
    int getArrival() const;
    int getService() const;
    int getWait() const;
    int getDeparture() const;

    // set methods
    void setName(string const &);
    void setArrival(int const &);
    void setService(int const &);
    void setWait(int const &);

    // Stream overload
    friend ostream &operator<<(ostream &out, const Customer &stu);

   private:
    string name;
    int arrival;
    int service;
    int wait;
};

#endif