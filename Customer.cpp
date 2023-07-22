#include  "Customer.h"
#include<fstream>
using namespace std;

Customer::Customer() {

}

Customer::Customer(string uname, string pass) {
    customer_id = ++id;
	username = uname;
	password = pass;
}

Customer::Customer(int cid, string uname, string pass) {
    customer_id = cid;
    username = uname;
    password = pass;
    id = customer_id;
}


string Customer:: getUsername() const {
    return username;
}

string Customer:: getPassword() const {
    return password;
}

int Customer::getCustomerId() const {
    return customer_id;
}

vector<Order> Customer :: getOrders() const {
    return orders;
}

void Customer::addOrder(Order order) {
    orders.push_back(order);
}

void Customer:: DisplayAllOrders() {
    cout << "Previous Orders:" << endl;

    for (auto& order : orders) {
        time_t t = order.getOrderDate();
        std::tm localTime;
        localtime_s(&localTime, &t);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
        cout << "Order Id : " << order.getOrderId() << ", Order Date: " << buffer << endl;
        order.printOrderItems();
    }

}

void Customer::saveToFile() {
    fstream customerfile;
    customerfile.open(Customer::filename, ios::app);
    customerfile << customer_id << "," << username << "," << password << endl;
    customerfile.close();
}
