#include "Admin.h"
#include<fstream>
#include <string>
#include <sstream>
using namespace std;

Admin::Admin() {

}
Admin::Admin(string uname, string pass) {
    username = uname;
    password = pass;
}

string Admin:: getUsername() const {
    return username;
}

string Admin:: getPassword() const {
    return password;
}

void Admin::loadFromFile() {
	fstream adminfile;
	adminfile.open(Admin::filename, ios::in);
	vector < string > v;
	if (adminfile.is_open()) {
		string line;
		getline(adminfile, line);
		stringstream ss(line);

		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			v.push_back(substr);
		}


		username = v[0];
		password = v[1];
	}

	adminfile.close();

}