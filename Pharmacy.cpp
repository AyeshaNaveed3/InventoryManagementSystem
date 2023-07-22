#include "Pharmacy.h"
#include <fstream>
#include <string>
#include <sstream>
#include<iostream>
#include <vector>
using namespace std;

Pharmacy::Pharmacy() {
	// to Read admin credentials from file
	admin.loadFromFile();

	loadMedicines();
	loadMedicineItem();
	loadStockIns();
	loadStockOuts();
	loadCustomers();
	
}

vector<Medicine> Pharmacy:: getMedicines() {
	return medicines;
}

void Pharmacy:: addMedicine(string name, int price) {
	Medicine medicine (name, price);
	medicine.saveToFile();
	medicines.push_back(medicine);
}

void Pharmacy::updateMedicine(int medicineId, string name, int price) {
	for (auto& medicine : medicines) {
		if (medicine.getMedicineId() == medicineId) {
			medicine.setMedicineName(name);
			medicine.setPrice(price);
			updateMedicines();
			cout << "Medicien update successfully. " << endl;
			return;
		}
	}
	cout << "Medicine not Found. " << endl;
}
void Pharmacy::deleteMedicine(int medicineId) {
	for (auto it = medicines.begin(); it != medicines.end(); ++it) {
		if (it->getMedicineId() == medicineId) {
			for (int i = 0; i < it->getQuantity(); i++) {
				for (auto itr = medicineItems.begin(); itr != medicineItems.end(); ++itr) {
					if (itr->getMedicine().getMedicineId() == medicineId) {
						medicineItems.erase(itr);
						break;
					}
				}

			}
			medicines.erase(it);
			updateMedicines();
			updateMedicineItems();
			cout << "Medicine deleted successfully." << endl;
			return;
		}
	}
	cout << "Medicine not found." << endl;
}

void Pharmacy::addStock(int medicineId, int quantity, time_t expiryDate) {
	for (auto& med : medicines) {
		if (med.getMedicineId() == medicineId) {
			med.setQuantity(med.getQuantity() + quantity);
			StockIn s = StockIn(med, quantity);
			s.saveToFile();
			stockIns.push_back(s);
			for (int i = 0; i < quantity; i++) {
				MedicineItem item(med, expiryDate);
				item.saveToFile();
				medicineItems.push_back(item);
			}
			updateMedicines();
			cout << "Stock added successfully." << endl;
			return;
		}
	}
	cout << "Medicine not found." << endl;
}

void Pharmacy:: removeStock(int medicineId, int quantity) {
	for (auto& medicine : medicines) {
		if (medicine.getMedicineId() == medicineId) {
			medicine.setQuantity(medicine.getQuantity() - quantity);
			updateMedicines();
			break;
		}
	}
}

int Pharmacy::getquantityNotExpired(int medicineId) {
	int q = 0;
	for (const auto& medItem : medicineItems) {
		if (medicineId == medItem.getMedicine().getMedicineId() && medItem.getExpiryDate() >= time(0)) {
			q++;
		}
	}
	return q;
}

void Pharmacy::displayAllMedicines() {
	cout << "Medicine List:" << endl;
	for (auto& med : medicines) {
		int q = getquantityNotExpired(med.getMedicineId());
		cout<<"Medicine Id: "<<med.getMedicineId()<<" , Medicine Name: "<< med.getMedicineName()
			<< ", Price: " << med.getPrice() << ", Total Stock: " << med.getQuantity()
			<< ", Medicines Not Expired: " << q << endl;
	}
	cout << endl;
}
void Pharmacy:: displayExpiryMedicines() const {
	cout << " Expiry Medicines List: " << endl;
	for (const auto& item : medicineItems) {
		if (item.getExpiryDate() < time(0)) {
			time_t t = item.getExpiryDate();
			std::tm localTime;
			localtime_s(&localTime, &t);
			char buffer[20];
			strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
			cout << "Medicine ID: " << item.getMedicine().getMedicineId()
				<< ", Name: " << item.getMedicine().getMedicineName()
				<< ", Expiry Date: " << buffer << "\n";
		}
	}
	cout << endl;
}


void Pharmacy:: deleteExpiryMedicines(){
	vector<MedicineItem> updatedItems;
	vector<StockOut> temporaryStockOut;
	for(auto &item:medicineItems){
		if (item.getExpiryDate()>=time(0)) {
			updatedItems.push_back(item);
		}
	
		else {
			removeStock(item.getMedicine().getMedicineId(), 1);
			bool isPresent = false;
			for (auto& stockitem : temporaryStockOut) {
				if (stockitem.getMedicine().getMedicineId() == item.getMedicine().getMedicineId()) {
					stockitem.setQuantity(stockitem.getQuantity() + 1);
					isPresent = true;
					break;
				}
			}
			if (!isPresent) {
				StockOut s = StockOut(item.getMedicine(), 1, "Expired");
				temporaryStockOut.push_back(s);
			}

		}
	}

	for (auto& s : temporaryStockOut) {
		s.saveToFile();
	}
	
	medicineItems = updatedItems;
	updateMedicineItems();
	stockOuts.insert(stockOuts.end(), temporaryStockOut.begin(), temporaryStockOut.end());
}

// for login
Customer* Pharmacy::findCustomer(string username, string password) {
	for (auto& customer : customers) {
		if (customer.getUsername() == username && customer.getPassword() == password) {
			return &customer;
		}
  }
	return  nullptr;
}

void Pharmacy:: createCustomer(string username, string password) {
	Customer customer (username, password);
	customer.saveToFile();
	customers.push_back(customer);
}

bool Pharmacy:: isAdminLogin(string username, string password) {
	return (admin.getUsername() == username && admin.getPassword() == password);
}

bool Pharmacy::checkAvailableStock(int medicineId, int quantity) {
	for (auto & med:medicines) {
		if (med.getMedicineId() == medicineId) {
			if (med.getQuantity() >= quantity) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

void Pharmacy:: placeOrder(Customer& cust) {

	Order order;
	while (1) {
		int medicineId, quantity;
		string newitem;
		cout << "Enter medicine ID: ";
		cin >> medicineId;
		cout << "Enter quantity: ";
		cin >> quantity;

		Medicine med;
		bool isPresent = false;
		for (const auto& medicine : medicines) {
			if (medicine.getMedicineId() == medicineId) {
				med = medicine;
				isPresent = true;
				break;
			}
		}

		if (isPresent == false) {
			cout << "Medicine doesnot exist" << endl;
			cout << "Do you want to add new item(y/n): ";
			cin >> newitem;

			if (newitem == "Y" or newitem == "y") {
				continue;
			}
			else {
				break;
			}
		}



		bool DuplicatePresent = false;
		vector<OrderItem> items = order.getItems();

		// Duplicate Medicine
		for (auto& item : items) {
			if (item.getMedicine().getMedicineId() == med.getMedicineId()) {
				cout << "Duplicate Medicine" << endl;
				DuplicatePresent = true;
				quantity = item.getQuantity() + quantity;

				// Available Stock
				if (!checkAvailableStock(med.getMedicineId(), quantity)) {
					cout << "Medicine Stock not available" << endl;
					break;
				}

				// Get quantity not expired
				int q = getquantityNotExpired(med.getMedicineId());

				if (q < quantity)
				{
					cout << "Medicine Stock not available(Expired)" << endl;
					break;
				}
				item.setQuantity(quantity);


				order.setItems(items);

				break;


			}
		}

		if (!DuplicatePresent) {


			// Available Stock
			if (!checkAvailableStock(med.getMedicineId(), quantity)) {
				cout << "Medicine Stock not available" << endl;
				cout << "Do you want to add new item(y/n): ";
				cin >> newitem;

				if (newitem == "Y" or newitem == "y") {
					continue;
				}
				else {
					break;
				}
			}

			// Get quantity not expired

			int q = getquantityNotExpired(med.getMedicineId());

			if (q < quantity)
			{
				cout << "Medicine Stock not available(Expired)" << endl;
				cout << "Do you want to add new item(y/n): ";
				cin >> newitem;

				if (newitem == "Y" or newitem == "y") {
					continue;
				}
				else {
					break;
				}
			}
			//new item added to order
			OrderItem orderItem = OrderItem(med, quantity);

			order.addItem(orderItem);

		}

		order.printOrderItems();

		cout << "Do you want to add new item(y/n): ";
		cin >> newitem;

		if (newitem == "Y" or newitem == "y") {
			continue;
		}
		else {
			break;
		}

	}

	vector<OrderItem> items = order.getItems();

	for (auto& item : items) {
		item.saveToFile(order.getOrderId());
		StockOut s = StockOut(item.getMedicine(), item.getQuantity(), "Sold");
		s.saveToFile();
		stockOuts.push_back(s);
		for (int q = 0; q < item.getQuantity(); q++) {
			for (auto itr = medicineItems.begin(); itr != medicineItems.end(); ++itr) {
				if (itr->getMedicine().getMedicineId() == item.getMedicine().getMedicineId() &&
					itr->getExpiryDate() >= time(0)) {
					medicineItems.erase(itr);
					break;
				}
			}
		}
		removeStock(item.getMedicine().getMedicineId(), item.getQuantity());
	}

	updateMedicineItems();
	order.saveToFile(cust.getCustomerId());
	cust.addOrder(order);

	cout << "Order Placed succesfully" << endl;

}

void Pharmacy::displayStockIns() const {

	cout << "Stock ins: " << endl;

	for (const auto& stockin : stockIns) {
		time_t t = stockin.getDate();
		std::tm localTime;
		localtime_s(&localTime, &t);
		char buffer[20];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
		cout << "Medicine ID: " << stockin.getMedicine().getMedicineId()
			<< ", Name: " << stockin.getMedicine().getMedicineName()
			<< ", Quantity: " << stockin.getQuantity() 
			<<", Date: " << buffer << "\n";
	}
}
void Pharmacy::displayStockOuts() const {

	cout << "Stock outs: " << endl;

	for (const auto& stockout : stockOuts) {
		time_t t = stockout.getDate();
		std::tm localTime;
		localtime_s(&localTime, &t);
		char buffer[20];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
		cout << "Medicine ID: " << stockout.getMedicine().getMedicineId()
			<< ", Name: " << stockout.getMedicine().getMedicineName()
			<< ", Quantity: " << stockout.getQuantity()
			<< ", Date: " << buffer 
			<< ", Reason: "<< stockout.getReason() << "\n";
	}

}

void Pharmacy::displaySoldStocks() const {

	cout << "Sold Stocks: " << endl;

	for (const auto& stockout : stockOuts) {
		if (stockout.getReason() == "Sold") {
			time_t t = stockout.getDate();
			std::tm localTime;
			localtime_s(&localTime, &t);
			char buffer[20];
			strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
			cout << "Medicine ID: " << stockout.getMedicine().getMedicineId()
				<< ", Name: " << stockout.getMedicine().getMedicineName()
				<< ", Quantity: " << stockout.getQuantity()
				<< ", Date: " << buffer << "\n";
		}
		
	}

}


void Pharmacy::loadCustomers() {
	vector<Order> allOrders;
	vector<int> allCustomers;
	fstream orderfile;
	orderfile.open(Order::filename, ios::in);
	if(orderfile.is_open()){
		string line;
		while (getline(orderfile, line)) {
			stringstream ss(line);
			string oid, custid, bufferDate;
			getline(ss, oid, ',');
			getline(ss, custid, ',');
			getline(ss, bufferDate, ',');

			stringstream ssDate(bufferDate);
			string yy, mm, dd;
			getline(ssDate, yy, '-');
			getline(ssDate, mm, '-');
			getline(ssDate, dd, '-');

			tm t1 = tm{ 0, 0, 0, stoi(dd), stoi(mm) - 1, stoi(yy) - 1900 };
			time_t orderDate = mktime(&t1);
			allCustomers.push_back(stoi(custid));
			Order o = Order(stoi(oid), orderDate);

			fstream orderitemfile;
			orderitemfile.open(OrderItem::filename, ios::in);
			string line1;
			while (getline(orderitemfile, line1)) {
				stringstream ss1(line1);
				string oid1, mid1, q1;
				getline(ss1, oid1, ',');
				getline(ss1, mid1, ',');
				getline(ss1, q1, ',');
				if (stoi(oid1) == stoi(oid)) {
					for (auto& med : medicines) {
						if (med.getMedicineId() == stoi(mid1)) {
							OrderItem itemOrder = OrderItem(med, stoi(q1));
							o.addItem(itemOrder);
						}
					}

				}

			}
			orderitemfile.close();

			allOrders.push_back(o);

			

		}
	}
	orderfile.close();
	fstream customerfile;
	customerfile.open(Customer::filename, ios::in);
	if (customerfile.is_open()) {
		string line;
		while (getline(customerfile, line)) {
			stringstream ss(line);
			string id, username, password;
			getline(ss, id, ',');
			getline(ss, username, ',');
			getline(ss, password, ',');
			Customer c = Customer(stoi(id), username, password);

			for (int i = 0; i < allCustomers.size(); i++) {
				if (allCustomers[i] == c.getCustomerId()) {
					c.addOrder(allOrders[i]);
				}
			}

			customers.push_back(c);
		}
		
	}

	customerfile.close();

}

void Pharmacy::loadMedicines() {
	fstream medicinefile;
	medicinefile.open(Medicine::filename, ios::in);
	if (medicinefile.is_open()) {
		string line;
		while (getline(medicinefile, line)) {
			stringstream ss(line);
			string mid, name, price, quantity;
			getline(ss, mid, ',');
			getline(ss, name, ',');
			getline(ss, price, ',');
			getline(ss, quantity, ',');
			Medicine m = Medicine(stoi(mid), name, stoi(price), stoi(quantity));
			medicines.push_back(m);
		}

	}

	medicinefile.close();

}

void Pharmacy::updateMedicines() {
	fstream medicinefile;
	medicinefile.open(Medicine::filename, ios::out);

	for (auto& med : medicines) {
		medicinefile << med.getMedicineId() << "," << med.getMedicineName() << "," << med.getPrice() << "," << med.getQuantity() << endl;
	}
	

	medicinefile.close();

}

void Pharmacy::loadMedicineItem() {
	fstream medicineitemfile;
	medicineitemfile.open(MedicineItem::filename, ios::in);
	if (medicineitemfile.is_open()) {
		string line;
		while (getline(medicineitemfile, line)) {
			stringstream ss(line);
			string mItemid, mid, bufferDate;
			getline(ss, mItemid, ',');
			getline(ss, mid, ',');
			getline(ss, bufferDate, ',');


			stringstream ssDate(bufferDate);
			string yy, mm, dd;
			getline(ssDate, yy, '-');
			getline(ssDate, mm, '-');
			getline(ssDate, dd, '-');

			tm t1 = tm{ 0, 0, 0, stoi(dd), stoi(mm) - 1, stoi(yy) - 1900 };

			time_t expiryDate = mktime(&t1);

			for (auto& med : medicines) {
				if (med.getMedicineId() == stoi(mid)) {
					MedicineItem itemnew = MedicineItem(stoi(mItemid), med, expiryDate);
					medicineItems.push_back(itemnew);
				}
			}


			
		}

	}

	medicineitemfile.close();

}

void Pharmacy::updateMedicineItems() {
	fstream medicineitemfile;
	medicineitemfile.open(MedicineItem::filename, ios::out);

	for (auto& item : medicineItems) {
		time_t t = item.getExpiryDate();
		std::tm localTime;
		localtime_s(&localTime, &t);
		char buffer[20];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
		medicineitemfile << item.getMedicineItemId() << "," << item.getMedicine().getMedicineId() << "," << buffer << endl;
	}


	medicineitemfile.close();

}


void Pharmacy::loadStockIns() {
	fstream stockinfile;
	stockinfile.open(StockIn::filename, ios::in);
	if (stockinfile.is_open()) {
		string line;
		while (getline(stockinfile, line)) {
			stringstream ss(line);
			string mid, quantity, bufferDate;
			getline(ss, mid, ',');
			getline(ss, quantity, ',');
			getline(ss, bufferDate, ',');


			stringstream ssDate(bufferDate);
			string yy, mm, dd;
			getline(ssDate, yy, '-');
			getline(ssDate, mm, '-');
			getline(ssDate, dd, '-');

			tm t1 = tm{ 0, 0, 0, stoi(dd), stoi(mm) - 1, stoi(yy) - 1900 };

			time_t stockDate = mktime(&t1);

			for (auto& med : medicines) {
				if (med.getMedicineId() == stoi(mid)) {
					StockIn s = StockIn(med, stoi(quantity), stockDate);
					stockIns.push_back(s);
				}
			}
		}
	}

	stockinfile.close();

}



void Pharmacy::loadStockOuts() {
	fstream stockoutfile;
	stockoutfile.open(StockOut::filename, ios::in);
	if (stockoutfile.is_open()) {
		string line;
		while (getline(stockoutfile, line)) {
			stringstream ss(line);
			string mid, quantity, reason, bufferDate;
			getline(ss, mid, ',');
			getline(ss, quantity, ',');
			getline(ss, reason, ',');
			getline(ss, bufferDate, ',');

		
			stringstream ssDate(bufferDate);
			string yy, mm, dd;
			getline(ssDate, yy, '-');
			getline(ssDate, mm, '-');
			getline(ssDate, dd, '-');

			tm t1 = tm{ 0, 0, 0, stoi(dd), stoi(mm) - 1, stoi(yy) - 1900 };

			time_t stockDate = mktime(&t1);

			for (auto& med : medicines) {
				if (med.getMedicineId() == stoi(mid)) {
					StockOut s = StockOut(med, stoi(quantity), stockDate, reason);
					stockOuts.push_back(s);
				}
			}
		}
	}

	stockoutfile.close();

}