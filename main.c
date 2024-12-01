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

    const char* MenuHeader =    "Tower Of Hanoi\n";
    const char* MenuItems[] = {
                                "New Game\n",
                                "Continue\n",
                                "View Scores\n",
                                "Tutorial\n\n",

                                "Exit\n\n"
    };
    const char* MenuFooter =    "Press Enter to Continue...\n";
    int ItemsCount = 5;

    do
    {
        switch(Menu(ItemsCount, MenuItems, MenuHeader, MenuFooter)) {
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