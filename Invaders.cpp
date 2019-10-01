/*

    Copyright 2006 Daniele Faggi (Delta6)

    This file is part of Invaders.

    Invaders is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Invaders is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Invaders.  If not, see <http://www.gnu.org/licenses/>.

*/

// Invaders.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The title bar text


HWND hAppWnd;

int  record = 0;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


void WriteRecord() {

	TCHAR lpszRec[256];
	memset(lpszRec, 0, sizeof(TCHAR) * 256);
	_stprintf(lpszRec, _T("%d"), record);
	LONG cb = _tcslen(lpszRec);

	RegSetValue(HKEY_CURRENT_USER, _T("Software\\DF\\Invaders\\HiScore"), REG_SZ, lpszRec, cb);


}

void ReadRecord() {

	LONG cb = sizeof(TCHAR)*256;
	TCHAR lpszRec[256];
	memset(lpszRec, 0, sizeof(TCHAR) * 256);
	RegQueryValue(HKEY_CURRENT_USER, _T("Software\\DF\\Invaders\\HiScore"), lpszRec, &cb);
	record = _ttol(lpszRec);


}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_INVADERS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_INVADERS);
	
	ReadRecord();

	InitializeBackbuffers(GetDC(hAppWnd));

	LoadBitmaps(hInstance);
	LoadSounds(hInstance);

	InitializeGameVars();
	InitializeBarriers();

	GetGameVars()->lives = 0;
	GetGameVars()->enter_level_timer = 0;

	DWORD time = 0;

	// Main message loop:

	while (TRUE) 
	{
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if(msg.message == WM_QUIT) break;

		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Frame Processing
		DWORD nexttime = GetTickCount();

		if(time < nexttime) {
			// Update positions
			UpdateVars();

			// Render screen
			Render(GetGameVars());
			
			// Exchange backbuffers
			FlipBackbuffers();

			// Signal for screen update
			InvalidateRect(hAppWnd, NULL, FALSE);

			// Ensure 30 fps
			time = nexttime + (1000 / 30); // 30 fps
		}

	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_INVADERS);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_INVADERS;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);

	RECT rect;
	memset(&rect, 0, sizeof(RECT));

	rect.left = 0;
	rect.top  = 0;
	rect.right = 640;
	rect.bottom = 460;

	AdjustWindowRect(&rect,(WS_OVERLAPPEDWINDOW&~WS_THICKFRAME)|WS_DLGFRAME, TRUE);
	
    HWND hWnd;

    hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindow(szWindowClass, szTitle, (WS_OVERLAPPEDWINDOW&~WS_THICKFRAME&~WS_MAXIMIZEBOX)|WS_DLGFRAME,
      (w-rect.right)/2, (h-rect.bottom)/2, rect.right, rect.bottom, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
       return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    hAppWnd = hWnd;

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	int nVirtKey;
	long lKeyData;

	BOOL bNoSound;
	HMENU hmenu;

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				    DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				    break;
				case IDM_EXIT:
					if(IDOK == MessageBox(hAppWnd, _T("Surrender, are you sure ?"), _T("Question"), MB_OKCANCEL|MB_ICONQUESTION)) {
						DestroyWindow(hWnd);
					}
				    break;
				case IDM_NEW:
					if(!(GetGameVars()->lives == 0 && GetGameVars()->tank == NULL)) {
						if(IDOK == MessageBox(hAppWnd, _T("Current game is not ended, restart ?"), _T("Question"), MB_OKCANCEL|MB_ICONQUESTION)) {
							
							// Restart Game
							
							FreeGameVars();
							InitializeGameVars();
							InitializeBarriers();
							InitializeTank();
						}

					} else {

						// Restart Game
							
						FreeGameVars();
						InitializeGameVars();
						InitializeBarriers();
						InitializeTank();

					}
				    break;
				case IDM_NOSOUND:

					hmenu = GetMenu(hAppWnd);
					
					MENUITEMINFO mii;
					memset(&mii, 0, sizeof(MENUITEMINFO));
					mii.cbSize = sizeof(MENUITEMINFO);
					mii.fMask = MIIM_STATE;

					GetMenuItemInfo(hmenu, IDM_NOSOUND, FALSE, &mii);
					
					bNoSound = (mii.fState & MFS_CHECKED) != 0;
					
					bNoSound = !bNoSound;

					if(bNoSound) {
						mii.fState = MFS_CHECKED;
						SoundOff();
					} else {
						mii.fState = MFS_UNCHECKED;
						SoundOn();
					}

					SetMenuItemInfo(hmenu, IDM_NOSOUND, FALSE, &mii);

					break;

				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			RECT rt;
			GetClientRect(hWnd, &rt);
			RenderToDC(hdc);
			EndPaint(hWnd, &ps);
			break;

		case WM_CLOSE:
			if(IDOK == MessageBox(hAppWnd, _T("Surrender, are you sure ?"), _T("Question"), MB_OKCANCEL|MB_ICONQUESTION)) {
				WriteRecord();
				DestroyWindow(hWnd);
			}
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			nVirtKey = (int) wParam;    // virtual-key code 
			lKeyData = lParam;          // key data 
			switch(wParam) {
				case VK_LEFT: 
					TankStartLeft();
					break;
				case VK_RIGHT:
					TankStartRight();
					break;
				case VK_UP:
					TankFire();
					break;
			}
			break;
		case WM_KEYUP:
			nVirtKey = (int) wParam;    // virtual-key code 
			lKeyData = lParam;          // key data 
			switch(wParam) {
				case VK_LEFT: 
					TankStopLeft();
					break;
				case VK_RIGHT:
					TankStopRight();
					break;
				case VK_UP:
					if(GetGameVars()->tank == NULL && GetGameVars()->lives > 0)
						InitializeTank();
					break;
			}

			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
