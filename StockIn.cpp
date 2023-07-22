#include "StockIn.h"
#include<fstream>
using namespace std;

StockIn::StockIn(): Stock() {
	date = time(0);
}

StockIn::StockIn(Medicine med, int q, time_t d) : Stock(med, q) {
	date = d;
}

StockIn::StockIn(Medicine med, int q) : Stock(med, q) {
	date = time(0);
}

time_t StockIn::getDate() const {
	return date;
}

void StockIn::setDate(time_t d) {
	date = d;
}

void StockIn::saveToFile() {

    time_t t = date;
    std::tm localTime;
    localtime_s(&localTime, &t);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);

    fstream stockinfile;
    stockinfile.open(StockIn::filename, ios::app);
    stockinfile << med.getMedicineId() << "," << quantity << "," << buffer << endl;
    stockinfile.close();

}
