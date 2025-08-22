#include "minejectable.h"

HANDLE hInitThread = NULL; // Handle to the initialization thread

JavaVM* vm = NULL;      // Pointer to a Java VM instance
JNIEnv* env = NULL;     // Pointer to a JNI environment
HMODULE g_hModule = NULL;

// Cleanup function that handles resource deallocation
void cleanup() {
    // Restore original window title before cleanup
    restore_window_title();
    
    if (vm != NULL) {
        vm->DetachCurrentThread();
        vm = NULL;
    }
    
    env = NULL;

    if (GetConsoleWindow() != NULL) {
        fclose(stdout);
        FreeConsole();
    }

    // Clean up initialization thread if it exists and isn't the current thread
    if (hInitThread != NULL && hInitThread != GetCurrentThread()) {
        CloseHandle(hInitThread);
        hInitThread = NULL;
    }
}

// Main initialization function for the DLL
DWORD WINAPI init(LPVOID lpParam) {
    // g_hModule is already set in DllMain, lpParam verification for safety
    if (g_hModule != (HMODULE)lpParam) {
        printf("[-] Warning: Module handle mismatch\n");
        g_hModule = (HMODULE)lpParam;
    }

    if (!AllocConsole() || freopen("CONOUT$", "w", stdout) == NULL) {
        cleanup();
        return 1;
    }
    SetConsoleTitleA(WINDOW_TITLE);
    
    banner();

    // Find and attach to JVM
    jsize vmCount = 0;
    if (JNI_GetCreatedJavaVMs(&vm, 1, &vmCount) != JNI_OK || vmCount == 0 || vm == NULL) {
        printf("[-] No JVMs found\n");
        cleanup();
        return 1;
    }

    jint res = vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
    if (res == JNI_EDETACHED) {
        res = vm->AttachCurrentThread((void**)&env, NULL);
    }

    if (res != JNI_OK || env == NULL) {
        printf("[-] Failed to attach to JVM\n");
        cleanup();
        return 1;
    }

    client();

    cleanup();

    FreeLibraryAndExitThread(g_hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            g_hModule = hModule;
            hInitThread = CreateThread(NULL, 0, init, hModule, 0, NULL);
            if (hInitThread == NULL) {
                printf("[-] Failed to create init thread, error: %lu\n", GetLastError());
                cleanup();
                return FALSE;
            }
            break;
        case DLL_PROCESS_DETACH:
            cleanup();
            break;
    }
    return TRUE;
}
