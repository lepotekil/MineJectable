#include "minejectable.h"

void helper() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const wchar_t* text =
        L"\n"
        L"╔═════════════════════════════════════════╗\n"
        L"║           MINEJECTABLE v1.0.1           ║\n"
        L"╠═════════════════════════════════════════╣\n"
        L"║                                         ║\n"
        L"║  [INSERT] Show this menu                ║\n"
        L"║  [END]    Exit the program              ║\n"
        L"║                                         ║\n"
        L"║                       A GouGous's Cheat ║\n"
        L"╚═════════════════════════════════════════╝\n";
    
    DWORD written;
    WriteConsoleW(hConsole, text, wcslen(text), &written, NULL);
}
