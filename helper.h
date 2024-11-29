#ifndef helper_h
#define helper_h

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3
#define PROCEED 4
#define UNNECESSARY_INPUT -1

void setConsoleColor(int color);
void SetConsoleSize(int width, int height);
void clear_screen();

void PrintfColor(const char* input, int color);

int StringIsEmpty(const char* string);
void DeleteString(char* string);

int PlayerInput();
/*
    return the following
    0 : UP_ARROW_KEY (UP)
    1 : LEFT_ARROW_KEY (LEFT)
    2 : DOWN_ARROW_KEY (DOWN)
    3 : RIGHT_ARROW_KEY (RIGHT)
    4 : Proceed, Interact

    more keybind can be easily added
*/

void DiskToString(char* disks, int current_disk, int biggest_disk);
/*
    Convert Disk length to String, e.g:
    besar_disk = 5     biggest_disk = 7
    
    disks has (biggest_disk + 2) elements of chars
    so disks now has 9 elements of chars

    input (biggest_disk - current_disk)/2, or 1 space
    " "

    input '<'
    " <"
    
    input (current_disk), or 5 '='
    " <====="

    input '>'
    " <=====>"

    input 1 space
    " <=====> "

    and add null terminator since c always acts funny

    return all those strings to disks
*/

void TowerToString(char* disks, int biggest_disk, char accessories);
/*
    same as above except
    e.g: biggest_disk = 7

    input biggest_disk / 2 spaces (3)
    "   "

    input '|' or ACCESSORIES (bisa dipakai buat petunjuk, atau A B C, dll)
    "   |"

    input 3 spaces
    "   |   "

    return those strings to disks
*/

#endif