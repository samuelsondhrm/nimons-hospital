// Include any necessary headers
#include <stdio.h>
#include <string.h>
#include "header/Boolean.h"
#include "header/interface.h"
#include "header/parser_config_txt.h"
#include "header/csv_parser.h"
#include "header/ADT/liststatik.h"
#include "header/ADT/map.h"
#include "header/ADT/matrix.h"
#include "header/ADT/queue.h"
#include "header/ADT/room.h"
#include "header/ADT/set.h"
#include "header/ADT/stack.h"
#include "header/ADT/user.h"
#include "header/ADT/linkedlist.h"
#include "header/ADT/penyakit_dan_obat.h"



//include header for each features
#include "header/login.h"
#include "header/register.h"
#include "header/logout.h"
#include "header/lupaPassword.h"
#include "header/help.h"
#include "header/denah.h"
#include "header/lihatuser.h"
#include "header/cariuser.h"
#include "header/lihatantrian.h"
#include "header/tambahdokter.h"
#include "header/diagnosis.h"
#include "header/ngobatin.h"
#include "header/pulangDok.h"
#include "header/checkUp.h"
#include "header/antrianSaya.h"
#include "header/minumObat.h"
#include "header/minumPenawar.h"
#include "header/exit.h"
#include "header/load.h"
#include "header/save.h"

#include "c/interface.c"

// boolean accessCheck(const char* required_role, User request) {
//     if (strcmp(required_role, ROLE(request)) != 0) {
//         printf(" hanya bisa diakses: %s\n", required_role);
//         printf("Sementara kamu adalah: %s\n", ROLE(request));
//         return false;
//     }
//     return true;
// }

// GLOBAL VARIABLES
    

int main() {
/* INITIALIZATION */
    char ans[MAX_FIELD]; 
    boolean ON = true;

    // // INISIALISASI OPTIONS
    // Map options;
    // CreateEmptyMap(&options);
    // InsertMap(&options, "LOGIN", 0); // ACCESS: All
    // InsertMap(&options, "REGISTER", 1); // ACCESS: Pasien
    // InsertMap(&options, "LOGOUT", 2); // ACCESS: All
    // InsertMap(&options, "LUPA_PASSWORD", 3); // ACCESS: All
    // InsertMap(&options, "HELP", 4); // ACCESS: All
    // InsertMap(&options, "LIHAT_DENAH", 5); // ACCESS: All
    // InsertMap(&options, "LIHAT_USER", 6); // ACCESS: Manager
    // InsertMap(&options, "LIHAT_PASIEN", 7); // ACCESS: Manager
    // InsertMap(&options, "LIHAT_DOKTER", 8); // ACCESS: Manager
    // InsertMap(&options, "CARI_USER", 9); // ACCESS: Manager
    // InsertMap(&options, "CARI_PASIEN", 10); // ACCESS: Manager
    // InsertMap(&options, "CARI_DOKTER", 11); // ACCESS: Manager
    // InsertMap(&options, "LIHAT_SEMUA_ANTRIAN", 12); // ACCESS: Manager 
    // InsertMap(&options, "TAMBAH_DOKTER", 13); // ACCESS: Manager
    // InsertMap(&options, "ASSIGN_DOKTER", 14); // ACCESS: Manager
    // InsertMap(&options, "DIAGNOSIS", 15); // ACCESS: Dokter
    // InsertMap(&options, "NGOBATIN", 16); // ACCESS: Dokter
    // InsertMap(&options, "PULANGDOK", 17); // ACCESS: Pasien
    // InsertMap(&options, "DAFTAR_CHECKUP", 18); // ACCESS: Pasien
    // InsertMap(&options, "ANTRIAN", 19); // ACCESS: Pasien
    // InsertMap(&options, "MINUM_OBAT", 20); // ACCESS: Pasien
    // InsertMap(&options, "PENAWAR", 21); // ACCESS: Pasien
    // InsertMap(&options, "EXIT", 22); // ACCESS: All
    // InsertMap(&options, "SAVE", 23); // ACCESS: All
    // int selected_option;
    
    // ListUser accounts;
    // User cur_user;
    // RumahSakit rs;
    // ListPenyakit lPenyakit;
    // ListObat lObat; 
    // ListFormula lFormula; 
    // Inventory inventory; 

    // // INISIALISASI VARIABEL GLOBAL
    // InitializeListUser(&accounts);
    // CreateUser(&cur_user);
    // InitializeRumahSakit(&rs);
    // InitializeListPenyakit(&lPenyakit);
    // InitializeListObat(&lObat);
    // InitializeListFormula(&lFormula);
    // InitializeInventory(&inventory);

    // // PARSING
    // const char* user_csv_path = "file/user.csv";
    // const char* obat_csv_path = "file/obat.csv";
    // const char* penyakit_csv_path = "file/penyait.csv";
    // const char* obatpenyakit_csv_path = "file/obat_penyakit.csv";
    // parse_user_csv(user_csv_path, &accounts);
    // parse_obat_csv(obat_csv_path, &lObat);
    // parse_penyakit_csv(penyakit_csv_path, &lPenyakit);
    // parse_obatpenyakit_csv(obatpenyakit_csv_path, &lFormula);

/* MAIN LOOP */
    printf("%s", ascii_art);
    // PrintMap(options);
    while(ON){
        printf(">>> ");
        fgets(ans, MAX_FIELD, stdin);
        ans[strcspn(ans, "\n")] = 0;

        // //kasus khusus untuk LIHAT_RUANGAN
        // if(strncmp(ans, "LIHAT_RUANGAN ", 14) == 0 && strlen(ans) >= 16){
        //     lihatRuangan(rs, ans + 14 /* kode diambil secara otomatis dari character ke-15 string ans */, accounts);
        // }
        // else{
        //     selected_option = GetValue(options, ans);
        //     printf("%d", selected_option);
        //     switch(selected_option){
        //         case 0: printf("LOGIN");
        //             login(&accounts,&cur_user); 
        //         break;
        //         case 1: printf("REGISTER");
        //             User new_user;
        //             CreateUser(&new_user);
        //             register_pasien(&accounts, &new_user);
        //             break;
        //         case 2: printf("LOGOUT"); 
        //             logout(&SudahLogin, &cur_user);
        //             break;
        //         case 3: printf("LUPA_PASSWORD"); 
        //             lupa_password(&accounts);
        //             tulis_user_csv("src/file/user.csv", &accounts);
        //             break;
        //         case 4: printf("HELP"); break;
        //         case 5: printf("LIHAT_DENAH");
        //             printDenah(rs);
        //             break;
        //         case 6: printf("LIHAT_USER"); 
        //             if(!accessCheck("manager", cur_user)); break; 
        //             lihatUser(&accounts, 0);
        //             break;
        //         case 7: printf("LIHAT_PASIEN"); 
        //             if(!accessCheck("manager", cur_user)); break;
        //             lihatUser(&accounts, 1);
        //             break;
        //         case 8: printf("LIHAT_DOKTER");
        //             if(!accessCheck("manager", cur_user)); break;
        //             lihatUser(&accounts, 2);
        //             break;
        //         case 9: printf("CARI_USER"); 
        //             if(!accessCheck("manager", cur_user)); break;
        //             cariUser(&accounts);
        //             break;
        //         case 10: printf("CARI_PASIEN"); 
        //             if(!accessCheck("manager", cur_user)); break;
        //             cariPasien(&accounts);
        //             break;
        //         case 11: printf("CARI_DOKTER"); 
        //             if(!accessCheck("manager", cur_user)); break;
        //             cariDokter(&accounts);
        //             break;
        //         case 12: printf("LIHAT_SEMUA_ANTRIAN"); 
        //             if(!accessCheck("manager", cur_user)); break;
        //             lihatSemuaAntrian(rs, accounts);
        //             break;
        //         case 13: printf("TAMBAH_DOKTER"); 
        //             if(!accessCheck("manager", cur_user)); break;
        //             tambahDokter(&accounts);
        //             break;
        //         case 14: printf("ASSIGN_DOKTER"); 
        //             if(!accessCheck("manager", cur_user)); break;
        //             assignDokter(&rs, &accounts);
        //             break;
        //         case 15: printf("DIAGNOSIS");
        //             if(!accessCheck("dokter", cur_user)); break;
        //             diagnosis(&cur_user,&rs,&accounts,&lPenyakit, &SudahDiagnosis);
        //             break;
        //         case 16: printf("NGOBATIN"); 
        //             if(!accessCheck("dokter", cur_user)); break;
        //             TambahObatKeInventory(inventory);
        //             ngobatin(cur_user, &rs, &accounts,&lObat,&lFormula,&lPenyakit, &inventory);
        //             break;
        //         case 17: printf("PULANGDOK"); 
        //             if(!accessCheck("pasien", cur_user)); break;
        //             bolehPulang(cur_user, &inventory, &lObat, &lFormula, &lPenyakit, &rs);
        //             break;
        //         case 18: printf("DAFTAR_CHECKUP");
        //             if(!accessCheck("pasien", cur_user)); break;
        //             tampilkanDokterTersedia(accounts,rs);
        //             DaftarCheckUp(&accounts, &rs, USERNAME(cur_user));
        //             break;
        //         case 19: printf("ANTRIAN"); 
        //             if(!accessCheck("pasien", cur_user)); break;
        //             antrianSaya(cur_user, rs);
        //             break;
        //         case 20: printf("MINUM_OBAT"); 
        //             if(!accessCheck("pasien", cur_user)); break;
        //             minumObat(cur_user, &inventory, &rs, &lObat);
        //             break;
        //         case 21: printf("PENAWAR"); 
        //             if(!accessCheck("pasien", cur_user)); break;
        //             minumPenawar(cur_user, &inventory, &lObat);
        //             break;
        //         case 22: printf("EXIT"); break;
        //         case 23: printf("SAVE"); break;
        //         default: printf("Perintah tidak dikenali.\n");
        //     }
        printf("\n");
        }
        return 0;
    }