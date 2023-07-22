#include "Stock.h"
using namespace std;

Stock::Stock() {
    stockId = ++id;
}
Stock::Stock(Medicine m, int q) {
    stockId = ++id;
    med = m;
    quantity = q;
}

Medicine Stock::getMedicine() const {
    return med;
}

int  Stock::getQuantity() const {
    return quantity;
}

void  Stock::setMedicineItem(Medicine m) {
    med = m;
}

void  Stock::setQuantity(int q) {
    quantity = q;
}


