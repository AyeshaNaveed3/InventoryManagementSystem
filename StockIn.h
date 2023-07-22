#ifndef STOCKIN_H
#define STOCKIN_H
#include <iostream>
#include <vector>
#include <ctime>
#include<string>
#include "Stock.h"
using namespace std;

class StockIn : public Stock {

private:
	time_t date;
public:
	static string filename;
	StockIn();
	StockIn(Medicine med, int q, time_t d);
	StockIn(Medicine med, int q);
	time_t getDate() const;
	void setDate(time_t d);
	void saveToFile();
};


#endif // STOCKIN_H
