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

#define MOVE_CURSOR -4

// Main Menu Modules
int Menu();
void printMenu(char Menu[]);
int MenuInput(int *selected, char Menu[]);
void MoveMenuCursor(char Menu[], int *selected, int UpOrDown);

// Cases
int CursorIsAtTop(int cursor);
int CursorIsAtBottom(int cursor);
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

    char Menu[5] = {'\0'};

    int result;
    int selected = 0;
    Menu[selected] = '>';

    SetConsoleSize(64, 12);

    do
    {
        clear_screen();
        printMenu(Menu);

        while ((result = MenuInput(&selected, Menu)) == UNNECESSARY_INPUT);    // refrain the player from making unnecessary input
        
        if (result != MOVE_CURSOR) return result;
        
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

int MenuInput(int *selected, char Menu[]) {
    
    switch (PlayerInput()) {
    case UP:

        if (CursorIsAtTop(*selected)) return UNNECESSARY_INPUT;
        MoveMenuCursor(Menu, &(*selected), -1);

        break;
    case DOWN:

        if (CursorIsAtBottom(*selected)) return UNNECESSARY_INPUT;
        MoveMenuCursor(Menu, &(*selected), 1);

        break;
    case PROCEED: 
        return *selected;

    default: return UNNECESSARY_INPUT;     // this means that player are making unnecessary input
    }

    return MOVE_CURSOR;  // this means that player actually presses up / down
}

// Up = -1, Down = 1
void MoveMenuCursor(char Menu[], int *selected, int UpOrDown) {

    Menu[*selected] = '\0';
    *selected += UpOrDown;
    Menu[*selected] = '>';

}

int CursorIsAtTop(int cursor) {
    return cursor == 0;
}

int CursorIsAtBottom(int cursor) {
    return cursor == 4;
}

void NewGame() {
    PlayerData player;

    if (load(&player) == 1) {
        printf("\nYou have an ongoing Progress. Do you want to proceed? [Y/N]: ");
        
        switch(toupper(getche())) {
            case 'Y': break;
            default : return;
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
        printf("\nYou do not have any recent progress. Please start a new game");
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