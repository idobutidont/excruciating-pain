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
#include <windows.h>
#include <stdio.h>


int MAX_DISKS, MAX_TOWERS;

// Cases
int HandIsEmpty(int hand) {
    return hand <= 0;
}

int HandIsBiggerThanTower(int hand, Tower tower) {
    return hand > tower.disks[tower.top];
}

int HasWon(Tower tower[]) {

    for (int i = 1; i < MAX_TOWERS; ++i) 
        if (tower[i].top == MAX_DISKS - 1) return 1;
    
    return 0;
}

int HasRanOutOfMoves(int moves, int max_moves) {
    return (moves + 1) > max_moves;
}

int HandAtRight(int hand) {
    return hand == MAX_TOWERS - 1;
}

int HandAtLeft(int hand) {
    return hand == 0;
}
// End of cases

// Prints
// Module to print the towers
void printTower(char* stringDisk, const char* stringTower, Tower towers[], int biggest_disk) {
    
    // use a combined string for batching print, much faster compared to (tower * disk) amount of prints
    char stringDiskTower[4096] = "";
    int current_disk;

    for (int i = MAX_DISKS - 1; i >= 0; i--) {
        for (int j = 0; j < MAX_TOWERS; j++) {
            if (i <= towers[j].top) {                                   // Check if disk were available on tower 'j', done by tracking if the top of tower 'j' is above disk at level 'i'

                current_disk = towers[j].disks[i];                      // temporarily put disk into a variable to avoid issues with iterator 'j'
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
void printSpaces(int lenArray, int hand_position) {
    printf("%*s", (lenArray * hand_position), "");
}

// Module to print Cursor
void printCursor(const char* stringCursor, int hand_position, int lenArray) {
    printSpaces(lenArray, hand_position);
    printf("%s\n", stringCursor);
}

// Module to Print Hand
void printHand(char* stringHand, int hand_position, int hand, int lenArray, int biggest_disk) {

    if (HandIsEmpty(hand)) {
        printf("\n");
        return;
    }

    printSpaces(lenArray, hand_position);
    DiskToString(stringHand, hand, biggest_disk);
    printf("%s\n", stringHand);
}

void printUI(int moves, int max_moves, const char* message) {

    printf("\nMoves: %d", moves);
    printf("\tMoves Left: %d", (max_moves-moves));

    // Changing console color reduces performance by alot
    // so we need to check if the string is empty to increase performance on non-wrong move
    if (!StringIsEmpty(message)) 
        PrintfColor(message, 12);
}
// end of Prints

// Use a Memo to significantly reduce calculation time
int moveMemo[32][8] = {0};

// AUTHOR: CHATGPT
// Based on Frame Stewart Conjecture
// T(disk, tower) = Min (1 <= i < disk) [2 * T(i, tower) + T(disk - i, tower - 1)]
int CalculateMaxMove(int disk, int tower) {
    // Base cases
    if (disk == 0) return 0;  // No moves needed for 0 disks
    if (disk == 1) return 1;  // Only 1 move needed for 1 disk

    // If exactly 3 towers, we can use the optimal formula
    if (tower == 3) {
        // Using bit shifting to calculate 2^disks - 1 (equivalent to pow(2, disks) - 1)
        return (1 << disk) - 1;  // 2^disks - 1
    }

    // Check if the current iteration has already been saved into memo
    if (moveMemo[disk][tower] != 0) {
        return moveMemo[disk][tower];   // if it does exist, then early return
    }

    // If we have more than 3 towers, try different splits
    if (tower > 3) {
        int min_moves = INT_MAX;  // Initialize to maximum value
        // Try splitting the disks into two parts
        for (int i = 1; i < disk; ++i) {
            // Calculate the total moves for this split, memoize recursively
            int moves = 2 * CalculateMaxMove(i, tower) + CalculateMaxMove(disk - i, tower - 1);

            // Track the minimum moves
            if (moves < min_moves) {
                min_moves = moves;
            }
        }

        // "Memorize" the result for the current disk and tower
        moveMemo[disk][tower] = min_moves;
        return min_moves;  
    }

    return INT_MAX;  // If towers <= 3 and disks > 1, fallback (invalid case)
}

// Gameplay Modules
int MoveCursor(int LeftOrRight, int *hand_position) {

    if (LeftOrRight == LEFT) {
        if (HandAtLeft(*hand_position)) return UNNECESSARY_INPUT;
        --(*hand_position);
    } else {
        if (HandAtRight(*hand_position)) return UNNECESSARY_INPUT;
        ++(*hand_position);
    }

    return 1;
}

int PickUpDisk(Tower *tower, int *hand, char* message) {

    if (!HandIsEmpty(*hand)) {
        strcpy(message, "\nYou already got disk on your hand.\0");
        return WRONG_MOVE;
    }
    if (TowerIsEmpty(*tower)) {
        strcpy(message, "\nThere's no disk there.\0");
        return WRONG_MOVE;
    }

    *hand = pop(&(*tower));
    return 1;
}

int PutDownDisk(Tower *tower, int *hand, char* message) {

    if (HandIsEmpty(*hand)) {
        strcpy(message, "\nYour hand is empty.\0");
        return WRONG_MOVE;
    }
    if ((!TowerIsEmpty(*tower) && HandIsBiggerThanTower(*hand, *tower))) {
        strcpy(message, "\nThe disk on your hand is bigger than the one on the tower.\0"); 
        return WRONG_MOVE;
    }

    push(&(*tower), *hand, MAX_DISKS);
    *hand = 0; 

    return 1;
}

void IncrementMove(int *moves) {
    ++(*moves);
}
// End Gameplay

// Player Input Events. POP, PUSH, disk movement
int EventDetection(Tower *tower, int *hand, int *hand_position, int *moves, char* message) {

    switch (PlayerInput()) {

        case UP: // UP (POP) Pick up disk to hand
            if (PickUpDisk(&(*tower), &(*hand), message) == WRONG_MOVE) return WRONG_MOVE;
            break;
            
        case DOWN: // DOWN (PUSH) Put down disk from hand
            if (PutDownDisk(&(*tower), &(*hand), message) == WRONG_MOVE) return WRONG_MOVE;
            
            IncrementMove(&(*moves));
            break;

        case LEFT: // LEFT
            if (MoveCursor(LEFT, &(*hand_position)) == UNNECESSARY_INPUT) return UNNECESSARY_INPUT;
            break;

        case RIGHT: // RIGHT
            if (MoveCursor(RIGHT, &(*hand_position)) == UNNECESSARY_INPUT) return UNNECESSARY_INPUT;
            break;

        default :
            return UNNECESSARY_INPUT;
    }

    strcpy(message, "\0");

    return 1;
}

// return 1 if won, -1 otherwise
// TODO: MORE REFACTOR.
int inGame(PlayerData *player) {

    MAX_DISKS = player->max_disks;
    MAX_TOWERS = player->max_towers;

    int biggest_disk = (MAX_DISKS * 2) - 1;

    // biggest_disk + '<' + '>'
    int lenArray = biggest_disk + 2;

    int input = 0;

    char stringDisk[lenArray], stringTower[lenArray], stringCursor[lenArray], stringHand[lenArray];
    char msg[64] = {'\0'};

    TowerToString(stringCursor, biggest_disk, 'V');
    TowerToString(stringTower, biggest_disk, '|');

    SetConsoleSize(lenArray * MAX_TOWERS, MAX_DISKS + 6);

    do
    {
        clear_screen();
        printCursor(stringCursor, player->handPosition, lenArray);
        printHand(stringHand, player->handPosition, player->hand, lenArray, biggest_disk);
        printTower(stringDisk, stringTower, player->tower, biggest_disk);  
        printUI(player->moves, player->max_moves, msg);

        if (input != WRONG_MOVE) save(*player);                              // autosave, performance is very awful now.

        if (HasWon(player->tower)) return 1;                                // print the last position before winning
        if (HasRanOutOfMoves(player->moves, player->max_moves)) return -1;  // print the last position before taking the L

        //refrain the player from spamming or making unnecessary input
        while ((input = EventDetection(&(player->tower[player->handPosition]), &player->hand, &player->handPosition, &player->moves, msg)) == UNNECESSARY_INPUT);

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
        push(&player->tower[0], i, player->max_disks);

}