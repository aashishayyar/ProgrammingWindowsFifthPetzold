#include <windows.h>
#include "sysmets.h"

// Macros for Error Checking 
#define ERRORBOX1(lpText, lpCaption) {																		 \
										MessageBox((HWND)NULL, TEXT(lpText), TEXT(lpCaption), MB_ICONERROR); \
										ExitProcess(EXIT_FAILURE);											 \
									}

#define ERRORBOX2(hwnd, lpText, lpCaption) {																 \
										MessageBox((HWND)NULL, TEXT(lpText), TEXT(lpCaption), MB_ICONERROR); \
									 	DestroyWindow(hwnd);												 \
									 }

// Declaring Window Procedure Call
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdShow, int nCmdShow)
{
	HWND 		hwnd;
	MSG 		msg;
	WNDCLASSEX 	wndclass;
	HICON 		hIcon;
	HICON 		hIconSm;
	HBRUSH		hBrush;
	HCURSOR 	hCursor;	
	TCHAR 		szAppName[] = TEXT("Template Application");

	// Acquire brush to paint the window background 
	hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	if (hBrush == NULL)
		ERRORBOX1("Failed to acquire brush to paint window background", "Error");
	
	// Set an Icon 
	hIcon = (HICON)LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
	if (hIcon == NULL)
		ERRORBOX1("Failed to load Icon", "Error");

	// Set a Small Icon
	hIconSm = (HICON)LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
	if (hIconSm == NULL)
		ERRORBOX1("Failed to load Small Icon", "Error");

	// Set a Cursor
	hCursor = (HCURSOR)LoadCursor((HINSTANCE)NULL,IDC_ARROW);
	if (hCursor == NULL)
		ERRORBOX1("Failed to load Cursor", "Error");		

	wndclass.cbSize 		= sizeof(WNDCLASSEX);
	wndclass.style  		= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpszMenuName 	= NULL;
	wndclass.lpszClassName  = szAppName;
	wndclass.cbClsExtra 	= 0;
	wndclass.cbWndExtra 	= 0;
	wndclass.hInstance 		= hInstance;
	wndclass.lpfnWndProc 	= WndProc;
	wndclass.hIcon 			= hIcon;
	wndclass.hIconSm 		= hIconSm;
	wndclass.hCursor		= hCursor;
	wndclass.hbrBackground	= hBrush;	

	// Registering the above filled structure
	if (RegisterClassEx(&wndclass) == 0)
		ERRORBOX1("Failed to Register Class", "Error");

	// Creating Window in memory
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
						szAppName,
						TEXT("TemplateApplication : Aashish Ayyar"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
					 	CW_USEDEFAULT,
						NULL, NULL,
						hInstance,
						NULL);
	if (hwnd == NULL)
		ERRORBOX1("Failed to Create Window", "Error");

	// Displaying the window on Screen
	ShowWindow  (hwnd, nCmdShow);

	// To send an WM_PAINT message
	UpdateWindow(hwnd);

	// Message Loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage (&msg);	
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	/*VAriable required for TextOut()*/
	static int  cxChar, cxCaps, cyChar;
	HDC 		hdc;
	int 		i;
	PAINTSTRUCT ps;
	TEXTMETRIC  tm;
	TCHAR 		szBuffer[10];

	switch(iMsg)
	{
		case WM_CREATE:
		/* To set the starting point of the TextOut()*/
			hdc = GetDC(hwnd);
			if (hdc == NULL)
				ERRORBOX2(hwnd, "Failed to acquire Device Context", "Error");

			GetTextMetrics(hdc, &tm)	;
			cxChar = tm.tmAveCharWidth	;
			cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
			cyChar = tm.tmHeight + tm.tmExternalLeading;
			ReleaseDC(hwnd, hdc);
			break;

		case WM_PAINT:
		/*Actually printing the characters */
			hdc = BeginPaint(hwnd, &ps);

			for (i = 0; i < NUMLINES ; i++)
			{
				TextOut(hdc, 0, cyChar * i,
						sysmetrics[i].szLabel,
						lstrlen (sysmetrics[i].szLabel));
				TextOut(hdc, 22 * cxCaps, cyChar * i,
						sysmetrics[i].szDesc,
						lstrlen (sysmetrics[i].szDesc));

				SetTextAlign(hdc, TA_RIGHT | TA_TOP);

				TextOut(hdc, 22 * cxCaps + 40 * cxChar,
						cyChar  * i, szBuffer, wsprintf(szBuffer, TEXT("%5d"), GetSystemMetrics(sysmetrics[i].iIndex)));
				SetTextAlign(hdc, TA_LEFT | TA_TOP);
			}
			EndPaint(hwnd, &ps);

			break;
		case WM_DESTROY:
			PostQuitMessage(0);	
			break;	 
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}