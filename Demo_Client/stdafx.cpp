// stdafx.cpp : source file that includes just the standard includes
// Demo_Client.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

void userSignUp(string filename)
{
	ofstream ofs(filename, ios::out, ios::app);
	string id, password;
	getline(cin, id);
	ofs << id << endl;
	getline(cin, id);
	ofs << password << endl;

	ofs.close();
}