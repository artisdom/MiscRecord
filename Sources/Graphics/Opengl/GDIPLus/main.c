#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
using namespace Gdiplus;
#pragma comment(lib,"gdiplus")
vector<string> vec;
int num = 0;
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	//2.��ȡGDI+֧�ֵ�ͼ���ʽ�������������Լ�ImageCodecInfo����Ĵ�Ŵ�С
	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

					//3.ΪImageCodecInfo����������ռ�
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

					//4.��ȡ���е�ͼ���������Ϣ
	GetImageEncoders(num, size, pImageCodecInfo);

	//5.���ҷ��ϵ�ͼ���������Clsid
	for (UINT j = 0; j < num; ++j) {
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	//6.�ͷŲ���3������ڴ�
	free(pImageCodecInfo);
	return -1;  // Failure
}



void draw_image(const char* file)
{

	int width, height;
	size_t len = strlen(file) + 1;
	size_t converted = 0;
	wchar_t *WStr;
	string savename = file;
	savename += ".bmp";
	WStr = (wchar_t*)malloc(len*sizeof(wchar_t));
	mbstowcs_s(&converted, WStr, len, file, _TRUNCATE);
	//����ͼ��
	Image image(WStr);
	//ȡ�ÿ�Ⱥ͸߶�
	width = image.GetWidth();
	height = image.GetHeight();
	CLSID   encoderClsid;
	GetEncoderClsid(L"image/bmp", &encoderClsid);
	wstring savename2 = StringToWstring(savename);
	image.Save(savename2.c_str(), &encoderClsid, NULL);
	//cout<<width<<" "<<height<<endl;
	return;
}
void encode(void) {
	int len = vec.size();
	for (int i = 0; i<len; i++)
		draw_image(vec[i].c_str());
}
void calctime(void(*fun)(void)) {
	clock_t st, et;
	st = clock();
	fun();
	et = clock();
	cout << double(et - st) / CLOCKS_PER_SEC << endl;
}
void initiate()
{
	//
	ifstream ifs("test.txt");
	string temp;
	int tempr, tempt;
	while (!ifs.eof()) {
		getline(ifs, temp);
		if (temp.length()>4)
			vec.push_back(temp);
		//cout<<temp<<endl;
	}
	ifs.close();
}
int main()
{

	//GdiPlus��ʼ��
	ULONG_PTR gdipludToken;
	GdiplusStartupInput gdiplusInput;
	GdiplusStartup(&gdipludToken, &gdiplusInput, NULL);
	//
	initiate();
	//
	calctime(encode);
	//GdiPlus ȡ����ʼ��
	GdiplusShutdown(gdipludToken);

	return 0;
}