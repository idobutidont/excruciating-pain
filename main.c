/***************************************************************
* FILENAME: main.c
* DESCRIPTION: 
* AUTHOR: 
* DATE: 
****************************************************************/

#include "helper.h"
#include <stdio.h>
#include <windows.h>
#include "player.h"

int Menu();
/*
    return 0: newGame
    return 1: Continue from last saved state
    return 2: View Score
    return 3: Setting
    return 4: exit app
*/

void printMenu(char *Menu);

int MenuInput(int *selected, char* Menu);

int maintest() {

    do
    {
        switch(Menu()) {
            case 0: break;
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: return 0;
        }

    } while (1);
    // continously playing the game until user exited.

    return 0;
}

void printMenu(char *Menu) {
    printf(
        "   Tower Of Hanoi\n"
        "   %c New Game\n"
        "   %c Continue\n"
        "   %c View Scores\n"
        "   %c Settings\n\n"
        "   %c Exit\n\n"
        "Press Enter to Continue...",
        Menu[0], Menu[1], Menu[2], Menu[3], Menu[4]
        );
}

int Menu() {

    char Menu[5] = {'\0'};

    int result;
    int selected = 0;
    Menu[selected] = '>';

    do
    {
        system("cls");
        printMenu(Menu);

        while ((result = MenuInput(&selected, Menu)) == -1);
        
        if (result >= 0) return result;
        
    } while (1);
    
    return -1;

}

int MenuInput(int *selected, char *Menu) {
    
    switch (PlayerInput()) {
    // UP
    case 0:

        if (*selected == 0) return -1;

        --(*selected);

        Menu[*selected] = '>';
        Menu[*selected + 1] = '\0';

        break;
    // DOWN
    case 2:

        if (*selected == 4) return -1;
        
        ++(*selected);

        Menu[*selected] = '>';
        Menu[*selected - 1] = '\0';
        break;
    
    case 4: 
    switch (*selected) {
        case 0: return 0;
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        case 4: return 4;
        default: return -1;
        }

    default: return -1;     // this means that player are making unnecessary input
    }

    return -2;  // this means that player actually presses up / down
}