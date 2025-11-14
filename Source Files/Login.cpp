#include "Login.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string username, email, password;
string Login::username_file2;

bool is_valid_email(const string& email)
{
	return email.find("gmail.com") != string::npos ||
		email.find("hotmail.com") != string::npos;
}

bool is_valid_password(const string& password)
{
	if (password.size() < 8)
		return false;
	bool has_digit = false, has_alpha = false;
	for (auto c : password)
	{
		if (isalpha(c)) has_alpha = true;
		if (isdigit(c)) has_digit = true;
	}
	return has_alpha && has_digit;
}

bool Login::login()
{
	string email2, password2, username_file, email_file, password_file;
	cout << "Please enter email" << endl;
	cin >> email2;
	cout << "Please enter password" << endl;
	cin >> password2;
	ifstream users("users.txt");
	if (!users.is_open())
	{
		cerr << "Error : Unable users.txt file" << endl;
		return false;
	}
	while (users >> username_file >> email_file >> password_file)
	{
		if (email2 == email_file && password2 == password_file)
		{
			cout << "Welcome : " << username_file << endl;
			Login::username_file2 = username_file;
			users.close();
			return true;
		}

	}
	users.close();
	return false;
}

void Login::SingUp()
{
	cout << "Please enter username :" << endl;
	cin >> username;
	do
	{
		cout << "Please enter email : " << endl;
		cin >> email;
	} while (!is_valid_email(email));
	do
	{
		cout << "Please enter passwod : " << endl;
		cin >> password;
	} while (!is_valid_password(password));
	ofstream users("users.txt", ios::app);
	users << username << " " << email << " " << password;
	users.close();
}
