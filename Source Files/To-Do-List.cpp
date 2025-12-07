// To-Do-List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "login.h"
#include "Tasks.h"
#include "Change_Information.h"
#include "Settings.h"
#include <iostream>

using namespace std;

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
            cout << "A : Add tasks : " << endl;
            cout << "D : Delete the tasks : " << endl;
            cout << "I : Important : " << endl;
            cout << "M : Mark as done : " << endl;
            cout << "T : Show the task : " << endl;
            cout << "S : Settings : " << endl;
            cout << "E : Return the login or singup page : " << endl;
            cout << "What your choice : ";

            char lact;
            cin >> lact;

            if (lact == 'A' || lact == 'a')
                Tasks::AddTask();
            else if (lact == 'D' || lact == 'd')
                Tasks::delete_tasks();
            else if (lact == 'I' || lact == 'i')
                Tasks::important_taks();
            else if (lact == 'M' || lact == 'm')
                Tasks::mark_task();
            else if (lact == 'T' || lact == 't')
                Tasks::show_taks();
            else if (lact == 'S' || lact == 's')
                Settings::settings();
            else if (lact == 'E' || lact == 'e')
                login2 = false;
            else
                cout << "You entered wrong key, Please try again." << endl;
        }
    }
}
