#include "Change_Information.h"
#include "Login.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool Change_Information::userExit;

bool Is_Valid_Password(const string& password)
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

void save_information(vector<string>& username1, vector<string>& mail, vector<string>& password)
{
	string username2, mail1, password1;
	ifstream user("users.txt");
	if (!user.is_open())
		cerr << "Error : Unable users file" << endl;
	else {
		while (user >> username2 >> mail1 >> password1)
		{
			username1.push_back(username2);
			mail.push_back(mail1);
			password.push_back(password1);
		}
		user.close();
	}
}

void copy_task(const string& filename, const string& important, const string& markedtask,
	vector<string>& tasksc, vector<string>& itasksc, vector<string>& mtasksc)
{
	ifstream task(filename);
	if (!task.is_open())
		cerr << "Error : Tasks file is not found." << endl;
	else {
		string sentence;
		while (getline(task, sentence))
			tasksc.push_back(sentence);
	}
	task.close();

	ifstream important1(important);
	if (!important1.is_open())
		cerr << "Error : İmportant tasks file is not found." << endl;
	else {
		string sentence;
		while (getline(important1, sentence))
			itasksc.push_back(sentence);
	}
	important1.close();

	ifstream markedtasks(markedtask);
	if (!markedtasks.is_open())
		cerr << "Error : Markedtasks file is not found." << endl;
	else {
		string sentence;
		while (getline(markedtasks, sentence))
			mtasksc.push_back(sentence);
	}
	markedtasks.close();
}

void save_task(const string& filename, const vector<string>& taskc)
{
	ofstream tasks(filename);
	if (taskc.size() == 0)
		cout << "Dont write any tasks." << endl;
	else {
		for (int i = 0; i < taskc.size(); i++)
		{
			tasks << taskc[i] << endl;
		}
		tasks.close();
	}
}

void save_itask(const string& important, const vector<string>& itaskc)
{
	ofstream important1(important);
	if (itaskc.size() == 0)
		cout << "Dont write any important task" << endl;
	else {
		for (int i = 0; i < itaskc.size(); i++)
			important1 << itaskc[i] << endl;
		important1.close();
	}
}

void save_mtask(const string& markedtasks, const vector<string>& mtaskc)
{
	ofstream markedtask(markedtasks);
	if (mtaskc.size() == 0)
		cout << "Dont write any marked taks" << endl;
	else {
		for (int i = 0; i < mtaskc.size(); i++)
		{
			markedtask << mtaskc[i] << endl;
		}
		markedtask.close();
	}
}

void Change_Information::change_information()
{
	string tasks = (Login::username_file2 + "_tasks") + ".txt";
	string important = (Login::username_file2 + "_important") + ".txt";
	string markedtasks = (Login::username_file2 + "_marked") + ".txt";

	bool ciexit = false;
	vector<string> mail, password, username1;
	vector<string> tasksc, itasksc, mtasksc;
	save_information(username1, mail, password);
	while (!ciexit)
	{
		std::cout << "P : Change password : " << endl;
		std::cout << "U : Change username : " << endl;
		std::cout << "E : Exit the page : " << endl;
		std::cout << "What will do : ";

		char ciact;
		cin >> ciact;
		if (ciact == 'P' || ciact == 'p')
		{
			string password2;
			while (password2 != Login::password_file2)
			{
				std::cout << "Please enter password" << endl;
				cin >> password2;
			}
			int idx = 0;
			for (int i = 0; i < password.size(); i++)
				if (password[i] == password2)
					idx = i;
			do
			{
				cout << "Please enter new password " << endl;
				cin >> password2;
			} while (!Is_Valid_Password(password2));

			ofstream user("users.txt");
			for (int i = 0; i < username1.size(); i++)
			{
				user << username1[i] << " " << mail[i] << " ";
				if (idx == i)
					user << password2 << endl;
				else
					user << password[i] << endl;
			}
			user.close();
			Change_Information::userExit = true;
			ciexit = true;
		}
		else if (ciact == 'U' || ciact == 'u')
		{
			std::cout << "Please enter new username : " << endl;
			string username4;
			cin >> username4;
			ifstream tasks2(tasks);
			if (!tasks2.is_open())
				continue;
			else {
				tasks2.close();
				copy_task(tasks, important, markedtasks, tasksc, itasksc, mtasksc);

				const char* filename1 = tasks.c_str();
				remove(filename1);

				const char* important123 = important.c_str();
				remove(important123);

				const char* markedtask123 = markedtasks.c_str();
				remove(markedtask123);

				tasks = (username4 + "_tasks") + ".txt";
				important = (username4 + "_important") + ".txt";
				markedtasks = (username4 + "_marked") + ".txt";

				save_task(tasks, tasksc);
				save_itask(important, itasksc);
				save_mtask(markedtasks, mtasksc);

				int idx = 0;
				for (int i = 0; i < password.size(); i++)
					if (username1[i] == Login::username_file2)
						idx = i;

				ofstream user("users.txt");
				for (int i = 0; i < username1.size(); i++)
				{
					if (i == idx)
						user << username4 << " " << mail[i] << " " << password[i] << endl;
					else
						user << username1[i] << " " << mail[i] << " " << password[i] << endl;
				}
				user.close();
			}

		}
		else if (ciact == 'E' || ciact == 'e')
			ciexit = true;
		else
			std::cout << "You entered wrong key" << endl;
	}
}
