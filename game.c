// BASIC IMPLEMENTATION, NO GAMEPLAY
// TODO: GAME LOGIC, USER INTERACTION, PROPER CODE COMMENTS, REFACTOR (MAYBE)

#include <stdio.h>
#include <stdlib.h>

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
        tower->disks[++(tower->top)] = disk;    // tower.top = disk, tower.top++
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
void printTower(Tower towers[3]) {
    for (int i = MAX_DISKS - 1; i >= 0; i--) {
        for (int j = 0; j < 3; j++) {
            if (i <= towers[j].top)
                printf("%d     ", towers[j].disks[i]);      // print number with spaces instead of number without spaces
            else
                printf("      ");                           // handling empty disks
        }
        printf("\n");
    }
    printf("███  ███  ███\n"); // tower base
    printf("A     B     C\n");
}

int main() { //placeholder main function
    Tower towers[3];
    for (int i = 0; i < 3; i++) {
        initializeTower(&towers[i]);
    }
    
    // Initialize the starting tower with disks
    for (int i = MAX_DISKS; i >= 1; i--) {
        push(&towers[0], i); // Put all disks onto the first tower
    }

    printTower(towers);

    return 0;
}