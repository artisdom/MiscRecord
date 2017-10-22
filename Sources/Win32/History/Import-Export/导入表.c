#include <stdio.h>
#include <windows.h>
#include <Dbghelp.h> //ImageRvaToVa

int main(int argc, char* argv[])
{
	int i, j;
	HANDLE hFile = CreateFile(
	                   argv[1], //PE�ļ���
	                   GENERIC_READ,
	                   FILE_SHARE_READ,
	                   NULL,
	                   OPEN_EXISTING,
	                   FILE_ATTRIBUTE_NORMAL,
	                   NULL);

	if(hFile == INVALID_HANDLE_VALUE) {
		printf("Create File Failed.\n");
		return 0;
	}

	HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY,    0, 0, NULL);

	if (hFileMapping == NULL || hFileMapping == INVALID_HANDLE_VALUE) {
		printf("Could not create file mapping object (%d).\n", GetLastError());
		return 0;
	}

	LPBYTE lpBaseAddress = (LPBYTE)MapViewOfFile(hFileMapping,   // handle to map object
	                       FILE_MAP_READ, 0, 0, 0);

	if (lpBaseAddress == NULL) {
		printf("Could not map view of file (%d).\n", GetLastError());
		return 0;
	}

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)(lpBaseAddress + pDosHeader->e_lfanew);

	//������rva��0x2a000;
	DWORD Rva_import_table = pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;

	if(Rva_import_table == 0) {
		printf("no import table!");
		goto UNMAP_AND_EXIT;
	}

	//�����Ȼ���ڴ��ַ�����Ǽ�ȥ�ļ���ͷ�ĵ�ַ�������ļ���ַ��
	//�����ַ����ֱ�Ӵ������ȡ����Ҫ�Ķ�����
	PIMAGE_IMPORT_DESCRIPTOR pImportTable = (PIMAGE_IMPORT_DESCRIPTOR)ImageRvaToVa(
	        pNtHeaders,
	        lpBaseAddress,
	        Rva_import_table,
	        NULL
	                                        );

	//��ȥ�ڴ�ӳ����׵�ַ�������ļ���ַ�ˡ������ܼ򵥰ɣ�
	printf("FileAddress Of ImportTable: %p\n", ((DWORD)pImportTable - (DWORD)lpBaseAddress));

	//���������˵�������ǰ��IMAGE_IMPORT_DESCRIPTOR ���飨��0Ԫ��Ϊ��ֹ��
	//�����ʾ�����β��nullԪ�أ�
	IMAGE_IMPORT_DESCRIPTOR null_iid;
	IMAGE_THUNK_DATA null_thunk;
	memset(&null_iid, 0, sizeof(null_iid));
	memset(&null_thunk, 0, sizeof(null_thunk));

	//ÿ��Ԫ�ش�����һ�������DLL��
	for(i=0; memcmp(pImportTable + i, &null_iid, sizeof(null_iid))!=0; i++) {
		//LPCSTR: ���� const char*
		LPCSTR szDllName = (LPCSTR)ImageRvaToVa(
		                       pNtHeaders, lpBaseAddress,
		                       pImportTable[i].Name, //DLL���Ƶ�RVA
		                       NULL);

		//�õ���DLL������
		printf("-----------------------------------------\n");
		printf("[%d]: %s\n", i, szDllName);
		printf("-----------------------------------------\n");

		//����ȥ�����Ӹ�DLL����������Щ����
		//����������DLL�� IMAGE_TRUNK_DATA ���飨IAT�������ַ��ǰ��
		PIMAGE_THUNK_DATA32 pThunk = (PIMAGE_THUNK_DATA32)ImageRvaToVa(
		                                 pNtHeaders, lpBaseAddress,
		                                 pImportTable[i].OriginalFirstThunk, //��ע�⡿����ʹ�õ���OriginalFirstThunk
		                                 NULL);

		for(j=0; memcmp(pThunk+j, &null_thunk, sizeof(null_thunk))!=0; j++) {
			//����ͨ��RVA�����λ�жϺ����ĵ��뷽ʽ��
			//������λΪ1������ŵ��룬�������Ƶ���
			if(pThunk[j].u1.AddressOfData & IMAGE_ORDINAL_FLAG32) {
				printf("\t [%d] \t %ld \t ����ŵ���\n", j, pThunk[j].u1.AddressOfData & 0xffff);
			} else {
				//�����Ƶ��룬�����ٴζ��򵽺�����ź�����
				//ע�����ַ����ֱ���ã���Ϊ��Ȼ��RVA��
				PIMAGE_IMPORT_BY_NAME pFuncName = (PIMAGE_IMPORT_BY_NAME)ImageRvaToVa(
				                                      pNtHeaders,    lpBaseAddress,
				                                      pThunk[j].u1.AddressOfData,
				                                      NULL);

				printf("\t [%d] \t %ld \t %s\n", j, pFuncName->Hint, pFuncName->Name);
			}
		}
	}


UNMAP_AND_EXIT:

	//�ر��ļ����������
	UnmapViewOfFile(lpBaseAddress);
	CloseHandle(hFileMapping);
	CloseHandle(hFile);
	//getchar();
	return 0;
}