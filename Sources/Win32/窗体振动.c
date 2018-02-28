#include<windows.h>
#include<math.h>
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM ) ;            //�������ڹ��̺���



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow )
{
    static TCHAR szAppName[] = TEXT("PrintText") ;
    HWND hwnd ;
    MSG msg ;
    WNDCLASS wndclass;

    //�������Ա����
    wndclass.lpfnWndProc = WndProc ;
    wndclass.lpszClassName = szAppName ;
    wndclass.hInstance = hInstance ;
    wndclass.style = CS_HREDRAW | CS_VREDRAW ;
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH) ;
    wndclass.hCursor = LoadCursor( NULL, IDC_ARROW ) ;
    wndclass.hIcon = LoadIcon( NULL, IDI_APPLICATION ) ;
    wndclass.cbClsExtra = 0 ;
    wndclass.cbWndExtra = 0 ;
    wndclass.lpszMenuName = NULL ;

    //ע�ᴰ����
    if( !RegisterClass( &wndclass ) )
    {
        MessageBox( NULL, TEXT("����, ����ע��ʧ��!"), TEXT("����"), MB_OK | MB_ICONERROR ) ;
        return 0 ;
    }
    
    //��������
    hwnd = CreateWindow(szAppName, TEXT("������"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL );

    //��ʾ����
    ShowWindow( hwnd, iCmdShow ) ;
    UpdateWindow( hwnd ) ;

    //��ȡ�����롢�ַ���Ϣ
    while( GetMessage( &msg, NULL, 0, 0 ) )
    {
        TranslateMessage( &msg ) ;
        DispatchMessage( &msg ) ;
    }
    return msg.wParam ;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    HDC hdc ;
    PAINTSTRUCT ps ;
	static int inc=0;

    switch(message)
    {
	case WM_CREATE:
		//MoveWindow(hwnd,0,100,500,500,0);
		SetTimer(hwnd,1,10,0);
		break;
    case WM_TIMER:    //����WM_PAINT��Ϣ
		if(inc>320)break;
		inc+=10;
		MoveWindow(hwnd,400+3*sin(inc),100+3*cos(inc),500,500,0);
		MessageBeep(0);
		break;
    case WM_DESTROY:    //����WM_DESTROY��Ϣ
        PostQuitMessage(0) ;
        return 0 ;
    }

    return DefWindowProc( hwnd, message, wParam, lParam ) ;
}