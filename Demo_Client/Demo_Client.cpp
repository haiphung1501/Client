#include "stdafx.h"
#include "Demo_Client.h"
#include "afxsock.h"
#include <string>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
DWORD WINAPI function_cal(LPVOID arg) {
	SOCKET* hConnected = (SOCKET*)arg;
	CSocket mysock;
	//Chuyen ve lai CSocket
	mysock.Attach(*hConnected);


	//Code
	cout << "Hello";
	//Code

	delete hConnected;
	mysock.Close();
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
			if (client.Connect(CA2W(ip), port))
			{
				cout << "Succesfully Connected!" << endl;

				SOCKET* hConnected = new SOCKET();
				*hConnected = client.Detach();
				threadStatus = CreateThread(NULL, 0, function_cal, hConnected, 0, &threadID);

				client.Attach(*hConnected);
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