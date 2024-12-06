/***************************************************************
* FILENAME: menu.c
* DESCRIPTION: Code that mostly helps with menu handling.
* AUTHOR: Azzar
* DATE: 12 / 11 / 2024
****************************************************************/

#include "menu.h"

#include <conio.h>
#include <windows.h>
#include <stdio.h>

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)color);
}

void setConsoleSize(int width, int height) {
    char stringCommand[16];
    sprintf(stringCommand, "mode %d,%d", width, height);
    system(stringCommand);
}

// AUTHOR: (Duthomhas) https://cplusplus.com/articles/4z18T05o/
// Significantly more efficient clear screen function
void clear_screen() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    DWORD dwCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    /* Get the number of cells in the current buffer */
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    DWORD dwSize = (DWORD) (csbi.dwSize.X * csbi.dwSize.Y);

    /* Fill the entire buffer with spaces */
    FillConsoleOutputCharacter(hStdOut, ' ', dwSize, coordScreen, &dwCharsWritten);

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, coordScreen);
}

void printfColor(const char* input, int color) {
    setConsoleColor(color);
    printf("%s", input);
    setConsoleColor(15); //default console color
}

// Basically what this does is print spaces for length time
void printSpaces(int length) {
    printf("%*s", length, "");
}

// this require the string to have a NULL at the end of the element.
int sizeArrStr(const char* string[]) {
    int i = -1;
    while (string[++i] != NULL);
    return i;
}

int Menu(const char* MenuHeader, const char* MenuItems[], const char* MenuFooter){
    return MenuItem(sizeArrStr(MenuItems), MenuHeader, MenuItems, MenuFooter);
}

// Ini bakal nge return nilai yang ada di antara MenuItems, contoh bisa liat di main main.c
int MenuItem(int ItemsCount, const char* MenuHeader, const char* MenuItems[], const char* MenuFooter) {

    int input;
    int cursor = 0;

    clear_screen();
    setConsoleSize((ItemsCount + 2) * 12, (ItemsCount + 2) * 2);

    do
    {
        clear_screen();
        printf("\n\t%s", MenuHeader);
        PrintMenuItems(ItemsCount, MenuItems, cursor);
        printf("\t%s", MenuFooter);

        while ((input = MenuInput(&cursor, ItemsCount)) == UNNECESSARY_INPUT);    // refrain the player from making unnecessary input
        
        if (input != MOVE_CURSOR) return input;
        
    } while (1);
    
    return -1;

}

void PrintMenuItems(int ItemsCount, const char* MenuItems[], int Cursor) {

    for (int i = 0; i < ItemsCount; ++i) {
        if (i == Cursor) {
            printf("\t> %s", MenuItems[i]);
        } else {
            printf("\t %s", MenuItems[i]);
        }
    }

}

int MenuInput(int *cursor, int ItemsCount) {
    
    switch (PlayerInput()) {

    case LEFT: case UP:

        if (CursorIsAtTop(*cursor)) return UNNECESSARY_INPUT;
        MoveMenuCursor(&(*cursor), UP);

        break;

    case RIGHT: case DOWN:

        if (CursorIsAtBottom(*cursor, ItemsCount)) return UNNECESSARY_INPUT;
        MoveMenuCursor(&(*cursor), DOWN);

        break;
        
    case PROCEED: 
        return *cursor;

    default: 
        return UNNECESSARY_INPUT;
    }

    return MOVE_CURSOR;
}

void MoveMenuCursor(int *cursor, int UpOrDown) {
    
    if (UpOrDown == UP) --*(cursor);

    if (UpOrDown == DOWN) ++*(cursor);

}

int CursorIsAtTop(int cursor) {
    return cursor == 0;
}

int CursorIsAtBottom(int cursor, int ItemsCount) {
    return cursor == ItemsCount - 1;
}

void ChangeableMenu(int *item, const char* NameItem, int minSize, int maxSize) {

    int input_result, windowWidth, windowHeight;

    *item = minSize;

    // strlen + 2 indents (8) + " Amount: <  >" (13) + maxSize (roughly 3 digit at max lol)
    // 42 = "Press Enter to Continue..." + 2 indents
    windowWidth =(int) max( strlen(NameItem) + 32, 42);
    windowHeight = 6;

    clear_screen();
    setConsoleSize(windowWidth, windowHeight);

    do
    {
        clear_screen();
        printf("\n\t%s Amount: < %d >", NameItem, *item);

        printf("\n\n\tPress Enter to Continue...");

        while ((input_result = ChangeableMenuInput(&*item, minSize, maxSize)) == UNNECESSARY_INPUT);

        if (input_result != MOVE_CURSOR) return;

    } while (1);
    
}

int ChangeableMenuInput(int *item, int minSize, int maxSize) {
    switch (PlayerInput()) {

    case RIGHT:
        if (*item >= maxSize) return UNNECESSARY_INPUT;
        ++(*item);
        break;
    
    case LEFT:
        if (*item <= minSize) return UNNECESSARY_INPUT;
        --(*item);
        break;

    case PROCEED:
        return *item;

    default: 
        return UNNECESSARY_INPUT;

    }

    return MOVE_CURSOR;
}

int PlayerInput() {

    switch (getch()) {
        
        // escape key
        case 27: return ESC;

        // case 224 || 0
        case 224: case 0:
        
            switch(getch()) {
                case 72: return UP;
                case 75: return LEFT;  
                case 80: return DOWN;
                case 77: return RIGHT;
                default: return UNNECESSARY_INPUT;
            }

        case 13: return PROCEED;

        default: return UNNECESSARY_INPUT;
    }

}
