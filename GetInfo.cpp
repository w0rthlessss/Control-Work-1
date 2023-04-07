#include "GetInfo.h"

//очистка потока ввода
void IgnoreLine()
{
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
}

//считывание целого числа с консоли
int GetInt(string s) {
	cout << s;
	int tmp = 0;
	while (true) {
		cin >> tmp;
		if (cin.fail()) {
			cin.clear();
			IgnoreLine();
			cout << "\nUse correct values!\n\n";
			cout << s;
		}
		else if (tmp <= 0) {
			cout << "\nValue must be >0\n\n";
			cin.clear();
			IgnoreLine();
			cout << s;
		}
		else {
			IgnoreLine();
			return tmp;
		}
	}
}

//считывание строки с консоли, указывая номер объекта для которого строка считывается
string GetString(string s, int i)
{
	string a = "";
	while (true) {
		cout << s << i << ": ";
		cin >> a;
		if (getchar() != '\n') {
			cout << "\nInput only one word per line!\n";
			cout << s;
			cin.clear();
			IgnoreLine();
		}
		else if (a.empty()) {
			cout << "\nYou must enter a word!\n";
			cout << s;
			cin.clear();
			IgnoreLine();
		}
		else return a;
	}
}

//считывание всей строки для указания адреса файла
string GetLink(string s)
{
	string b = "";
	cout << s;
	cout << "Path must not contain cyrillic symbols!\n\n>>";
	getline(cin, b);
	return b;
}

//считывание строки без нумерации
string GetString(string s)
{
	string b = "";
	while (true) {
		cout << s;
		cin >> b;
		if (getchar() != '\n') {
			cout << "\nInput only one word per line!\n";
			cout << s;
			cin.clear();
			IgnoreLine();
		}
		else if (b.empty()) {
			cout << "\nYou must enter a word!\n";
			cout << s;
			cin.clear();
			IgnoreLine();
		}
		else return b;
	}
	return b;
}

//считывание ответа y/n
char GetChar(string s)
{
	char tmp = '\n';
	cout << s;
	while (true) {
		tmp = getchar();
		if (tmp == '\n') {
			cout << "You must type y or n!\n\n";
			cout << s;
			cin.clear();
			IgnoreLine();
		}
		else if (getchar() != '\n') {
			cout << "Incorrect input! Type only y or n!\n\n";
			cout << s;
			cin.clear();
			IgnoreLine();
		}
		else return tmp;
	}
}

