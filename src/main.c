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

// include header for each features
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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Tidak ada nama folder yang diberikan!\n");
        printf("Usage : %s <<nama_folder>>\n", argv[0]);
        return 1;
    }
    
    /* KAMUS */
    // Definisi konstanta
    #define MAX_FIELD 128 // Maksimal panjang field untuk input
    #define MAX_BARIS_RUANGAN 10 // Maksimal jumlah baris ruangan
    #define MAX_KOLOM_RUANGAN 10 // Maksimal jumlah kolom ruangan
    #define CAPACITY_QUEUE 100 // Kapasitas antrian pasien
    #define CAPACITY_MAP 50 // Kapasitas map untuk opsi
/* INITIALIZATION */
    char ans[MAX_FIELD]; 
    boolean ON = true;

    // INISIALISASI OPTIONS
    Map options;
    CreateEmptyMap(&options);
    InsertMap(&options, "LOGIN", 0); // ACCESS: All
    InsertMap(&options, "REGISTER", 1); // ACCESS: Pasien
    InsertMap(&options, "LOGOUT", 2); // ACCESS: All
    InsertMap(&options, "LUPA_PASSWORD", 3); // ACCESS: All
    InsertMap(&options, "HELP", 4); // ACCESS: All
    InsertMap(&options, "LIHAT_DENAH", 5); // ACCESS: All
    InsertMap(&options, "LIHAT_USER", 6); // ACCESS: Manager
    InsertMap(&options, "LIHAT_PASIEN", 7); // ACCESS: Manager
    InsertMap(&options, "LIHAT_DOKTER", 8); // ACCESS: Manager
    InsertMap(&options, "CARI_USER", 9); // ACCESS: Manager
    InsertMap(&options, "CARI_PASIEN", 10); // ACCESS: Manager
    InsertMap(&options, "CARI_DOKTER", 11); // ACCESS: Manager
    InsertMap(&options, "LIHAT_SEMUA_ANTRIAN", 12); // ACCESS: Manager 
    InsertMap(&options, "TAMBAH_DOKTER", 13); // ACCESS: Manager
    InsertMap(&options, "ASSIGN_DOKTER", 14); // ACCESS: Manager
    InsertMap(&options, "DIAGNOSIS", 15); // ACCESS: Dokter
    InsertMap(&options, "NGOBATIN", 16); // ACCESS: Dokter
    InsertMap(&options, "PULANGDOK", 17); // ACCESS: Pasien
    InsertMap(&options, "DAFTAR_CHECKUP", 18); // ACCESS: Pasien
    InsertMap(&options, "ANTRIAN", 19); // ACCESS: Pasien
    InsertMap(&options, "MINUM_OBAT", 20); // ACCESS: Pasien
    InsertMap(&options, "PENAWAR", 21); // ACCESS: Pasien
    InsertMap(&options, "EXIT", 22); // ACCESS: All
    InsertMap(&options, "SAVE", 23); // ACCESS: All
    int selected_option;
    
    ListUser accounts;
    User cur_user;
    RumahSakit rs;
    ListPenyakit lPenyakit;
    ListObat lObat; 
    ListFormula lFormula; 
    Inventory inventory;
    boolean SudahLogin = false;
    
    // // INISIALISASI VARIABEL GLOBAL
    InitializeListUser(&accounts);
    CreateUser(&cur_user);
    InitializeRumahSakit(&rs);
    InitializeListPenyakit(&lPenyakit);
    InitializeListObat(&lObat);
    InitializeListFormula(&lFormula);
    InitializeInventory(&inventory);

    // PARSING
    const char* data_path = "../src/file/";

    char user_csv_path[100];
    char obat_csv_path[100];
    char penyakit_csv_path[100];
    char obatpenyakit_csv_path[100];
    char config_txt_path[100];

    strcpy(user_csv_path, data_path);
    strcat(user_csv_path, "user.csv");
    strcpy(obat_csv_path, data_path);
    strcat(obat_csv_path, "obat.csv");
    strcpy(penyakit_csv_path, data_path);
    strcat(penyakit_csv_path, "penyakit.csv");
    strcpy(obatpenyakit_csv_path, data_path);
    strcat(obatpenyakit_csv_path, "obat_penyakit.csv");
    strcpy(config_txt_path, data_path);
    strcat(config_txt_path, "config.txt");
    
    parse_user_csv(user_csv_path, &accounts);
    parse_obat_csv(obat_csv_path, &lObat);
    parse_penyakit_csv(penyakit_csv_path, &lPenyakit);
    parse_obatpenyakit_csv(obatpenyakit_csv_path, &lFormula);
    if(!loadConfig(config_txt_path, &rs, &inventory, accounts)) printf("CONFIG.TXT ERROR");
    
    char folder_path[512];
    #ifdef _WIN32
    #define SEPARATOR '\\'
    #else
    #define SEPARATOR '/'
    #endif
    snprintf(folder_path, sizeof(folder_path), "data%c%s", SEPARATOR, argv[1]);

    // Try to load data
    if (!load_data(folder_path, &accounts, &lObat, &lPenyakit, &lFormula, &rs, &inventory)) {
        return 1;  // Exit if load fails
    }

/* MAIN LOOP */

    // PrintMap(options);
    while(ON){
        print_header(cur_user);
        
        animate_text("Enter input > > > ", 100);
        fgets(ans, MAX_FIELD, stdin);
        ans[strcspn(ans, "\n")] = 0;

        //kasus khusus untuk LIHAT_RUANGAN
        if(strncmp(ans, "LIHAT_RUANGAN ", 14) == 0 && strlen(ans) >= 16){
            print_case("LIHAT_RUANGAN", cur_user);
            lihatRuangan(rs, ans + 14 /* kode diambil secara otomatis dari character ke-15 string ans */, accounts);
        }
        else{
            selected_option = GetValue(options, ans);
            switch(selected_option){
                case 0: print_case("LOGIN", cur_user);
                    login(&accounts, &cur_user, &SudahLogin ); 
                    SudahLogin = true;
                break;
                case 1: print_case("REGISTER", cur_user);
                    User new_user;
                    CreateUser(&new_user);
                    register_pasien(&accounts, &new_user);
                    break;
                case 2: print_case("LOGOUT", cur_user); 
                    logout(&SudahLogin, &cur_user);
                    break;
                case 3: print_case("LUPA_PASSWORD", cur_user); 
                    lupaPassword(&accounts);
                    tulis_user_csv("src/file/user.csv", &accounts);
                    break;
                case 4: print_case("HELP", cur_user);
                    if(strcmp(ROLE(cur_user), "manager") == 0) helpManager(cur_user);
                    else if(strcmp(ROLE(cur_user), "dokter") == 0) helpDokter(cur_user);
                    else if(strcmp(ROLE(cur_user), "pasien") == 0) helpPasien(cur_user);
                    else notLogin();
                break;
                case 5: print_case("LIHAT_DENAH", cur_user);
                    printDenah(rs);
                    break;
                case 6: print_case("LIHAT_USER", cur_user); 
                    if(!accessCheck("manager", cur_user)) break; 
                    lihatUser(&accounts, 0);
                    break;
                case 7: print_case("LIHAT_PASIEN", cur_user); 
                    if(!accessCheck("manager", cur_user)) break;
                    lihatUser(&accounts, 1);
                    break;
                case 8: print_case("LIHAT_DOKTER", cur_user);
                    if(!accessCheck("manager", cur_user)) break;
                    lihatUser(&accounts, 2);
                    break;
                case 9: print_case("CARI_USER", cur_user); 
                    if(!accessCheck("manager", cur_user)) break;
                    cariUser(&accounts);
                    break;
                case 10: print_case("CARI_PASIEN", cur_user); 
                    if(!accessCheck("manager", cur_user)) break;
                    cariPasien(&accounts);
                    break;
                case 11: print_case("CARI_DOKTER", cur_user); 
                    if(!accessCheck("manager", cur_user)) break;
                    cariDokter(&accounts);
                    break;
                case 12: print_case("LIHAT_SEMUA_ANTRIAN", cur_user); 
                    if(!accessCheck("manager", cur_user)) break;
                    lihatSemuaAntrian(rs, accounts);
                    break;
                case 13: print_case("TAMBAH_DOKTER", cur_user); 
                    if(!accessCheck("manager", cur_user)) break;
                    tambahDokter(&accounts);
                    break;
                case 14: print_case("ASSIGN_DOKTER", cur_user); 
                    if(!accessCheck("manager", cur_user)) break;
                    assignDokter(&rs, &accounts);
                    break;
                case 15: print_case("DIAGNOSIS", cur_user);
                    if(!accessCheck("dokter", cur_user)) break;
                    diagnosis(&cur_user,&rs,&accounts,&lPenyakit);
                    break;
                case 16: print_case("NGOBATIN", cur_user); 
                    if(!accessCheck("dokter", cur_user)) break;
                    ngobatin(cur_user, &rs, &accounts,&lObat,&lFormula,&lPenyakit, &inventory);
                    break;
                case 17: print_case("PULANGDOK", cur_user); 
                    if(!accessCheck("pasien", cur_user)) break;
                    bolehPulang(cur_user, &inventory, &lObat, &lFormula, &lPenyakit, &rs);
                    break;
                case 18: print_case("DAFTAR_CHECKUP", cur_user);
                    if(!accessCheck("pasien", cur_user)) break;
                    tampilkanDokterTersedia(&accounts, &rs);
                    DaftarCheckUp(&accounts, &rs, USERNAME(cur_user));
                    break;
                case 19: print_case("ANTRIAN", cur_user); 
                    if(!accessCheck("pasien", cur_user)) break;
                    antrianSaya(cur_user, rs);
                    break;
                case 20: print_case("MINUM_OBAT", cur_user); 
                    if(!accessCheck("pasien", cur_user)) break;
                    minumObat(cur_user, &inventory, &rs, &lObat);
                    break;
                case 21: print_case("PENAWAR", cur_user); 
                    if(!accessCheck("pasien", cur_user)) break;
                    minumPenawar(cur_user, &inventory, &lObat);
                    break;
                case 22: print_case("EXIT", cur_user);
                    exitProgram(accounts, lObat, lPenyakit, lFormula, rs, &inventory);
                    break;
                case 23: print_case("SAVE", cur_user);
                    save_data(accounts, lObat, lPenyakit, lFormula, rs, &inventory);
                    break;
                default: print_color("INPUT TIDAK VALID", MERAH);
                         printf("\n");
                         printf("Masukkan HELP untuk melihat input valid\n");
                         break;
            }
        }
        printf("\n(Klik enter untuk lanjut)");
        while (getchar() != '\n');
    }
    return 0;
}
