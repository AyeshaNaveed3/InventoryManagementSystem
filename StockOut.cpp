#include "StockOut.h"
#include<fstream>
using namespace std;

StockOut::StockOut() : Stock() {
	date = time(0);
}

StockOut::StockOut(Medicine med, int q, time_t d, string r) : Stock(med, q) {
	date = d;
	reason = r;
}

StockOut::StockOut(Medicine med, int q, string r) : Stock(med, q) {
	date = time(0);
	reason = r;
}

time_t StockOut::getDate() const {
	return date;
}

void StockOut::setDate(time_t d) {
	date = d;
}

string StockOut::getReason() const {
	return reason;
}

void StockOut::setReason(string r) {
	reason = r;

}

void StockOut::saveToFile() {

	time_t t = date;
	std::tm localTime;
	localtime_s(&localTime, &t);
	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);

	fstream stockoutfile;
	stockoutfile.open(StockOut::filename, ios::app);
	stockoutfile << med.getMedicineId() << "," << quantity << "," << reason << "," << buffer << endl;
	stockoutfile.close();

}

