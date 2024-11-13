// BASIC IMPLEMENTATION, NO GAMEPLAY

#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 5

typedef struct {
    int disks[MAX_DISKS];
    int top;
} Tower;

// Function to initialize a tower
void initTower(Tower *tower) {
    tower->top = -1; // Initialize the empty tower
}

// Function to push a disk onto a tower
void push(Tower *tower, int disk) {
    if (tower->top < MAX_DISKS - 1) {
        tower->disks[++(tower->top)] = disk;
    }
}

// Function to pop a disk from a tower
int pop(Tower *tower) {
    if (tower->top >= 0) {
        return tower->disks[(tower->top)--];
    }
    return -1; // Return -1 if tower is empty
}

// Function to print the towers
void printTower(Tower towers[3]) {
    for (int i = MAX_DISKS - 1; i >= 0; i--) {
        for (int j = 0; j < 3; j++) {
            if (i <= towers[j].top) {
                printf("%2d", towers[j].disks[i]);
            } else {
                printf("     "); // Messy print, the spaces are going everywhere
            }
        }
        printf("\n");
    }
    printf("███████████\n");
    printf(" A   B   C\n");
}

int main() {
    Tower towers[3];
    for (int i = 0; i < 3; i++) {
        initTower(&towers[i]);
    }
    
    // Initialize the starting tower with disks
    for (int i = MAX_DISKS; i >= 1; i--) {
        push(&towers[0], i); // Put all disks onto the first tower
    }

    printTower(towers);

    return 0;
}