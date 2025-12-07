#include "Tasks.h"
#include "Login.h"
#include "Settings.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

using namespace std;

int findmaxid(const string& tasks)
{
	std::ifstream filename(tasks);
	if (!filename.is_open()) {
		std::cerr << "Error: File is not opened." << std::endl;
		return 0;
	}

	int max_id = 0;
	std::string line;

	while (std::getline(filename, line)) {
		std::stringstream ss(line);
		int current_id;

		if (ss >> current_id) {
			if (current_id > max_id) {
				max_id = current_id;
			}
		}
	}
	filename.close();
	return max_id;
}


void Tasks::AddTask()
{
	string tasks = (Login::username_file2 + "_tasks") + ".txt";
	ofstream filename(tasks, ios::app);
	bool addtask = true;
	int yeni_id = findmaxid(tasks) + 1;
	if (!filename.is_open())
		cerr << "Error : Unable txt file." << endl;
	while (addtask)
	{
		cout << "Please enter the task : " << endl;
		string cümle;
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, cümle);
		filename << "ID : " << yeni_id << " " << "Task : " << cümle << " " << "Status : " << "To be done" << endl;
		yeni_id += 1;
		cout << "IF you exit the page please enter 'E' or you continue add the task please enter 'C' : ";
		char action;
		cin >> action;
		if (action == 'E' || action == 'e')
			addtask = false;
		else if (action != 'C' && action != 'c')
			break;
	}
	filename.close();
}

void save_i(const string& important, vector<string>* itask = new vector<string>)
{
	ifstream important2(important);
	if (!important2.is_open())
		cerr << "Error : Unable important txt file." << endl;
	else {
		string sentence;
		while (getline(important2, sentence))
		{
			cout << sentence << endl;
			itask->push_back(sentence);
		}
	}
	important2.close();
}

void save_t(const string& tasks, vector<string>* tasks2 = new vector<string>)
{
	ifstream task(tasks);
	if (!task.is_open())
		cerr << "Error : Unable tasks txt file." << endl;
	else {
		string sentence;
		while (getline(task, sentence))
		{
			cout << sentence << endl;
			tasks2->push_back(sentence);
		}
		task.close();
	}
}

bool bdftt; // Görevler kısmındaki dtf

void select2()
{
	string tasks = (Login::username_file2 + "_tasks") + ".txt";
	string important = (Login::username_file2 + "_important") + ".txt";

	vector<string>* itask = new vector<string>;
	vector<string>* tasks2 = new vector<string>;

	cout << "I : Delete important tasks : " << endl;
	cout << "D : Delete tasks : " << endl;

	char sact;
	cin >> sact;

	if (sact == 'I' || sact == 'i')
	{
		save_i(important, itask);
		cout << "Please enter the tasks id : " << endl;

		int idx;
		cin >> idx;
		
		bool bsure = false;
		if (bdftt)
		{
			do
			{
				cout << "Please enter 'SURE' : ";
				string sure;
				cin >> sure;
				if (sure == "SURE")
					bsure = true;
			} while (!bsure);
		}

		if (idx < itask->size()) {
			itask->erase(itask->begin() + idx);
		}
		else
			cout << "Dont deleted your tasks." << endl;
		
		ofstream important2(important);
		for (size_t i = 0; i < itask->size(); ++i) {
			important2 << (*itask)[i];
		}
		important2.close();
	}
	else if (sact == 'D' || sact == 'd')
	{
		save_t(tasks, tasks2);
		cout << "Please enter the tasks id : ";

		int idx;
		cin >> idx;

		bool bsure2 = false;

		if (bdftt)
		{
			do
			{
				cout << "Please enter SURE : ";
				string sure2;
				cin >> sure2;
				if (sure2 == "SURE")
					bsure2 = true;
			} while (!bsure2);
		}

		if (idx < tasks2->size())
		{
			tasks2->erase(tasks2->begin() + idx);
		}
		else
			cout << "Dont deleted your task." << endl;

		ofstream task(tasks);
		for (size_t i = 0; i < tasks2->size(); i++)
			task << (*tasks2)[i] << endl;
		task.close();
	}
	else
		cout << "You entered wrong key returning delete tasks page." << endl;
}

void Tasks::delete_tasks()
{
	bool dtext = false;
	while (!dtext)
	{
		string setting = (Login::username_file2 + "_settings") + ".txt";
		ifstream settingf(setting);
		string empt;
		while(settingf >> bdftt)
		settingf.close();

		cout << "D : Delete Tasks : " << endl;
		cout << "E : Exit the page : " << endl;

		char dact;
		cin >> dact;

		if (dact == 'D' || dact == 'd')
			select2();
		else if (dact == 'E' || dact == 'e')
			dtext = true;
		else
			cout << "You entered wrong key please try again." << endl;
	}
}

void show_important(const string& tasks, vector<string>* import2 = new vector<string>)
{
	ifstream tasks2(tasks);
	if (!tasks2.is_open())
		cerr << "Error : Tasks file is not opened." << endl;
	string sentence;
	while (getline(tasks2, sentence))
	{
		cout << sentence << endl;
		import2->push_back(sentence);
	}
	tasks2.close();
	this_thread::sleep_for(chrono::seconds(3));
}

void deletei(const string& tasks)
{
	ofstream tasks2(tasks);
	if (!tasks2.is_open()) {
		std::cerr << "File is not opened." << std::endl;
	}
	else {
		tasks2.close();
	}
}

void Tasks::important_taks()
{
	string tasks = (Login::username_file2 + "_tasks") + ".txt";
	string important = (Login::username_file2 + "_important") + ".txt";
	vector<string>* import2 = new vector<string>;

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

			show_important(tasks, import2);

			cout << "Please enter task ID number : ";
			int j;
			cin >> j;

			if (important2.is_open())
			{
				important2 << (*import2)[j] << " " << "*" << endl;
				important2.close();
			}

			deletei(tasks);

			ofstream tasks2(tasks, ios::app);
			if (tasks2.is_open())
			{
				for (int i = 0; i < import2->size(); i++)
				{
					if (i == j)
						continue;
					string sentence1 = (*import2)[i];
					tasks2 << sentence1 << endl;
				}
				tasks2.close();
			}
		}
		else if (iact == 'S' || iact == 's')
		{
			ifstream important2(important);
			if (!important2.is_open())
				cerr << "Error : Txt file is not opened." << endl;
			string* sentence2 = new string ;
			while (getline(important2, *sentence2))
			{
				cout << *sentence2 << endl;
			}
			this_thread::sleep_for(chrono::seconds(3));
			important2.close();
		}
		else if (iact == 'E' || iact == 'e')
			important1 = false;
		else
			cout << "You entered wrong key. Please try again." << endl;
	}
}

void show(const string& filename, vector<string>* task = new vector<string>)
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
		task->push_back(sentence);
	}
	tasks.close();
}

void deletet(const string& filename)
{
	ofstream tasks(filename);
	if (!tasks.is_open()) {
		std::cerr << "File is not opened." << std::endl;
	}
	else {
		tasks.close();
	}
}

void Tasks::mark_task()
{
	string tasks = (Login::username_file2 + "_tasks") + ".txt";
	string important = (Login::username_file2 + "_important") + ".txt";
	string markedtasks = (Login::username_file2 + "_marked") + ".txt";

	bool markaction = true;
	while (markaction)
	{
		cout << "M : Mark as done for task : " << endl;
		cout << "S : Show the marked as done for task : " << endl;
		cout << "E : Exit the page : " << endl;
		cout << "What your choice : ";

		char maction;
		cin >> maction;

		vector<string>* task = new vector<string>;
		if (maction == 'M' || maction == 'm')
		{
			show(tasks, task);
			cout << "Please enter the task ID number : ";

			int N;
			cin >> N;

			string hedef_cumle =(*task)[N];
			stringstream ss(hedef_cumle);
			string kelimeler;
			vector<string>* word = new vector<string>;

			while (ss >> kelimeler)
				word->push_back(kelimeler);

			ofstream markedtasks2(markedtasks, ios::app);

			if (markedtasks2.is_open())
			{
				for (int i = 0; i < word->size(); i++)
				{
					if ((*word)[i] == "To")
						continue;
					if ((*word)[i] == "be")
						continue;
					if ((*word)[i] == "done")
						continue;
					markedtasks2 << (*word)[i] << " ";

				}
				markedtasks2 << "Done" << endl;
				markedtasks2.close();
			}

			deletet(tasks);
			ofstream tasks1(tasks, ios::app);

			if (tasks1.is_open())
			{
				for (int i = 0; i < task->size(); i++)
				{
					if (i == N)
						continue;
					tasks1 << (*task)[i] << endl;
				}
				tasks1.close();
			}
		}
		else if (maction == 'S' || maction == 's')
		{
			ifstream markedtasks2(markedtasks);
			if (!markedtasks2.is_open())
				cerr << "Marked tasks file is not opened." << endl;
			string sentence;
			while (getline(markedtasks2, sentence))
				cout << sentence << endl;
			markedtasks2.close();
		}
		else if (maction == 'E' || maction == 'e')
			markaction = false;
		else
			cout << "You entered wrong key please try again : " << endl;
	}
}

void Tasks::show_taks()
{
	string tasks = (Login::username_file2 + "_tasks") + ".txt";
	string important = (Login::username_file2 + "_important") + ".txt";
	string markedtasks = (Login::username_file2 + "_marked") + ".txt";

	ifstream filename(tasks);
	if (!filename.is_open())
		cerr << "Error : Task file is not opened." << endl;
	string sentence;
	while (getline(filename, sentence))
	{
		cout << sentence << endl;
	}
	filename.close();
	ifstream important1(important);
	if (!important1.is_open())
		cerr << "Error : Important task file is not opened." << endl;
	string imsentence;
	while (getline(important1, imsentence))
		cout << imsentence << endl;
	important1.close();
	this_thread::sleep_for(chrono::seconds(3));
}
