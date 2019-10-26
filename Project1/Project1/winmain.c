#include <windows.h>

/* 处理窗口过程 */

LRESULT CALLBACK WindowProc(
	 _In_ HWND   hwnd,//消息所属的窗口句柄
	_In_ UINT   uMsg,//具体消息名称WM_***
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) 
{

	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);//发送另一个消息
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		 
		break;
	 
	case WM_LBUTTONDOWN:

	{
        int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);
		char buf[1024];
		wsprintf(buf,TEXT("x=%d,y=%d"), xPos, yPos);
		MessageBox(hwnd, buf, TEXT("鼠标左键按下"),MB_OK);
		break;
	}
	case WM_KEYDOWN:
	{
		MessageBox(hwnd, TEXT("键盘按下"), TEXT("键盘按下"), MB_OK);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 101, TEXT("lixuhui"), strlen("lixuhui"));
		EndPaint(hwnd, &ps);
		break;
	}
		
		
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,/* 应用程序实例句柄 */
	_In_opt_ HINSTANCE hPrevInstance,/*  */
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	WNDCLASS cs;
	cs.cbClsExtra = 0;
	cs.cbWndExtra = 0;
	cs.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//F1
	cs.hCursor = LoadCursor(NULL,IDC_HAND);
	cs.hIcon = LoadIcon(NULL, IDI_ERROR);
	cs.hInstance = hInstance;
	cs.lpfnWndProc = WindowProc;
	cs.lpszClassName = TEXT("win");
	cs.lpszMenuName = NULL;
	cs.style = 0;


	RegisterClass(&cs);	
	/* lpClassName, lpWindowName, dwStyle, x, y,
		nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam */
	HWND hwnd=CreateWindow(cs.lpszClassName, TEXT("WINDOWS"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT ,NULL, NULL, hInstance, NULL);


	 
	ShowWindow(hwnd, SW_SHOWNORMAL);

	UpdateWindow(hwnd);

	/*  HWND        hwnd;
	UINT        message;
	WPARAM      wParam;
	LPARAM      lParam;
	DWORD       time;
	POINT       pt; */
	MSG msg;

	while (1)
	{
		if (GetMessage(&msg,NULL,0,0)==FALSE)
		{
			/*  _Out_ LPMSG lpMsg,
	            _In_opt_ HWND hWnd,
	            _In_ UINT wMsgFilterMin,
	            _In_ UINT wMsgFilterMax */
			break;
		}
		TranslateMessage(&msg);


		DispatchMessage(&msg);
	}


	return 0;
}