/***************************************************************
* FILENAME: main.c
* DESCRIPTION: 
* AUTHOR: 
* DATE: 
****************************************************************/

#include "helper.h"
#include "game.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

int Menu();
/*
    return 0: newGame
    return 1: Continue from last saved state
    return 2: View Score
    return 3: Setting
    return 4: exit app
*/

void printMenu(char Menu[]);

int MenuInput(int *selected, char Menu[]);

void Continue();
void NewGame();

void startGame(PlayerData player);

int main() {

    do
    {
        switch(Menu()) {
            case 0: NewGame(); break;
            case 1: Continue(); break;
            case 2: break;
            case 3: break;
            case 4: return 0;
        }

    } while (1);
    // continously playing the game until user exited.

    return 0;
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

        while ((result = MenuInput(&selected, Menu)) == -1);    // refrain the player from making unnecessary input
        
        if (result >= 0) return result;
        
    } while (1);
    
    return -1;

}

void NewGame() {
    PlayerData player;

    if (load(&player) == 1) {
        printf("\nYou have an ongoing Progress. Do you want to proceed? [Y/N]: ");
        
        switch(toupper(getchar())) {
            case 'Y': break;
            default : getchar(); return;
        }

    }

    //TODO: initialize based on difficulty, username input
    initializePlayer(&player);

    startGame(player);
    return;
}

void Continue() {

    PlayerData player;
    if (load(&player) == -1) {
        printf("\nYou do not have any recent progress. Please start a new game\n");
        getch();    // hold this screen until player input something
        return;
    }

    startGame(player);

    return;

}

void startGame(PlayerData player) {
    if (inGame(&player) == 1) {
        printf("You Won!");
        remove("save.dat");
        // putDataToScore(player);

    } else {
        printf("You Lose!");
        remove("save.dat");
    }

    return;
}

void printMenu(char Menu[]) {
    printf(
        "\n"
        "   Tower Of Hanoi\n"
        "   %c New Game\n"
        "   %c Continue\n"
        "   %c View Scores\n"
        "   %c Settings\n\n"
        "   %c Exit\n\n"
        "   Press Enter to Continue...",
        Menu[0], Menu[1], Menu[2], Menu[3], Menu[4]
        );
}

int MenuInput(int *selected, char Menu[]) {
    
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
    
    // ENTER
    case 4: 
        return *selected;

    default: return -1;     // this means that player are making unnecessary input
    }

    return -2;  // this means that player actually presses up / down
}