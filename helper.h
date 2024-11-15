#ifndef helper_h
#define helper_h

#include <conio.h>
#include <windows.h>
#include <stdio.h>

void setConsoleColor(int color);

void PrintfColor(char* input, int color);

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

void DiscToString(char* discs, int current_disc, int biggest_disc);
/*
    Convert Disc length to String, e.g:
    besar_disc = 5     biggest_disc = 7
    
    discs has (biggest_disc + 2) elements of chars
    so discs now has 9 elements of chars

    input (biggest_disc - current_disc)/2, or 1 space
    " "

    input '<'
    " <"
    
    input (current_disc), or 5 '='
    " <====="

    input '>'
    " <=====>"

    input 1 space
    " <=====> "

    and add null terminator since c always acts funny

    return all those strings to discs
*/

void TowerToString(char* discs, int biggest_disc, char accessories);
/*
    same as above except
    e.g: biggest_disc = 7

    input biggest_disc / 2 spaces (3)
    "   "

    input '|' or ACCESSORIES (bisa dipakai buat petunjuk, atau A B C, dll)
    "   |"

    input 3 spaces
    "   |   "

    return those strings to discs
*/

#endif