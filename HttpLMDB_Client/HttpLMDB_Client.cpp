// HttpLMDB_Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Include\Base64Helper.h"

int main()
{
	std::wstring dbname = _T("cache_v100");
	if (Init(dbname) == false)
	{
		std::wcout << _T("Init failed") << std::endl;
		return 0;
	}

	::Sleep(1000);

	TCHAR sz[255];
	_stprintf_s(sz, _T("key_%ld"), GetTickCount());
	std::wstring key = std::wstring(sz);
	_stprintf_s(sz, _T("value_%ld"), GetTickCount());
	std::wstring value = std::wstring(sz);
	SetData(key, value, dbname);

	value = _T("");
	GetData(key, value, dbname);
	std::wcout << _T("key:") << key << _T(" value:") << value << std::endl;

	std::string value2 = "azertyuiopqsdfghjklmwxcvbn";
	std::string buffer = Base64Helper::base64_encode((const unsigned char*)value2.c_str(), value2.length());
	std::wstring value3(buffer.begin(), buffer.end());
	SetData(key, value3, value3.length(), dbname);

	Uninit(dbname);
    return 0;
}

				