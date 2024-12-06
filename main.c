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

void MainMenu();

void NewGame();
void Continue();
void HowToPlay();

void startGame(PlayerData player);

void printEndScreen(int WinOrLose);

int main() {
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

    startGame(player);
    return;
}

void Continue() {

    PlayerData player;
    if (loadPlayer(&player) == -1) {
        printf("\n\tYou do not have any recent progress. Please start a new game");
        getch();    // hold this screen until player input something
        return;
    }

    startGame(player);

    return;

}

void startGame(PlayerData player) {

    // InitiateHighscore
    Score Highscore, playerScore;
    initializeHighscore(&Highscore);

    int result = inGame(&player, Highscore);

    switch (result) {

    case WON: case LOSE:

        PutPlayerToScore(player, &playerScore);
        PutScoreToFile(playerScore);

        if (playerScore.score > Highscore.score)
            saveHighscore(&playerScore);

        printEndScreen(result);

        remove(SAVE_FILE);
        return;

    case EXIT:
        return;

    default:
        return;
    }
}

void printEndScreen(int WinOrLose) {

    clear_screen();
    setConsoleSize(43, 7);

    if (WinOrLose == LOSE)
    printfColor(
            " __   __            _              _   _ \n"
            " \\ \\ / /__  _   _  | |    ___  ___| |_| |\n"
            "  \\ V / _ \\| | | | | |   / _ \\/ __| __| |\n"
            "   | | (_) | |_| | | |__| (_) \\__ \\ |_|_|\n"
            "   |_|\\___/ \\__,_| |_____\\___/|___/\\__(_)\n\n"
    , 12);

    else 
    printfColor(
                " __   __           __        __          _ \n"
                " \\ \\ / /__  _   _  \\ \\      / /__  _ __ | |\n"
                "  \\ V / _ \\| | | |  \\ \\ /\\ / / _ \\| '_ \\| |\n"
                "   | | (_) | |_| |   \\ V  V / (_) | | | |_|\n"
                "   |_|\\___/ \\__,_|    \\_/\\_/ \\___/|_| |_(_)\n\n"
    , 11);

    
    printf("Press any key to return to the main menu...");
    getch();
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