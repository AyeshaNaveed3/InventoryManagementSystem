#include "IncomingStock.h"
#include<fstream>
using namespace std;

IncomingStock::IncomingStock() : Stock() {
    date = time(0);
}

IncomingStock::IncomingStock(Medicine med, int q, time_t d) : Stock(med, q) {
    date = d;
}

IncomingStock::IncomingStock(Medicine med, int q) : Stock(med, q) {
    date = time(0);
}

time_t IncomingStock::getDate() const {
    return date;
}

void IncomingStock::setDate(time_t d) {
    date = d;
}

void IncomingStock::saveToFile() {

    time_t t = date;
    std::tm localTime;
    localtime_s(&localTime, &t);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);

    fstream stockinfile;
    stockinfile.open(IncomingStock::filename, ios::app);
    stockinfile << med.getMedicineId() << "," << quantity << "," << buffer << endl;
    stockinfile.close();

}
