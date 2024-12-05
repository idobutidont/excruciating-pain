/***************************************************************
* FILENAME: main.c
* DESCRIPTION: 
* AUTHOR: 
* DATE: 
****************************************************************/

#include "helper.h"
#include "game.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "score.h"

void NewGame();
void Continue();

void startGame(PlayerData player);

int main() {

    const char* MenuHeader =    "Tower Of Hanoi\n";
    const char* MenuItems[] = {
                                "New Game\n",
                                "Continue\n",
                                "View Scores\n",
                                "How To Play\n\n",

                                "Exit\n\n", NULL
    };
    const char* MenuFooter =    "Press Enter to Continue...\n";

    do
    {
        switch(Menu(MenuHeader, MenuItems, MenuFooter)) {
            case 0: NewGame(); break;
            case 1: Continue(); break;
            case 2: printScoreMenu(); break;
            case 3: HowToPlay(); break;
            case 4: return 0;
        }

    } while (1);
    // continously playing the game until user exited.

    return 0;
}

void NewGame() {
    PlayerData player;

    if (load(&player) == 1) {
        printf("\nYou have an ongoing Progress. Do you want to proceed? [Y/N]: ");
        if (toupper(getche()) != 'Y') return;
    }

    initializePlayer(&player);

    startGame(player);
    return;
}

void Continue() {

    PlayerData player;
    if (load(&player) == -1) {
        printf("\nYou do not have any recent progress. Please start a new game");
        getch();    // hold this screen until player input something
        return;
    }

    startGame(player);

    return;

}

void startGame(PlayerData player) {

    switch (inGame(&player)) {

    case WON:

        printf("You Won!");

        PutPlayerToScore(player);

        remove(SAVE_FILE);
        break;

    case LOSE:
    
        printf("You Lose!");
        remove(SAVE_FILE);
        break;

    default:
        return;
    }

    return;
}

int HowToPlay() {
    printf("How To Play? \n");
    printf("\n1. Pilih tingkat kesulitan yang Anda inginkan. \n");
    printf("2. Pindahkan seluruh disk dari tower yang satu ke tower lainnya sehingga disk tertumpuk sesuai ukurannya. \n");
    printf("3. Tekan up arrow pada keyboard untuk mengangkat disk dan down arrow untuk menurunkan disk. \n");
    printf("4. Disk yang diambil adalah disk yang berada di paling atas tower. \n");
    printf("5. Hanya satu disk yang boleh dipindahkan dalam satu waktu. \n");
    printf("6. Tidak boleh meletakkan disk di atas disk lain yang lebih kecil. \n");
    printf("7. Anda akan memenangkan game jika disk sudah tertumpuk dalam satu tower selain tower awal. \n");
    printf("8. Anda akan kalah apabila Anda kehabisan jatah pergerakan. \n");
}