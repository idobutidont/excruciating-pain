
#include "helper.h"

#include <conio.h>
#include <windows.h>
#include <stdio.h>

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)color);
}

void PrintfColor(char* input, int color) {
    setConsoleColor(color);
    printf("%s", input);
    setConsoleColor(15); //bright white supposedly
}

int PlayerInput() {

    int firstInput = getch();

    if (firstInput == 224 || firstInput == 0) {
    
        switch(getch()) {
            case 'H': return 0; // UP
            case 'K': return 1; // LEFT
            case 'P': return 2; // DOWN
            case 'M': return 3; // RIGHT
            default : return -1;
        }

    } else if (firstInput == '\r') { // ENTER
        return 4; // Proceed, Interact
    } else {
        return -1;
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

    //handling empty string.
    if (accessories == ' ')  {
        for (int i = biggest_disk + 2; i >= 0; --i) {
            disks[i] = ' ';
        }
        return;
    }

    int count = 0;
    int space = (biggest_disk / 2) + 1;

    for (int i = 0; i < space; ++i)
        disks[count++] = ' ';
    
    disks[count++] = accessories;

    for (int i = 0; i < space; ++i)
        disks[count++] = ' ';

    disks[count] = '\0';

}