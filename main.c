/***************************************************************
* FILENAME: main.c
* DESCRIPTION: Program utama yang memulai permainan
* AUTHOR: Azzar, Idotoho
* DATE: 11 / 11 / 2024
****************************************************************/

#include "menu.h"
#include "game.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

void MainMenu();

void NewGame();
void Continue();
void HowToPlay();

void playGame(PlayerData *player);
void endGame(int result, PlayerData *player);

int main() {
    SetConsoleTitle("Tower Of Hanoi");
    MainMenu();
    return 0;
}

void MainMenu() {

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
            case 2: ViewScore(); break;
            case 3: HowToPlay(); break;
            case 4: return;
        }

    } while (1);
    // continously playing the game until user exited.

}

void NewGame() {

    PlayerData player;
    if (loadPlayer(&player) == 1) {
        printf("\n\tYou have an ongoing Progress. Do you want to proceed? [Y/N]: ");
        if (toupper(getche()) != 'Y') return;
    }

    if (initializePlayer(&player) == EXIT) return;

    playGame(&player);
}

void Continue() {

    PlayerData player;
    if (loadPlayer(&player) == -1) {
        printf("\n\tYou do not have any recent progress. Please start a new game");
        getch();    // hold this screen until player input something
        return;
    }

    playGame(&player);
}

void playGame(PlayerData *player) {

    Score Highscore;
    initializeHighscore(&Highscore);

    int result = processGame(&*player, Highscore);

    endGame(result, &*player);
}

void endGame(int result, PlayerData *player) {

    Score playerScore;

    switch (result) {

    case WON: case LOST:

        PutPlayerToScore(&*player, &playerScore);
        PutScoreToFile(playerScore);
        SortScoreFile();

        remove(SAVE_FILE);

        printEndScreen(result, playerScore);

        return;

    case EXIT:
        return;

    default:
        return;
    }

}

void HowToPlay() {

    clear_screen();
    setConsoleSize(128, 14);
    printf( "\n\tHow To Play? \n\n"
            "\t1. Pilih tingkat kesulitan yang Anda inginkan. \n"
            "\t2. Pindahkan seluruh disk dari tower yang satu ke tower lainnya sehingga disk tertumpuk sesuai ukurannya. \n"
            "\t3. Tekan UP_ARROW pada keyboard untuk mengangkat disk dan DOWN_ARROW untuk menurunkan disk. \n"
            "\t4. Disk yang diambil adalah disk yang berada di paling atas tower. \n"
            "\t5. Hanya satu disk yang boleh dipindahkan dalam satu waktu. \n"
            "\t6. Tidak boleh meletakkan disk di atas disk lain yang lebih kecil. \n"
            "\t7. Anda akan memenangkan game jika disk sudah tertumpuk dalam satu tower selain tower awal. \n"
            "\t8. Anda akan kalah apabila Anda kehabisan jatah pergerakan. \n\n"
            "\tTekan tombol apapun untuk kembali ke menu awal..."
    );

    getch();
}