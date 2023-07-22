#include "Order.h"
#include<fstream>
using namespace std;

Order::Order() {
	orderId = ++id;
	orderDate = time(0);
}

Order::Order(int oid, time_t dateOrder) {
	orderId = oid;
	orderDate = dateOrder;
	id = orderId;
}

int Order:: getOrderId() const {
	return orderId;
}

vector<OrderItem> Order::getItems() const {
	return items;
}

time_t Order::getOrderDate() const {
	return orderDate;
}
void Order :: addItem(OrderItem item) {
	items.push_back(item);

}
void Order :: setItems(vector<OrderItem> item) {
	items.clear();
	for (int i = 0;i<item.size();i++) {
		items.push_back(item[i]);
	}
}
void Order:: printOrderItems(){
	cout << "Items: ";
	for (const auto& item : items) {
		cout << "Medicine: " << item.getMedicine().getMedicineId()
			<< " , Quantity: " << item.getQuantity()<<endl;
	}
	cout << endl;
}

void Order::saveToFile(int customer) {

	time_t t = orderDate;
	std::tm localTime;
	localtime_s(&localTime, &t);
	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);

	fstream orderfile;
	orderfile.open(Order::filename, ios::app);
	orderfile << orderId << "," << customer << "," << buffer << endl;
	orderfile.close();
}