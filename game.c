// BASIC IMPLEMENTATION, NO GAMEPLAY
// TODO: GAME LOGIC, USER INTERACTION, PROPER CODE COMMENTS, REFACTOR (MAYBE)

#include "helper.h"
#include "tower.h"
#include "player.h"

#include <string.h>
#include <windows.h>
#include <stdio.h>

// try changing MAX_DISKS to other numbers and run the file
// #define MAX_DISKS 9

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
void printTower(Tower towers[], int biggest_disk, char* disk, char* empty_disk) {
    
    int current_disk;

    for (int i = MAX_DISKS - 1; i >= 0; i--) {
        for (int j = 0; j < MAX_TOWERS; j++) {
            if (i <= towers[j].top) {

                current_disk = towers[j].disks[i];                  // temporarily put disk into a variable to avoid issues with iterator 'j'
                DiskToString(disk, current_disk, biggest_disk); // harus pake variable dan gabisa di masukin langsung towers[j].disks[i] nya, nanti nge bug

                printf("%s ", disk);

            } else 
                printf("%s ", empty_disk);                        // handling empty disks
        }
        printf("\n");
    }
}

// Module to print Cursor
void printCursor(int current_pos, int lenArray, char accessories) {

    int empty_length = (lenArray * current_pos) + (lenArray / 2) - 1;
    for (int i = 0; i < empty_length; i++) {
        printf(" ");
    }

    printf("%c\n", accessories);
}

// Module to Print Hand
void printHand(int currentPos, int hand, int lenArray, int biggest_disk) {

    if (hand <= 0) {
        printf("\n");
        return;
    }

    int len = (lenArray * currentPos);
    for (int i = 0 ; i < len; ++i) 
        printf(" ");
    
    char stringHand[lenArray];
    DiskToString(stringHand, hand, biggest_disk);
    printf("%s\n", stringHand);
}

void printUI(int moves, int max_moves, char* message) {
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
            if (TowerIsEmpty(tower->top)) {
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
            if ((!TowerIsEmpty(tower->top) && HandIsBiggerThanTower(*hand, *tower))) {
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
int inGame(PlayerData *player) {

    int biggest_disk = (MAX_DISKS * 2) - 1;
    int lenArray = biggest_disk + 3;

    char stringDisk[lenArray], stringEmpty[lenArray];
    char msg[128];

    TowerToString(stringEmpty, biggest_disk, '|');

    do
    {
        system("cls");
        printCursor(player->currentPosition, lenArray, 'V');
        printHand(player->currentPosition, player->hand, lenArray, biggest_disk);
        printTower(player->tower, biggest_disk, stringDisk, stringEmpty);  
        printUI(player->moves, player->max_moves, msg);

        if (HasWon(player->tower)) return 1;                                // print the last position before winning
        if (HasRanOutOfMoves(player->moves, player->max_moves)) return -1;  // print the last position before taking the L

        while (EventDetection(&(player->tower[player->currentPosition]), &player->hand, &player->currentPosition, &player->moves, msg) == -1); //reefrain the player from spamming or making unnecessary input
        save(*player);      // autosave, performance is very awful now.

    } while (1);
}

void initializePlayer (PlayerData *player) { //placeholder
    
    while (1) {
        scanf("%d %d", &player->max_disks, &player->max_towers);
        if (player->max_disks <= 16 && player->max_towers <= 6) break;
    }

    player->hand = 0;
    player->moves = 0;
    player->currentPosition = 0;
    player->max_moves = 256;

    for (int i = 0; i < player->max_towers; ++i) 
        initializeTower(&player->tower[i]);
    

    for (int i = (MAX_DISKS * 2) - 1; i >= 1; i-=2 ) 
        push(&player->tower[0], i, MAX_DISKS);

}

int main() { // placeholder no.2 bruh

    PlayerData player;

    //initializePlayer(&player);
    load(&player);              // kalo pertama kali main pake initializeplayer dulu

    MAX_DISKS = player.max_disks;
    MAX_TOWERS = player.max_towers;

    if (inGame(&player) == 1) {
        printf("\nYou Won!\n");
    } else {
        printf("\nYou Lose!\n");
    }


}

// int main() { //placeholder main function

//     while (1){
//         scanf("%d %d", &MAX_DISKS, &MAX_TOWERS);
//         if (MAX_DISKS <= 16 && MAX_TOWERS <= 6) break; // Validate input (a 1920x1080 laptop display can fit about 6 towers max in fullscreen)
//     }

//     int biggest_disk = (MAX_DISKS * 2) - 1;
//     int lenArray = biggest_disk + 3;

//     Tower towers[MAX_TOWERS];
//     for (int i = 0; i < MAX_TOWERS; i++) {
//         initializeTower(&towers[i]);
//     }
    
//     // Initialize the starting tower with biggest_disk, odd number only
//     for (int i = biggest_disk; i >= 1; i -= 2) {
//         push(&towers[0], i, MAX_DISKS); // Put all disks onto the first tower
//     }

//     char stringDisk[lenArray], stringEmpty[lenArray];

//     TowerToString(stringEmpty, biggest_disk, '|');   // put this here instead of them being put inside printTower for performance concern
    
//     int currentPosition = 0,hand = 0, moves = 0;

//     char msg[100] = {'\0'};

//     int max_moves = 50; //place holder max moves

//     do
//     {
//         system("cls");
//         printCursor(currentPosition, lenArray, 'V');
//         printHand(currentPosition, hand, lenArray, biggest_disk);
//         printTower(towers, biggest_disk, stringDisk, stringEmpty);  
//         printUI(moves, max_moves, msg);

//         if (HasWon(towers)) return 1;                      // print the last position before winning
//         if (HasRanOutOfMoves(moves, max_moves)) return 0;  // print the last position before taking the L

//         while (EventDetection(&towers[currentPosition], &hand, &currentPosition, &moves, msg) == -1); //reefrain the player from spamming or making unnecessary input

//     } while (1);
    
//     return 0;
// }   