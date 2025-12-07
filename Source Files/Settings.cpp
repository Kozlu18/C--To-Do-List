#include "Settings.h"
#include "Change_Information.h"
#include "Login.h"
#include <iostream>
#include <fstream>

using namespace std;

bool Settings::dtf = false; // silmeden önce onayla
bool dtf_file;

void Clears()
{
#if defined _WIN32
	system("cls");
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
	system("clear");
#endif
}

void vdtf()
{
	string setting = (Login::username_file2 + "_settings") + ".txt";
	ofstream settingf(setting);
	if (Settings::dtf == false)
	{
		Settings::dtf = true;
		cout << "Your status(0 = false, 1 = true) : " << Settings::dtf << endl;
		settingf << Settings::dtf;
		settingf.close();
	}
	else
	{
		Settings::dtf = false;
		cout << "Your status(0 = false, 1 = true) : " << Settings::dtf << endl;
		settingf << Settings::dtf;
		settingf.close();
	}
}

void Settings::settings()
{
	bool setexit = false;

	while (!setexit)
	{
		Clears();
		string setting = (Login::username_file2 + "_settings") + ".txt";
		ifstream settingf(setting);

		while (settingf >> dtf_file);
		settingf.close();

		cout << "C : Change personal information : " << endl;
		cout << "D : Confirm before deleting. Your status(0 = false, 1 = true) : " << dtf_file << endl;
		cout << "E : Exit settings : " << endl;

		char sact; // ayarlar yapýlacak olay
		cin >> sact;

		if (sact == 'C' || sact == 'c')
		{
			Change_Information::change_information();
			setexit = true;
		}
		else if (sact == 'D' || sact == 'd')
			vdtf();
		else if (sact == 'E' || sact == 'e')
			setexit = true;
	}
}