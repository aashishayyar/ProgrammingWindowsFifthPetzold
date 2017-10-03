#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdShow, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("TextOut Application");

	wndclass.cbSize 		= sizeof(WNDCLASSEX);
	wndclass.style  		= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpszMenuName 	= NULL;
	wndclass.lpszClassName  = szAppName;
	wndclass.cbClsExtra 	= 0;
	wndclass.cbWndExtra 	= 0;
	wndclass.hInstance 		= hInstance;
	wndclass.lpfnWndProc 	= WndProc;
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);	
	wndclass.hIcon 			= LoadIcon	(NULL, IDI_APPLICATION);
	wndclass.hIconSm 		= LoadIcon	(NULL, IDI_APPLICATION);
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
						szAppName,
						TEXT("TextOutApplication : Aashish Ayyar"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
					 	CW_USEDEFAULT,
						NULL, NULL,
						hInstance,
						NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);	
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
		case WM_CREATE:
			break;
		case WM_PAINT:
			break;
		case WM_DESTROY:
			PostQuitMessage(0);	
			break;	 
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}