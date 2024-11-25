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
// End of cases

// Function to print the towers
// added biggest_disk, string for empty disk and non-empty disk for repetitive print handling
void printTower(char* stringDisk, const char* stringTower, Tower towers[], int biggest_disk) {
    
    int current_disk;

    for (int i = MAX_DISKS - 1; i >= 0; i--) {
        for (int j = 0; j < MAX_TOWERS; j++) {
            if (i <= towers[j].top) {

                current_disk = towers[j].disks[i];                      // temporarily put disk into a variable to avoid issues with iterator 'j'
                DiskToString(stringDisk, current_disk, biggest_disk);   // harus pake variable dan gabisa di masukin langsung towers[j].disks[i] nya, nanti nge bug

                printf("%s ", stringDisk);

            } else 
                printf("%s ", stringTower);                        // handling empty disks
        }
        printf("\n");
    }
}

// Basically what this does is print spaces until before our actual current position.
void printSpaces(int lenArray, int current_pos) {
    printf("%*s", (lenArray * current_pos), "");
}

// Module to print Cursor
void printCursor(const char* stringCursor, int current_pos, int lenArray) {

    printSpaces(lenArray, current_pos);

    printf("%s\n", stringCursor);
}

// Module to Print Hand
void printHand(char* stringHand, int currentPos, int hand, int lenArray, int biggest_disk) {

    if (HandIsEmpty(hand)) {
        printf("\n");
        return;
    }

    printSpaces(lenArray, currentPos);
    
    DiskToString(stringHand, hand, biggest_disk);

    printf("%s\n", stringHand);
}

void printUI(int moves, int max_moves, const char* message) {
    printf("Moves: %d\n", moves);
    printf("Moves Left: %d\n", (max_moves-moves));
    PrintfColor(message, 12);
}


int EventDetection(Tower *tower, int *hand, int *current_pos, int *moves, char* message) {

    switch (PlayerInput()) {

        case 0: // UP (POP) Pick up disk to hand
            if (!HandIsEmpty(*hand)) {
                strcpy(message, "You already got disk on your hand big guy.\0");
                return 1;
            }
            if (TowerIsEmpty(*tower)) {
                strcpy(message, "There's no disk there.\0");
                return 1;
            }

            *hand = pop(&(*tower)); 
            break;

        case 1: // LEFT
            if (*current_pos == 0) return -1;
            --*(current_pos); 
            break;
            
        case 2: // DOWN (PUSH) Put down disk from hand

            if (HandIsEmpty(*hand)) {
                strcpy(message, "Your hand is empty big guy.\0");
                return 1;
            }
            if ((!TowerIsEmpty(*tower) && HandIsBiggerThanTower(*hand, *tower))) {
                strcpy(message, "The disk on your hand is bigger than the one on the tower.\0"); 
                return 1;
            }

            ++*(moves);
            push(&*tower, *hand, MAX_DISKS);
            *hand = 0; 
            break;

        case 3: // RIGHT
            if (*current_pos == MAX_TOWERS - 1) return -1;
            ++*(current_pos); 
            break;

        default : 
            return -1;
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
    int lenArray = biggest_disk + 3;

    char stringDisk[lenArray], stringTower[lenArray], stringCursor[lenArray], stringHand[lenArray];
    char msg[128] = {'\0'};

    TowerToString(stringCursor, biggest_disk, 'V');
    TowerToString(stringTower, biggest_disk, '|');

    do
    {
        system("cls");
        printCursor(stringCursor, player->currentPosition, lenArray);
        printHand(stringHand, player->currentPosition, player->hand, lenArray, biggest_disk);
        printTower(stringDisk, stringTower, player->tower, biggest_disk);  
        printUI(player->moves, player->max_moves, msg);

        save(*player);      // autosave, performance is very awful now.

        if (HasWon(player->tower)) return 1;                                // print the last position before winning
        if (HasRanOutOfMoves(player->moves, player->max_moves)) return -1;  // print the last position before taking the L

        while (EventDetection(&(player->tower[player->currentPosition]), &player->hand, &player->currentPosition, &player->moves, msg) == -1); //refrain the player from spamming or making unnecessary input

    } while (1);
}

void initializePlayer (PlayerData *player) { //placeholder
    
    while (1) {
        scanf("%d %d", &player->max_disks, &player->max_towers);
        if (player->max_disks <= 16 && player->max_disks >=5 && player->max_towers <= 6 && player->max_towers >= 3) break;
    }

    player->hand = 0;
    player->moves = 0;
    player->currentPosition = 0;
    player->max_moves = 256;

    for (int i = 0; i < player->max_towers; ++i) 
        initializeTower(&player->tower[i]);
    

    for (int i = (player->max_disks * 2) - 1; i >= 1; i-= 2) 
        push(&player->tower[0], i, player->max_disks);

}