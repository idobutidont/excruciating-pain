#ifndef placeholder_h
#define point_h

/*
    ini masi perancangan, belum final
    nanti bakal dipisah ke beberapa folder
        inGame.c
        saving.c
        scores.c
        helper.c <- buat Input, printcolor, utility gitu-gitu
        settings.c
        main.c
*/

typedef struct PlayerData                       // Gunanya buat di simpan ke save-file.
{   
    char Username[25];                          // Literal Username
    int Moves;                                  // Udah berapa move yang dilakukan player
    int difficulty;                             // Tingkat kesulitan (1 - 5), niatnya sih jumlah tiang sama platesnya yang nentuin difficulty-nya
    int DiscsItems[16][16];                     // DiscsItems[Y][X], Tower Y Discs X, gunanya buat nyimpen data disc ke file
    int Towers;                                 // Ada berapa towers yang dimiliki player       // niatnya Towers dan Discs itu
    int Discs;                                  // Ada berapa Discs yang dimiliki player        // diambil dari DiscsItems, jadi ga butuh 2 var ini sebenarnya
    int hand;                                   // Apakah di tangannya ada plate atau kosong, kalau ada berapa besarnya
    int currentPosition;                        // Posisi Tangannya ada di pole mana

    //kalau ada tambahan boleh.

};

void Menu();
// Buat Main Menu playernya

void PlayerInput();
// Buat WASD, ARROW_KEY, INTERACT, dll

void printfColor(char input[], int color);
// kayak printf tapi ada tambahan warna pada fontnya

void PutPlatestoString(char plate[], int besar_plate, int max_plate);
// buat nge render plate, max_plate ditentukan difficulty-nya, besar_plate itu panjang '=' nya
/*
    Kenapa pakai max_plate?
    Karena nanti masing-masing plate itu bisa beda beda panjangnya, dan nanti si visualnya bakal rusak
    - Dan untuk mengatasi hal ini aing nge render string se panjang max_plate + 2.

    Terus kalau tempat yang kosongnya gimana?
    - Di string plate nya nanti aku tambahin spasi ' ' sebanyak yang dibutuhkan

    misal, max_plate 5, besar_plate 3, nanti panjang string buat platenya itu bakal jadi 7 (5 + 2).
    " <===> "

    besar_plate 1
    "  <=>  "

    besar_plate 5
    "<=====>"

*/
// DEMO: " <=============> " atau "⊏==============⊐" "⊂================⊃"

void PrintScreen();
// buat nge print layar in-game
/*
    PEAK DEMO INCOMING!!!
    (Plate Terbesar: 5, Banyak Poles: 3)

               ↓          
           | <===> |       
       _   |   _   |   _
       │   |   │   |   │
       │   |   │   |   │
    <=====>|   │   |  <=>

    Moves: 0        Move(s) Left: 15
    Score: 0        Autosave: On

    Press Z or DOWN_ARROW_KEY to put plates to the pole
    Press X or UP_ARROW_KEY to pick up plates from the pole


    ini masi rencana, niatnya bakal lebih terlihat lah
*/

int MovesToScore(int Moves, int Towers, int Discs);
// Hitung Score Multiplier yang dipengaruhi oleh settingan jumlah towers dan discs
// Jika towers nambah, Score Multiplier ngurang
// Jika Discs nambah, Score Multiplier nambah
// Jika Moves nambah, Score Multiplier ngurang

void SaveToFile(PlayerData player);
// Menyimpan data player ke file save.dat

#endif