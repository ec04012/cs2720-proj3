#include "Customer.h"

#include <iomanip>

// Class constructors
// Default constructor, uses placeholder name and times
Customer::Customer() {
    setName("John Smith");
    setArrival(0);
    setService(0);
    setWait(0);
}
// Param constructor, gets name, arrival, service, and wait as params
Customer::Customer(const string& name, const int& arrival, const int& service, const int& wait) {
    setName(name);
    setArrival(arrival);
    setService(service);
    setWait(wait);
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
int Customer::getDeparture() const {
    return arrival + wait + service;
}

// set methods
void Customer::setName(const string& newName) {
    this->name = newName;
}
void Customer::setArrival(const int& newArrival) {
    this->arrival = newArrival;
}
void Customer::setService(const int& newService) {
    this->service = newService;
}
void Customer::setWait(const int& newWait) {
    this->wait = newWait;
}

// Stream overload
ostream& operator<<(ostream& out, const Customer& cus) {
    out << cus.getName();
    out << "\tArrival " << std::setw(6) << left << cus.getArrival();
    out << "\tWait " << std::setw(6) << left << cus.getWait();
    out << "\tService " << std::setw(6) << left << cus.getService();
    out << "\tDeparture " << std::setw(6) << left << cus.getDeparture();
    return out;
}