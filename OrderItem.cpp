#include "OrderItem.h"
#include<fstream>
using namespace std;

OrderItem::OrderItem(){

}
OrderItem::OrderItem(Medicine medicine, int quant) {
	med = medicine;
	quantity = quant;
}
Medicine OrderItem:: getMedicine() const {
    return med;
}

int OrderItem:: getQuantity() const {
    return quantity;
}

void OrderItem:: setQuantity(int q) {
    quantity = q;
}

void OrderItem::saveToFile(int order) {
    fstream orderfile;
    orderfile.open(OrderItem::filename, ios::app);
    orderfile << order << "," << med.getMedicineId() << "," << quantity << endl;
    orderfile.close();
}