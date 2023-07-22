#ifndef STOCK_H
#define STOCK_H
#include <iostream>
#include <vector>
#include <ctime>
#include<string>
#include"Medicine.h"
using namespace std;

class Stock {
protected:
	int stockId;
	static int id; // for automatically assigning id
	Medicine med;
	int quantity;
public:
	Stock();
	Stock(Medicine m, int q);
	Medicine getMedicine() const;
	int getQuantity() const;
	void setMedicineItem(Medicine m);
	void setQuantity(int q);

};

#endif // MEDICINE_H

