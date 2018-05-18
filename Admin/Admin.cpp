// Admin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int wmain(int argc, wchar_t *argv[])
{
	std::wstring defaultAddress = _T("localhost");
	std::wstring port = _T("7001");

	if (argc == 2)
	{
		port = argv[1];
	}
	if (argc == 3)
	{
		defaultAddress = argv[1];
		port = argv[2];
	}

	if (argc == 4)
	{
		defaultAddress = argv[1];
		port = argv[2];
	}

	TCHAR sz[255];
	_stprintf_s(sz, _T("http://%s:%s/MyServer/LMDB/"), defaultAddress.c_str(), port.c_str());

	std::wstring address = sz;

	std::wcout << L"Client " << address << std::endl;

	std::wstring cmd;

	std::wcout << _T("Enter a command:");
	std::wcin >> cmd;

	http_client client(address);

	http_response response;

	try
	{
		response = client.request(methods::GET, cmd).get();
		wcout << response.to_string() << endl;
	}
	catch (http_exception ex)
	{
		std::string err = ex.what();
	}

	return 0;
}

