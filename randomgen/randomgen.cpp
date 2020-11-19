

#include "framework.h"
#include "randomgen.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;     
WCHAR szTitle[MAX_LOADSTRING];  
WCHAR szWindowClass[MAX_LOADSTRING];      
WCHAR creator[MAX_LOADSTRING];
WCHAR pressbutton[MAX_LOADSTRING];
WCHAR pba[MAX_LOADSTRING];
WCHAR resulttemplate[MAX_LOADSTRING];


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_Creator, creator, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_RANDOMGEN, szWindowClass, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_PressBtnTxt, pressbutton, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_Movetext, pba, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_resulttemplate, resulttemplate, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RANDOMGEN));
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RANDOMGEN));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_RANDOMGEN);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

HWND hwnd_st_u;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_DEVLOPER_STOREIT: {
			std::ofstream filestream("dev.save.txt");
			filestream << u8"Randomgen \u00a6 \u00a9Sharkbyteprojects\n" << u8"Time\u00a0\u00a0\u00a0\u00a0\u00a0\u00a0\t" << seperator << "Mouse x" << seperator << "Mouse y" << std::endl;
			for (dataversion dv : datasstore) {
				filestream << dv.time << "\t" << seperator << dv.x << seperator << dv.y << "\n";
			}
			filestream << u8"\u007b\u007b\u0045\u004e\u0044\u007d\u007d" << std::endl;
			filestream.close();
		}
			break;
		case BN_CLICKED:
		{
			{
				switch (workstateof) {
				case workstate::movemouse: {
					if (prevworkstateof == workstate::nulls) {
						SetWindowText(hwnd_st_u, pba);
						datasstore.clear();
						fut = std::async(collectdata, &hWnd, &stopsss);
						stopsss = false;
						prevworkstateof = workstateof;
						workstateof = workstate::gettingdata;
					}
				}; break;
				case workstate::gettingdata: {
					if (prevworkstateof == workstate::movemouse) {
						SetWindowText(hwnd_st_u, L"Send Stopcode");
						stopsss = true;
						SetWindowText(hwnd_st_u, L"Waiting for result.");
						int result = fut.get();
						srand(time(NULL) * result);
						result = rand() % maximal + minimal;//MIN=0 MAX=100
						WCHAR output = (WCHAR)result;
						wchar_t buffer[MAX_LOADSTRING];
						wsprintfW(buffer, resulttemplate, result);
						SetWindowText(hwnd_st_u, buffer);
						prevworkstateof = workstateof;
						workstateof = workstate::nulls;
					}
				}; break;
				default: {
					prevworkstateof = workstateof;
					workstateof = workstate::movemouse;
					SetWindowText(hwnd_st_u, pressbutton);
				}break;
				}
			}
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		CreateWindowW(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"CLICK",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			10,         // x position 
			10,         // y position 
			150,        // Button width
			30,        // Button height
			hWnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			NULL);      // Pointer not needed.
		hwnd_st_u = CreateWindow(L"static", pressbutton,
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			10, 80, 900, 60,
			hWnd, NULL,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}