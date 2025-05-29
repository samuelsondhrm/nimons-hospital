// Include any necessary headers
#include <stdio.h>
#include <string.h>
#include "header/Boolean.h"
#include "header/parser_config_txt.h"
#include "header/parser_user_csv.h"
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
    ListUser accounts;

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
    InsertMap(&options, "LIHAT_RUANGAN ", 24); //perlukah, Nael? soalnya ini special case.  // ACCESS: All
    int selected_option;
    
    // InitializeListUser(&accounts);
    // parse_user_csv(user_csv_path, &accounts);


/* MAIN LOOP */
    printf("%s", ascii_art);
    PrintMap(options);
    while(ON){
        printf(">>> ");
        fgets(ans, MAX_FIELD, stdin);
        ans[strcspn(ans, "\n")] = 0;

        //kasus khusus untuk LIHAT_RUANGAN
        if(strncmp(ans, "LIHAT_RUANGAN ", 14) == 0  /* Buat check 14 char pertama 'LIHAT_RUANGAN ' atau bukan */ 
           && 
           strlen(ans) >= 16                        /* Buat check input nyertain ruangan apa kaga */ ){
            RumahSakit rs; //global
            ListUser lUser; //global
            lihatRuangan(&rs, ans + 14 /* kode diambil secara otomatis dari character ke-15 string ans */, lUser);
        }

        selected_option = GetValue(options, ans);
        printf("%d", selected_option);
        switch(selected_option){
            case 0: printf("LOGIN");
                ListUser users; //global
                login(users);
            break;
            case 1: printf("REGISTER");
                ListUser Listuser; // global
                User new_user; // global
                user current_user; // global
                register_pasien(ListUser)
                CreateUser(&new_user);
            
                break;
            case 2: printf("LOGOUT"); 
                break;
            case 3: printf("LUPA_PASSWORD"); break;
            case 4: printf("HELP"); break;
            case 5: printf("LIHAT_DENAH");
                RumahSakit rs; //global
                ListUser lUser; //global
                printDenah(rs);
                break;
            case 6: printf("LIHAT_USER"); 
                ListUser lUser; //global
                lihatUser(&lUser, 0);
                break;
            case 7: printf("LIHAT_PASIEN"); 
                ListUser lUser; //global
                lihatUser(&lUser, 1);
                break;
            case 8: printf("LIHAT_DOKTER");
                ListUser lUser; //global
                lihatUser(&lUser, 2);
                break;
            case 9: printf("CARI_USER"); 
                ListUser lUser; //global
                cariUser(&lUser);
                break;
            case 10: printf("CARI_PASIEN"); 
                ListUser lUser; //global
                cariPasien(&lUser);
                break;
            case 11: printf("CARI_DOKTER"); 
                ListUser lUser; //global
                cariDokter(&lUser);
                break;
            case 12: printf("LIHAT_SEMUA_ANTRIAN"); 
                RumahSakit rs; //global
                ListUser lUser; //global
                lihatSemuaAntrian(rs, lUser);
                break;
            case 13: printf("TAMBAH_DOKTER"); 
                ListUser lUser; //global
                tambahDokter(&lUser);
                break;
            case 14: printf("ASSIGN_DOKTER"); 
                RumahSakit rs; //global
                ListUser lUser; //global
                assignDokter(&rs, &lUser);
                break;
            case 15: printf("DIAGNOSIS");
                RumahSakit rs; // global
                ListUser lUser; // global
                User current_user; //global
                ListPenyakit lPenyakit; //global
                diagnosis(current_user,rs,&lUser,&lPenyakit);
            break;

            case 16: printf("NGOBATIN");
             case 16: printf("NGOBATIN"); 
                Inventory inv; // global
                User current_user; // global
                RumahSakit rs; // global
                ListUser lUser; // global
                ListObat lObat; // global
                ListFormula lFormula; // global
                ListPenyakit lPenyakit; // global
                TambahObatKeInventory(inv);
                ngobatin(rs,&lUser,&IObat,&IFormula,&lPenyakit,inv);
            break;
            case 17: printf("PULANGDOK"); break;
            case 18: printf("DAFTAR_CHECKUP");
                ListUser listUser; // global
                RumahSakit rs; // global
                tampilkanDokterTersedia(listUser,rs);
                DaftarCheckUp(rs,listUser);
            break;
            case 19: printf("ANTRIAN"); break;
            case 20: printf("MINUM_OBAT"); break;
            case 21: printf("PENAWAR"); break;
            case 22: printf("EXIT"); break;
            case 23: printf("SAVE"); break;
            case 24: printf("LIHAT_RUANGAN"); break;
            default: printf("Perintah tidak dikenali.\n");
        }
    printf("\n");
    }
    return 0;
}