// BASIC IMPLEMENTATION, NO GAMEPLAY
// TODO: GAME LOGIC, USER INTERACTION, PROPER CODE COMMENTS, REFACTOR (MAYBE)

#include "helper.h"

// try changing MAX_DISKS to other numbers and run the file
// #define MAX_DISKS 9

int MAX_DISKS, MAX_TOWERS;

typedef struct {
    int disks[16];  // set the maximum amount of disks possible is 16, user can only have less than 16 disks in a single game.
    int top;        // Tracks the latest or topmost disk pushed onto a tower 
} Tower;

// Function to initialize tower
void initializeTower(Tower *tower) {
    tower->top = -1; // Initialize the tower as empty
}

// Cases

int DiskcanMove(int fromDisk, int toDisk) {
    return toDisk == -1 || fromDisk < toDisk;
}

int TowerIsEmpty(Tower tower) {
    return tower.top <= -1;
}

int HandIsEmpty(int hand) {
    return hand <= 0;
}

int HandIsBiggerThanTower(int hand, Tower tower) {
    return hand > tower.disks[tower.top];
}

// End of cases

// Function to push a disk onto a tower
void push(Tower *tower, int disk) {
    if (tower->top < MAX_DISKS - 1) {           // make sure the top isn't on the most upper slot
        tower->disks[++(tower->top)] = disk;    // tower.top++; tower.disks[tower.top] = disk;
    }
}

// Function to "pop" a disk from a tower
int pop(Tower *tower) {
    if (tower->top >= 0) {                      
        return tower->disks[(tower->top)--];    // return tower.disks[top]; top--;
    }
    return -1; // Return -1 if tower is empty
}

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

// TODO: switch from constant to variable for MAX_DISKS.
int main() { //placeholder main function

    while (1){
        scanf("%d %d", &MAX_DISKS, &MAX_TOWERS);
        if (MAX_DISKS <= 16 && MAX_TOWERS <= 6) break; // Validate input (a 1920x1080 laptop display can fit about 6 towers max in fullscreen)
    }

    int biggest_disk = (MAX_DISKS * 2) - 1;
    int lenArray = biggest_disk + 3;

    Tower towers[MAX_TOWERS];
    for (int i = 0; i < MAX_TOWERS; i++) {
        initializeTower(&towers[i]);
    }
    
    // Initialize the starting tower with biggest_disk, odd number only
    for (int i = biggest_disk; i >= 1; i -= 2) {
        push(&towers[0], i); // Put all disks onto the first tower
    }

    char stringDisk[lenArray], stringEmpty[lenArray];

    TowerToString(stringEmpty, biggest_disk, '|');   // put this here instead of them being put inside printTower for performance concern
    
    int currentPosition = 0,hand = 0;

    // TODO: print UI (Moves, Scores, Move(s) Left)
    do
    {
        system("cls");
        printCursor(currentPosition, lenArray, 'V');
        printHand(currentPosition, hand, lenArray, biggest_disk);
        printTower(towers, biggest_disk, stringDisk, stringEmpty);     

        switch (PlayerInput()) {

            case 0: // UP (POP) Pick up disk to hand
                if (!HandIsEmpty(hand) || TowerIsEmpty(towers[currentPosition]))
                    break;

                hand = pop(&towers[currentPosition]); 
                break;

            case 1: // LEFT
                if (currentPosition == 0) break;
                --currentPosition; 
                break;
                
            case 2: // DOWN (PUSH) Put down disk from hand
                if (HandIsEmpty(hand) || (!TowerIsEmpty(towers[currentPosition]) && HandIsBiggerThanTower(hand, towers[currentPosition])))
                    break;

                push(&towers[currentPosition], hand);
                hand = 0; 
                break;

            case 3: // RIGHT
                if (currentPosition == MAX_TOWERS - 1) break;
                ++currentPosition; 
                break;

            default : 
                break;
        }

    } while (1);
    
    return 0;
}