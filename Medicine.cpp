#include "Medicine.h"
#include<fstream>
using namespace std;
Medicine::Medicine() {

 }
Medicine::Medicine(string name, int cost) {
	medicineId = ++id;
	quantity = 0;
	medicineName = name;
	price = cost;

}
Medicine::Medicine(int mid, string name, int cost, int q) {
	medicineId = mid;
	quantity = q;
	medicineName = name;
	price = cost;
	id = medicineId;

}
int Medicine :: getMedicineId() const {
    return medicineId;
}

string Medicine :: getMedicineName() const {
    return medicineName;
}

int Medicine :: getPrice() const {
    return price;
}
void  Medicine ::setMedicineName(string name) {
    medicineName = name;
}

void Medicine :: setPrice(int cost) {
    price = cost;
}

int  Medicine:: getQuantity() const {
    return quantity;
}

void  Medicine:: setQuantity(int q) {
    quantity = q;
}

void Medicine::saveToFile() {
    fstream medicinefile;
    medicinefile.open(Medicine::filename, ios::app);
    medicinefile << medicineId << "," << medicineName << "," << price << "," << quantity << endl;
    medicinefile.close();
}