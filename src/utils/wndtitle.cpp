#include "minejectable.h"

// Global variables
HWND hwndMinecraft = NULL;        // Handle of the Minecraft window
char originalWindowTitle[256] = { 0 }; // Buffer to store the original window title
bool windowTitleChanged = false;  // Track if we've changed the title

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
    windowTitleChanged = true;
    printf("[+] Minecraft launcher owned by %s!\n", newTitle);
}

// Function to get the cached window handle
HWND get_minecraft_window() {
    return hwndMinecraft;
}

// Function to validate if the cached window is still valid
bool is_minecraft_window_valid() {
    return hwndMinecraft != NULL && IsWindow(hwndMinecraft);
}

// Function to restore the original window title
void restore_window_title() {
    if (hwndMinecraft != NULL && windowTitleChanged && strlen(originalWindowTitle) > 0) {
        SetWindowTextA(hwndMinecraft, originalWindowTitle);
        windowTitleChanged = false;
        printf("[+] Window title restored to: %s\n", originalWindowTitle);
    }
}