#include "Settings.h"
#include "Change_Information.h"
#include "Login.h"
#include <iostream>
#include <fstream>

using namespace std;

 // silmeden önce onayla
bool dtf_file, nts_file;// mst = Move starred tasks to the top


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
	if (dtf_file == false)
	{
		dtf_file = true;
		Settings::dtf = dtf_file;
		settingf << "DTF : " << dtf_file << " NTS : " << nts_file << endl;
		cout << "Your status(0 = false, 1 = true) : " << dtf_file << endl;
		settingf.close();
	}
	else
	{
		dtf_file = false;
		Settings::dtf = dtf_file;
		settingf << "DTF : " << dtf_file << " NTS : " << nts_file << endl;
		cout << "Your status(0 = false, 1 = true) : " << dtf_file << endl;
		settingf.close();
	}
}

void vnst()
{
	string setting = (Login::username_file2 + "_settings") + ".txt";
	ofstream settingf(setting);
	if(nts_file)
	{
		nts_file = false;
		settingf << "DTF : " << dtf_file << " NTS : " << nts_file << endl;
		settingf.close();
	}
	else{
		nts_file = true;
		settingf << "DTF : " << dtf_file << " NTS : " << nts_file << endl;
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
		string empt;

		while (settingf >> empt >> empt >> dtf_file >> empt >> empt >>nts_file);
		settingf.close();

		cout << "C : Change personal information : " << endl;
		cout << "D : Confirm before deleting. Your status(0 = false, 1 = true) : " << dtf_file << endl;
		cout << "S : Move starred tasks to the top : Your status(0 = false, 1 = true) : " << nts_file << endl;
		cout << "E : Exit settings : " << endl;

		char sact; // ayarlar yapılacak olay
		cin >> sact;

		if (sact == 'C' || sact == 'c')
		{
			Change_Information::change_information();
			setexit = true;
		}
		else if (sact == 'D' || sact == 'd')
			vdtf();
		else if (sact == 'S' || sact == 's')
			vnst();
		else if (sact == 'E' || sact == 'e')
			setexit = true;
	}
}
