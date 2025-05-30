#include "../header/lupaPassword.h"

// Run-Length Encoding (case-sensitive)
void runLengthEncode(const char *input, char *output) {
    int len = strlen(input);
    int count = 1;
    int outIdx = 0;

    for (int i = 1; i <= len; i++) {
        if (input[i] == input[i - 1]) {
            count++;
        } 
        
        else {
            if (count > 1) {
                outIdx += sprintf(output + outIdx, "%d", count);
            }
            output[outIdx++] = input[i - 1];
            count = 1;
        }
    }
    output[outIdx] = '\0';
}

void lupaPassword(ListUser *LU) {
    char username[MAX_FIELD];        
    char kodeUnik[MAX_FIELD];
    char expectedKode[MAX_FIELD];

    printf("Username: ");
    scanf("%s", username);

    int userIndex = -1;
    for (int i = 0; i < LU->jumlahuser; i++) {
        if (strcmp(LU->users[i].username, username) == 0) {
            userIndex = i;
            break;
        }
    }

    // Invalid (Username tidak ada atau kode unik salah)
    if (userIndex == -1) {
        printf("Username tidak terdaftar!\n");
        return;
    }

    printf("Kode Unik: ");
    scanf("%s", kodeUnik);

    runLengthEncode(username, expectedKode);

    if (strcmp(kodeUnik, expectedKode) != 0) {
        printf("Kode unik salah!\n");
        return;
    }

    // Valid
    printf("Halo ");
    if (strcmp(LU->users[userIndex].role, "Dokter") == 0) {
        printf("Dokter ");
    } 

    else if (strcmp(LU->users[userIndex].role, "Manager") == 0) {
        printf("Manager ");
    } 
    
    else {
        printf("Pasien ");
    }

    printf("%s, silakan daftarkan ulang password anda!\n", LU->users[userIndex].username);

    char newPassword[MAX_FIELD];
    printf("Password Baru: ");
    scanf("%s", newPassword);

    strcpy(LU->users[userIndex].password, newPassword);
}
