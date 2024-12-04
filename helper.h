#ifndef helper_h
#define helper_h

#define UP                  0
#define LEFT                1
#define DOWN                2
#define RIGHT               3
#define PROCEED             4
#define ESC                 5
#define UNNECESSARY_INPUT   -1

#define MOVE_CURSOR -4

// Console Handling
void setConsoleColor(int color);
void SetConsoleSize(int width, int height);
void clear_screen();
// End Console Handling

// Print Handling
void PrintfColor(const char* input, int color);
void printSpaces(int length);
void printEqualIndent(int input_length, int max_length);
// End Print Handling

// String Handling
int sizeArrStr(const char* string[]);
int StringIsEmpty(const char* string);
void DeleteString(char* string);
void EmptyString(char* string, int size);
// End String handling

// Game Handling
void DiskToString(char* stringDisk,int current_disk, int biggest_disk);
void TowerToString(char* stringTower,int biggest_disk, char accessories);
int CalculateMaxMove(int disk, int tower);
// End Game Handling

// Menu Modules
// MenuItems[] require a NULL at the end of the array as a breakpoint.
int Menu(const char* MenuHeader, const char* MenuItems[], const char* MenuExtras);
int MenuItem(int ItemsCount, const char* MenuHeader, const char* MenuItems[], const char* MenuFooter);
void PrintMenuItems(int ItemsCount, const char* MenuItems[], int Cursor);
int MenuInput(int *selected, int ItemsCount);
void MoveMenuCursor(int *selected, int UpOrDown);

// Cases
int CursorIsAtTop(int cursor);
int CursorIsAtBottom(int cursor, int ItemsCount);
// End Cases
// End Menu Modules

int PlayerInput();
// return UP LEFT DOWN RIGHT PROCEED (ENTER)

#endif