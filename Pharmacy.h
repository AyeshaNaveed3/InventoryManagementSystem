#ifndef PHARMACY_H
#define PHARMACY_H
#include <iostream>
#include <vector>
#include <ctime>
#include<string>

#include "Admin.h"
#include "MedicineItem.h"
#include "Medicine.h"
#include "Customer.h"
#include "StockIn.h"
#include "StockOut.h"

using namespace std;

class Pharmacy {

private:

	Admin admin;
	vector<Medicine> medicines;
	vector<MedicineItem> medicineItems;
	vector<Customer> customers;
	vector<StockIn> stockIns;
	vector<StockOut> stockOuts;

public:

	Pharmacy();
	vector<Medicine> getMedicines();
	void addMedicine(string name, int price);
	void updateMedicine(int medicineId, string name, int price);
	void deleteMedicine(int medicineId);
	void addStock(int medicineId, int quantity, time_t expiryDate);
	void removeStock(int medicineId, int quantity);
	int getquantityNotExpired(int medicineId);
	void displayAllMedicines();
	void displayExpiryMedicines() const;
	void deleteExpiryMedicines();
	Customer* findCustomer(string username, string password);
	void createCustomer(string username, string password);
	bool isAdminLogin(string username, string password);
	bool checkAvailableStock(int medicineId, int quantity);
	void placeOrder(Customer& cust);
	void displayStockIns() const;
	void displayStockOuts() const;
	void displaySoldStocks() const;
	void loadCustomers();
	void loadMedicines();
	void updateMedicines();
	void loadMedicineItem();
	void updateMedicineItems();
	void loadStockIns();
	void loadStockOuts();
};

#endif //PHARMACY_H