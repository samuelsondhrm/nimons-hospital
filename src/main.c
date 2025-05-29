// Include any necessary headers
#include <stdio.h>
#include <string.h>
#include "header/Boolean.h"
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

/* 
TAMBAH FUNGSI/PROSEDUR VALIDASI APAKAH FITUR YANG DIAKSES SUDAH SESUAI DENGAN ROLE

Jika salah, akan menampilkan: 
"Anda tidak bisa mengakses fitur <ans>, fitur <ans> hanya boleh diakses oleh seorang <role yang boleh akses fitur tsb>!" 

Catatan:
- fitur ini akan dijalankan sekali setelah user menginput <ans> dan menggunakan skema if-else
- jadi butuh membuat 2 fungsi/prosedur dan 1 typedef/list/yang lainnya untuk:
    1. function mengecek apakah fitur boleh diakses ato ga (boolean)
    2. procedure menampilkan pesan error yang bisa otomatis menginput ans dan role yang bisa akses fitur
    3. constant list/typedef untuk ngedeclare role x bisa akses apa aja (untuk keperluan function dan procedure diatas), idenya sih memanfaatkan List Map options aja
*/
// Terkait constant listny kita coba buat kalau semuanya udah selesai aja dlu, sekarang masih dikit fungsi yang butuh permission jadi masi aman aj harusny

boolean accessCheck(const char* required_role, User request) {
    if (strcmp(required_role, ROLE(request)) != 0) {
        printf(" hanya bisa diakses: %s\n", required_role);
        printf("Sementara kamu adalah: %s\n", ROLE(request));
        return false;
    }
    return true;
}

// GLOBAL VARIABLES
    ListUser accounts;
    User current_user;
    CreateUser(current_user);
    RumahSakit rs;
    ListPenyakit lPenyakit;
    ListObat lObat; 
    ListFormula lFormula; 
    Inventory inventory; 

int main() {
/* INITIALIZATION */
    const char *ascii_art = 
"          _____                   _______                   _____                    _____                    _____                _____                    _____                    _____  \n"
"         /\\    \\                 /::\\    \\                 /\\    \\                  /\\    \\                  /\\    \\              /\\    \\                  /\\    \\                  /\\    \\ \n"
"        /::\\____\\               /::::\\    \\               /::\\    \\                /::\\    \\                /::\\    \\            /::\\    \\                /::\\    \\                /::\\____\\\n"
"       /:::/    /              /::::::\\    \\             /::::\\    \\              /::::\\    \\               \\:::\\    \\           \\:::\\    \\              /::::\\    \\              /:::/    /\n"
"      /:::/    /              /::::::::\\    \\           /::::::\\    \\            /::::::\\    \\               \\:::\\    \\           \\:::\\    \\            /::::::\\    \\            /:::/    / \n"
"     /:::/    /              /:::/~~\\:::\\    \\         /:::/\\:::\\    \\          /:::/\\:::\\    \\               \\:::\\    \\           \\:::\\    \\          /:::/\\:::\\    \\          /:::/    /  \n"
"    /:::/____/              /:::/    \\:::    \\       /:::/__\\:::    \\        /:::/__\\:::    \\               \\:::    \\           \\:::    \\        /:::/__\\:::    \\        /:::/    /   \n"
"   /::::\\    \\             /:::/    / \\:::    \\      \\:::\\   \\:::    \\      /::::\\   \\:::    \\              /::::\\    \\          /::::\\    \\      /::::\\   \\:::    \\      /:::/    /    \n"
"  /::::::\\    \\   _____   /:::/____/   \\:::____\\   ___\\:::   \\:::    \\    /::::::\\   \\:::    \\    ____    /::::::\\    \\        /::::::\\    \\    /::::::\\   \\:::    \\    /:::/    /     \n"
" /:::/\\:::    \\ /\\    \\ |:::|    |     |:::|    | /\\   \\:::   \\:::    \\  /:::/\\:::   \\:::____\\  /\\   \\  /:::/\\:::    \\      /:::/\\:::    \\  /:::/\\:::   \\:::    \\  /:::/    /      \n"
"/:::/  \\:::    /::\\____\\|:::|____|     |:::|    |/::\\   \\:::   \\:::____\\/:::/  \\:::   \\:::|    |/::\\   \\/:::/  \\:::____\\    /:::/  \\:::____\\/:::/  \\:::   \\:::____\\/:::/____/       \n"
"\\::/    \\:::  /:::/    / \\:::    \\   /:::/    / \\:::   \\:::   \\::/    /\\::/    \\:::  /:::|____|\\:::  /:::/    \\::/    /   /:::/    \\::/    /\\::/    \\:::  /:::/    /\\:::\\    \\       \n"
" \\/____/ \\:::\\/:::/    /   \\:::    \\ /:::/    /   \\:::   \\:::   \\/____/  \\/_____/\\::: \\/:::/    /  \\:::\\/:::/    / \\/____/   /:::/    / \\/____/  \\/____/ \\::: \\/:::/    /  \\:::\\    \\      \n"
"          \\::::::/    /     \\:::    /:::/    /     \\:::   \\:::    \\               \\::::::/    /    \\::::::/    /           /:::/    /                    \\::::::/    /    \\:::\\    \\     \n"
"           \\::::/    /       \\:::__/:::/    /       \\:::   \\:::____\\               \\::::/    /      \\::::/____/           /:::/    /                      \\::::/    /      \\:::\\    \\    \n"
"           /:::/    /         \\::::::::/    /         \\:::  /:::/    /                \\::/____/        \\:::    \\           \\::/    /                       /:::/    /        \\:::\\    \\   \n"
"          /:::/    /           \\::::::/    /           \\:::\\/:::/    /                  ~~               \\:::    \\           \\/____/                       /:::/    /          \\:::\\    \\  \n"
"         /:::/    /             \\::::/    /             \\::::::/    /                                     \\:::    \\                                       /:::/    /            \\:::\\    \\ \n"
"        /:::/    /               \\::/____/               \\::::/    /                                       \\:::____\\                                     /:::/    /              \\:::\\____\\\n"
"        \\::/    /                 ~~                      \\::/    /                                         \\::/    /                                     \\::/    /                \\::/    /\n"
"         \\/____/                                           \\/____/                                           \\/____/                                       \\/____/                  \\/____/ \n"
"                                                                                                                                                                                             \n"
"          _____                    _____                    _____                   _______                   _____                    _____                                                \n"
"         /\\    \\                  /\\    \\                  /\\    \\                 /::\\    \\                 /\\    \\                  /\\    \\                                               \n"
"        /::\\____\\                /::\\    \\                /::\\____\\               /::::\\    \\               /::\\____\\                /::\\    \\                                              \n"
"       /::::|   |                \\:::    \\              /::::|   |              /::::::\\    \\             /::::|   |               /::::\\    \\                                             \n"
"      /:::::|   |                 \\:::    \\            /:::::|   |             /::::::::\\    \\           /:::::|   |              /::::::\\    \\                                            \n"
"     /::::::|   |                  \\:::    \\          /::::::|   |            /:::/~~\\:::    \\         /::::::|   |             /:::/\\:::    \\                                           \n"
"    /:::/|::|   |                   \\:::    \\        /:::/|::|   |           /:::/    \\:::    \\       /:::/|::|   |            /:::/__\\:::    \\                                          \n"
"   /:::/ |::|   |                   /::::\\    \\      /:::/ |::|   |          /:::/    / \\:::    \\     /:::/ |::|   |            \\:::   \\:::    \\                                         \n"
"  /:::/  |::|   | _____    ____    /::::::\\    \\    /:::/  |::|___|______   /:::/____/   \\:::____\\   /:::/  |::|   | _____    ___\\:::   \\:::    \\                                        \n"
" /:::/   |::|   |/\\    \\  /\\   \\  /:::/\\:::    \\  /:::/   |::::::::\\    \\ |:::|    |     |:::|    | /:::/   |::|   |/\\    \\  /\\   \\:::   \\:::    \\                                       \n"
"/:: /    |::|   /::\\____\\/::\\   \\/:::/  \\:::____\\/:::/    |:::::::::\\____\\|:::|____|     |:::|    |/:: /    |::|   /::\\____\\/::\\   \\:::   \\:::____\\                                      \n"
"\\::/    /|::|  /:::/    /\\:::   /:::/    \\::/    /\\::/    / ~~~~~/:::/    / \\:::    \\   /:::/    / \\::/    /|::|  /:::/    /\\:::   \\:::   \\::/    /                                      \n"
" \\/____/ |::| /:::/    /  \\:::\\/:::/    / \\/____/  \\/____/      /:::/    /   \\:::    \\ /:::/    /   \\/____/ |::| /:::/    /  \\:::   \\:::   \\/____/                                       \n"
"         |::|/:::/    /    \\::::::/    /                       /:::/    /     \\:::    /:::/    /            |::|/:::/    /    \\:::   \\:::    \\                                           \n"
"         |::::::/    /      \\::::/____/                       /:::/    /       \\:::__/:::/    /             |::::::/    /      \\:::   \\:::____\\                                          \n"
"         |:::::/    /        \\:::    \\                      /:::/    /         \\::::::::/    /              |:::::/    /        \\:::  /:::/    /                                          \n"
"         |::::/    /          \\:::    \\                    /:::/    /           \\::::::/    /               |::::/    /          \\:::\\/:::/    /                                           \n"
"         /:::/    /            \\:::    \\                  /:::/    /             \\::::/    /                /:::/    /            \\::::::/    /                                            \n"
"        /:::/    /              \\:::____\\                /:::/    /               \\::/____/                /:::/    /              \\::::/    /                                             \n"
"        \\::/    /                \\::/    /                \\::/    /                 ~~                      \\::/    /                \\::/    /                                              \n"
"         \\/____/                  \\/____/                  \\/____/                                           \\/____/                  \\/____/                                               \n";
    const char* user_csv_path = "file/user.csv";
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
    
    // INISIALISAS VARIABEL GLOBAL
    // parse_user_csv(user_csv_path, &accounts);
/* MAIN LOOP */
    printf("%s", ascii_art);
    PrintMap(options);
    while(ON){
        printf(">>> ");
        fgets(ans, MAX_FIELD, stdin);
        ans[strcspn(ans, "\n")] = 0;

        //kasus khusus untuk LIHAT_RUANGAN
        if(strncmp(ans, "LIHAT_RUANGAN ", 14) == 0 && strlen(ans) >= 16){
            lihatRuangan(&rs, ans + 14 /* kode diambil secara otomatis dari character ke-15 string ans */, accounts);
        }
        else{
            selected_option = GetValue(options, ans);
            printf("%d", selected_option);
            switch(selected_option){
                case 0: printf("LOGIN");
                    login(&accounts,&current_user); 
                break;
                case 1: printf("REGISTER");
                    CreateUser(&new_user);
                    register_pasien(&accounts, new_user);
                    break;
                case 2: printf("LOGOUT"); 
                    break;
                case 3: printf("LUPA_PASSWORD"); break;
                case 4: printf("HELP"); break;
                case 5: printf("LIHAT_DENAH");
                    printDenah(rs);
                    break;
                case 6: printf("LIHAT_USER"); 
                    if(!accessCheck("manager", current_user)); break; 
                    lihatUser(&accounts, 0);
                    break;
                case 7: printf("LIHAT_PASIEN"); 
                    if(!accessCheck("manager", current_user)); break;
                    lihatUser(&accounts, 1);
                    break;
                case 8: printf("LIHAT_DOKTER");
                    if(!accessCheck("manager", current_user)); break;
                    lihatUser(&accounts, 2);
                    break;
                case 9: printf("CARI_USER"); 
                    if(!accessCheck("manager", current_user)); break;
                    cariUser(&accounts);
                    break;
                case 10: printf("CARI_PASIEN"); 
                    if(!accessCheck("manager", current_user)); break;
                    cariPasien(&accounts);
                    break;
                case 11: printf("CARI_DOKTER"); 
                    if(!accessCheck("manager", current_user)); break;
                    cariDokter(&accounts);
                    break;
                case 12: printf("LIHAT_SEMUA_ANTRIAN"); 
                    if(!accessCheck("manager", current_user)); break;
                    lihatSemuaAntrian(rs, accounts);
                    break;
                case 13: printf("TAMBAH_DOKTER"); 
                    if(!accessCheck("manager", current_user)); break;
                    tambahDokter(&accounts);
                    break;
                case 14: printf("ASSIGN_DOKTER"); 
                    if(!accessCheck("manager", current_user)); break;
                    assignDokter(&rs, &accounts);
                    break;
                case 15: printf("DIAGNOSIS");
                    if(!accessCheck("dokter", current_user)); break;
                    ListPenyakit lPenyakit; 
                    diagnosis(current_user,rs,&accounts,&lPenyakit);
                    break;
                case 16: printf("NGOBATIN"); 
                    if(!accessCheck("dokter", current_user)); break;
                    TambahObatKeInventory(inv);
                    ngobatin(rs,&accounts,&IObat,&IFormula,&lPenyakit,inventory);
                    break;
                case 17: printf("PULANGDOK"); 
                    if(!accessCheck("pasien", current_user)); break;
                    break;
                case 18: printf("DAFTAR_CHECKUP");
                    if(!accessCheck("pasien", current_user)); break;
                    tampilkanDokterTersedia(accounts,rs);
                    DaftarCheckUp(rs,accounts);
                    break;
                case 19: printf("ANTRIAN"); 
                    if(!accessCheck("pasien", current_user)); break;
                    break;
                case 20: printf("MINUM_OBAT"); 
                    if(!accessCheck("pasien", current_user)); break;
                    break;
                case 21: printf("PENAWAR"); 
                    if(!accessCheck("pasien", current_user)); break;
                    break;
                case 22: printf("EXIT"); break;
                case 23: printf("SAVE"); break;
                default: printf("Perintah tidak dikenali.\n");
            }
        printf("\n");
        }
    }
    return 0;
}