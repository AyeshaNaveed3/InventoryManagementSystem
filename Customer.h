#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <vector>
#include <ctime>
#include<string>
#include "Order.h"
using namespace std;
class  Customer {

private:
    int customer_id;
    string username;
    string password;
    vector<Order> orders;
    static int id;

public:
    static string filename;
    Customer();
    Customer(string uname, string pass);
    Customer(int cid, string uname, string pass);
    string getUsername() const;
    string getPassword() const;
    int getCustomerId() const;
    vector<Order> getOrders() const;
    void addOrder(Order order);
    void DisplayAllOrders();
    void saveToFile();

};

#endif//CUSTOMER_H