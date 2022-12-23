// productivitymonitoring.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "productivitymonitoring.h"
//#include "Data.h"
#include <vector>
#include <string>
#include <fstream>

#define MAX_LOADSTRING 100


// Global Variables:
HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];        
std::vector<std::wstring> CPU;
std::vector<std::vector<std::wstring>> DISK;
std::vector<std::vector<std::wstring>> VOLUME;
std::vector<std::vector<std::wstring>> RAM;
std::vector<std::vector<std::wstring>> GPU;
std::wstring RAMUsage;

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRODUCTIVITYMONITORING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRODUCTIVITYMONITORING));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRODUCTIVITYMONITORING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PRODUCTIVITYMONITORING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        200, 200, 1200, 850, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

void DeleteHeader(std::wstring& text) {
    if (text.size() == 0)
    {
        return;
    }
    auto number = text.find(':') + 2;
    text.erase(text.begin(), text.begin() + number);
}

void FillString(std::vector<std::wstring>& data) {
    int max = 0;
    for (auto str : data )
    {
        auto number = str.find(' ');
        if (number > max)
        {
            max = number;
        }
    }
    for (int i = 0; i < data.size(); i++)
    {
        auto space = data[i].find(' ');
        data[i].insert(data[i].begin() + space, (max - space) / 2, ' ');
    }
}

std::wifstream fin;

void GetData(std::string path, std::vector<std::wstring>& data) {
    fin.open(path);
    fin.ignore(2);
    std::wstring temp;
    while (fin)
    { 
        std::getline(fin, temp);
        if (temp.size() == 0)
        {
            break;
        }
        data.push_back(temp);
    }
    FillString(data);
    fin.close();
}

void GetData(std::string path, std::vector<std::vector<std::wstring>>& data) {
    fin.open(path);
    fin.ignore(2);
    std::wstring temp;
    std::wstring previous;
    data.push_back(std::vector<std::wstring>());
    int i = 0;
    while (fin)
    {
        std::getline(fin, temp);
        if (previous == temp)
        {
            break;
        }
        if (temp.size() == 0)
        {
            i++;
            data.push_back(std::vector<std::wstring>());  
        }
        else
        {
            DeleteHeader(temp);
            data[i].push_back(temp);
        }
        previous = temp;
    }
    data.pop_back();
    fin.close();
}

void LoadData() {
    system("start powershell.exe -windowStyle hidden C:\\Users\\maks2\\Desktop\\productivitymonitoring\\productivitymonitoring\\GetDataScript.ps1");
    GetData("CPU.txt", CPU);
    GetData("DISK.txt", DISK);
    GetData("VOLUME.txt", VOLUME);
    GetData("GPU.txt", GPU);
    GetData("RAM.txt", RAM);
    fin.open("RAMUsage.txt");
    std::getline(fin, RAMUsage);
    fin.close();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        LoadData();
        
        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case 1: 
            {
                CPU.clear();
                DISK.clear();
                VOLUME.clear();
                RAM.clear();
                GPU.clear();
                RAMUsage.clear();
                LoadData();
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
                
            }
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // CPU
            std::wstring text = L"CPU";
            TextOut(hdc, 0, 0, text.c_str(), text.size());
            int y = 20;
            for (int i = 0; i < CPU.size(); i++, y += 20)
            {
                TextOut(hdc, 20, y, CPU[i].c_str(), CPU[i].size());
            }
            y += 40;
            // DISK
            text = L"DISK";
            TextOut(hdc, 0, y, text.c_str(), text.size());
            y += 20;
            text = L"Model";
            TextOut(hdc, 20, y, text.c_str(), text.size());
            text = L"MediaType";
            TextOut(hdc, 270, y, text.c_str(), text.size());
            text = L"BusType";
            TextOut(hdc, 520, y, text.c_str(), text.size());
            text = L"Size";
            TextOut(hdc, 770, y, text.c_str(), text.size());
            y += 20;
            for (int i = 0; i < DISK.size(); i++, y+= 20)
            {
                for (int j = 0, x = 20; j < DISK[i].size(); j++,x+=250)
                {
                    TextOut(hdc, x, y, DISK[i][j].c_str(), DISK[i][j].size());
                }
            }
            y += 40;
            // VOLUME
            text = L"VOLUME";
            TextOut(hdc, 0, y, text.c_str(), text.size());
            y += 20;
            text = L"DriveLetter";
            TextOut(hdc, 20, y, text.c_str(), text.size());
            text = L"FileSystemLabel";
            TextOut(hdc, 220, y, text.c_str(), text.size());
            text = L"FileSystemType";
            TextOut(hdc, 420, y, text.c_str(), text.size());
            text = L"Size";
            TextOut(hdc, 620, y, text.c_str(), text.size());
            text = L"SizeRemaining";
            TextOut(hdc, 820, y, text.c_str(), text.size());
            y += 20;
            for (int i = 0; i < VOLUME.size(); i++, y += 20)
            {
                for (int j = 0, x = 20; j < VOLUME[i].size(); j++, x += 200)
                {
                    TextOut(hdc, x, y, VOLUME[i][j].c_str(), VOLUME[i][j].size());
                }
            }
            y += 40;
            // GPU
            text = L"GPU";
            TextOut(hdc, 0, y, text.c_str(), text.size());
            y += 20;
            text = L"Name";
            TextOut(hdc, 20, y, text.c_str(), text.size());
            text = L"CurrentHorizontalResolution";
            TextOut(hdc, 220, y, text.c_str(), text.size());
            text = L"MaxRefreshRate";
            TextOut(hdc, 420, y, text.c_str(), text.size());
            text = L"CurrentVerticalResolution";
            TextOut(hdc, 620, y, text.c_str(), text.size());
            text = L"AdapterRAM";
            TextOut(hdc, 820, y, text.c_str(), text.size());
            y += 20;
            for (int i = 0; i < GPU.size(); i++, y += 20)
            {
                for (int j = 0, x = 20; j < GPU[i].size(); j++, x += 200)
                {
                    TextOut(hdc, x, y, GPU[i][j].c_str(), GPU[i][j].size());
                }
            }
            y += 40;
            // RAM
            text = L"RAM";
            TextOut(hdc, 0, y, text.c_str(), text.size());
            y += 20;
            text = L"Manufacturer";
            TextOut(hdc, 20, y, text.c_str(), text.size());
            text = L"PartNumber";
            TextOut(hdc, 220, y, text.c_str(), text.size());
            text = L"SerialNumber";
            TextOut(hdc, 420, y, text.c_str(), text.size());
            text = L"DeviceLocator";
            TextOut(hdc, 620, y, text.c_str(), text.size());
            text = L"Capacity";
            TextOut(hdc, 820, y, text.c_str(), text.size());
            text = L"Speed";
            TextOut(hdc, 1020, y, text.c_str(), text.size());
            y += 20;
            for (int i = 0; i < RAM.size(); i++, y += 20)
            {
                for (int j = 0, x = 20; j < RAM[i].size(); j++, x += 200)
                {
                    TextOut(hdc, x, y, RAM[i][j].c_str(), RAM[i][j].size());
                }
            }
            y += 20;
            // RAM USAGE
            text = L"RAM Usage - ";
            text += RAMUsage + L"%";
            TextOut(hdc, 20, y, text.c_str(), text.size());
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
