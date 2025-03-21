#ifndef __MINEJECTABLE_H__
#define __MINEJECTABLE_H__

// C++
#include <thread>
#include <chrono>

// Windows
#include <winsock2.h>
#include <windows.h>
#include <winternl.h>
#include <tlhelp32.h>
#include <wincrypt.h>

// JNI
#include "jnix64/jni.h" // Include the JNI header for 64-bit

// Main
#include "main.h"


// Utils
#include "utils/banner.h"
#include "utils/helper.h"
#include "utils/wndproc.h"
#include "utils/wndtitle.h"


// Constants
#define WINDOW_TITLE "MineJectable"

// Global variables
extern JavaVM* vm;
extern JNIEnv* env;
extern HMODULE g_hModule;

extern WNDPROC originalWndProc;

#endif // __MINEJECTABLE_H__