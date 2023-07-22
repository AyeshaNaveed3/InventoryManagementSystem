#include "MedicineItem.h"
#include<fstream>
using namespace std;

MedicineItem::MedicineItem() {}

MedicineItem::MedicineItem(Medicine med, time_t expiry) {
    medicineItemId = ++id;
    medicine = med;
    expiryDate = expiry;
}

MedicineItem::MedicineItem(int mid, Medicine med, time_t expiry) {
    medicineItemId = mid;
    medicine = med;
    expiryDate = expiry;
    id = medicineItemId;
}

int MedicineItem:: getMedicineItemId() const {
    return medicineItemId;
}

Medicine MedicineItem:: getMedicine() const {
    return medicine;
}

time_t MedicineItem:: getExpiryDate() const {
    return expiryDate;
}

void MedicineItem::saveToFile() {

    time_t t = getExpiryDate();
    std::tm localTime;
    localtime_s(&localTime, &t);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);

    fstream medicineitemfile;
    medicineitemfile.open(MedicineItem::filename, ios::app);
    medicineitemfile << medicineItemId << "," << medicine.getMedicineId() << "," << buffer << endl;
    medicineitemfile.close();
}


