#include "minejectable.h"

// Global variables
HWND hwndMinecraft = NULL;        // Handle of the Minecraft window
char originalWindowTitle[256] = { 0 }; // Buffer to store the original window title

// Function to change the window title
void change_window_title(const char* newTitle) {
    // If we haven't already found the Minecraft window
    if (hwndMinecraft == NULL) {
        hwndMinecraft = FindWindowA(NULL, "Minecraft");
        if (hwndMinecraft == NULL) {
            printf("[-] Could not find window with title 'Minecraft'.\n");
            return;
        }

        // Save the original window title
        GetWindowTextA(hwndMinecraft, originalWindowTitle, sizeof(originalWindowTitle));
    }

    // Change the window title
    SetWindowTextA(hwndMinecraft, newTitle);
    printf("[+] Minecraft launcher owned by %s!\n", newTitle);
}