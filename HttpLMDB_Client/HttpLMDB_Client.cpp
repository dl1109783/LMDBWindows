// HttpLMDB_Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Include\Base64Helper.h"

int main()
{
	USES_CONVERSION;

	std::wstring dbname = _T("cache_v100");
	if (Init(dbname) == false)
	{
		std::wcout << _T("Init failed") << std::endl;
		return 0;
	}

	::Sleep(1000);

	std::wstring key = _T("key_v10");
	std::wstring value = _T("value_v10");
	SetData(key, value);

	value = _T("");
	GetData(key, value);
	std::wcout << _T("key:") << key << _T(" value:") << value << std::endl;

	std::string value2 = W2A(_T("azertyuiopqsdfghjklmwxcvbn"));
	std::string buffer = Base64Helper::base64_encode((const unsigned char*)value2.c_str(), value2.length());
	std::wstring value3(buffer.begin(), buffer.end());
	SetData(key, value3, value3.length());

	Uninit(dbname);
    return 0;
}

				