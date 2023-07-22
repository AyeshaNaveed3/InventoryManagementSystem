#ifndef MEDICINE_H
#define MEDICINE_H
#include <iostream>
#include <vector>
#include <ctime>
#include<string>
using namespace std;
class Medicine {
private:
	int medicineId;
	int price;
	static int id; // for automatically assigning id
	string medicineName;
	int quantity;

public:
	static string filename;
	Medicine();
	Medicine(string name, int cost);
	Medicine(int mid, string name, int cost, int q);
	int getMedicineId() const;
	string getMedicineName() const;
	int getPrice() const;
	int getQuantity() const;
	void setMedicineName(string name);
	void setPrice(int cost);
	void setQuantity(int q);
	void saveToFile();

};

#endif // MEDICINE_H
