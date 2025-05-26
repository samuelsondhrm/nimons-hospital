#include <stdio.h>
#include <string.h>
#include "lupaPassword.h"  

int main() {
    char username[MAX_FIELD];
    char kode[MAX_FIELD];
    char instruksi[MAX_FIELD];
    char passwordBaru[MAX_FIELD];
    char role[MAX_FIELD];

    printf(">>> ");
    scanf("%s", instruksi);

    if (strcmp(instruksi, "LUPA_PASSWORD") == 0) {
        printf("Username: ");
        scanf("%s", username);

        printf("Kode Unik: ");
        scanf("%s", kode);

        if (usernameFound(username, "user.csv") && kodeUnik(username, kode)) {
            getRole(username, "user.csv", role);
            printf("Halo %s %s, silahkan daftarkan ulang password anda!\n", role, username);
            printf("Password Baru: ");
            scanf("%s", passwordBaru);

            updatePassword(username, passwordBaru, "user.csv");
            printf("Password berhasil diubah!\n");
        } 

        else {
            
            if (!usernameFound(username, "user.csv")) {
                printf("Username tidak terdaftar!\n");
            } 
            
            else if (!kodeUnik(username, kode)) {
                printf("Kode unik salah!\n");
            }
        }
    }

    return 0;
}
