
#pragma warning(disable : 4786)
#pragma  comment(lib,"GdiPlus.lib")
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#define ULONG_PTR void*
#include <GdiPlus.h>			/*������ʾBMP��JPG�ļ��Ŀ�*/
const int KEY_VALUE_B = 66;		/*B��ֵ*/
const int KEY_VALUE_S = 83;		/*S��ֵ*/
const int RANGE_MAX = 100;		/*��������Χ*/
using namespace std;
using namespace Gdiplus;


// Global Variables:
static int iAllBmpJpg = 0;				/*��ǰĿ¼������BMP��JPG�ļ���*/
static int iCurBmpJpg = 0;				/*��ǰ�ļ���*/
static double fMultiple = 1.0;			/*Ĭ�ϷŴ���Ϊ1*/
static const double fEnlarge = 1.2;		/*ÿ�ηŴ� 20% */

										// Foward declarations of functions included in this code module:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
int GetBmpJpg(std::vector<std::string>& oBJPicture);
wchar_t* ChrToWChr(const char* buffer);


/*
����˵����		��������Ӧ�ó������ڵ㣬��ʼ��Ӧ�ó�����ʾ�����ڣ�����һ����Ϣ����һ����ѭ��
�������˵����
�������˵����
����ֵ˵����
��ע��
*/

int main()
{
	HINSTANCE hInstance=NULL;
	PSTR szCmdLine;
	int iCmdShow;
	static TCHAR szAppName[] = TEXT("Bricks1");
	HWND                         hwnd;
	MSG                           msg;
	WNDCLASS                      wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("LoadBitmap Demo"),
		WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	iCmdShow = SW_SHOWMAXIMIZED;	/*Ĭ����󻯴���*/
	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}



/*
����˵����		Processes messages for the main window
WM_PAINT	- Paint the main window
WM_DESTROY	- post a quit message and return
�������˵����
�������˵����
����ֵ˵����
��ע��
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static POINT pt;
	int iXSource = 0;						/*���ص�ͼƬ��*/
	int iYSource = 0;						/*���ص�ͼƬ��*/
	char szCur[50] = { 0 };					/*�洢����iCurBmpJpgת���ɵ��ַ���*/
	char szAll[50] = { 0 };					/*�洢����iAllBmpJpgת���ɵ��ַ���*/
	std::string oShow;						/*��ʾͼƬ��Ϣ*/
	std::vector<std::string> oPicture;		/*��ŵ�ǰĿ¼��BMP��JPGͼƬ�ļ���*/
	SCROLLINFO si;
	static int iVertPos = 0;				/*��ֱ��������λ��*/
	static int iHorzPos = 0;				/*ˮƽ��������λ��*/

	switch (message) {
	case WM_SIZE: {					/*��Ȼ�ô��ڵ�һ����ʾʱ�������յ�����Ϣ*/
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_RANGE | SIF_POS;
		si.nPos = 0;
		si.nMin = 0;
		si.nMax = RANGE_MAX;

		SetScrollInfo(hWnd, SB_VERT, &si, TRUE);	/*���ô�ֱ�������Ĺ�����Χ�ͳ�ʼλ��*/
		SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);	/*����ˮƽ�������Ĺ�����Χ�ͳ�ʼλ��*/

		break;
	}
	case WM_VSCROLL: {		/*��ֱ����������Ϣ*/
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		GetScrollInfo(hWnd, SB_VERT, &si);
		iVertPos = si.nPos;

		switch (LOWORD(wParam)) {
		case SB_TOP:
			si.nPos = si.nMin;
			break;
		case SB_BOTTOM:
			si.nPos = si.nMax;
			break;
		case SB_LINEUP:
			si.nPos -= 100;
			break;
		case SB_LINEDOWN:
			si.nPos += 100;
			break;
		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;
		default:
			break;
		}

		si.fMask = SIF_POS;
		SetScrollInfo(hWnd, SB_VERT, &si, TRUE);	/*���ô�ֱ�������µ�λ��*/
		GetScrollInfo(hWnd, SB_VERT, &si);

		if (si.nPos != iVertPos) {	/*λ�÷����ı�ʱ�ػ�*/
			iVertPos = si.nPos;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	}
	case WM_HSCROLL: {	/*ˮƽ����������Ϣ*/
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		GetScrollInfo(hWnd, SB_HORZ, &si);
		iHorzPos = si.nPos;

		switch (LOWORD(wParam)) {
		case SB_LEFT:
			si.nPos = si.nMin;
			break;
		case SB_RIGHT:
			si.nPos = si.nMax;
			break;
		case SB_LINELEFT:
			si.nPos -= 100;
			break;
		case SB_LINERIGHT:
			si.nPos += 100;
			break;
		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
		default:
			break;
		}

		si.fMask = SIF_POS;
		SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);	/*����ˮƽ�������µ�λ��*/
		GetScrollInfo(hWnd, SB_HORZ, &si);

		if (iHorzPos != si.nPos) {	/*λ�÷����ı�ʱ�ػ�*/
			iHorzPos = si.nPos;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	}
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		RECT rect;
		GetClientRect(hWnd, &rect);


#if 0		/*�������õ���GDI+˫����*/
		/*GDI ˫����*/
		hdcMem = CreateCompatibleDC(hdc);
		hMemBitMap = CreateCompatibleBitmap(hdcMem, rect.right - rect.left, rect.bottom - rect.top);
		SelectObject(hdcMem, hMemBitMap);

		/*����ڴ汳��λͼΪ��ɫ*/
		hBrush = CreateSolidBrush(RGB(0xff, 0xff, 0x00));
		FillRect(hdcMem, &rect, hBrush);
		//SetBkColor(hdcMem, RGB(0xff, 0x00, 0xff));
#endif

		/*�õ���ǰĿ¼������BMP��JPG�ļ�*/
		iAllBmpJpg = GetBmpJpg(oPicture);
		if (iAllBmpJpg == 0) {
			MessageBox(NULL, "there are not bmp jpg picture!", NULL, MB_OK);
			exit(0);
		}

		/*ʹoShow������Щ��ʾ��Ϣ��iCurBmpJpg��iBmpJpg����ǰ�ļ���*/
		itoa(iCurBmpJpg + 1, szCur, 10);
		itoa(iAllBmpJpg, szAll, 10);
		oShow += szCur;
		oShow += "/";
		oShow += szAll;
		oShow += "\n";
		oShow += oPicture[iCurBmpJpg];

		/*�ѵ�ǰͼƬ�ļ���char��ת����WCHAR��*/
		wchar_t *pwFileName = NULL;
		pwFileName = ChrToWChr(oPicture[iCurBmpJpg].c_str());
		if (NULL == pwFileName) {
			MessageBox(NULL, "pwFileName is NULL!", NULL, MB_OK);
			exit(0);
		}

		/*����ͼƬ*/
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		Gdiplus::Image *pImage = Gdiplus::Image::FromFile(pwFileName);
		iXSource = pImage->GetWidth();
		iYSource = pImage->GetHeight();

		/*ͼƬδ��������ʱ���ع�����*/
		if (iXSource * fMultiple < rect.right - rect.left) {	/*ͼƬˮƽ����δ��������ʱ������ˮƽ������*/
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_PAGE;
			si.nPage = si.nMax;		/*ҳ���С���ڵ��ڹ�������Χ��Windowsͨ�����ع�����*/
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
		}
		else {												/*ͼƬˮƽ���򳬹�����ʱ����ʾˮƽ������*/
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_PAGE;
			si.nPage = 0;			/*ҳ���СС�ڹ�������Χ����ʾ������*/
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
		}

		if (iYSource * fMultiple < rect.bottom - rect.top) {	/*ͼƬ��ֱ����δ��������ʱ�����ش�ֱ������*/
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_PAGE;
			si.nPage = si.nMax;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
		}
		else {												/*ͼƬ��ֱ���򳬹�����ʱ����ʾ��ֱ������*/
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_PAGE;
			si.nPage = 0;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
		}

		/*�����ڴ�λͼ,����˫����*/
		Bitmap *pMemBitmap = new Bitmap(rect.right - rect.left, rect.bottom - rect.top);
		if (NULL == pMemBitmap) {
			exit(1);
		}
		Graphics graphicsMemBitmap(pMemBitmap);
		// ����λ��
		
		/*�����ڴ�λͼ�ı���Ϊ��ɫ*/
		graphicsMemBitmap.Clear(Color::White);


		/*�����ص�ͼƬ�����ڴ�λͼ�������м䣬��ͼƬ�ܴ�ʱ������ʵ�ֹ�������ͼ*/
		RectF rectMap(long((iXSource * fMultiple > rect.right - rect.left) ? rect.left : (rect.right - rect.left - iXSource * fMultiple) / 2),
			long((iYSource * fMultiple > rect.bottom - rect.top) ? rect.top : (rect.bottom - rect.top - iYSource * fMultiple) / 2),
			long((iXSource * fMultiple > rect.right - rect.left)
				? rect.right - rect.left : iXSource * fMultiple),
			long((iYSource * fMultiple > rect.bottom - rect.top)
				? rect.bottom - rect.top : iYSource * fMultiple));

		graphicsMemBitmap.DrawImage(pImage,
			//int((rect.right - rect.left - iXSource * fMultiple) > 0 ? (rect.right - rect.left - iXSource * fMultiple)/2 : 0),
			//int((rect.bottom - rect.top - iYSource * fMultiple) > 0 ? (rect.bottom - rect.top - iYSource * fMultiple)/2 : 0),
			rectMap,
			int((iXSource * fMultiple > rect.right - rect.left)
				? (float(iHorzPos) / RANGE_MAX * (iXSource * fMultiple - (rect.right - rect.left))) / fMultiple : 0),
			int((iYSource * fMultiple > rect.bottom - rect.top)
				? (float(iVertPos) / RANGE_MAX * (iYSource * fMultiple - (rect.bottom - rect.top))) / fMultiple : 0),
			int((iXSource * fMultiple > rect.right - rect.left) ? (rect.right - rect.left) / fMultiple : iXSource),
			int((iYSource * fMultiple > rect.bottom - rect.top) ? (rect.bottom - rect.top) / fMultiple : iYSource),
			UnitPixel);


		

		/*���ڴ�λͼ�ϻ���ǰ�ļ��������ļ������ļ���*/
		SolidBrush solidBrush(Color(255, 0, 0, 0));
	



		/*���ڴ�λͼ�����豸DC*/
		Graphics graphics(hdc);
		//graphics.Clear(Color::White);
		printf("%d\n", pt.x);
		graphics.DrawImage(pMemBitmap, (int)rect.left+pt.x, (int)rect.top+pt.y, (int)(rect.right - rect.left), (int)(rect.bottom - rect.top));

		
		if (NULL != pwFileName) {
			delete[] pwFileName;
			pwFileName = NULL;
		}
		
		if (NULL != pImage) {
			delete pImage;
			pImage = NULL;
		}
		if (NULL != pMemBitmap) {
			delete pMemBitmap;
			pMemBitmap = NULL;
		}

		//Gdiplus::GdiplusShutdown(gdiplusToken);
		EndPaint(hWnd, &ps);
		break;
	}
				   
	case WM_KEYDOWN: {	/*������Ϣ*/
		if (wParam == KEY_VALUE_B) {	/*B��*/
			if (fMultiple < 10.0) {	/*���Ŵ�ʮ��*/
				fMultiple *= fEnlarge;
			}
		}
		else if (wParam == KEY_VALUE_S) {	/*S��*/
			if (fMultiple > 0.1) {	/*�����Сʮ��*/
				fMultiple /= fEnlarge;
			}
		}
		else if (wParam == VK_RIGHT) {	/*S��*/
			if (iCurBmpJpg < iAllBmpJpg - 1) {
				iCurBmpJpg++;
			}
			else if (iCurBmpJpg == iAllBmpJpg - 1) {	/*���һ��ͼƬ��ѭ����������һ��*/
				iCurBmpJpg = 0;
			}
		}
		else if (wParam == VK_LEFT) {	/*S��*/
			if (iCurBmpJpg > 0) {
				iCurBmpJpg--;
			}
			else if (iCurBmpJpg == 0) {	/*��һ�ţ�ѭ�����������һ��*/
				iCurBmpJpg = iAllBmpJpg - 1;
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_MOUSEWHEEL:
		//0x020A
		if ((INT)wParam > 0)
			fMultiple /= fEnlarge;

		else
			fMultiple *= fEnlarge;

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		//cout << pt.x << " " << pt.y << endl;
		pt.x = LOWORD(lParam) - (rect.left+rect.right)/2;
		pt.y = HIWORD(lParam) - (rect.top+rect.bottom)/2;
		cout<< pt.x <<" "<< pt.y <<endl;
		//InvalidateRgn()
		//SendMessage(hWnd, WM_ERASEBKGND, NULL, NULL);
		InvalidateRect(hWnd, NULL, FALSE);
		
		UpdateWindow(hWnd);
		//SendMessage(hWnd, WM_ERASEBKGND, NULL, NULL);
		//SendMessage(hWnd, WM_PAINT, NULL, NULL);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	case WM_ERASEBKGND: {
		break;
	}
	default: {
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	}
	return 0;
}

/*
����˵����		�õ���ǰĿ¼�����е�BMP��JPG�ļ���
�������˵����
�������˵����	oBJPicture���洢BMP��JPG�ļ���
����ֵ˵����	���е�BMP��JPG�ļ�����
��ע��
*/
int GetBmpJpg(std::vector<std::string>& oBJPicture)
{
	int iRet = 0;
	HANDLE	hFile;
	WIN32_FIND_DATA oFindDate;
	string path = "D:\\Software\\MSYS2\\home\\user\\opengl\\allimg\\160124\\";
#if 1
	/*Ѱ��.jpg�ļ�*/
	//cout << path + "*.jpg" << endl;
	hFile = FindFirstFile((path+"*.jpg").c_str(), &oFindDate);
	if (hFile == INVALID_HANDLE_VALUE) {
		//MessageBox(NULL, "FindFirstFile() failed!", NULL, MB_OK);
		//return 0;
		iRet = 0;
	}
	else {
		iRet = 1;
	}
	while (iRet) {
		oBJPicture.push_back(path+oFindDate.cFileName);
		iRet = FindNextFile(hFile, &oFindDate);
	}
#endif
	/*Ѱ��.bmp�ļ�*/
	hFile = FindFirstFile((path+"*.bmp").c_str(), &oFindDate);
	if (hFile == INVALID_HANDLE_VALUE) {
		//MessageBox(NULL, "FindFirstFile() failed!", NULL, MB_OK);
		//return 0;
		iRet = 0;
	}
	else {
		iRet = 1;
	}
	while (iRet) {
		oBJPicture.push_back(path + oFindDate.cFileName);
		iRet = FindNextFile(hFile, &oFindDate);
	}

	/*Ѱ����ϣ��ͷž��*/
	FindClose(hFile);

#if 0
	/*������*/
	char szBJSize[10] = { 0 };
	itoa(oBJPicture.size(), szBJSize, 10);
	MessageBox(NULL, szBJSize, NULL, NULL);
	for (int i = 0; i < oBJPicture.size(); i++) {
		MessageBox(NULL, oBJPicture[i].c_str(), NULL, NULL);
	}
#endif

	/*�����ҵ���BMP��JPG�ļ�����*/
	return oBJPicture.size();
}


/*
����˵����		��char�ַ���ת����WCHAR�ַ���
�������˵����	buffer:�ַ���ָ��
�������˵����
����ֵ˵����	WCHAR�ַ���ָ��
��ע��
*/
wchar_t* ChrToWChr(const char* pBuffer)
{
	if (NULL == pBuffer) {
		return NULL;
	}
	//size_t ilen = strlen(pBuffer) + 1;

	wchar_t* pwBuf;

	size_t iwlen = MultiByteToWideChar(CP_ACP, 0, (const char*)pBuffer, -1, NULL, 0);

	pwBuf = new wchar_t[iwlen];

	MultiByteToWideChar(CP_ACP, 0, (const char*)pBuffer, -1, pwBuf, int(iwlen));

	return pwBuf;
}