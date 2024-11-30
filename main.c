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


// Main Menu Modules
int Menu();
void printMenu(char Menu[]);
// end Main Menu

void NewGame();
void Continue();

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

    int MenuLength = 5;
    char Menu[MenuLength];

    EmptyString(Menu, MenuLength);

    int input;
    int selected = 0;
    Menu[selected] = '>';

    SetConsoleSize(64, 12);

    do
    {
        clear_screen();
        printMenu(Menu);

        while ((input = MenuInput(&selected, Menu, MenuLength)) == UNNECESSARY_INPUT);    // refrain the player from making unnecessary input
        
        if (input != MOVE_CURSOR) return input;
        
    } while (1);
    
    return -1;

}

void printMenu(char Menu[]) {
    printf(
        "\n   Tower Of Hanoi\n"
        "   %c New Game\n"
        "   %c Continue\n"
        "   %c View Scores\n"
        "   %c Tutorial\n\n"
        "   %c Exit\n\n"

        "   Press Enter to Continue...",
        Menu[0], Menu[1], Menu[2], Menu[3], Menu[4]
        );
}

void NewGame() {
    PlayerData player;

    if (load(&player) == 1) {
        printf("\nYou have an ongoing Progress. Do you want to proceed? [Y/N]: ");
        if (toupper(getche()) != 'Y') return;
    }

    initializePlayer(&player);

    startGame(player);
    return;
}

void Continue() {

    PlayerData player;
    if (load(&player) == -1) {
        printf("\nYou do not have any recent progress. Please start a new game");
        getch();    // hold this screen until player input something
        return;
    }

    startGame(player);

    return;

}

void startGame(PlayerData player) {

    switch (inGame(&player)) {

    case WON:

        printf("You Won!");

        // PutPlayerDataToScore();

        remove(SAVE_FILE);
        break;

    case LOSE:
    
        printf("You Lose!");
        remove(SAVE_FILE);
        break;

    default:
        return;
    }

    return;
}