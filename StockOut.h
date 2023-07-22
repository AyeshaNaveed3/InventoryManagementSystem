#ifndef STOCKOUT_H
#define STOCKOUT_H
#include <iostream>
#include <vector>
#include <ctime>
#include<string>
#include "Stock.h"
using namespace std;

class StockOut : public Stock {

private:
	time_t date;
	string reason;
public:
	static string filename;
	StockOut();
	StockOut(Medicine med, int q, time_t d, string r);
	StockOut(Medicine med, int q, string r);
	time_t getDate() const;
	void setDate(time_t d);
	string getReason() const;
	void setReason(string r);
	void saveToFile();
};


#endif // STOCKOUT_H
