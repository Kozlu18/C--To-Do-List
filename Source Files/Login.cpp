#include "includes.h"

using namespace std;
namespace fs = std::filesystem;

string username, email, password;
string Login::username_file2;
string Login::password_file2;
int Forgetp::rand;

void Clearl()
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

bool is_valid_email(const string& email)
{
	return email.find("gmail.com") != string::npos ||
		email.find("hotmail.com") != string::npos;
}

bool is_valid_password(const string& password3)
{
	if (password3.size() < 8)
		return false;
	bool has_digit = false, has_alpha = false;
	for (auto c : password3)
	{
		if (isalpha(c)) has_alpha = true;
		if (isdigit(c)) has_digit = true;
	}
	return has_alpha && has_digit;
}

bool Login::login()
{
	string email2, password2, username_file, email_file, password_file;
	cout << "If you forgeted the password please enter 'P' or you remember password please enter 'C'" << endl;

	char fact;
	cin >> fact;

	if (fact == 'C' || fact == 'c')
	{
		cout << "Please enter email" << endl;
		cin >> email2;
		cout << "Please enter password" << endl;
		cin >> password2;
		ifstream users("users.txt");
		if (!users.is_open())
		{
			cerr << "Error : Unable users.txt file" << endl;
			return false;
		}
		while (users >> username_file >> email_file >> password_file)
		{
			if (email2 == email_file && password2 == password_file)
			{
				cout << "Welcome : " << username_file << endl;
				Login::username_file2 = username_file;
				Login::password_file2 = password_file;
				Change_Information::userExit = false;
				users.close();

				string targetFolder = "Tasks_" + username_file;
				if (fs::exists(targetFolder) && fs::is_directory(targetFolder)) {

					// 3. KLASÖRE GİRİŞ (Dizini Değiştirme)
					fs::current_path(targetFolder);

					std::cout << "Folder entered. New Path: " << fs::current_path() << "\n";
					return true;

					// Artık burada oluşturulan bir dosya 'yeni_klasor' içinde oluşur
				}
				else {
					std::cout << "Error: Folder dont found.\n";
					return false;
				}
			}
		}
		users.close();
		cout << "You entered wrong mail or password please try again." << endl;
		return false;
	}
	else if (fact == 'P' || fact == 'p')
	{
		srand(time(0));
		const int min_value = 100000;
		const int max_value = 999999;
		Forgetp::rand = (rand() % (max_value - min_value + 1)) + min_value;
		cout << "Your code please remember the code : " << Forgetp::rand << endl;
		Forgetp::change_pass();
		return false;
	}
	else {
		cout << "You entered wrong key returning singup or login page." << endl;
		return false;
	}
}

bool Login::Check()
{
	ifstream users("users.txt");
	if (!users.is_open())
		cerr << "Error : Not found users file." << endl;
	else {
		string username_file3, email_file3, password_file3;
		while (users >> username_file3 >> email_file3 >> password_file3)
		{
			if (email == email_file3)
				return true;
		}
		return false;
	}
}

void save_settings()
{
	string setting = (username + "_settings") + ".txt";

	ofstream settingf(setting);

	bool dtfl = false;
	bool nts = false;

	settingf << "DTF : " << dtfl << " NTS : " << nts << endl;
	settingf.close();
}

void save_listname()
{

	string nlistn = (username + "_List") + ".txt";

	ofstream list(nlistn);
	string tname = "Tasks";
	list << tname << endl;
	list.close();
}

void Login::SingUp()
{
	cout << "Please enter username :" << endl;
	cin >> username;
	do
	{
		cout << "Please enter email : " << endl;
		cin >> email;
	} while (!is_valid_email(email));
	do
	{
		cout << "Please enter passwod : " << endl;
		cin >> password;
	} while (!is_valid_password(password));
	bool checktf;
	checktf = Login::Check();
	if (checktf == true)
	{
		cout << "You have account." << endl;
		this_thread::sleep_for(chrono::seconds(1));
		Clearl();
	}
	else
	{
		ofstream users("users.txt", ios::app);
		users << username << " " << email << " " << password << endl;
		users.close();

		if (fs::create_directory("Tasks_" + username)) {
			std::cout << "Folder succesfully created.\n";
		}
		else {
			// Klasör zaten varsa veya hata oluştuysa false döner
			if (fs::exists("Tasks_" + username)) {
				std::cout << "The folder already exists.\n";
			}
			else {
				std::cout << "Folder dont created.\n";
			}
		}

		string targetFolder = "Tasks_" + username;
		if (fs::exists(targetFolder) && fs::is_directory(targetFolder)) {

			// 3. KLASÖRE GİRİŞ (Dizini Değiştirme)
			fs::current_path(targetFolder);

			std::cout << "Folder entered. New Path: " << fs::current_path() << "\n";

			save_settings();
			save_listname();

			if (fs::create_directory("Tasks")) {
				std::cout << "Folder succesfully created.\n";
			}
			else {
				if (fs::exists("Tasks")) {
					std::cout << "The folder already exists.\n";
				}
				else {
					std::cout << "Folder dont created.\n";
				}
			}

			fs::path mevcutYol = fs::current_path();
			fs::current_path(mevcutYol.parent_path());

		}
		else {
			std::cout << "Error: Folder dont found.\n";
		}

		Clearl();
	}

}
