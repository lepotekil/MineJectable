#include "minejectable.h"

int speedmine = 0;
int esp = 0;
int xray = 0;
int reach = 0;

// Helper function to toggle features
void toggleFeature(int& feature, const char* featureName) {
    feature = !feature;  // Switch between 0 and 1
    printf("[%c] %s %s\n", 
        feature ? '+' : '-',
        featureName,
        feature ? "enabled" : "disabled");
}

void client() {

    change_window_title(WINDOW_TITLE); // Change window title of the process to 'MineJectable'
    helper();                       // Display the UI helper menu

    // Main loop for program logic
    while (TRUE) {
        wndproc(); // Process window-specific events

        // Handle the Insert key to open the helper menu
        if (GetAsyncKeyState(VK_INSERT) & 1) { // Use bitwise & for key debounce
            helper();
        }

        if (GetAsyncKeyState('K') & 1) {
            toggleFeature(speedmine, "Speedmine");
        }

        if (GetAsyncKeyState('L') & 1) {
            toggleFeature(esp, "ESP");
        }

        if (GetAsyncKeyState('W') & 1) {
            toggleFeature(xray, "Xray");
        }

        if (GetAsyncKeyState('M') & 1) {
            toggleFeature(reach, "Reach");
        }

        // Check if the END key is pressed to exit the loop gracefully
        if (GetAsyncKeyState(VK_END) & 1) { // Use bitwise & for better event detection
            printf("\n[+] Exiting MineJectable...\n");
            break;
        }

        // Pause execution to reduce CPU usage
        Sleep(150);
    }

    return;
}