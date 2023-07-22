#ifndef ORDERITEM_H
#define ORDERITEM_H
#include <iostream>
#include <vector>
#include <ctime>
#include<string>
#include "Medicine.h"
using namespace std;
class OrderItem {
private:
	Medicine med;
	int quantity;
public:
    static string filename;
    OrderItem();
    OrderItem(Medicine medicine, int quant);
    Medicine getMedicine() const;
    int getQuantity() const;
    void setQuantity(int q);
    void saveToFile(int order);
 };

#endif // ORDERITEM_H