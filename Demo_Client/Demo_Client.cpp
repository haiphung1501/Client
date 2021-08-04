#include "stdafx.h"
#include "Demo_Client.h"
#include "afxsock.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;
using namespace std;




DWORD WINAPI function_cal1(LPVOID arg)
{
	SOCKET* hConnected = (SOCKET*)arg;
	CSocket client;
	//Chuyen ve lai CSocket
	client.Attach(*hConnected);
	int number_continue = 1;
	int choice, choice_dummy;
	string user, pass;
	int check;
	bool loginCheck = 0;
	do {
		fflush(stdin);
		system("cls");
		textcolor(243);
		gotoxy(48, 9);
		cout << ' ' << setw(15) << ' ';
		gotoxy(48, 10);
		cout << "  0. Exit"  << setw(7) << ' ' << endl;
		gotoxy(48, 11);
		cout << "  1. Log in" << setw(5) << ' ' << endl;
		gotoxy(48, 12);
		cout << "  2. Sign up" << setw(4) << ' ' << endl;
		gotoxy(48, 13);
		cout << "  Your choice:" << "  ";
		gotoxy(48, 14);
		cout << ' ' << setw(15) << ' ';
		gotoxy(62, 13);
		cin >> choice;
		cin.ignore();
		textcolor(7);
		client.Send(&choice, sizeof(choice), 0);

		if (choice == 1) {
			login(user, pass);
			client.Send(&user, sizeof(user), 0);
			client.Send(&pass, sizeof(pass), 0);

			client.Receive(&check, sizeof(check), 0);
			if (check == 1) {
				gotoxy(48, 14);
				textcolor(242);
				cout << "  Login Successful  " << endl;
				textcolor(7);
				loginCheck = 1;
				Sleep(1000);
			}
			else {
				gotoxy(48, 14);
				textcolor(244);
				cout << "  Error         " << endl;
				Sleep(1000);
				textcolor(7);
			}
		}
		else if (choice == 2) {
			system("cls");
			textcolor(243);
			gotoxy(48, 9);
			cout << ' ' << setw(19) << ' ';
			gotoxy(48, 10);
			cout << "  Enter Username:   ";
			gotoxy(48, 11);
			cout << ' ' << setw(19) << ' ';
			gotoxy(50, 11);
			getline(cin, user);
			gotoxy(48, 12);
			cout << "  Enter password:   ";
			gotoxy(48, 13);
			cout << ' ' << setw(19) << ' ';
			gotoxy(50, 13);
			getline(cin, pass);
			textcolor(7);
			client.Send(&user, sizeof(user), 0);
			client.Send(&pass, sizeof(pass), 0);

			client.Receive(&check, sizeof(check), 0);
			if (check == 1) {
				gotoxy(48, 14);
				textcolor(242);
				cout << "Sign up Successful  " << endl;
				textcolor(7);
			}
			else {
				gotoxy(48, 14);
				textcolor(244);
				cout << "Username has been used" << endl;
				textcolor(7);
			}
			Sleep(1000);
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
	if (choice != 0) {
		do {
			fflush(stdin);
			system("cls");
			textcolor(243);
			gotoxy(48, 9);
			cout << ' ' << setw(45) << ' ';
			gotoxy(48, 10);
			cout << "  0. Exit" << setw(37) << ' ';
			gotoxy(48, 11);
			cout << "  1. Check currency rate based on website" << setw(5) << ' ';;
			gotoxy(48, 12);
			cout << "  2. Check currency rate based on server data" << ' ';;
			gotoxy(48, 13);
			cout << setw(46) << ' ';
			gotoxy(48, 14);
			cout << "  choice: " << setw(36) << ' ';
			gotoxy(60, 14);
			cin >> choice_dummy;
			textcolor(7);
			cin.ignore();
			client.Send(&choice_dummy, sizeof(choice_dummy), 0);

			if (choice_dummy == 0)
				break;
			else if (choice_dummy == 1) {
				system("cls");
				textcolor(243);
				gotoxy(48, 9);
				cout << ' ' << setw(12) << ' ';
				gotoxy(48, 10);
				cout << "  0.Back" << setw(5) << ' ';
				gotoxy(48, 11);
				cout << "  1. AUD" << setw(5) << ' ';
				gotoxy(48, 12);
				cout << "  2. CAD" << setw(5) << ' ';
				gotoxy(48, 13);
				cout << "  3. CHF" << setw(5) << ' ';
				gotoxy(48, 14);
				cout << "  4. EUR" << setw(5) << ' ';
				gotoxy(48, 15);
				cout << "  5. GBP" << setw(5) << ' ';
				gotoxy(48, 16);
				cout << "  6. JPY" << setw(5) << ' ';
				gotoxy(48, 17);
				cout << "  7. USD" << setw(5) << ' ';
				gotoxy(48, 18);
				cout << "  choice: " << setw(3) << ' ';
				gotoxy(58, 18);
				cin >> choice_dummy;
				textcolor(7);
				cin.ignore();
				client.Send(&choice_dummy, sizeof(choice_dummy), 0);
				if (choice_dummy != 0) {
					system("cls");
					client.Receive(&typeString, sizeof(typeString), 0);
					client.Receive(&sell, sizeof(sell), 0);
					client.Receive(&buy, sizeof(buy), 0);
					textcolor(243);
					gotoxy(48, 9);
					cout << ' ' << setw(12) << ' ';
					gotoxy(48, 10);
					cout << "  Type: " << typeString << "  ";
					gotoxy(48, 11);
					cout << "  Buy: " << buy << " VND ";
					gotoxy(48, 12);
					cout << "  Sell: " << sell << " VND ";
					gotoxy(48, 13);
					system("pause");
					textcolor(7);
				}
				else
					continue;
			}
			else if (choice_dummy == 2) {
				system("cls");
				textcolor(243);
				gotoxy(48, 9);
				cout << ' ' << setw(12) << ' ';
				gotoxy(48, 10);
				cout << "  0.Back" << setw(5) << ' ';
				gotoxy(48, 11);
				cout << "  1. USD" << setw(5) << ' ';
				gotoxy(48, 12);
				cout << "  2. EUR" << setw(5) << ' ';
				gotoxy(48, 13);
				cout << "  3. YEN" << setw(5) << ' ';
				gotoxy(48, 14);
				cout << "  choice: " << setw(3) << ' ';
				gotoxy(58, 14);
				cin >> type;
				textcolor(7);
				cin.ignore();
				//gui du lieu nhap vao
				client.Send(&type, sizeof(type), 0);
				if (type != 0)
				{
					system("cls");
					textcolor(243);
					gotoxy(48, 9);
					cout << ' ' << setw(32) << ' ';
					gotoxy(48, 10);
					cout << "  Enter date: (Format dd/mm/yyyy)";
					gotoxy(48, 11);
					cout << ' ' << setw(32) << ' ';
					gotoxy(50, 11);
					getline(cin, dateString);
					client.Send(&dateString, sizeof(dateString), 0);
					client.Receive(&typeString, sizeof(typeString), 0);
					client.Receive(&sell, sizeof(sell), 0);
					gotoxy(48, 12);
					cout << ' ' << setw(32) << ' ';
					gotoxy(48, 13);
					cout << ' ' << setw(32) << ' ';
					gotoxy(48, 13);
					cout << "  " << typeString << " = " << sell << " VND" << endl;
					gotoxy(48, 14);
					system("pause");
					textcolor(7);
				}
				else {
					continue;
				}
			}
		} while (number_continue);
	}

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
			client.Create();
			cout << "Enter server's IP: ";
			char ip[] = "127.0.0.1";
			cin.getline(ip, 30);
			int port;
			cout << "Enter server's port: ";
			cin >> port;
			cin.ignore();
			int number_continue = 0;
			if (client.Connect(CA2W(ip), port)) {
				cout << "Succesfully Connected!" << endl;

				SOCKET* hConnected = new SOCKET();
				*hConnected = client.Detach();
				threadStatus = CreateThread(NULL, 0, function_cal1, hConnected, 0, &threadID);

				client.Attach(*hConnected);
				string stop_sign;
				while (1) {
					//check if thread still running
					DWORD dwWait = WaitForSingleObject(threadStatus, 0); // timeout right away if thread handle is not signalled
					if (dwWait == WAIT_OBJECT_0)
					{
						exit(0);
						client.Receive(&stop_sign, sizeof(stop_sign), 0);
					}
						
					else if (dwWait == WAIT_TIMEOUT) // still running
					{
						client.Receive(&stop_sign, sizeof(stop_sign), 0);
						if (stop_sign == "stop") {
							TerminateThread(threadStatus, threadID);
							//closeHandle(threadStatus);

							client.Close();

							cout << endl << endl << "SERVER STOP WORKING !";
							_getch();
							return 0;
						}
					}
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