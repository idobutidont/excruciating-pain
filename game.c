// BASIC IMPLEMENTATION, NO GAMEPLAY
// TODO: GAME LOGIC, USER INTERACTION, PROPER CODE COMMENTS, REFACTOR (MAYBE)

#include "helper.c"

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
int TowerisFull(Tower* tower) {
    return tower->top == MAX_DISKS - 1;
}

int TowerisEmpty(Tower* tower) {
    return tower->top == -1;
}

int DiskcanMove(int fromDisk, int toDisk) {
    return toDisk == -1 || fromDisk < toDisk;
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

// Function to move disks
void moveDisk(Tower* from, Tower* to) {
    if (!TowerisEmpty(from)) {
        int disk = pop(from);
        if (DiskcanMove(disk, to->top >= 0 ? to->disks[to->top] : -1)) {
            push(to, disk);
        } else {
            push(from, disk); // Return the disc if the disk can't be moved (TheManWhoCan'tBeMoved.flac)
        }
    }
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
void printCursor(int current_pos, int lenArray) {

    int empty_length = (lenArray * current_pos) + (lenArray / 2) - 1;
    for (int i = 0; i < empty_length; i++) {
        printf(" ");
    }

    printf("%c\n", 'V');
}

// TODO: switch from constant to variable for MAX_DISKS.
int main() { //placeholder main function

    while (1){
        scanf("%d %d", &MAX_DISKS, &MAX_TOWERS);
        if (MAX_DISKS <= 16 && MAX_TOWERS <= 6) break; // Validate input (a 1920x1080 laptop display can fit about 6 towers max in fullscreen)
    }

    int biggest_disk = (MAX_DISKS * 2) - 1;     // 5 -> 9
    int lenArray = biggest_disk + 3;            // 5 -> 12 (9, + 2 for '<' and '>', + 1 for '\0')

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

    // VERY RAW GAMEPLAY
    // TODO: LOGIC HANDLING, and pretty much everything
    do
    {
        system("cls");
        printCursor(currentPosition, lenArray);
        printf("\n");
        printTower(towers, biggest_disk, stringDisk, stringEmpty);     

        switch (PlayerInput()) {
            case 0: hand = currentPosition; break;
            case 1: --currentPosition; break;
            case 2: moveDisk(&towers[hand], &towers[currentPosition]); hand = 0; break;
            case 3: ++currentPosition; break;
            default : break;
        }

        if (currentPosition < 0) {
            ++currentPosition;
        } else if (currentPosition > MAX_TOWERS - 1) 
            --currentPosition;

    } while (1);
    
    return 0;
}