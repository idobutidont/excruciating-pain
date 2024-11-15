// BASIC IMPLEMENTATION, NO GAMEPLAY
// TODO: GAME LOGIC, USER INTERACTION, PROPER CODE COMMENTS, REFACTOR (MAYBE)

#include "helper.h"

// try changing MAX_DISKS to other numbers and run the file
#define MAX_DISKS 5

typedef struct {
    int disks[MAX_DISKS];
    int top; // Tracks the latest or topmost disk pushed onto a tower 
} Tower;

// Function to initialize tower
void initializeTower(Tower *tower) {
    tower->top = -1; // Initialize the tower as empty
}

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
        for (int j = 0; j < 3; j++) {
            if (i <= towers[j].top) {
                //printf("%d     ", towers[j].disks[i]);            // print number with spaces instead of number without spaces

                current_disk = towers[j].disks[i];                  // temporarily put disk into a variable to avoid issues with iterator 'j'
                PutDiscsToString(disk, current_disk, biggest_disk); // harus pake variable dan gabisa di masukin langsung towers[j].disks[i] nya, nanti nge bug

                printf("%s ", disk);

            } else 
                printf("%s ", empty_disk);                        // handling empty disks
        }
        printf("\n");
    }
    // printf("███  ███  ███\n"); // tower base
    // printf("A     B     C\n");
}

// TODO: switch from constant to variable for MAX_DISKS.
int main() { //placeholder main function

    int biggest_disk = (MAX_DISKS * 2) - 1;     // 5 -> 9
    int lenArray = (MAX_DISKS * 2) + 2;         // 5 -> 12 (9, + 2 for '<' and '>', + 1 for '\0')

    Tower towers[3];
    for (int i = 0; i < 3; i++) {
        initializeTower(&towers[i]);
    }
    
    // Initialize the starting tower with biggest_disk, odd number only
    for (int i = biggest_disk; i >= 1; i -= 2) {
        push(&towers[0], i); // Put all disks onto the first tower
    }

    char stringDisk[lenArray], stringEmpty[lenArray];

    PutEmptyDiscsToString(stringEmpty, biggest_disk);   // put this here instead of them being put inside printTower for performance concern

    printTower(towers, biggest_disk, stringDisk, stringEmpty);

    return 0;
}