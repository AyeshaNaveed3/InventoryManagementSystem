#ifndef INCOMINGMEDICINE_H
#define INCOMINGSTOCK_H
#include <iostream>
#include <vector>
#include <ctime>
#include<string>
#include "Stock.h"
using namespace std;

class IncomingStock : public Stock {

private:
	time_t date;
public:
	static string filename;
	IncomingStock();
	IncomingStock(Medicine med, int q, time_t d);
	IncomingStock(Medicine med, int q);
	time_t getDate() const;
	void setDate(time_t d);
	void saveToFile();
};
#endif // STOCKIN_H

