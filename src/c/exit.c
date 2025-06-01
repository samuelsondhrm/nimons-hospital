#include "../header/exit.h"


void exitProgram(ListUser listuser, ListObat Listobat, ListPenyakit Listpenyakit, ListFormula listformula , RumahSakit rs , Inventory *inventory) {
    char input[10];
    printf("Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (y/n) ");
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove newline
        input[strcspn(input, "\n")] = '\0';
        
        if (input[0] == 'y' || input[0] == 'Y') {
            // Assuming save_data expects a RumahSakit struct, construct or pass the correct variable here.
            // Example: save_data(rumahSakit);
            // Replace 'rumahSakit' with the actual variable of type RumahSakit you have.
            // If save_data expects different arguments, adjust accordingly.
            save_data(listuser, Listobat, Listpenyakit, listformula , rs, inventory); // old call
        }
    }
    
    exit(0); // Exit program regardless of save choice
}