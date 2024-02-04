#include <windows.h>
#include "rect.h"

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#pragma comment(linker, "/subsystem:Windows")


// name's
const wchar_t * lpClassName = L"Rect";
const wchar_t * lpWindowName   = L"Transform";

LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, wchar_t* lpCmdLine, int nCmdShow)
{
    WNDCLASSEXW  WndClsEx = {0};

    WndClsEx.cbSize        = sizeof (WNDCLASSEX);
    WndClsEx.style         = CS_HREDRAW | CS_VREDRAW;
    WndClsEx.lpfnWndProc   = WndProc;
    WndClsEx.hInstance     = hInstance;
    WndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClsEx.lpszClassName = lpClassName;

    if (!RegisterClassExW(&WndClsEx)){
        MessageBox(NULL, "RegisterClassExW Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return -1;
    }

    HWND hwnd = CreateWindowExW(0, lpClassName, lpWindowName,
                                WS_OVERLAPPEDWINDOW,
                                100, 100, 600, 600,
                                HWND_DESKTOP, NULL, hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, "CreateWindowExW Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return -1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // loop
    MSG Msg = {0};
    while(GetMessageW(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessageW(&Msg);
    }
    return 0;
}

// rect obj's
gui::Rect r1, r2, r3, r4;

void paint(const gui::Rect& r, HDC &hdc, const gui::Pen &pen, int min_rect_size = 7)
{
    bool ok = r.valid();
    if (!ok)
        return;

    HPEN _pen = CreatePen(pen.iStyle, pen.cWidth, pen.color);       // custom pen
    SelectObject(hdc, _pen);

    // main rect
    Rectangle(hdc, r.left(), r.top(), r.right(), r.bottom());

    // other rect's
    gui::Rect _tmp(r);
    while ((_tmp.width() > 3 * min_rect_size) && (_tmp.height() > 3 * min_rect_size)) {
        _tmp.inflate(-min_rect_size, -min_rect_size);
        Rectangle(hdc, _tmp.left(), _tmp.top(), _tmp.right(), _tmp.bottom());
    }

    DeleteObject(_pen);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg) {

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // prev
        HPEN     prev_pen = static_cast<HPEN>(SelectObject(hdc, GetStockObject(DC_PEN)));
        HBRUSH prev_brush = static_cast<HBRUSH>(SelectObject(hdc, GetStockObject(NULL_BRUSH)));

        // window rect
        gui::Rect r(ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left + 1, ps.rcPaint.bottom - ps.rcPaint.top + 1);

        // painting of 4 rect's
        r1 = r; r2 = r; r3 = r; r4 = r;
        const auto [dx, dy] = r.size();

        // r1
        r1.right()  -= (dx / 2);
        r1.bottom() -= (dy / 2);

        // r2
        r2.left()   = r1.right();
        r2.bottom() = r1.bottom();

        // r3
        r3.top()   = r1.bottom();
        r3.right() = r1.right();

        // r4
        r4.top()  = r1.bottom();
        r4.left() = r1.right();

        r1.inflate(-5, -5);
        r2.inflate(-5, -5);
        r3.inflate(-5, -5);
        r4.inflate(-5, -5);

        paint(r1, hdc, gui::Pen(PS_SOLID, 1, RGB(255, 0, 0)));
        paint(r2, hdc, gui::Pen(PS_SOLID, 1, RGB(0, 255, 0)));
        paint(r3, hdc, gui::Pen(PS_SOLID, 1, RGB(0, 0, 255)));
        paint(r4, hdc, gui::Pen(PS_SOLID, 1, RGB(255, 100, 50)));

        // restore
        SelectObject(hdc, prev_pen);
        SelectObject(hdc, prev_brush);

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_CLOSE: DestroyWindow(hwnd); break;
    case WM_DESTROY: PostQuitMessage(WM_QUIT); break;
    default: return DefWindowProcW(hwnd, Msg, wParam, lParam);
    }

    return 0;
}
