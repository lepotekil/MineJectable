#include "minejectable.h"

// Original window procedure pointer
WNDPROC originalWndProc;

// Custom window procedure (hooked to handle custom message processing)
LRESULT CALLBACK CustomWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // Handle specific messages explicitly
    switch (msg) {
        case WM_CLOSE:        // Ensure proper window close behavior
        case WM_DESTROY:      // Handle window destruction
        case WM_QUIT:         // Properly handle quit messages
            return CallWindowProc(originalWndProc, hwnd, msg, wParam, lParam);

        // Optionally, handle other messages here

        default:
            // Pass all unhandled messages to the original window procedure
            break;
    }
    return CallWindowProc(originalWndProc, hwnd, msg, wParam, lParam);
}

// Hook the window procedure of the target application
void wndproc() {
    // Find the window by title using the WinAPI FindWindowA function
    HWND hwnd = FindWindowA(NULL, WINDOW_TITLE);

    // Check if the target window is found
    if (hwnd == NULL) {
        printf("[-] Could not find window with title 'Minecraft'.\n");
        return;
    }

    // Hook the window procedure by replacing it with CustomWndProc
    WNDPROC prevWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)CustomWndProc);

    // Ensure we properly store the original procedure the first time
    if (!originalWndProc && prevWndProc) {
        originalWndProc = prevWndProc;
    }

    // Check if the hooking was successful
    if (!originalWndProc) {
        // printf("[-] Failed to set custom wndproc.\n");
        return;
    }
    
    // printf("[+] wndproc for 'Minecraft' hooked!\n");
}