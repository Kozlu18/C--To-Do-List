#include "includes.h"

using namespace std;
namespace fs = std::filesystem;

string NList::listname;

void Add_List()
{
    cout << "Please enter new list name(example shopping...) : " << endl;

    string listname;
    cin >> listname;

    if (fs::create_directory(listname)) {
        std::cout << "Folder succesfully created.\n";
    }
    else {
        // Klasör zaten varsa veya hata oluþtuysa false döner
        if (fs::exists(listname)) {
            std::cout << "The folder already exists.\n";
        }
        else {
            std::cout << "Folder dont created.\n";
        }
    }

}

void Delete_List()
{

}

void NList::ListPage()
{
    bool NList_ext = false;
    while (!NList_ext)
    {
        cout << "A : Add new list : " << endl;
        cout << "D : Delete list : " << endl;
        cout << "E : Exit the page : " << endl;

        char liact;
        cin >> liact;

        if (liact == 'A' || liact == 'a')
            Add_List();
        else if (liact == 'D' || liact == 'd')
            Delete_List();
        else if (liact == 'E' || liact == 'e')
            NList_ext = true;
    }
}