#include "minejectable.h"

void AdjustConsoleSize(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;

    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };

    SetConsoleScreenBufferSize(hConsole, bufferSize);
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

void banner() {
    const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;

    // Initial configuration of the console
    SetConsoleOutputCP(CP_UTF8);
    AdjustConsoleSize(120, 30);

    // Constant definition
    static constexpr LPCWSTR banner = LR"(
███╗   ███╗██╗███╗   ██╗███████╗     ██╗███████╗ ██████╗████████╗ █████╗ ██████╗ ██╗     ███████╗
████╗ ████║██║████╗  ██║██╔════╝     ██║██╔════╝██╔════╝╚══██╔══╝██╔══██╗██╔══██╗██║     ██╔════╝
██╔████╔██║██║██╔██╗ ██║█████╗       ██║█████╗  ██║        ██║   ███████║██████╔╝██║     █████╗  
██║╚██╔╝██║██║██║╚██╗██║██╔══╝  ██   ██║██╔══╝  ██║        ██║   ██╔══██║██╔══██╗██║     ██╔══╝  
██║ ╚═╝ ██║██║██║ ╚████║███████╗╚█████╔╝███████╗╚██████╗   ██║   ██║  ██║██████╔╝███████╗███████╗
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝ ╚════╝ ╚══════╝ ╚═════╝   ╚═╝   ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝                                                                                          
    )";
    static constexpr const char* msg = "[+] MineJectable DLL loaded into Minecraft!\n";

    // Display banner
    DWORD written;
    WriteConsoleW(hConsole, banner, lstrlenW(banner), &written, nullptr);
    putchar('\n'); // Reset cursor position

    // Message animation
    for (size_t i = 0; msg[i] != '\0'; ++i) {
        putchar(msg[i]);
        fflush(stdout);
        Sleep(25);
    }
}
