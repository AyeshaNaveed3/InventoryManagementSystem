#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <vector>
#include <ctime>
#include<string>

using namespace std;

class Admin {
private:

	string username;
	string password;
	static string filename;
public:
	Admin();
	Admin(string uname, string pass);
	string getUsername() const;
	string getPassword() const;
	void loadFromFile();
 };

#endif//ADMIN_H
