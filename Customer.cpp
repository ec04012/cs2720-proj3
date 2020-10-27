#include "Customer.h"

// Class constructors
// Default constructor, uses placeholder name and id
Customer::Customer() {
    this->setName("John Smith");
    this->setArrival(0);
    this->setService(60);
    this->setWait(0);
}
// Param constructor, gets name, arrival, service, and wait as params
Customer::Customer(string const& name, int const& arrival, int const& service, int const& wait) {
    this->setName(name);
    this->setArrival(arrival);
    this->setService(service);
    this->setWait(wait);
}

// get methods
string Customer::getName() const {
    return name;
}
int Customer::getArrival() const {
    return arrival;
}
int Customer::getService() const {
    return service;
}
int Customer::getWait() const {
    return wait;
}

// set methods
void Customer::setName(string const& newName) {
    this->name = newName;
}
void Customer::setArrival(int const& newArrival) {
    this->arrival = newArrival;
}
void Customer::setService(int const& newService) {
    this->arrival = newService;
}
void Customer::setWait(int const& newWait) {
    this->arrival = newWait;
}