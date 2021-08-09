// stdafx.cpp : source file that includes just the standard includes
// Demo_Client.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

void Logo() {
	ifstream ifs("logo.txt");
	if (ifs.fail()) {
		cout << "Fail to open logo File !!!";
		return;
	}
	while (!ifs.eof()) {
		textcolor(10);
		string ch;
		getline(ifs, ch);
		if (ch.length() <= 5)
			continue;
		cout << ch << endl;
	}
	textcolor(7);
	ifs.close();
}

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

string passwordInput(unsigned maxLength)
{
	string pw;
	for (char c; (c = _getch()); )
	{
		if (c == '\n' || c == '\r') { //Enter
			cout << "\n";
			break;
		}
		else if (c == '\b') { // Backspace
			cout << "\b \b";
			if (!pw.empty()) pw.erase(pw.size() - 1);
		}
		else if (c == -32) { //up down right left
			_getch();
		}
		else if (isprint(c) && pw.size() < maxLength) {
			std::cout << '*';
			pw += c;
		}
	}
	return pw;
}

void login(string& user, string& pass)
{
	system("cls");
	Logo();
	textcolor(243);
	gotoxy(48, 9);
	cout << ' ' << setw(19) << ' ';
	gotoxy(48, 10);
	cout << "  Enter Username:   ";
	gotoxy(48, 11);
	cout << ' ' << setw(19) << ' ';
	gotoxy(50, 11);
	getline(cin, user, '\n');
	gotoxy(48, 12);
	cout << "  Enter password:   ";
	gotoxy(48, 13);
	cout << ' ' << setw(19) << ' ';
	gotoxy(50, 13);
	pass = passwordInput(30);
	textcolor(7);
}
