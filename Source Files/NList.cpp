#include "includes.h"

using namespace std;
namespace fs = std::filesystem;

string NList::listname;

void Add_List()
{
    cout << "Please enter new list name(example shopping...) : " << endl;

    string listname;
    cin >> listname;

    string nlistn = (Login::username_file2 + "_List") + ".txt";

    ofstream list(nlistn, ios::app);
    list << listname << endl;
    list.close();

    if (fs::create_directory(listname)) {
        std::cout << "Folder succesfully created.\n";
    }
    else {
        // Klasör zaten varsa veya hata oluştuysa false döner
        if (fs::exists(listname)) {
            std::cout << "The folder already exists.\n";
        }
        else {
            std::cout << "Folder dont created.\n";
        }
    }

}

void NList::show_list()
{
    cout << endl << "Your list : " << endl;

    string nlistn = (Login::username_file2 + "_List") + ".txt";
    string listname2;

    ifstream list(nlistn);

    if (!list.is_open())
        cerr << "Error : You dont have list." << endl;
    else
        while (list >> listname2)
            cout << listname2 << endl;
    cout << endl;
}

void Delete_List()
{
    NList::show_list();

    this_thread::sleep_for(chrono::seconds(1));
    cout << "Please enter the list name : ";

    string listname3;
    cin >> listname3;

    fs::remove_all(listname3);
}

void NList::ListPage()
{
    bool NList_ext = false;
    while (!NList_ext)
    {
        cout << "A : Add new list : " << endl;
        cout << "D : Delete list : " << endl;
        cout << "S : Show list : " << endl;
        cout << "E : Exit the page : " << endl;

        char liact;
        cin >> liact;

        if (liact == 'A' || liact == 'a')
            Add_List();
        else if (liact == 'D' || liact == 'd')
            Delete_List();
        else if (liact == 'S' || liact == 's')
            NList::show_list();
        else if (liact == 'E' || liact == 'e')
            NList_ext = true;
    }
}
