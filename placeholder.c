#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int Inputs();

void NewGame();
void Continue();
void Highscores();
void Settings();

void test() {

    char Menu[5] = {'\0'};

    int selected = 0;
    Menu[selected] = '>';

    do
    {
        system("cls");
        printf(
            "   Tower Of Hanoi\n"
            "   %c New Game\n"
            "   %c Continue\n"
            "   %c Highscores\n"
            "   %c Settings\n\n"
            "   %c Exit\n\n"
            "Press Enter to Continue...",
            Menu[0], Menu[1], Menu[2], Menu[3], Menu[4]
            );

        switch (Inputs()) {
        // UP
        case 0:

            --selected;
            if (selected < 0) {
                selected++;
                break;
            }

            Menu[selected] = '>';
            Menu[selected + 1] = '\0';

            break;
        // DOWN
        case 2:

            ++selected;
            if (selected > 4) {
                selected--;
                break;
            }

            Menu[selected] = '>';
            Menu[selected - 1] = '\0';
            break;
        
        case 4: 
        switch (selected) {
            case 0: NewGame(); break;
            case 1: Continue(); break;
            case 2: Highscores(); break;
            case 3: Settings(); break;
            case 4: return;
            }

        default: break;
        }

    } while (1);
    
    return;
}

void KirimScore(int score) {

}

int Inputs(){

    char a, b;
    a = getch();

    /*
    TODO: customizable keybinding
    Ketika user menekan tombol arrow keys, yang dibaca oleh console itu ada dua huruf, yaitu
    huruf 'a' (-32) (cmd.exe) atau '\0' (0) (vsc terminal),
    dan huruf keduanya 'H' untuk ARROW_UP, 'K' untuk 'ARROW_LEFT' dst.
    */
    if (a == -32 || a == 0) {
        b = getch();
        switch(b) {
            case 'H': return 0; // UP
            case 'K': return 1; // LEFT
            case 'P': return 2; // DOWN
            case 'M': return 3; // RIGHT
            default : return -1;
        }
    } else if (a == '\r') { //TODO: ganti char enter dengan variabel yang bisa di customize
        return 4;
    } else {
        return -1;
    }
}

void NewGame() {

}

void Continue() {

}

void Highscores() {

}

void Settings() {

}