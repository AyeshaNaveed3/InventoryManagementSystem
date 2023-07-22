#ifndef ORDER_H
#define ORDER_H
#include <iostream>
#include <vector>
#include <ctime>
#include<string>
#include "OrderItem.h"
using namespace std;
class Order {
private:
	int orderId;
	static int id; // for automatically assigning id
	vector<OrderItem> items;
	time_t orderDate;

public:
	static string filename;
	Order();
	Order(int oid, time_t dateOrder);
	int getOrderId() const;
	vector<OrderItem> getItems() const;
	time_t getOrderDate() const;
	void addItem(OrderItem item);
	void printOrderItems();
	void setItems(vector<OrderItem> item);
	void saveToFile(int customer);
};

#endif // ORDER_H
