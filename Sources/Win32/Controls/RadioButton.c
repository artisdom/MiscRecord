#include <Windows.h>
// #include <WindowsX.h>
#include <CommCtrl.h> //����ͷ�ļ�
// ���뾲̬��
#pragma comment(lib, "Comctl32.lib")
// �����Ӿ�Ч�� Copy from MSDN
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// ������һ��WindowProc�ص�
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
// ��ڵ�
int WINAPI wWinMain(HINSTANCE hTheApp, HINSTANCE hPrevApp, LPWSTR lpCmd, int nShow)
{
    PCWSTR cn = L"My"; // ������
    PCWSTR tt = L"Ӧ�ó���"; // ���ڱ���
                         // ��ƴ�����
    WNDCLASS wc = { sizeof(WNDCLASS) };
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpfnWndProc = WindowProc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    LoadIconMetric(hTheApp, IDI_APPLICATION, LIM_SMALL, &wc.hIcon);
    wc.lpszClassName = cn;
    wc.hInstance = hTheApp;
    RegisterClass(&wc); // ע�ᴰ����
                        // ��������
    HWND hwnd = CreateWindow(cn, tt, WS_OVERLAPPEDWINDOW,
        28, 34, 400, 330, NULL, NULL, hTheApp, NULL);
    if (!hwnd)
    { /* ������ڴ���ʧ�ܣ�
      �Ǽ���ִ��Ҳû������
      ��ʹ�����ʹ�������ɡ�
      */
        return 0;
    }
    ShowWindow(hwnd, nShow); //��ʾ����
    UpdateWindow(hwnd); //���´���
                        // ��Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); //������Ϣ��WindowProc�ص�
    }
    return 0;
}

/*-----------------------------------------------------------------*/
//�ؼ�ID
#define IDC_RADBTN1			50001
#define IDC_RADBTN2			50002
#define IDC_RADBTN3			50003
#define IDC_RADBTNBLUE		51001
#define IDC_RADBTNRED		51002
#define IDC_RADBTNGREEN		51003
#define IDC_BTN_OK			1107 //ȷ����ťID
/*-----------------------------------------------------------------*/
// ��Ϣ������
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        // ��ȡ��ǰʵ�����
        HINSTANCE hthisapp = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
        // �����꣬�ؼ����Դ���Ϊ��׼��
        // ����ʱ��������
        int yLoc = 0;
        // ������ʾ�ı�
        yLoc += 10;
        CreateWindow(L"Static", L"��������Ա��ǣ�",
            SS_SIMPLE | WS_CHILD | WS_VISIBLE,
            10, yLoc, 160, 18,
            hwnd, NULL,
            hthisapp,
            NULL);
        // ��һ�鵥ѡ��ť
        yLoc += 22;
        CreateWindow(L"Button", L"��",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
            12, yLoc, 60, 16,
            hwnd,
            (HMENU)IDC_RADBTN1,
            hthisapp, NULL);
        yLoc += 20;
        CreateWindow(L"Button", L"Ů",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            12, yLoc, 60, 16,
            hwnd, (HMENU)IDC_RADBTN2, hthisapp, NULL);
        yLoc += 20;
        CreateWindow(L"Button", L"����", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            12, yLoc, 60, 16, hwnd, (HMENU)IDC_RADBTN3, hthisapp, NULL);
        // ��ʾ�ı�
        yLoc += 38;
        CreateWindow(L"Static", L"��ϲ����һ����ɫ��",
            WS_CHILD | WS_VISIBLE | SS_SIMPLE,
            10, yLoc, 150, 18, hwnd, NULL, hthisapp, NULL);
        //�ڶ��鵥ѡ��ť
        yLoc += 22;
        CreateWindow(L"Button", L"��ɫ", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
            12, yLoc, 60, 16, hwnd, (HMENU)IDC_RADBTNBLUE, hthisapp, NULL);
        yLoc += 20;
        CreateWindow(L"Button", L"��ɫ", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            12, yLoc, 60, 16, hwnd, (HMENU)IDC_RADBTNRED, hthisapp, NULL);
        yLoc += 20;
        CreateWindow(L"Button", L"��ɫ", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            12, yLoc, 60, 16, hwnd, (HMENU)IDC_RADBTNGREEN, hthisapp, NULL);
        // ����һ��ȷ����ť
        CreateWindow(L"Button", L"ȷ��", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            230, 180, 80, 27, hwnd, (HMENU)IDC_BTN_OK, hthisapp, NULL);
    }
    return 0;
    case WM_DESTROY:
        PostQuitMessage(0); //ƽ���˳�
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}