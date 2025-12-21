// To-Do-List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "login.h"
#include "Tasks.h"
#include "Change_Information.h"
#include "Settings.h"
#include <iostream>
#include <fstream>

using namespace std;

bool Settings::nts;
bool Settings::dtf;

void Clear()
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

int main()
{
    bool siteexit = false;
    while (!siteexit)
    {
        bool login2 = false;
        cout << "C : Create account or L : Login account or E : exit console." << endl;

        char act;
        cin >> act;

        if (act == 'c' || act == 'C')
            Login::SingUp();
        else if (act == 'L' || act == 'l')
            login2 = Login::login();
        else if (act == 'E' || act == 'e')
            siteexit = true;
        else
            cout << "You entered wrong key" << endl;
        while (login2 && !Change_Information::userExit)
        {
            Clear();
            string setting = (Login::username_file2 + "_settings") + ".txt";
            ifstream settingf(setting);
            string empt;

            while (settingf >> empt >> empt >> Settings::dtf >> empt >> empt >> Settings::nts);
            settingf.close();

            cout << "E : Edit tasks : " << endl;
            cout << "S : Settings : " << endl;
            cout << "R : Return the login or singup page : " << endl;
            cout << "What your choice : ";

            char lact;
            cin >> lact;

            if (lact == 'E' || lact == 'e')
                Tasks::TasksPage();
            else if (lact == 'S' || lact == 's')
                Settings::settings();
            else if (lact == 'R' || lact == 'r')
                login2 = false;
            else
                cout << "You entered wrong key, Please try again." << endl;
        }
    }
}
