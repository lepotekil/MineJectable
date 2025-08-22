#ifndef __MINEJECTABLE_WNDTITLE_H__
#define __MINEJECTABLE_WNDTITLE_H__

void change_window_title(const char* newTitle);
void restore_window_title();
HWND get_minecraft_window();
bool is_minecraft_window_valid();

#endif