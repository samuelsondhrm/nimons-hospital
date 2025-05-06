#include <stdio.h>
#include <string.h>
#ifndef PARSE_USER_CSV
#define PARSE_USER_CSV

#define MAX_FIELD 128
#define MAX_ROWS 100
#include "user.h"

// Menerima string berisikan integer, mengembalikan dalam bentuk integer (Pengganti atoi)
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

// Menerima string berisikan float dengan pemisah (.), mengembalikan dalam bentuk float (Pengganti atof)
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

// Membuka file user.csv, jumlah pasien akan diupdate dan array
void parse_user_csv(const char *filename, User ListUser[], int *jumlah) {
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
    while (ch != EOF && ch != '\n'){
        ch = fgetc(file);
    }

    while ((ch = fgetc(file)) != EOF && row < MAX_ROWS) {
        if (ch == ';' || ch == '\n') {
            field[field_pos] = '\0';
            // Simpan field ke struct
            switch (col) {
                case 0: ListUser[row].id = string_to_int(field); break;
                case 1: strcpy(ListUser[row].username, field); break;
                case 2: strcpy(ListUser[row].password, field); break;
                case 3: strcpy(ListUser[row].role, field); break;
                case 4: strcpy(ListUser[row].riwayat_penyakit, field); break;
                case 5: ListUser[row].suhu_tubuh = string_to_float(field); break;
                case 6: ListUser[row].tekanan_darah_sistolik = string_to_int(field); break;
                case 7: ListUser[row].tekanan_darah_diastolik = string_to_int(field); break;
                case 8: ListUser[row].detak_jantung = string_to_int(field); break;
                case 9: ListUser[row].saturasi_oksigen = string_to_float(field); break;
                case 10: ListUser[row].kadar_gula_darah = string_to_int(field); break;
                case 11: ListUser[row].berat_badan = string_to_float(field); break;
                case 12: ListUser[row].tinggi_badan = string_to_int(field); break;
                case 13: ListUser[row].kadar_kolesterol = string_to_int(field); break;
                case 14: ListUser[row].kadar_kolesterol_ldl = string_to_int(field); break;
                case 15: ListUser[row].trombosit = string_to_int(field); break;
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

    // Baris terakhir jika tak diakhiri newline
    if (field_pos > 0 && col > 0) {
        field[field_pos] = '\0';
        switch (col) {
            case 0: ListUser[row].id = string_to_int(field); break;
            case 1: strcpy(ListUser[row].username, field); break;
            case 2: strcpy(ListUser[row].password, field); break;
            case 3: strcpy(ListUser[row].role, field); break;
            case 4: strcpy(ListUser[row].riwayat_penyakit, field); break;
            case 5: ListUser[row].suhu_tubuh = string_to_float(field); break;
            case 6: ListUser[row].tekanan_darah_sistolik = string_to_int(field); break;
            case 7: ListUser[row].tekanan_darah_diastolik = string_to_int(field); break;
            case 8: ListUser[row].detak_jantung = string_to_int(field); break;
            case 9: ListUser[row].saturasi_oksigen = string_to_float(field); break;
            case 10: ListUser[row].kadar_gula_darah = string_to_int(field); break;
            case 11: ListUser[row].berat_badan = string_to_float(field); break;
            case 12: ListUser[row].tinggi_badan = string_to_int(field); break;
            case 13: ListUser[row].kadar_kolesterol = string_to_int(field); break;
            case 14: ListUser[row].kadar_kolesterol_ldl = string_to_int(field); break;
            case 15: ListUser[row].trombosit = string_to_int(field); break;
        }
        row++;
    }
    *jumlah = row;
    fclose(file);
}

void tampilkan_pasien(User ListUser[], int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        User p = ListUser[i];
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

// ListUser nantinya harus ada file header sendiri yang menggunakan listdin.h dengan ElType user.
#endif