/***************************************************************
* FILENAME: helper.c
* DESCRIPTION: 
* AUTHOR: 
* DATE: 
****************************************************************/

#include "helper.h"

#include <conio.h>
#include <windows.h>
#include <stdio.h>

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)color);
}

// AUTHOR: CHATGPT
// Significantly more efficient clear screen function
void clear_screen() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    DWORD dwCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    DWORD dwSize = (DWORD) (csbi.dwSize.X * csbi.dwSize.Y);
    FillConsoleOutputCharacter(hStdOut, ' ', dwSize, coordScreen, &dwCharsWritten);
    SetConsoleCursorPosition(hStdOut, coordScreen);
}

void SetConsoleSize(int width, int height) {
    char stringCommand[16];
    sprintf(stringCommand, "mode %d,%d", width, height);
    system(stringCommand);
}

void PrintfColor(const char* input, int color) {
    setConsoleColor(color);
    printf("%s", input);
    setConsoleColor(15); //default console color
}

// Basically what this does is print spaces for length time
void printSpaces(int length) {
    printf("%*s", length, "");
}

int StringIsEmpty(const char* string) {
    return string[0] == '\0';
}

void DeleteString(char* string) {
    string[0] = '\0';
}

void EmptyString(char* string, int size) {
    for (int i = 0 ; i < size; ++i)
        string[i] = 0;
}

// this require the string to have a NULL at the end of the element.
int sizeArrStr(const char* string[]) {
    int i = -1;
    while (string[++i] != NULL);
    return i;
}

int PlayerInput() {

    int firstInput = getch();

    if (firstInput == 224 || firstInput == 0) {
    
        switch(getch()) {
            case 'H': return UP;
            case 'K': return LEFT;
            case 'P': return DOWN;
            case 'M': return RIGHT;
            default : return UNNECESSARY_INPUT;
        }

    } else if (firstInput == '\r') { // ENTER
        return PROCEED;
    } else {
        return UNNECESSARY_INPUT;
    }
}

//PRECONDITION besar_disks pasti lebih dari 0.
void DiskToString(char* stringDisk, int current_disk, int biggest_disk) {
    
    int count = 0;
    int space = (biggest_disk - current_disk) / 2;

    for (int i = 0; i < space; ++i)
        stringDisk[count++] = ' ';

    stringDisk[count++] = '<';

    for (int i = 0; i < current_disk; ++i)
        stringDisk[count++] = '=';

    stringDisk[count++] = '>';

    for (int i = 0; i < space; ++i)
        stringDisk[count++] = ' ';

    stringDisk[count] = '\0';
}

void TowerToString(char* stringTower, int biggest_disk, char accessories) {

    int count = 0;
    int space = (biggest_disk / 2) + 1;

    for (int i = 0; i < space; ++i)
        stringTower[count++] = ' ';
    
    stringTower[count++] = accessories;

    for (int i = 0; i < space; ++i)
        stringTower[count++] = ' ';

    stringTower[count] = '\0';
}

// Use a Memo to handle repeating T(disk, tower) calculation.
int moveMemo[32][8] = {0};

// AUTHOR: CHATGPT
// Based on Frame Stewart Conjecture
int CalculateMaxMove(int disk, int tower) {

    // base cases
    if (disk == 0) return 0;
    if (disk == 1) return 1;
    if (tower == 3) return (1 << disk) - 1;     // 2^disks - 1
    if (tower < 3) return INT_MAX;              // since there's no way to solve a 1 or 2 towers in tower of hanoi with more than 1 disk
    if (disk < tower) return (2 * disk) - 1;
    if (disk == tower) return (2 * disk) + 1;

    // Check if the current calculation has already been saved into memo
    if (moveMemo[disk][tower] != 0) return moveMemo[disk][tower];

    int moves;
    int min_moves = INT_MAX;

    // T(disk, tower) = Min (1 <= i < disk) [2 * T(i, tower) + T(disk - i, tower - 1)]
    for (int i = 1; i < disk; ++i) {
        moves = 2 * CalculateMaxMove(i, tower) + CalculateMaxMove(disk - i, tower - 1);

        if (moves < min_moves) {
            min_moves = moves;
        }
    }

    // "Memorize" the result for the current disk and tower
    moveMemo[disk][tower] = min_moves; 

    return min_moves;
}

// Ini bakal nge return nilai yang ada di antara MenuItems, contoh bisa liat di main main.c
int Menu(const char* MenuHeader, const char* MenuItems[], const char* MenuFooter) {

    int ItemsCount = sizeArrStr(MenuItems);
    int input;
    int selected = 0;

    SetConsoleSize((ItemsCount + 2) * 12, (ItemsCount + 2) * 2);

    do
    {
        clear_screen();
        printf("\n\t%s", MenuHeader);
        PrintMenuItems(ItemsCount, MenuItems, selected);
        printf("\t%s", MenuFooter);

        while ((input = MenuInput(&selected, ItemsCount)) == UNNECESSARY_INPUT);    // refrain the player from making unnecessary input
        
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


int MenuInput(int *selected, int ItemsCount) {
    
    switch (PlayerInput()) {
    case UP:

        if (CursorIsAtTop(*selected)) return UNNECESSARY_INPUT;
        MoveMenuCursor(&(*selected), UP);

        break;
    case DOWN:

        if (CursorIsAtBottom(*selected, ItemsCount)) return UNNECESSARY_INPUT;
        MoveMenuCursor(&(*selected), DOWN);

        break;
    case PROCEED: 
        return *selected;

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
