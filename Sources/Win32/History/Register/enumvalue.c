#include <stdio.h>
#include <windows.h>
#define NAME_LEN 100
int main()
{
	HKEY hKey;
	// LPCTSTR lpSubKey="Environment";

	// if(RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_READ, &hKey)!= ERROR_SUCCESS) {
		// return ;
	// }
	LPCTSTR lpSubKey="SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment";

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ, &hKey)!= ERROR_SUCCESS) {
		return ;
	}
	char szValueName[NAME_LEN];
	BYTE szValue[NAME_LEN];
	LONG status;
	DWORD dwIndex = 0;
	DWORD dwSizeValueName=100;
	DWORD dwSizeofValue=100;
	DWORD Type;
	dwSizeValueName = NAME_LEN;
	dwSizeofValue = NAME_LEN;
	do {
		status = RegEnumValue(hKey, dwIndex++, szValueName, &dwSizeValueName, NULL, &Type,
		                      szValue, &dwSizeofValue);
		if((status == ERROR_SUCCESS)) {
			printf("%s=%s\n",szValueName,szValue);
		}
		//ÿ��ȡһ��dwSizeValueName��dwSizeofValue���ᱻ�޸�
		//ע��һ��Ҫ����,�������ֺ�����Ĵ���,���˾��Թ���û������,���ֶ�����COM����10���ϵĴ���
		dwSizeValueName = NAME_LEN;
		dwSizeofValue = NAME_LEN;
	} while((status!= ERROR_NO_MORE_ITEMS));
	RegCloseKey(hKey);
}