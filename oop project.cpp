#include <iostream>
#include <vector>
#include <ctime>
#include<string>
#include"Pharmacy.h"
#include"Customer.h"

using namespace std;

int Medicine::id = 0;
int Order::id = 0;
int MedicineItem::id = 0;
int Stock::id = 0;
int Customer::id = 0;
string Admin::filename = "Admin.txt";
string Customer::filename = "Customer.txt";
string Medicine::filename = "Medicine.txt";
string MedicineItem::filename = "MedicineItem.txt";
string StockIn::filename = "StockIn.txt";
string StockOut::filename = "StockOut.txt";
string Order::filename = "Order.txt";
string OrderItem::filename = "OrderItem.txt";

void adminMenu(Pharmacy& pharmacy) {
    int choice;
    do {
        cout << "Admin Menu:" << endl;
        cout << "1. Add New Medicine" << endl;
        cout << "2. Update a Medicine" << endl;
        cout << "3. Delete a Medicine" << endl;
        cout << "4. Add Stock of Medicine" << endl;
        cout << "5. Display All Medicines" << endl;
        cout << "6. Display Expiry Medicines" << endl;
        cout << "7. Delete Expiry Medicines" << endl;
        cout << "8. Display All Stock ins" << endl;
        cout << "9. Display All Stock outs" << endl;
        cout << "10. Display All Sold Stocks" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int price;
            cout << "Enter medicine name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter medicine price: ";
            cin >> price;
            pharmacy.addMedicine(name, price);
            cout << "Medicine added successfully." << endl;
            break;
        }
        case 2: {
            int medicineId;
            string name;
            int price;
            cout << "Enter medicine ID to update: ";
            cin >> medicineId;
            cout << "Enter new name for the medicine: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter new price for the medicine: ";
            cin >> price;
            pharmacy.updateMedicine(medicineId, name, price);
            break;
        }
        case 3: {
            int medicineId;
            cout << "Enter medicine ID to delete: ";
            cin >> medicineId;
            pharmacy.deleteMedicine(medicineId);
            break;
        }
        case 4: {
            int medicineId, quantity;
            int day, month, year;

            cout << "Enter medicine ID: ";
            cin >> medicineId;
            cout << "Enter stock quantity: ";
            cin >> quantity;
            cout << "Enter Expiry Date (Day Month Year): ";
            cin >> day >> month >> year;

            tm t = tm{ 0, 0, 0, day, month - 1, year - 1900 };

            time_t expiryDate = mktime(&t);
            pharmacy.addStock(medicineId, quantity, expiryDate);
            break;
        }
        case 5: {
            pharmacy.displayAllMedicines();
            break;
        }
        case 6: {
            pharmacy.displayExpiryMedicines();
            break;
        }
        case 7: {
            pharmacy.deleteExpiryMedicines();
            cout << "Expired medicines deleted successfully." << endl;
            break;
        }
        case 8: {
            pharmacy.displayStockIns();
            break;
        }
        case 9: {
            pharmacy.displayStockOuts();
            break;
        }
        case 10: {
            pharmacy.displaySoldStocks();
            break;
        }
        case 0:
            cout << "Exiting Admin Menu." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
        cout << endl;
    } while (choice != 0);
}

void customerMenu(Pharmacy& pharmacy, Customer& customer) {
    int choice;
    do {
        cout << "Customer Menu:" << endl;
        cout << "1. Display All Medicines" << endl;
        cout << "2. Place Order" << endl;
        cout << "3. Display Previous Orders" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            pharmacy.displayAllMedicines();
            break;
        case 2: {
            pharmacy.placeOrder(customer);            
            break;
        }
        case 3: {
            customer.DisplayAllOrders();
            break;
        }
        case 0:
            cout << "Exiting Customer Menu." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    } while (choice != 0);
}

int main() {
    Pharmacy pharmacy;
    int choice;
    do {
        cout << "Main Menu:" << endl;
        cout << "1. Login as Admin" << endl;
        cout << "2. Login as Customer" << endl;
        cout << "3. Create New Customer" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string username, password;
            cout << "Enter admin username: ";
            cin >> username;
            cout << "Enter admin password: ";
            cin >> password;
            if (pharmacy.isAdminLogin(username, password)) {
                adminMenu(pharmacy);
            }
            else {
                cout << "Invalid admin credentials." << endl;
            }
            break;
        }
        case 2: {
            string username, password;
            cout << "Enter customer username: ";
            cin >> username;
            cout << "Enter customer password: ";
            cin >> password;
            Customer* customer = pharmacy.findCustomer(username, password);
            if (customer != nullptr) {
                customerMenu(pharmacy, *customer);
            }
            else {
                cout << "Invalid customer credentials." << endl;
            }
            break;
        }
        case 3: {
            string username, password;
            cout << "Enter new customer username: ";
            cin >> username;
            cout << "Enter new customer password: ";
            cin >> password;
            pharmacy.createCustomer(username, password);
            cout << "Customer created successfully." << endl;
            break;
        }
        case 0:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}
