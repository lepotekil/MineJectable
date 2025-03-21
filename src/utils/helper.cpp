#include "minejectable.h"

void helper() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const wchar_t* text =
        L"\n"
        L"╔═════════════════════════════════════════╗\n"
        L"║           MINEJECTABLE v1.0.0           ║\n"
        L"╠═════════════════════════════════════════╣\n"
        L"║                                         ║\n"
        L"║  [INSERT] Show the menu                 ║\n"
        L"║                                         ║\n"
        L"║  [K]      Speedmine     [ON/OFF]        ║\n"
        L"║  [L]      ESP           [ON/OFF]        ║\n"
        L"║  [W]      Xray          [ON/OFF]        ║\n"
        L"║  [M]      Reach         [ON/OFF]        ║\n"
        L"║                                         ║\n"
        L"║  [END]    Exit the progam               ║\n"
        L"║                                         ║\n"
        L"║                       A GouGous's Cheat ║\n"
        L"╚═════════════════════════════════════════╝\n";
    
    DWORD written;
    WriteConsoleW(hConsole, text, wcslen(text), &written, NULL);
}
