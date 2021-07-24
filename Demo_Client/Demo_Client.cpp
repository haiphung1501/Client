// Demo_Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Demo_Client.h"
#include "afxsock.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

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
			string ip;
			client.Create();
			if (client.Connect(_T("192.168.1.172"), 4567))
				cout << "Ket noi thanh cong" << endl;
			else
				cout << "Ket noi khong thanh cong" << endl;
			string s;
			string serverName;
			serverName = "Client 2";
			
			do {
				fflush(stdin); 
				client.Send(&serverName, sizeof(serverName), 0);
				client.Receive(&s, sizeof(s), 0);
				cout << "Server: " << s << endl;
				cout << "Client: ";
				getline(cin, s);
				if (s != "Thoat")
				{
					client.Send(&s, sizeof(s), 0);
				}
				else break;
			}while(true);
			client.Close();

		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
	//TEST
}
