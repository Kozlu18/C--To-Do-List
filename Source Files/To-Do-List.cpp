// To-Do-List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "login.h"
#include "Tasks.h"
#include <iostream>

using namespace std;

int main()
{
    bool siteexit = false;
    while (!siteexit)
    {
        bool login2 = false;
        cout << "C : Create account or L : Login account" << endl;
        char act;
        cin >> act;
        if (act == 'c' || act == 'C')
            Login::SingUp();
        else if (act == 'L' || act == 'l')
            login2 = Login::login();
        else
            cout << "You entered wrong key" << endl;
        while (login2 == true)
        {
            cout << "A : Add tasks : " << endl;
            cout << "D : Delete the tasks : " << endl;
            cout << "I : Important : " << endl;
            cout << "M : Mark as done : " << endl;
            cout << "T : Show the task : " << endl;
            cout << "C : Change information : " << endl;
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
            else if (lact == 'C' || lact == 'c')
                Change_Information::change_information();
            else if (lact == 'E' || lact == 'e')
                login2 = false;
        }
    }
}

