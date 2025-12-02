#include "Forgetp.h"
#include "Login.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool is_valid_mail2(const string& mail3)
{
	return mail3.find("gmail.com") != string::npos ||
		mail3.find("hotmail.com") != string::npos;
}

bool is_valid_password2(const string& pass)
{
	if (pass.size() < 8)
		return false;
	bool has_digit = false, has_alpha = false;
	for (auto c : pass)
	{
		if (isalpha(c)) has_alpha = true;
		if (isdigit(c)) has_digit = true;
	}
	return has_alpha && has_digit;
}

void save_formation(vector<string>* username1 = new vector<string>, vector<string>* mail = new vector<string>, vector<string>* password = new vector<string>)
{
	string username2, mail1, password1;
	ifstream user("users.txt");
	if (!user.is_open())
		cerr << "Error : Unable users file" << endl;
	else {
		while (user >> username2 >> mail1 >> password1)
		{
			username1->push_back(username2);
			mail->push_back(mail1);
			password->push_back(password1);
		}
		user.close();
	}
}

void Forgetp::change_pass()
{
	vector<string>* mail = new vector<string>;
	vector<string>* password = new vector<string>;
	vector<string>* username1 = new vector<string>;

	string email, pass;
	int code;

	cout << "Please enter the code : ";
	cin >> code;

	if (code != Forgetp::rand)
		cout << "You entered wrong code returning the login or singup page." << endl;
	else {
		int idx = -1;
		while (idx < 0)
		{ 
			do
			{
				cout << "Please enter mail : ";
				cin >> email;
			} while (!is_valid_mail2(email));
			save_formation(username1, mail, password);
			for (int i = 0; i < mail->size(); i++)
			{
				if (email == (*mail)[i])
					idx = i;
			}
		}
		cout << "You entered true mail" << endl;
		do
		{
			cout << "Please enter new  : ";
			cin >> pass;
		} while (!is_valid_password2(pass));
		ofstream user("users.txt");
		for (int i = 0; i < username1->size(); i++)
		{
			user << (*username1)[i] << " " << (*mail)[i] << " ";
			if (idx == i)
				user << pass << endl;
			else
				user << (*password)[i] << endl;
		}
		user.close();
	}
}
