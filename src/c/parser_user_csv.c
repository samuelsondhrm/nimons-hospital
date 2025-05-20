#include <stdio.h>
#include <string.h>
#include "../header/parser_user_csv.h"

// Konversi string ke int
int string_to_int(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

// Konversi string ke float
float string_to_float(const char *str) {
    float result = 0.0f;
    float fraction = 0.0f;
    int sign = 1;
    int i = 0;
    int divisor = 1;

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.') {
        i++;
        while (str[i] >= '0' && str[i] <= '9') {
            fraction = fraction * 10 + (str[i] - '0');
            divisor *= 10;
            i++;
        }
        result += fraction / divisor;
    }
    return result * sign;
}

// Membaca data user dari CSV
void parse_user_csv(const char *filename, ListUser *ListUser) {
    InitializeListUser(ListUser);
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka user.csv, cek ulang line (x)");
        return;
    }

    char ch = fgetc(file);
    char field[MAX_FIELD];
    int field_pos = 0;
    int col = 0;
    int row = 0;

    // Skip header
    while (ch != EOF && ch != '\n') {
        ch = fgetc(file);
    }

    while ((ch = fgetc(file)) != EOF && row < MAX_FIELD) {
        if (ch == ',' || ch == '\n') {
            field[field_pos] = '\0';
            switch (col) {
                case 0: ListUser->users[row].id = string_to_int(field); break;
                case 1: strcpy(ListUser->users[row].username, field); break;
                case 2: strcpy(ListUser->users[row].password, field); break;
                case 3: strcpy(ListUser->users[row].role, field); break;
                case 4: strcpy(ListUser->users[row].riwayat_penyakit, field); break;
                case 5: ListUser->users[row].suhu_tubuh = string_to_float(field); break;
                case 6: ListUser->users[row].tekanan_darah_sistolik = string_to_int(field); break;
                case 7: ListUser->users[row].tekanan_darah_diastolik = string_to_int(field); break;
                case 8: ListUser->users[row].detak_jantung = string_to_int(field); break;
                case 9: ListUser->users[row].saturasi_oksigen = string_to_float(field); break;
                case 10: ListUser->users[row].kadar_gula_darah = string_to_int(field); break;
                case 11: ListUser->users[row].berat_badan = string_to_float(field); break;
                case 12: ListUser->users[row].tinggi_badan = string_to_int(field); break;
                case 13: ListUser->users[row].kadar_kolesterol = string_to_int(field); break;
                case 14: ListUser->users[row].kadar_kolesterol_ldl = string_to_int(field); break;
                case 15: ListUser->users[row].trombosit = string_to_int(field); break;
            }

            field_pos = 0;
            col++;

            if (ch == '\n') {
                row++;
                col = 0;
            }
        } else {
            if (field_pos < MAX_FIELD - 1) {
                field[field_pos++] = ch;
            }
        }
    }

    // Handle jika baris terakhir tidak diakhiri newline
    if (field_pos > 0 && col > 0) {
        field[field_pos] = '\0';
        switch (col) {
            case 0: ListUser->users[row].id = string_to_int(field); break;
            case 1: strcpy(ListUser->users[row].username, field); break;
            case 2: strcpy(ListUser->users[row].password, field); break;
            case 3: strcpy(ListUser->users[row].role, field); break;
            case 4: strcpy(ListUser->users[row].riwayat_penyakit, field); break;
            case 5: ListUser->users[row].suhu_tubuh = string_to_float(field); break;
            case 6: ListUser->users[row].tekanan_darah_sistolik = string_to_int(field); break;
            case 7: ListUser->users[row].tekanan_darah_diastolik = string_to_int(field); break;
            case 8: ListUser->users[row].detak_jantung = string_to_int(field); break;
            case 9: ListUser->users[row].saturasi_oksigen = string_to_float(field); break;
            case 10: ListUser->users[row].kadar_gula_darah = string_to_int(field); break;
            case 11: ListUser->users[row].berat_badan = string_to_float(field); break;
            case 12: ListUser->users[row].tinggi_badan = string_to_int(field); break;
            case 13: ListUser->users[row].kadar_kolesterol = string_to_int(field); break;
            case 14: ListUser->users[row].kadar_kolesterol_ldl = string_to_int(field); break;
            case 15: ListUser->users[row].trombosit = string_to_int(field); break;
        }
        row++;
    }

    ListUser->jumlahuser = row;
    fclose(file);
}

// Menulis data user ke file CSV
void tulis_user_csv(const char *filename, ListUser ListUser) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Gagal membuka file untuk ditulis: %s\n", filename);
        return;
    }

    fprintf(file,
        "id,username,password,role,riwayat_penyakit,suhu_tubuh,"
        "tekanan_darah_sistolik,tekanan_darah_diastolik,detak_jantung,"
        "saturasi_oksigen,kadar_gula_darah,berat_badan,tinggi_badan,"
        "kadar_kolesterol,kadar_kolesterol_ldl,trombosit\n");

    for (int i = 0; i < ListUser.jumlahuser; i++) {
        User u = ListUser.users[i];
        fprintf(file,
            "%d,%s,%s,%s,%s,%.1f,%d,%d,%d,%.1f,%d,%.1f,%d,%d,%d,%d\n",
            u.id, u.username, u.password, u.role, u.riwayat_penyakit,
            u.suhu_tubuh, u.tekanan_darah_sistolik, u.tekanan_darah_diastolik,
            u.detak_jantung, u.saturasi_oksigen, u.kadar_gula_darah,
            u.berat_badan, u.tinggi_badan, u.kadar_kolesterol,
            u.kadar_kolesterol_ldl, u.trombosit
        );
    }

    fclose(file);
}

// Menampilkan seluruh data pasien
void tampilkan_pasien(ListUser ListUser) {
    for (int i = 0; i < ListUser.jumlahuser; i++) {
        User p = ListUser.users[i];
        printf("Pasien %d:\n", i + 1);
        printf("  ID: %d\n", p.id);
        printf("  Username: %s\n", p.username);
        printf("  Role: %s\n", p.role);
        printf("  Riwayat Penyakit: %s\n", p.riwayat_penyakit);
        printf("  Suhu Tubuh: %.1f\n", p.suhu_tubuh);
        printf("  Tekanan Darah: %d/%d\n", p.tekanan_darah_sistolik, p.tekanan_darah_diastolik);
        printf("  Detak Jantung: %d bpm\n", p.detak_jantung);
        printf("  Saturasi Oksigen: %.1f %%\n", p.saturasi_oksigen);
        printf("  Gula Darah: %d mg/dL\n", p.kadar_gula_darah);
        printf("  Berat Badan: %.1f kg\n", p.berat_badan);
        printf("  Tinggi Badan: %d cm\n", p.tinggi_badan);
        printf("  Kolesterol Total: %d\n", p.kadar_kolesterol);
        printf("  LDL: %d\n", p.kadar_kolesterol_ldl);
        printf("  Trombosit: %d ribu/uL\n", p.trombosit);
        printf("\n");
    }
}
