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

DWORD WINAPI function_cal1(LPVOID arg) {
	SOCKET* hConnected = (SOCKET*)arg;
	CSocket client;
	//Chuyen ve lai CSocket
	client.Attach(*hConnected);
	int number_continue = 1;
	int choice;
	char letter;
	do {
		fflush(stdin);
		cout << "\n0. Exit" << endl;
		cout << "1. Log in" << endl;
		cout << "2. Sign in" << endl;
		cout << "Your choice: " << endl;
		cin >> choice;

		client.Send(&choice, sizeof(choice), 0);

		if (choice == 1) {
			string user, pass;
			int check;
			cin.ignore();
			login(user, pass);
			client.Send(&user, sizeof(user), 0);
			client.Send(&pass, sizeof(pass), 0);

			client.Receive(&check, sizeof(check), 0);
			if (check == 1) {
				cout << "Login Successful";
			}
			else {
				cout << "Error";
			}
		}
		if (choice == 2) {
				string user, pass;
				int check;
				cout << "Enter Username: ";
				cin.ignore();
				getline(cin, user);
				cout << "Enter Password: ";
				getline(cin, pass);

				client.Send(&user, sizeof(user), 0);
				client.Send(&pass, sizeof(pass), 0);

				client.Receive(&check, sizeof(check), 0);
				if (check == 1) {
					cout << "Sign in Successful";
				}
				else {
					cout << "Username has been used";
				}
		}
		if (choice == 0) {
			number_continue = 0;
		}
		getchar();
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