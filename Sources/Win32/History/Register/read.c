#include <stdio.h>
#include <windows.h>
int main()
{
	HKEY hKey;
	DWORD dwtype, BufferSize;
	char *buffer;
	int len;
	long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Environment", 0, KEY_READ|KEY_WRITE, &hKey);
	char* string="D:\\Program\\msys2\\mingw32\\share\\qt5\\plugins";
	len=strlen(string);
	char* Variable="QT_PLUGIN_PATH";
	RegSetValueEx(hKey, Variable,0,REG_EXPAND_SZ,(BYTE *)string,len);
	//long lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment", 0, KEY_READ, &hKey);
	// char* string="C:\\ProgramData\\Oracle\\Java\\javapath;%SystemRoot%\\system32;%SystemRoot%;%SystemRoot%\\System32\\Wbem;%SYSTEMROOT%\\System32\\WindowsPowerShell\\v1.0\\;%USERPROFILE%\\.dnx\\bin;C:\\Program Files\\Microsoft DNX\\Dnvm\\;C:\\Program Files (x86)\\Windows Kits\\8.1\\Windows Performance Toolkit\\;C:\\Program Files (x86)\\Microsoft SQL Server\\120\\Tools\\Binn\\;C:\\Program Files (x86)\\Microsoft SQL Server\\130\\Tools\\Binn\\;C:\\Program Files (x86)\\Microsoft Emulator Manager\\1.0\\;C:\\Program Files (x86)\\nodejs\\;C:\\Program Files\\Git\\cmd";
	// len=strlen(string);
	// printf("%d\n",len);
	// lRet=RegSetValueEx(hKey, "Path",0,REG_EXPAND_SZ,(BYTE *)string,len);
	if (lRet == ERROR_SUCCESS) {
	//��ȡ��ֵ
	RegQueryValueEx(hKey, Variable, 0, &dwtype, (BYTE*)buffer, &BufferSize);//��һ�λ�ȡ����
	printf("%d\n",BufferSize);
	buffer=(char*)malloc(BufferSize);//�����ڴ�
	if(RegQueryValueEx(hKey, Variable, 0, &dwtype, (BYTE*)buffer, &BufferSize)==ERROR_SUCCESS)//��һ�λ�ȡֵ
		printf("%s\n",buffer);
	//�رռ�
	RegCloseKey(hKey);
	}
}