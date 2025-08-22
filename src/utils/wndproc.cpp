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
    // Get the cached window handle instead of searching repeatedly
    HWND hwnd = get_minecraft_window();

    // Check if we have a valid cached window handle
    if (hwnd == NULL || !is_minecraft_window_valid()) {
        // Window not found or no longer valid
        return;
    }

    // Hook the window procedure by replacing it with CustomWndProc (only if not already hooked)
    if (!originalWndProc) {
        WNDPROC prevWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)CustomWndProc);
        
        // Store the original procedure
        if (prevWndProc) {
            originalWndProc = prevWndProc;
            // printf("[+] wndproc for window hooked!\n");
        } else {
            // printf("[-] Failed to set custom wndproc.\n");
        }
    }
}