/***************************************************************
* FILENAME: game.c
* DESCRIPTION: 
* AUTHOR: 
* DATE: 
****************************************************************/

// TODO: GAME LOGIC, USER INTERACTION, PROPER CODE COMMENTS, REFACTOR (MAYBE)

#include "helper.h"
#include "game.h"

#include <string.h>
#include <stdio.h>

#define INT_MAX 2147483647

int MAX_DISKS, MAX_TOWERS;

// Cases
int HandIsEmpty(int hand) {
    return hand <= 0;
}

int HandIsBiggerThanTower(int hand, Tower tower) {
    return hand >= tower.disks[tower.top];
}

int HasDiskStacked(Tower tower[], int start_pos) {

    for (int i = 0; i < MAX_TOWERS; ++i) 
        if (i != start_pos && tower[i].top == MAX_DISKS - 1) return 1;
    
    return 0;
}

int HasWon(PlayerData *player) {
    return HasDiskStacked(player->tower, player->startTower);
}

int HasLose(PlayerData *player) {
    return HasRanOutOfMoves(player->moves, player->max_moves);
}

int HasRanOutOfMoves(int moves, int max_moves) {
    return (moves + 1) > max_moves;
}

int HandAtRightEdge(int hand_position) {
    return hand_position == MAX_TOWERS - 1;
}

int HandAtLeftEdge(int hand_position) {
    return hand_position == 0;
}   

int MoveIsValid(int move) {
    switch(move) {
        case DISK_PUT_DOWN: return 1;
        case DISK_PICK_UP: return 1;
        case CURSOR_MOVE: return 1;
        default: return 0;
    }
}

int PlayerPutDownDisk(int input) {
    return input == DISK_PUT_DOWN;
}
// End of cases

// Prints
// Module to print the towers
void printTower(Tower towers[]) {
    
    // use a combined string for batching print, faster compared to (tower * disk) amount of prints
    char stringDiskTower[4096] = "";

    int current_disk;
    int biggest_disk = 2 * MAX_DISKS - 1;
    int diskStringLength = biggest_disk + 2;

    char stringDisk[diskStringLength], stringTower[diskStringLength];

    TowerToString(stringTower, biggest_disk, '|');

    for (int height = MAX_DISKS - 1; height >= 0; --height) {
        for (int tower = 0; tower < MAX_TOWERS; ++tower) {
            if (height <= towers[tower].top) {                          // check if there's a disk on the tower, done by checking if the top is higher than current height level

                current_disk = towers[tower].disks[height];             // temporarily put disk into a variable to avoid issues with iterator
                DiskToString(stringDisk, current_disk, biggest_disk);

                strcat(stringDiskTower, stringDisk);                    // concatenate (tambahin string) stringDisk onto stringDiskTower

            } else {
                strcat(stringDiskTower, stringTower);                   // concatenate stringTower onto stringDiskTower
            }
        }
        strcat(stringDiskTower, "\n");
    }

    printf("%s", stringDiskTower);
}

// Module to print Cursor
void printCursor(int hand_position) {

    int biggest_disk = 2 * MAX_DISKS - 1;
    int diskStringLength = biggest_disk + 2;

    char stringCursor[diskStringLength];    
    TowerToString(stringCursor, biggest_disk, 'V');

    printSpaces(diskStringLength * hand_position);
    printf("%s\n", stringCursor);
}

// Module to Print Hand
void printHand(int hand_position, int hand) {

    if (HandIsEmpty(hand)) {
        printf("\n");
        return;
    }

    int biggest_disk = 2 * MAX_DISKS - 1;
    int diskStringLength = biggest_disk + 2;

    char stringHand[diskStringLength];
    DiskToString(stringHand, hand, biggest_disk);

    printSpaces(diskStringLength * hand_position);
    printf("%s\n", stringHand);
}

void printUI(int moves, int max_moves, int input) {

    printf("\nMoves: %d", moves);
    printf("\tMoves Left: %d", (max_moves-moves));

    printWrongMove(input);
}

void printWrongMove(int input) {
    switch(input) {
    case WM_DISK_AT_HAND: 
        PrintfColor("\nYou already got disk on your hand.", 12);
        break;

    case WM_TOWER_IS_EMPTY: 
        PrintfColor("\nThere's no disk there.", 12);
        break;

    case WM_HAND_IS_EMPTY: 
        PrintfColor("\nYour hand is empty.", 12);
        break;

    case WM_HAND_IS_BIGGER_THAN_TOWER: 
        PrintfColor("\nThe disk on your hand is bigger than the one on the tower.", 12);
        break;

    }
}
// end of Prints

// Gameplay Modules
int MoveCursor(int LeftOrRight, int *hand_position) {

    if (LeftOrRight == LEFT) {
        if (HandAtLeftEdge(*hand_position)) return UNNECESSARY_INPUT;
        --(*hand_position);
    }
    
    if (LeftOrRight == RIGHT) {
        if (HandAtRightEdge(*hand_position)) return UNNECESSARY_INPUT;
        ++(*hand_position);
    }

    return CURSOR_MOVE;
}

int PickUpDisk(Tower *tower, int *hand) {

    if (!HandIsEmpty(*hand)) {
        return WM_DISK_AT_HAND;
    }
    if (TowerIsEmpty(*tower)) {
        return WM_TOWER_IS_EMPTY;
    }

    *hand = pop(&(*tower));
    return DISK_PICK_UP;
}

int PutDownDisk(Tower *tower, int *hand) {

    if (HandIsEmpty(*hand)) {
        return WM_HAND_IS_EMPTY;
    }
    if ((!TowerIsEmpty(*tower) && HandIsBiggerThanTower(*hand, *tower))) {
        return WM_HAND_IS_BIGGER_THAN_TOWER;
    }

    push(&(*tower), *hand);
    *hand = 0;

    return DISK_PUT_DOWN;
}

void IncrementMove(int *moves) {
    ++(*moves);
}
// End Gameplay

// Player Input Events. POP, PUSH, disk movement
int PlayerEvent(PlayerData *player) {

    switch (PlayerInput()) {

    case UP:
        return PickUpDisk(&player->tower[player->handPosition], &player->hand);
        
    case DOWN:
        return PutDownDisk(&player->tower[player->handPosition], &player->hand);

    case LEFT:
        return MoveCursor(LEFT, &player->handPosition); 

    case RIGHT:
        return MoveCursor(RIGHT, &player->handPosition);

    default :
        return UNNECESSARY_INPUT;
        
    }
}

// return WON if won, LOSE if lose
// TODO: MORE REFACTOR.
int inGame(PlayerData *player) {

    MAX_DISKS = player->max_disks;
    MAX_TOWERS = player->max_towers;

    // biggest_disk + '<' + '>'
    int diskStringLength = 2 * MAX_DISKS + 1;
    int input = 0;

    SetConsoleSize(diskStringLength * MAX_TOWERS, player->max_disks + 6);

    do
    {
        clear_screen();
        printCursor(player->handPosition);
        printHand(player->handPosition, player->hand);
        printTower(player->tower);  
        printUI(player->moves, player->max_moves, input);

        if (MoveIsValid(input)) save(&*player);        // autosave, performance is very awful now.

        if (HasWon(&*player)) return WON;               // print the last position before winning
        if (HasLose(&*player)) return LOSE;             // print the last position before taking the L

        //refrain the player from spamming or making unnecessary input
        while ((input = PlayerEvent(&*player)) == UNNECESSARY_INPUT);

        if (PlayerPutDownDisk(input)) IncrementMove(&player->moves);

    } while (1);
}

void initializePlayer (PlayerData *player) { //placeholder

    DiffSelect(player);

    player->startTower = 0;
    player->hand = 0;
    player->moves = 0;
    player->handPosition = 0;
    player->max_moves = CalculateMaxMove(player->max_disks, player->max_towers);

    for (int i = 0; i < player->max_towers; ++i) 
        initializeTower(&player->tower[i]);
    
    // Initialize Disk onto starting Tower
    for (int i = (player->max_disks * 2) - 1; i >= 1; i -= 2) 
        push(&player->tower[player->startTower], i);

}

void DiffSelect(PlayerData *player) {
    const char* MenuHeader =    "Select Difficulty\n";
    const char* MenuItems[] = {
                                "Very Hard\n",
                                "Hard\n",
                                "Medium\n",
                                "Easy\n\n", NULL
    };
    const char* MenuFooter =    "Press Enter to Start...\n";

    switch(Menu(MenuHeader, MenuItems, MenuFooter)){
        case 0: player->max_disks = 16; player->max_towers = 3; break;
        case 1: player->max_disks = 16; player->max_towers = 4; break;
        case 2: player->max_disks = 7; player->max_towers = 3; break;
        case 3: player->max_disks = 5; player->max_towers = 3; break;
    }
}