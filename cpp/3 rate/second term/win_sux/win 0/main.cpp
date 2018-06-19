#include <iostream>
#include <windows.h>
#include <conio.h>
#include <tchar.h>
using namespace std;

void EnumerateSubKeysAndValues(HKEY hKey)
{
	DWORD lpcbSubKeys, lpcbMaxSubKeyLen, lpcValues,
		lpcbMaxValueNameLen, lpcbMaxValueLen,
		lpcbCurrentNameLen, dwType;
	
	RegQueryInfoKey( hKey, 0, 0, 0, &lpcbSubKeys, &lpcbMaxSubKeyLen, 
		0, &lpcValues,  &lpcbMaxValueNameLen, &lpcbMaxValueLen, 0, 0);
	
	if(lpcbSubKeys > 0)
	{
		cout<< "There're " << lpcbSubKeys << " keys " << endl;
		lpcbCurrentNameLen = lpcbMaxSubKeyLen + 1;

		LPWSTR lpName = new WCHAR[lpcbCurrentNameLen];

		for(int i = 0; i < lpcbSubKeys; i++)
		{
			lpcbCurrentNameLen = lpcbMaxSubKeyLen + 1;
			if( RegEnumKeyEx( hKey, i, lpName, &lpcbCurrentNameLen, 0,0,0,0) == ERROR_SUCCESS )
				wprintf( L"%d: %s \n", i, lpName );
		}
		delete []lpName;
	}

	if(lpcValues > 0)
	{
		WCHAR szTypes[12][31] = {	L"REG_NONE", 
									L"REG_SZ", 
									L"REG_EXPAND_SZ", 
									L"REG_BINARY", 
									L"REG_DWORD", 
									L"REG_DWORD_BIG_ENDIAN", 
									L"REG_LINK", 
									L"REG_MULTI_SZ", 
									L"REG_RESOURCE_LIST", 
									L"REG_FULL_RESOURCE_DESCRIPTOR", 
									L"REG_RESOURCE_REQUIREMENTS_LIST", 
									L"REG_QWORD"};
		
		cout<<"Values : "<<endl;
		lpcbCurrentNameLen = lpcbMaxSubKeyLen + 1;
		LPWSTR lpName = new WCHAR[lpcbCurrentNameLen];
		for(int i = 0; i < lpcValues; i++)
		{
			lpcbCurrentNameLen = lpcbMaxSubKeyLen + 1;
			if(RegEnumValue(hKey, i, lpName, &lpcbCurrentNameLen, 0, &dwType,0,0) == ERROR_SUCCESS)
				wprintf( L"%d: %s %s \n", i, szTypes[dwType], lpName);
				
		}
		delete []lpName;
	}
}

int main()
{
	WCHAR szData[] = L"Bla-bla-bla-bla-bla-bla-bla";
	WCHAR szMultiData[] = L"Bla-bla-bla-bla-bla-bla-bla";
	
	DWORD dwData = 481516, dwDisposition;
	HKEY hKey, hSubKey, hKeySoftware;
	
	if(RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Bla-bla", 0, 0, 0, 
		KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition) != ERROR_SUCCESS)
		cout << "Key hasn't been created";
	
	RegSetValueEx(hKey, L"REG_DWORD", 0, REG_DWORD, (BYTE*)&dwData, sizeof(dwData));
	RegSetValueEx(hKey, L"REG_SZ", 0, REG_SZ, (BYTE*)&szData, sizeof(szData));
	RegSetValueEx(hKey, L"REG_MULTI_SZ", 0, REG_MULTI_SZ, (BYTE*)&szMultiData, sizeof(szMultiData));
	
	RegCreateKeyEx(hKey, L"Bla-bla SubKey1", 0,0,0,KEY_ALL_ACCESS, NULL, &hSubKey, &dwDisposition);
	RegCloseKey(hSubKey);

	RegCreateKeyEx(hKey, L"Bla-bla SubKey2", 0,0,0,KEY_ALL_ACCESS, NULL, &hSubKey, &dwDisposition);
	RegCloseKey(hSubKey);

	RegCreateKeyEx(hKey, L"Bla-bla SubKey3", 0,0,0,KEY_ALL_ACCESS, NULL, &hSubKey, &dwDisposition);
	RegCloseKey(hSubKey);
	
	EnumerateSubKeysAndValues(hKey);

	RegOpenKeyEx(HKEY_CURRENT_USER, L"Software",0,KEY_ALL_ACCESS,&hKeySoftware);

	RegDeleteKey(hKeySoftware, L"Bla-bla");
	RegCloseKey(hKey);

	return 0;
}
