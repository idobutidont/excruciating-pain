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
    setConsoleColor(15); //bright white supposedly
}

int StringIsEmpty(const char* string) {
    return string[0] == '\0';
}

int PlayerInput() {

    int firstInput = getch();

    if (firstInput == 224 || firstInput == 0) {
    
        switch(getch()) {
            case 'H': return UP; // UP
            case 'K': return LEFT; // LEFT
            case 'P': return DOWN; // DOWN
            case 'M': return RIGHT; // RIGHT
            default : return UNNECESSARY_INPUT;
        }

    } else if (firstInput == '\r') { // ENTER
        return PROCEED; // Proceed, Interact
    } else {
        return UNNECESSARY_INPUT;
    }
}

//PRECONDITION besar_disks pasti lebih dari 0.
void DiskToString(char* disks, int current_disk, int biggest_disk) {

    int count = 0;
    int space = (biggest_disk - current_disk) / 2;

    for (int i = 0; i < space; ++i)
        disks[count++] = ' ';

    disks[count++] = '<';

    for (int i = 0; i < current_disk; ++i)
        disks[count++] = '=';

    disks[count++] = '>';

    for (int i = 0; i < space; ++i)
        disks[count++] = ' ';

    disks[count] = '\0'; 

}

void TowerToString(char* disks, int biggest_disk, char accessories) {

    int count = 0;
    int space = (biggest_disk / 2) + 1;

    for (int i = 0; i < space; ++i)
        disks[count++] = ' ';
    
    disks[count++] = accessories;

    for (int i = 0; i < space; ++i)
        disks[count++] = ' ';

    disks[count] = '\0';

}