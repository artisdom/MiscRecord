//g++ main.cpp -lwininet
#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#define MAXBLOCKSIZE 1024

void download(const char*);

int main(int argc, char* argv[])
{
	if(argc > 1) {
		download((const char*)argv[1]);
	} else {
		printf("Usage: auto-Update url");
	}
	return 0;
}


/**
 * 执行 文件下载 操作
 * @param Url: The target action url
 *
 */
void download(const char *Url)
{
	HINTERNET hSession = InternetOpen("RookIE/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hSession != NULL) {
		HINTERNET handle2 = InternetOpenUrl(hSession, Url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
		if (handle2 != NULL) {
			printf("%s\n",Url);
			byte Temp[MAXBLOCKSIZE];
			ULONG Number = 1;

			FILE *stream;
			if( (stream = fopen( "test.jpg", "wb" )) != NULL ) { //这里只是个测试，因此写了个死的文件路径
				while (Number > 0) {
					InternetReadFile(handle2, Temp, MAXBLOCKSIZE - 1, &Number);
					//fprintf(stream, (const char*)Temp);
					fwrite(Temp, sizeof (char), Number , stream);
				}
				fclose( stream );
			}

			InternetCloseHandle(handle2);
			handle2 = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
}