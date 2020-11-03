#include "Customer.h"

int main() {
    string name = "wasd";
    int arrival = 0;
    int service = 20;
    int wait = 10;
    Customer cus(name, arrival, service, wait);
    Customer cus2(name, arrival, service, wait);

    name = "qwerty";
    arrival = 30;
    service = 40;
    wait = 50;

    Customer cus3(name, arrival, service, wait);
    Customer cus4(name, arrival, service, wait);

    cout << "cus " << cus << endl;
    cout << "cus2" << cus2 << endl;
    cout << "cus3" << cus3 << endl;
    cout << "cus4" << cus4 << endl;
    return 0;
}