/*

3 PROSEDUR PEMANGGILAN:
    cariUser(&lu);
    cariPasien(&lu);
    cariDokter(&lu);

*/

#include "../header/cariuser.h"

int getIntInput(const char *prompt, int min, int max) {
    char buffer[100];
    int value;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &value) == 1 && value >= min && value <= max) {
                return value;
            } else {
                printf("Masukan salah, mohon input hanya integer dari %d sampai %d!\n", min, max);
            }
        } else {
            printf("Terjadi kesalahan saat membaca input.\n");
        }
    }
}

void getStringInput(const char *prompt, char *dest, int maxLen) {
    printf("%s", prompt);
    if (fgets(dest, maxLen, stdin)) {
        size_t len = strlen(dest);
        if (len > 0 && dest[len - 1] == '\n') {
            dest[len - 1] = '\0';
        }
    }
}

void toLowerCase(char *dest, const char *src) {
    int i;
    for (i = 0; src[i] && i < MAX_FIELD - 1; i++) {
        dest[i] = tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}
void swapUser(User *a, User *b) {
    User temp = *a; *a = *b; *b = temp;
}
void sortUsers(User arr[], int n, int byId, int asc) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int cmp;
            if (byId) cmp = arr[j].id - arr[j+1].id;
            else {
                char s1[MAX_FIELD], s2[MAX_FIELD];
                toLowerCase(s1, arr[j].username);
                toLowerCase(s2, arr[j+1].username);
                cmp = strcmp(s1, s2);
            }
            if ((asc && cmp > 0) || (!asc && cmp < 0)) swapUser(&arr[j], &arr[j+1]);
        }
    }
}
int binarySearchById(User arr[], int n, int id) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid].id == id) return mid;
        else if (arr[mid].id < id) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
int sequentialSearchByName(User arr[], int n, const char *name) {
    for (int i = 0; i < n; i++) {
        if (strcasecmp(arr[i].username, name) == 0) return i;
    }
    return -1;
}
int searchPatientsByDisease(User arr[], int n, const char *disease, int result[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strcasecmp(arr[i].role, "pasien") == 0 && strcasecmp(arr[i].riwayat_penyakit, disease) == 0) {
            result[count++] = i;
        }
    }
    return count;
}
void displayHeader(int mode) {
    if (mode == 0) {
        printf("%3s | %-10s | %-8s | %-20s\n", "ID", "Nama", "Role", "Penyakit");
        printf("----+------------+----------+----------------------\n");
    } else if (mode == 1) {
        printf("%3s | %-10s | %-20s\n", "ID", "Nama", "Penyakit");
        printf("----+------------+----------------------\n");
    } else {
        printf("%3s | %-10s\n", "ID", "Nama");
        printf("----+------------\n");
    }
}
void displayUser(const User *u, int mode) {
    const char* penyakit = (strcasecmp(u->role, "pasien") == 0) ? u->riwayat_penyakit : "-";

    if (mode == 0) {
        printf("%3d | %-10s | %-8s | %-20s\n", u->id, u->username, u->role, penyakit);
    } else if (mode == 1) {
        printf("%3d | %-10s | %-20s\n", u->id, u->username, u->riwayat_penyakit);
    } else {
        printf("%3d | %-10s\n", u->id, u->username);
    }
}

// Procedures for each command
void cariUser(ListUser *lu) {
    int choice = getIntInput("Cari berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan: ", 1, 2);

    if (choice == 1) {
        int id = getIntInput("\n>>> Masukkan nomor ID user: ", 1, lu->jumlahuser);
        int idx = binarySearchById(lu->users, lu->jumlahuser, id);
        if (idx == -1) printf("\nTidak ditemukan pengguna dengan ID %d!\n", id);
        else {
            printf("\nMenampilkan pengguna dengan nomor ID %d...\n", id);
            displayHeader(0);
            displayUser(&lu->users[idx], 0);
        }
    } else {
        char name[MAX_FIELD];
        getStringInput("\n>>> Masukkan nama user: ", name, MAX_FIELD);
        int idx = sequentialSearchByName(lu->users, lu->jumlahuser, name);
        if (idx == -1) printf("\nTidak ditemukan pengguna dengan nama %s!\n", name);
        else {
            printf("\nMenampilkan pengguna dengan nama %s...\n", name);
            displayHeader(0);
            displayUser(&lu->users[idx], 0);
        }
    }
}

void cariPasien(ListUser *lu) {
    int choice = getIntInput("Cari berdasarkan?\n1. ID\n2. Nama\n3. Penyakit\n>>> Pilihan: ", 1, 3);

    if (choice == 3) {
        char disease[MAX_FIELD];
        getStringInput("\n>>> Masukkan nama penyakit: ", disease, MAX_FIELD);
        int results[MAX_FIELD];
        int count = searchPatientsByDisease(lu->users, lu->jumlahuser, disease, results);
        if (count == 0) {
            printf("\nTidak ditemukan pasien dengan penyakit %s!\n", disease);
        } else {
            int sortBy = getIntInput("\nUrutkan berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan: ", 1, 2);
            int asc = getIntInput("\nUrutan sort?\n1. ASC (A-Z)\n2. DESC (Z-A)\n>>> Pilihan: ", 1, 2);
            User temp[MAX_FIELD];
            for (int i = 0; i < count; i++) temp[i] = lu->users[results[i]];
            sortUsers(temp, count, sortBy == 1, asc == 1);
            printf("\nMenampilkan pasien dengan penyakit %s dengan ID terurut %s...\n",
                   disease, asc == 1 ? "ascending" : "descending");
            displayHeader(1);
            for (int i = 0; i < count; i++) displayUser(&temp[i], 1);
        }
    } else if (choice == 1) {
        int id = getIntInput("\n>>> Masukkan nomor ID pasien: ", 1, lu->jumlahuser);
        int idx = binarySearchById(lu->users, lu->jumlahuser, id);
        if (idx == -1 || strcasecmp(lu->users[idx].role, "pasien") != 0)
            printf("\nTidak ditemukan pasien dengan ID %d!\n", id);
        else {
            printf("\nMenampilkan pasien dengan ID %d...\n", id);
            displayHeader(1);
            displayUser(&lu->users[idx], 1);
        }
    } else {
        char name[MAX_FIELD];
        getStringInput("\n>>> Masukkan nama pasien: ", name, MAX_FIELD);
        int idx = sequentialSearchByName(lu->users, lu->jumlahuser, name);
        if (idx == -1 || strcasecmp(lu->users[idx].role, "pasien") != 0)
            printf("\nTidak ditemukan pasien dengan nama %s!\n", name);
        else {
            printf("\nMenampilkan pasien dengan nama %s...\n", name);
            displayHeader(1);
            displayUser(&lu->users[idx], 1);
        }
    }
}

void cariDokter(ListUser *lu) {
    int choice = getIntInput("Cari berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan: ", 1, 2);

    if (choice == 1) {
        int id = getIntInput("\n>>> Masukkan nomor ID dokter: ", 1, lu->jumlahuser);
        int idx = binarySearchById(lu->users, lu->jumlahuser, id);
        if (idx == -1 || strcasecmp(lu->users[idx].role, "dokter") != 0)
            printf("\nTidak ditemukan dokter dengan ID %d!\n", id);
        else {
            printf("\nMenampilkan dokter dengan ID %d...\n", id);
            displayHeader(2);
            displayUser(&lu->users[idx], 2);
        }
    } else {
        char name[MAX_FIELD];
        getStringInput("\n>>> Masukkan nama dokter: ", name, MAX_FIELD);
        int idx = sequentialSearchByName(lu->users, lu->jumlahuser, name);
        if (idx == -1 || strcasecmp(lu->users[idx].role, "dokter") != 0)
            printf("\nTidak ditemukan dokter dengan nama %s!\n", name);
        else {
            printf("\nMenampilkan dokter dengan nama %s...\n", name);
            displayHeader(2);
            displayUser(&lu->users[idx], 2);
        }
    }
}