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

// Cases
int HandIsEmpty(int hand) {
    return hand <= 0;
}

int HandIsBiggerThanTower(int hand, Tower tower) {
    return hand >= tower.disks[tower.top];
}

int HasDiskStacked(Tower tower[], int MAX_DISKS, int MAX_TOWERS) {

    for (int i = 1; i < MAX_TOWERS; ++i) 
        if (tower[i].top == MAX_DISKS - 1) return 1;
    
    return 0;
}

int HasWon(PlayerData *player) {
    return HasDiskStacked(player->tower, player->max_disks, player->max_towers);
}

int HasLose(PlayerData *player) {
    return HasRanOutOfMoves(player->moves, player->max_moves);
}

int HasRanOutOfMoves(int moves, int max_moves) {
    return (moves + 1) > max_moves;
}

int HandAtRightEdge(int hand, int MAX_TOWERS) {
    return hand == MAX_TOWERS - 1;
}

int HandAtLeftEdge(int hand) {
    return hand == 0;
}

int MoveIsValid(int move) {
    switch(move) {
        case WM_DISK_AT_HAND: return 0;
        case WM_TOWER_IS_EMPTY: return 0;
        case WM_HAND_IS_EMPTY: return 0;
        case WM_HAND_IS_BIGGER_THAN_TOWER: return 0;
        case UNNECESSARY_INPUT: return 0;
        default: return 1;
    }
}
// End of cases

// Prints
// Module to print the towers
void printTower(char* stringDisk, const char* stringTower, Tower towers[], int biggest_disk, int MAX_DISKS, int MAX_TOWERS) {
    
    // use a combined string for batching print, faster compared to (tower * disk) amount of prints
    char stringDiskTower[4096] = "";
    int current_disk;

    for (int height = MAX_DISKS - 1; height >= 0; --height) {
        for (int tower = 0; tower < MAX_TOWERS; ++tower) {
            if (height <= towers[tower].top) {                          // check if there's a disk on the tower, done by checking if the top is higher than current height level

                current_disk = towers[tower].disks[height];             // temporarily put disk into a variable to avoid issues with iterator
                DiskToString(stringDisk, current_disk, biggest_disk);   // convert current_disk into a stringDisk.

                strcat(stringDiskTower, stringDisk);                    // concatenate (tambahin string) stringDisk onto stringDiskTower

            } else {
                strcat(stringDiskTower, stringTower);                   // concatenate stringTower onto stringDiskTower
            }
        }
        strcat(stringDiskTower, "\n");
    }

    printf("%s", stringDiskTower);
}

// Basically what this does is print spaces until before our actual hand position.
void printSpaces(int stringDiskLen, int hand_position) {
    printf("%*s", (stringDiskLen * hand_position), "");
}

// Module to print Cursor
void printCursor(const char* stringCursor, int hand_position, int stringDiskLen) {
    printSpaces(stringDiskLen, hand_position);
    printf("%s\n", stringCursor);
}

// Module to Print Hand
void printHand(char* stringHand, int hand_position, int hand, int stringDiskLen, int biggest_disk) {

    if (HandIsEmpty(hand)) {
        printf("\n");
        return;
    }

    printSpaces(stringDiskLen, hand_position);
    DiskToString(stringHand, hand, biggest_disk);
    printf("%s\n", stringHand);
}

void printUI(int moves, int max_moves, int input) {

    printf("\nMoves: %d", moves);
    printf("\tMoves Left: %d", (max_moves-moves));

    printWrongMove(input);
}

void printWrongMove(int move) {
    switch(move) {
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

// Gameplay Modules
int MoveCursor(int LeftOrRight, int *hand_position, int MAX_TOWERS) {

    if (LeftOrRight == LEFT) {
        if (HandAtLeftEdge(*hand_position)) return UNNECESSARY_INPUT;
        --(*hand_position);
    }
    
    if (LeftOrRight == RIGHT) {
        if (HandAtRightEdge(*hand_position, MAX_TOWERS)) return UNNECESSARY_INPUT;
        ++(*hand_position);
    }

    return 1;
}

int PickUpDisk(Tower *tower, int *hand) {

    if (!HandIsEmpty(*hand)) {
        return WM_DISK_AT_HAND;
    }
    if (TowerIsEmpty(*tower)) {
        return WM_TOWER_IS_EMPTY;
    }

    *hand = pop(&(*tower));
    return 1;
}

int PutDownDisk(Tower *tower, int *hand, int *moves) {

    if (HandIsEmpty(*hand)) {
        return WM_HAND_IS_EMPTY;
    }
    if ((!TowerIsEmpty(*tower) && HandIsBiggerThanTower(*hand, *tower))) {
        return WM_HAND_IS_BIGGER_THAN_TOWER;
    }

    push(&(*tower), *hand);
    *hand = 0;

    IncrementMove(&(*moves)); 

    return 1;
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
        return PutDownDisk(&player->tower[player->handPosition], &player->hand, &player->moves);

    case LEFT:
        return MoveCursor(LEFT, &player->handPosition, player->max_towers); 

    case RIGHT:
        return MoveCursor(RIGHT, &player->handPosition, player->max_towers);

    default :
        return UNNECESSARY_INPUT;
        
    }
}

// return WON if won, LOSE if lose
// TODO: MORE REFACTOR.
int inGame(PlayerData *player) {

    int biggest_disk = (player->max_disks * 2) - 1;

    // biggest_disk + '<' + '>'
    int stringDiskLen = biggest_disk + 2;

    int input = 0;

    char stringDisk[stringDiskLen], stringTower[stringDiskLen], stringCursor[stringDiskLen], stringHand[stringDiskLen];

    TowerToString(stringCursor, biggest_disk, 'V');
    TowerToString(stringTower, biggest_disk, '|');

    SetConsoleSize(stringDiskLen * player->max_towers, player->max_disks + 6);

    do
    {
        clear_screen();
        printCursor(stringCursor, player->handPosition, stringDiskLen);
        printHand(stringHand, player->handPosition, player->hand, stringDiskLen, biggest_disk);
        printTower(stringDisk, stringTower, player->tower, biggest_disk, player->max_disks, player->max_towers);  
        printUI(player->moves, player->max_moves, input);

        if (MoveIsValid(input)) save(&*player);        // autosave, performance is very awful now.

        if (HasWon(&*player)) return WON;               // print the last position before winning
        if (HasLose(&*player)) return LOSE;             // print the last position before taking the L

        //refrain the player from spamming or making unnecessary input
        while ((input = PlayerEvent(&*player)) == UNNECESSARY_INPUT);

    } while (1);
}

void initializePlayer (PlayerData *player) { //placeholder
    
    while (1) {
        scanf("%d %d", &player->max_disks, &player->max_towers);
        if (player->max_disks <= 16 && player->max_disks >=5 && player->max_towers <= 6 && player->max_towers >= 3) break;
    }

    player->hand = 0;
    player->moves = 0;
    player->handPosition = 0;
    player->max_moves = CalculateMaxMove(player->max_disks, player->max_towers);

    for (int i = 0; i < player->max_towers; ++i) 
        initializeTower(&player->tower[i]);
    
    // Initialize Disk onto starting Tower
    for (int i = (player->max_disks * 2) - 1; i >= 1; i -= 2) 
        push(&player->tower[0], i);

}