#pragma once
#include <string>

using namespace std;

class Login
{
public:
	static string username_file2;
	static string password_file2;
	static void SingUp();
	static bool login();
	static bool Check();
};
