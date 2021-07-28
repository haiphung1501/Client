#include "stdafx.h"
#include "Demo_Client.h"
#include "afxsock.h"
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;
using namespace std;

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
void login(string& user, string& pass) {
	cout << "Enter Username:";
	getline(cin, user, '\n');

	cout << "Enter password:";
	pass = passwordInput(30);
}

DWORD WINAPI function_cal1(LPVOID arg)
{
	SOCKET* hConnected = (SOCKET*)arg;
	CSocket client;
	//Chuyen ve lai CSocket
	client.Attach(*hConnected);
	int number_continue = 1;
	int choice;
	char letter;
	string user, pass;
	int check;
	bool loginCheck = 0;
	do {
		fflush(stdin);
		cout << "\n0. Exit" << endl;
		cout << "1. Log in" << endl;
		cout << "2. Sign up" << endl;
		cout << "Your choice: " << endl;
		cin >> choice;
		cin.ignore();
		client.Send(&choice, sizeof(choice), 0);

		if (choice == 1) {
			login(user, pass);
			client.Send(&user, sizeof(user), 0);
			client.Send(&pass, sizeof(pass), 0);

			client.Receive(&check, sizeof(check), 0);
			if (check == 1) {
				cout << "Login Successful" << endl;
				loginCheck = 1;
			}
			else {
				cout << "Error" << endl;
			}
		}
		if (choice == 2) {
			cout << "Enter Username: ";
			getline(cin, user);
			cout << "Enter Password: ";
			getline(cin, pass);

			client.Send(&user, sizeof(user), 0);
			client.Send(&pass, sizeof(pass), 0);

			client.Receive(&check, sizeof(check), 0);
			if (check == 1) {
				cout << "Sign in Successful" << endl;
			}
			else {
				cout << "Username has been used" << endl;
			}
		}
		if (loginCheck)
			number_continue = 0;
		if (choice == 0) {
			number_continue = 0;
		}
	} while (number_continue);
	number_continue = 1;
	int type;
	string dateString, typeString;
	double buy, sell;
	do {
		system("CLS");
		cout << "0. Exit\n";
		cout << "1. Check currency rate based on website\n";
		cout << "2. Check currency rate based on server data\n";
		cout << "3. Currency Converter\n";
		cin >> choice;
		cin.ignore();
		client.Send(&choice, sizeof(choice), 0);

		if (choice == 0)
			number_continue = 0;
		if (choice == 1) {
			cout << "0.Back\n";
			cout << "1. AUD\n";
			cout << "2. CAD\n";
			cout << "3. CHF\n";
			cout << "4. EUR\n";
			cout << "5.GBP\n";
			cout << "6.JPY\n";
			cout << "7.USD\n";
			cin >> choice;
			cin.ignore();
			client.Send(&choice, sizeof(type, 0));
			if (choice != 0) {
				client.Receive(&typeString, sizeof(typeString), 0);
				client.Receive(&sell, sizeof(sell), 0);
				client.Receive(&buy, sizeof(buy), 0);
				cout << typeString << " buy:" << buy << " sell: " << sell << endl;
				_getch();
			}
			else
				continue;
		}
		if (choice == 2) {
			cout << "0. Back" << endl;
			cout << "1. USD" << endl;
			cout << "2. EUR" << endl;
			cout << "3. YEN" << endl;
			cin >> type;
			cin.ignore();
			//gui du lieu nhap vao
			client.Send(&type, sizeof(type), 0);
			if (type != 0)
			{
				cout << "Enter date: (Format dd/mm/yyyy)";
				getline(cin, dateString);
				client.Send(&dateString, sizeof(dateString), 0);
				client.Receive(&typeString, sizeof(typeString), 0);
				client.Receive(&sell, sizeof(sell), 0);
				cout << typeString << " = " << sell << " VND" << endl;
				_getch();
			}
			else {
				continue;
			}
		}
		if (choice == 3) {

		}
	} while (number_continue);
	//Code
	cout << "Goi duoc Function Client";
	//Code

	delete hConnected;
	client.Close();
	return 0;
}
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			printf("Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			AfxSocketInit(NULL);
			CSocket client;
			DWORD threadID;
			HANDLE threadStatus;

			//cout << "Enter server's IP: ";
			char ip[] = "127.0.0.1";
			//cin.getline(ip, 30);
			int port = 1234;
			//cout << "Enter server's port: ";
			//cin >> port;
			//cin.ignore();
			client.Create();
			int number_continue = 0;
			char letter;
			if (client.Connect(CA2W(ip), port)) {
				cout << "Succesfully Connected!" << endl;

				SOCKET* hConnected = new SOCKET();
				*hConnected = client.Detach();
				threadStatus = CreateThread(NULL, 0, function_cal1, hConnected, 0, &threadID);

				client.Attach(*hConnected);

				while (1) {
					DWORD dwWait = WaitForSingleObject(threadStatus, 0); // timeout right away if thread handle is not signalled
					if (dwWait == WAIT_OBJECT_0)
						exit(0);
				}
			}
			else
				cout << "Ket noi khong thanh cong" << endl;
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}