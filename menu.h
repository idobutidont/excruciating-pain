#ifndef menu_h
#define menu_h

#define UP                  0
#define LEFT                1
#define DOWN                2
#define RIGHT               3
#define PROCEED             4
#define ESC                 5
#define UNNECESSARY_INPUT   -505

#define MOVE_CURSOR 101

// Console Handling
void setConsoleColor(int color);
void setConsoleSize(int width, int height);
void clear_screen();
// End Console Handling

// Print Handling
void printfColor(const char* input, int color);
void printSpaces(int length);
// End Print Handling

// String Handling
int sizeArrStr(const char* string[]);
// End String handling

// Menu Modules
// MenuItems[] require a NULL at the end of the array as a breakpoint.
int Menu(const char* MenuHeader, const char* MenuItems[], const char* MenuExtras);
int MenuItem(int ItemsCount, const char* MenuHeader, const char* MenuItems[], const char* MenuFooter);
void PrintMenuItems(int ItemsCount, const char* MenuItems[], int Cursor);
int MenuInput(int *selected, int ItemsCount);
void MoveMenuCursor(int *selected, int UpOrDown);

void ChangeableMenu(int *item, const char* NameItem, int minSize, int maxSize);
int ChangeableMenuInput(int *item, int minSize, int maxSize);

// Cases
int CursorIsAtTop(int cursor);
int CursorIsAtBottom(int cursor, int ItemsCount);
// End Cases
// End Menu Modules

int PlayerInput();
// return UP LEFT DOWN RIGHT PROCEED (ENTER)

#endif