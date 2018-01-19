//tcc -run gdiplus.c
#include <windows.h>
#pragma comment(lib,"gdiplus")

BOOL CenterWindow(HWND hwnd)
{
    HWND hwndParent;
    RECT rect, rectP;
    int width, height;      
    int screenwidth, screenheight;
    int x, y;
 
    //make the window relative to its parent
    hwndParent = GetDesktopWindow();    
     
    GetWindowRect(hwnd, &rect);
    GetWindowRect(hwndParent, &rectP);
     
    width  = rect.right  - rect.left;
    height = rect.bottom - rect.top;    
     
    x = ((rectP.right-rectP.left) -  width) / 2 + rectP.left;
    y = ((rectP.bottom-rectP.top) - height) / 2 + rectP.top;    
 
    screenwidth  = GetSystemMetrics(SM_CXSCREEN);
    screenheight = GetSystemMetrics(SM_CYSCREEN);
 
    //make sure that the dialog box never moves outside of//the screen
    if(x < 0) x = 0;
    if(y < 0) y = 0;
    if(x + width  > screenwidth)  x = screenwidth  - width;
    if(y + height > screenheight) y = screenheight - height;    
 
    MoveWindow(hwnd, x, y, width, height, FALSE);
        return TRUE;
}


//GDI+Flat
typedef struct _GdiplusStartupInput
{
    unsigned int GdiplusVersion;
    unsigned int DebugEventCallback;
    BOOL SuppressBackgroundThread;
    BOOL SuppressExternalCodecs;
}GdiplusStartupInput;


int WINAPI GdiplusStartup(int* token, GdiplusStartupInput *input, int *output);
void WINAPI GdiplusShutdown(int token);
int WINAPI GdipCreateFromHDC(HDC hdc, int* graphics);
int WINAPI GdipDeleteGraphics(int graphics);
//����
int WINAPI GdipCreatePen1(unsigned int argb_color, float width, int unit, int** pen);
int WINAPI GdipDeletePen(int* pen);
int WINAPI GdipDrawRectangle(int graphics, int* pen, float x, float y, float width, float height);
int WINAPI GdipDrawLine(int graphics, int* pen, float x1, float y1, float x2, float y2);

int token;
int* pen;

//*************************************************************
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

WNDCLASS wc;
const TCHAR* AppName = TEXT("MyWindowClass1");
HWND hwnd1;

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    //GDI+����
    GdiplusStartupInput StartupInput = { 0 };
    StartupInput.GdiplusVersion = 1;
    if (GdiplusStartup(&token, &StartupInput, NULL))MessageBox(0, TEXT("GdiPlus����ʧ��"), TEXT("����"), MB_ICONERROR);

    //�������ڹ���������ṹ
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;//���ڻص�����ָ��
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;//ʵ�����
    wc.hIcon = LoadIcon(hInstance, TEXT("ICON_1"));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);//Ĭ��ָ��
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);//Ĭ�ϱ�����ɫ
    wc.lpszMenuName = NULL;
    wc.lpszClassName = AppName;//��������

                               //ע�ᴰ����
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("ע�ᴰ����ʧ��!"), TEXT("����"), MB_ICONERROR);
        return 0;
    }

    //��������
    int style = WS_OVERLAPPEDWINDOW;
    hwnd1 = CreateWindow(AppName, TEXT("���ڱ���"), style, 50, 50, 500, 500, 0,NULL, hInstance, 0);
    if (hwnd1 == NULL)
    {
        MessageBox(NULL, TEXT("��������ʧ��!"), TEXT("����"), MB_ICONERROR);
        return 0;
    }
    //�ޱ߿򴰿�
    /*SetWindowLong(hwnd1, GWL_STYLE, WS_OVERLAPPED | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);*/

    CenterWindow(hwnd1);
    //��ʾ�����´���
    ShowWindow(hwnd1, nCmdShow);
    UpdateWindow(hwnd1);

    //��Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //GDI+�ر�
    GdiplusShutdown(token);//���԰����д����Ϣѭ�����棬�����˳������٣������ڲ���ҪGDI+ʱ���ã�����GDI+���ڵ�WM_DESTROY��Ϣ�����
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (uMsg)
    {

        case WM_PAINT:
            
            
            hdc = BeginPaint(hwnd, &ps);

            int graphics;
            GdipCreateFromHDC(hdc, &graphics);//����Graphics����
            GdipCreatePen1(0x60FF2015, 1, 2, &pen);//��������
            GdipDrawRectangle(graphics, pen, 20, 20, 120, 120);//������
            GdipDrawLine(graphics, pen, 50, 60, 170, 340);//��ֱ��

            GdipDeletePen(pen);//���ٻ���
            GdipDeleteGraphics(graphics);//����Graphics����

            EndPaint(hwnd, &ps);
            return 0;//����ϵͳ��WM_PAINT��Ϣ���Ѿ������ˣ����Ƕ������Ķ���ȥ�ɡ�
        case WM_CREATE:
            break;
        case WM_DESTROY://�����Ѿ�����
            PostQuitMessage(0);//�˳���Ϣѭ��������Ӧ�ó���
            return 0;
            break;
        case WM_LBUTTONDOWN://����������
                            //���ޱ߿򴰿��ܹ��϶�(�ڴ��ڿͻ����϶�)
            PostMessage(hwnd, WM_SYSCOMMAND, 61458, 0);
            break;
            /*case WM_MOUSEMOVE://����ƶ�
            int xPos, yPos;
            xPos = GET_X_LPARAM(lParam);//���λ��X����
            yPos = GET_Y_LPARAM(lParam);//���λ��Y����
            //��Ҫ��LOWORD��HIWORD��ȡ���꣬��Ϊ�����п����Ǹ���
            break;*/
        default:
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);//������Ϣ����ϵͳ����
}