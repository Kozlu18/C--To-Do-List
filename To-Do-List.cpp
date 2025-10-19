#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
#include <fstream>
#include <direct.h>
#include <cstdio>

using namespace std;

string email_input, password_input, username_file;

struct User
{
	string username;
	string email;
	string password;
};

bool Is_Valid_Password(string password)
{
	if (password.size() < 8)
	{
		std::cout << "Your password must higher than eight chracter." << endl;
		return false;
	}
	bool has_digit = false, has_alpha = false;
	for (char c : password)
	{
		if (isalpha(c)) has_alpha = true;
		if (isdigit(c)) has_digit = true;
	}
	return has_alpha && has_digit;
}

bool Is_Valid_Email(string email)
{
	return email.find("gmail.com") != string::npos ||
		email.find("icloud.com") != string::npos ||
		email.find("hotmail.com") != string::npos;
}

bool Login(string &username)
{
	int attempts = 0;

	cout << "Please enter email: ";
	cin >> email_input;
	cout << "Please enter password: ";
	cin >> password_input;

	ifstream file("users.txt");
	if (!file.is_open())
	{
		cerr << "Unable the txt file." << endl;
		return false;
	}

	string email_file, password_file;
	while (file >> username_file >> email_file >> password_file)
	{
		if (email_file == email_input && password_file == password_input)
		{
			cout << "Your information is true." << endl << "Welcome to To-Do-List" << " " << username_file << endl;
			file.close();
			username = username_file;
			return true;
		}
	}

	file.close();
	cout << "Invalid email or password. Please try again." << endl;
	return false;
}

void Singup(User& user)
{
	std::cout << "Please enter username : ";
	std::cin >> user.username;
	do
	{
		std::cout << "Please enter email : ";
		std::cin >> user.email;
	} while (!Is_Valid_Email(user.email));
	std::cout << "Your email is correct." << endl;
	do
	{
		std::cout << "Enter password. (Password must higher than eight character) : ";
		std::cin >> user.password;

	} while (!Is_Valid_Password(user.password));

	ofstream file("users.txt", ios::app);
	if (file.is_open())
	{
		file << user.username << " " << user.email << " " << user.password << endl;
		file.close();
		cout << "Your account succesfully created and saved." << endl;
	}
	else {
		cerr << "Error : Unable to open file for writing." << endl;
	}
}

int findmaxid(const string &filename)
{
	std::ifstream tasks(filename);
	if (!tasks.is_open()) {
		std::cerr << "Error: File is not opened." << std::endl;
		return 0;
	}

	int max_id = 0;
	std::string line;

	// Dosyayı satır satır oku
	while (std::getline(tasks, line)) {
		std::stringstream ss(line);
		int current_id;

		if (ss >> current_id) {
			if (current_id > max_id) {
				max_id = current_id;
			}
		}
	}
	tasks.close();
	return max_id;
}

void Addtask(const string &filename)
{
	ofstream tasks(filename);
	bool addtask = true;
	int yeni_id = findmaxid(filename) + 1;
	if (!tasks.is_open())
		cerr << "Error : Unable txt file." << endl;
	while (addtask)
	{
		cout << "Please enter the task : " << endl;
		string cümle;
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, cümle);
		tasks << "ID : " << yeni_id << " " << "Task : " << cümle << " " << "Status : " << "To be done" << endl;
		yeni_id += 1;
		cout << "IF you exit the page please enter 'E' or you continue add the task please enter 'C' : ";
		char action;
		cin >> action;
		if (action == 'E' || action == 'e')
			addtask = false;
		else if (action != 'C' && action != 'c')
			break;
	}
	tasks.close();
}

void i_show_important(vector<string>& important2, const string &important)
{
	ifstream important1(important);
	if(!important1.is_open())
		cerr << "Error : İmportant tasks file is not found." << endl;
	string sentence;
	while(getline(important1, sentence))
	{
		cout << sentence << endl;
		important2.push_back(sentence);
	}
	important1.close();
}

void t_delete_task(vector<string>& task3, const string& filename)
{
	ifstream tasks(filename);
	if(!tasks.is_open())
		cerr << "Error : Unable tasks file" << endl;
	string sentence;
	while(getline(tasks, sentence))
	{
		cout << sentence << endl;
		task3.push_back(sentence);
	}	
	tasks.close();
}

void delete_task(const string &filename, const string &important)
{
	bool d_t_e = false;
	while(!d_t_e)
	{
		cout << "You delete important task or you delete task" << endl;
		cout << "IF you delete important tasks please enter 'I' or you delete tasks please enter 'T' or exit enter 'E' : " << endl;

		char dtact;
		cin >> dtact;

		if(dtact == 'I' || dtact == 'i')
		{
			vector<string> important2;
			i_show_important(important2, important);
			cout << "Please enter task ID : ";

			int id;
			cin >> id;

			if(id < 0 || id >= important2.size()) {
				cout << "Invalid task ID. Please try again." << endl;
				continue;
			}

			ofstream important1(important);
			for(int i = 0; i < important2.size(); i++)
			{
				if(id == i)
					continue;
				string sentence1 = important2[i];
				important1 << sentence1 << endl;
			}
			important1.close();
		}
		else if(dtact == 'T' || dtact == 't')
		{
			vector<string> task3;
			t_delete_task(task3, filename);	
			cout << "Please enter task ID : ";

			int id;
			cin >> id;

			if(id < 0 || id >= task3.size()) {
				cout << "Invalid task ID. Please try again." << endl;
				continue;
			}

			ofstream tasks(filename);
			for(int i = 0; i < task3.size(); i++)
			{
				if(id == i)
					continue;
				string sentence1 = task3[i];
				tasks << sentence1 << endl;
			}
			tasks.close();
		}
		else if(dtact == 'E' || dtact == 'e')
			d_t_e = true;
	}
	cout << endl;
}

void show_the_task(const string &filename, const string &important)
{
	ifstream tasks(filename);
	if (!tasks.is_open())
		cerr << "Error : Task file is not opened." << endl;
	string sentence;
	while (getline(tasks, sentence))
	{
		cout << sentence << endl;
	}
	ifstream important1(important);
	if(!important1.is_open())
		cerr << "Error : Task file is not opened." << endl;
	string imsentence;
	while(getline(important1, imsentence))
		cout << imsentence << endl;
	important1.close();
	tasks.close();
	this_thread::sleep_for(chrono::seconds(3));
}

void show_important(vector<string>& import, const string &filename)
{
	ifstream tasks(filename);
	if (!tasks.is_open())
		cerr << "Error : Tasks file is not opened." << endl;
	string sentence;
	while (getline(tasks, sentence))
	{
		cout << sentence << endl;
		import.push_back(sentence);
	}
	tasks.close();
	this_thread::sleep_for(chrono::seconds(3));
}

void deletei(const string &filename)
{
	ofstream tasks(filename);
	if (!tasks.is_open()) {
		std::cerr << "File is not opened." << std::endl;
	}
	else {
		tasks.close();
	}
}

void Important(const string &filename, const string& important)
{
	bool important1 = true;
	while (important1)
	{
		cout << "I : Mark the task as important : " << endl;
		cout << "S : Show the important tasks : " << endl;
		cout << "E : Exit : " << endl;
		cout << "What your choice : ";

		char iact;
		cin >> iact;

		if (iact == 'I' || iact == 'i')
		{
			ofstream important2(important, ios::app);

			vector<string> import;
			show_important(import, filename);

			cout << "Please enter task ID number : ";
			int j;
			cin >> j;

			if (important2.is_open())
			{
				important2 << import[j] << " " << "*" << endl;
				important2.close();
			}

			deletei(filename);

			ofstream tasks(filename, ios::app);
			if (tasks.is_open())
			{
				for (int i = 0; i < import.size(); i++)
				{
					if (i == j)
						continue;
					string sentence1 = import[i];
					tasks << sentence1 << endl;
				}
				tasks.close();
			}
		}
		else if (iact == 'S' || iact == 's')
		{
			ifstream important2(important);
			if (!important2.is_open())
				cerr << "Error : Txt file is not opened." << endl;
			string sentence2;
			while (getline(important2, sentence2))
			{
				cout << sentence2 << endl;
			}
			important2.close();
		}
		else if (iact == 'E' || iact == 'e')
			important1 = false;
		else
			cout << "You entered wrong key. Please try again." << endl;
	}

}
void show(vector<string>& task, const string &filename)
{
	ifstream tasks(filename);
	if (!tasks.is_open())
	{
		cerr << "Tasks txt file is not opened. Please try again." << endl;
	}
	string sentence;
	while (getline(tasks, sentence))
	{
		cout << sentence << endl;
		task.push_back(sentence);
	}
	tasks.close();
}

void deletet(const string &filename)
{
	ofstream tasks(filename);
	if (!tasks.is_open()) {
		std::cerr << "File is not opened." << std::endl;
	}
	else {
		tasks.close();
	}
}

void mark_task(const string &filename, const string &important, const string & markedtask)
{
	bool markaction = true;
	while (markaction)
	{
		cout << "M : Mark as done for task : " << endl;
		cout << "S : Show the marked as done for task : " << endl;
		cout << "E : Exit the page : " << endl;
		cout << "What your choice : ";

		char maction;
		cin >> maction;

		vector<string> task;
		if (maction == 'M' || maction == 'm')
		{
			show(task, filename);
			cout << "Please enter the task ID number : ";
			int N;
			cin >> N;
			string hedef_cumle = task[N];
			stringstream ss(hedef_cumle);
			string kelimeler;
			vector<string> word;
			while(ss >> kelimeler)
				word.push_back(kelimeler);
			ofstream markedtasks(markedtask, ios::app);
			if (markedtasks.is_open())
			{
				for(int i = 0; i < word.size(); i++)
				{
					if(word[i] == "To")
						continue;
					if(word[i] == "be")
						continue;
					if(word[i] == "done")
						continue;
					markedtasks << word[i] << " ";
					
				}
				markedtasks << "Done" << endl;
				markedtasks.close();
			}
			deletet(filename);
			ofstream tasks(filename, ios::app);
			if (tasks.is_open())
			{
				for (int i = 0; i < task.size(); i++)
				{
					if (i == N)
						continue;
					tasks << task[i] << endl;
				}
				tasks.close();
			}
		}
		else if (maction == 'S' || maction == 's')
		{
			ifstream markedtasks(markedtask);
			if (!markedtasks.is_open())
				cerr << "Marked tasks file is not opened." << endl;
			string sentence;
			while (getline(markedtasks, sentence))
				cout << sentence << endl;
			markedtasks.close();
		}
		else if (maction == 'E' || maction == 'e')
			markaction = false;
		else
			cout << "You entered wrong key please try again : " << endl;
	}
}

void save_information(vector<string>& username1, vector<string>& mail, vector<string>& password)
{
	string username2, mail1, password1;
	ifstream user("users.txt");
	if(!user.is_open())
		cerr << "Error : Unable users file" << endl;
	else{
		while(user >> username2 >> mail1 >> password1)
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
	if(!task.is_open())
		cerr << "Error : Tasks file is not found." << endl;
	else{
		string sentence;
		while(getline(task, sentence))
			tasksc.push_back(sentence);
	}
	task.close();

	ifstream important1(important);
	if(!important1.is_open())
		cerr << "Error : İmportant tasks file is not found." << endl;
	else{
		string sentence;
		while(getline(important1, sentence))
			itasksc.push_back(sentence);
	}
	important1.close();

	ifstream markedtasks(markedtask);
	if(!markedtasks.is_open())
		cerr << "Error : Markedtasks file is not found." << endl;
	else{
		string sentence;
		while(getline(markedtasks, sentence))
			mtasksc.push_back(sentence);
	}
	markedtasks.close();
}

void save_task(const string& filename, const vector<string>& taskc)
{
	ofstream tasks(filename);
	if(taskc.size() == 0)
		cout << "Dont write any tasks." << endl;
	else{
		for(int i = 0; i < taskc.size(); i++)
		{
			tasks << taskc[i] << endl;
		}
		tasks.close();
	}
}

void save_itask(const string& important, const vector<string>& itaskc)
{
	ofstream important1(important);
	if(itaskc.size() == 0)
		cout << "Dont write any important task" << endl;
	else{
		for(int i = 0; i < itaskc.size(); i++)
			important1 << itaskc[i] << endl;
		important1.close();
	}
}

void save_mtask(const string& markedtasks, const vector<string>& mtaskc)
{
	ofstream markedtask(markedtasks);
	if(mtaskc.size() == 0)
		cout << "Dont write any marked taks" << endl;
	else{
		for(int i = 0; i < mtaskc.size(); i++)
		{
			markedtask << mtaskc[i] << endl;
		}
		markedtask.close();
	}
}

void change_information(string& filename, string& important, string& markedtask, bool& login, string& username)
{
	bool ciexit = false;
	vector<string> mail, password, username1;
	vector<string> tasksc, itasksc, mtasksc;
	save_information(username1, mail, password);
	while(!ciexit)
	{
		std::cout << "P : Change password : " << endl;
		std::cout << "U : Change username : " << endl;
		std::cout << "E : Exit the page : " << endl;
		std::cout << "What will do : ";

		char ciact;
		cin >> ciact;
		if(ciact == 'P' || ciact == 'p')
		{
			string password2;
			while(password2 != password_input)
			{
				std::cout << "Please enter password" << endl;
				cin >> password2;
			}
			int idx = 0;
			for(int i = 0; i < password.size(); i++)
				if(password[i] == password2)
					idx = i;
			do
			{
				cout << "Please enter new password " << endl;
				cin >> password2;
			} while (!Is_Valid_Password(password2));
			
			ofstream user("users.txt");
			for(int i = 0; i < username1.size(); i++)
			{
				user << username1[i] << " " << mail[i] << " ";
				if(idx == i)
					user << password2 << endl;
				else
					user << password[i] << endl;
			}
			user.close();
			login = false;
			ciexit = true;
		}
		else if(ciact == 'U' || ciact == 'u')
		{
			std::cout << "Please enter new username : " << endl;
			string username4;
			cin >> username4;
			ifstream tasks(filename);
			if(!tasks.is_open())
				continue;
			else{
				tasks.close();
				copy_task(filename, important, markedtask, tasksc, itasksc, mtasksc);

				const char* filename1 = filename.c_str();
				remove(filename1);

				const char* important123 = important.c_str();
				remove(important123);

				const char* markedtask123 = markedtask.c_str();
				remove(markedtask123);
				
				filename = (username4 + "_tasks") + ".txt";
				important = (username4 + "_important") + ".txt";
				markedtask = (username4 + "_marked") + ".txt";

				save_task(filename, tasksc);
				save_itask(important, itasksc);
				save_mtask(markedtask, mtasksc);

				int idx = 0;
				for(int i = 0; i < password.size(); i++)
					if(username1[i] == username_file)
						idx = i;

				ofstream user("users.txt");
				for(int i = 0; i < username1.size(); i++)
				{
					if(i == idx)
						user << username4 << " " << mail[i] << " " << password[i] << endl;
					else
						user << username1[i] << " " << mail[i] << " " << password[i] << endl;
				}
				user.close();
				username = username4;
			}

		}
		else if(ciact == 'E' || ciact == 'e')
			ciexit = true;
		else 
			std::cout << "You entered wrong key" << endl;
	} 
}

int main()
{
	bool siteexit = false;
	while (!siteexit)
	{
		string username;
		std::cout << "\n---Welcome to the To-Do-List ---" << endl;
		bool login = false;
		User user;
		while (!login && !siteexit)
		{
			std::cout << endl << "Please you have account enter 'L' or you dont have account please enter 'S' or you exit press 'E' : ";
			char action;
			std::cin >> action;
			if (action == 'S' || action == 's')
				Singup(user);
			else if (action == 'L' || action == 'l')
				login = Login(username);
			else if(action == 'E' || action == 'e')
				siteexit = true;
			else
				std::cout << "You entered wrong key. Please try again." << endl;
		}
		while (login)
		{
			std::cout << "A : Add task : " << endl;
			std::cout << "D : Delete task : " << endl;
			std::cout << "I : Important : " << endl;
			std::cout << "M : Mark as done : " << endl;
			std::cout << "T : Show the task : " << endl;
			std::cout << "C : Change the personal information : " << endl;
			std::cout << "E : Return the login or singup page : " << endl;
			std::cout << "What your choice : ";

			char act;
			std::cin >> act;

			string filename = (username + "_tasks") + ".txt";
			string important = (username + "_important") + ".txt";
			string markedtask = (username + "_marked") + ".txt";

			if (act == 'A' || act == 'a')
				Addtask(filename);
			else if(act == 'D' ||act == 'd')
				delete_task(filename, important);
			else if (act == 'I' || act == 'i')
				Important(filename, important);
			else if (act == 'M' || act == 'm')
				mark_task(filename, important, markedtask);
			else if (act == 'T' || act == 't')
				show_the_task(filename, important);
			else if(act == 'C' || act == 'c')
				change_information(filename, important, markedtask, login, username);
			else if (act == 'E' || act == 'e')
			{
				std::cout << "Returning the login and Singup page.";
				login = false;
			}
			else
				std::cout << "You entered wrong key. Please try again." << endl;
		}
	}
}
