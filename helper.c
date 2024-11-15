#include "helper.h"

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
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

//PRECONDITION besar_discs pasti lebih dari 0.
void DiscToString(char* discs, int current_disc, int biggest_disc) {

    int count = 0;
    int space = (biggest_disc - current_disc) / 2;

    for (int i = 0; i < space; ++i)
        discs[count++] = ' ';

    discs[count++] = '<';

    for (int i = 0; i < current_disc; ++i)
        discs[count++] = '=';

    discs[count++] = '>';

    for (int i = 0; i < space; ++i)
        discs[count++] = ' ';

    discs[count] = '\0'; 

}

void TowerToString(char* discs, int biggest_disc, char accessories) {

    //handling empty string.
    if (accessories == ' ')  {
        for (int i = biggest_disc + 2; i >= 0; --i) {
            discs[i] = ' ';
        }
        return;
    }

    int count = 0;
    int space = (biggest_disc / 2) + 1;

    for (int i = 0; i < space; ++i)
        discs[count++] = ' ';
    
    discs[count++] = accessories;

    for (int i = 0; i < space; ++i)
        discs[count++] = ' ';

    discs[count] = '\0';

}