#ifndef MEDICINEITEM_H
#define MEDICINEITEM_H
#include <iostream>
#include <vector>
#include <ctime>
#include<string>
#include "Medicine.h"
using namespace std;

class MedicineItem {

private:
	int medicineItemId;
    static int id; // for automatically assigning id
	Medicine medicine;
	time_t expiryDate;


public:
	static string filename;
	MedicineItem();
	MedicineItem(Medicine med, time_t expiry);
	MedicineItem(int mid, Medicine med, time_t expiry);
	int getMedicineItemId() const;
	time_t getExpiryDate() const;
	Medicine getMedicine() const;
	void saveToFile();

};


#endif // MEDICINEITEM_H

