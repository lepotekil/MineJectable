#include "minejectable.h"

void client() {

    change_window_title(WINDOW_TITLE); // Change window title of the process to 'MineJectable'
    helper();                       // Display the UI helper menu

    // Main loop for program logic
    while (TRUE) {
        // Check if Minecraft window is still valid, exit if not
        if (!is_minecraft_window_valid()) {
            printf("\n[-] Minecraft window is no longer valid. Exiting...\n");
            break;
        }

        wndproc(); // Process window-specific events

        // Handle the Insert key to open the helper menu
        if (GetAsyncKeyState(VK_INSERT) & 1) { // Use bitwise & for key debounce
            helper();
        }

        // Check if the END key is pressed to exit the loop gracefully
        if (GetAsyncKeyState(VK_END) & 1) { // Use bitwise & for better event detection
            break;
        }

        // Optimized pause to reduce CPU usage while maintaining responsiveness
        Sleep(50);
    }

    return;
}