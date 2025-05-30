#include "../header/exit.h"
#include "../header/save.h"
#include "../header/ADT/user.h"

void exitProgram(ListUser listUser, RumahSakit rs, Pasien pasienData[]) {
    char input[10];
    printf("Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (y/n) ");
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove newline
        input[strcspn(input, "\n")] = '\0';
        
        if (input[0] == 'y' || input[0] == 'Y') {
            save_data(listUser, rs, pasienData);
        }
    }
    
    exit(0); // Exit program regardless of save choice
}