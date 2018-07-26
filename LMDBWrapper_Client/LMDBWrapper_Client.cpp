// LMDBWrapper_Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Include\CWrapper.h"
#include "..\Include\Base64.h"

int main(int argc, char * argv[])
{
	int i = 0, j = 0, rc;
	int count;
	int *values;
	char szDebug[255];
	char szVerbose[255];
	bool verbose = false;

	count = 10;

	if (argc == 2)
	{
		count = atoi(argv[1]);
	}

	if (argc == 3)
	{
		count = atoi(argv[1]);
		strcpy(szVerbose, argv[2]);
		if (strcmp(szVerbose, "true") == 0)
		{
			verbose = true;
		}
	}

	values = (int *)malloc(count * sizeof(int));

	for (i = 0; i<count; i++) {
		values[i] = rand() % 1024;
	}

	char szDbName[255];
	strcpy_s(szDbName, "cache_v1000_A");

	CLMDBWrapper wrapper3;
	wrapper3.Init(szDbName);
	wrapper3.GetSet();
	//return 0;

	char szKey[255];
	char szValue[255];
	sprintf(szKey, "key_%d", 10);
	sprintf(szValue, "value_%d", 10);

	CLMDBWrapper wrapper1;
	wrapper1.Init(szDbName);
	wrapper1.Set(szKey, szValue);
	wrapper1.Uninit();
	wrapper1.Init(szDbName);
	LPSTR lpszValue1;
	wrapper1.Get(szKey, &lpszValue1);
	printf("GET key:%s value:%s\n", szKey, lpszValue1);
	free(lpszValue1);
	wrapper1.Uninit();

	sprintf(szKey, "key_%d", 12);
	sprintf(szValue, "value_%d", 12);

	CLMDBWrapper wrapper2;
	wrapper2.Init(szDbName);
	wrapper2.Set(szKey, szValue, strlen(szValue));
	wrapper2.Uninit();
	wrapper2.Init(szDbName);
	LPSTR lpszValue2;
	wrapper2.Get(szKey, &lpszValue2);
	printf("GET key:%s value:%s\n", szKey, lpszValue2);
	free(lpszValue2);
	wrapper2.Uninit();
	return 0;

	CLMDBWrapper wrapper;
	wrapper.Init(szDbName);
	wrapper.Set(szKey, szValue);	
	LPSTR lpszValue;
	wrapper.Get(szKey, &lpszValue);
	printf("GET key:%s value:%s\n", szKey, lpszValue);
	free(lpszValue);

	sprintf(szKey, "key_%d", 12);
	sprintf(szValue, "value_AZERTYUIOPQSDFGHJKLMWXCVBN");
	DWORD len = strlen(szValue);
	wrapper.Set(szKey, szValue, len);
	LPSTR lpszValue3;
	wrapper.Get(szKey, &lpszValue3);
	printf("GET key:%s value:%s\n", szKey, lpszValue3);
	free(lpszValue3);
	wrapper.Uninit();
	return 0;

	printf("Adding %d values\n", count);
	DWORD dwStart = GetTickCount();
	for (i = 0; i<count; i++)
	{
		char szKey[255];
		char szValue[255];
		sprintf(szKey, "key_%d", i);
		sprintf(szValue, "value_%d", i);

		if (verbose)
		{
			printf("SET key:%s value:%s\n", szKey, szValue);
		}

		//wrapper.SetData(szKey, szValue);
	}

	char szKey2[255];
	LPSTR szValue2;
	sprintf(szKey2, "key_AA");
	if( wrapper.Get(szKey2, &szValue2) == true )
		free(szValue2);


	DWORD dwStop = GetTickCount();
	sprintf(szDebug, "Elapsed for put: %ld ms\n", dwStop - dwStart);
	printf(szDebug);

	dwStart = GetTickCount();
	for (int i = 0; i < count; i++)
	{
		char szKey[255];
		LPSTR szValue;
		sprintf(szKey, "key_%d", i);
		//memset(szValue, 0, 255);

		if (i > 101)
		{
			int i2 = 101;
		}

		if (wrapper.Get(szKey, &szValue) == true)
		{
			free(szValue);

			if (verbose)
			{
				printf("GET key:%s value:%s\n", szKey, szValue);
			}
		}

	}

	dwStop = GetTickCount();
	sprintf(szDebug, "Elapsed for get: %ld ms\n", dwStop - dwStart);
	printf(szDebug);

	wrapper.Uninit();

	return 0;

	//
	// Binary insertion
	//

	//char szKey[20];
	strcpy_s(szKey, "skyfall.mp3");

	int fd = _open("D:\\Files_Music_More\\BOF - James Bond 007\\skyfall.mp3", _O_RDONLY);
	int s = _filelength(fd);
	char * lpszBuffer = (char *)malloc(s);
	_read(fd, lpszBuffer, s);
	_close(fd);

	char szDb[255];
	strcpy_s(szDb, "cache_v1000");

	CLMDBWrapper w;
	w.Init(szDb);
	w.Set(szKey, (LPSTR) lpszBuffer, s);

	LPSTR lpsz = NULL;
	w.Get(szKey, &lpsz);

	w.Uninit();

	return 0;
}

