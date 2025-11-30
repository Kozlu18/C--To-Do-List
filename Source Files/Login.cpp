#include "Login.h"
#include "Forgetp.h"
#include "Change_Information.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>

using namespace std;

string username, email, password;
string Login::username_file2;
string Login::password_file2;
int Forgetp::rand;

bool is_valid_email(const string& email)
{
	return email.find("gmail.com") != string::npos ||
		email.find("hotmail.com") != string::npos;
}

bool is_valid_password(const string& password3)
{
	if (password3.size() < 8)
		return false;
	bool has_digit = false, has_alpha = false;
	for (auto c : password3)
	{
		if (isalpha(c)) has_alpha = true;
		if (isdigit(c)) has_digit = true;
	}
	return has_alpha && has_digit;
}

bool Login::login()
{
	string email2, password2, username_file, email_file, password_file;
	cout << "If you forgeted the password please enter 'P' or you remember password please enter 'C'" << endl;

	char fact;
	cin >> fact;

	if (fact == 'C' || fact == 'c')
	{
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
				Login::password_file2 = password_file;
				Change_Information::userExit = false;
				users.close();
				return true;
			}
		}
		users.close();
		cout << "You entered wrong mail or password please try again." << endl;
		return false;
	}
	else if (fact == 'P' || fact == 'p')
	{
		srand(time(0));
		const int min_value = 100000;
		const int max_value = 999999;
		Forgetp::rand = (rand() % (max_value - min_value + 1)) + min_value;
		cout << "Your code please remember the code : " << Forgetp::rand << endl;
		Forgetp::change_pass();
		return false;
	}
	else{
		cout << "You entered wrong key returning singup or login page." << endl;
		return false;
	}
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
