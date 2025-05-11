#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/room.h"
#include "../header/parser_config_txt.h"


void parseLineToInts(const char *line, int *arr, int *count) {
    int i = 0, val = 0, neg = 0;
    *count = 0;
    while (line[i]) {
        if ((line[i] >= '0' && line[i] <= '9') || 
            (line[i] == '-' && (line[i + 1] >= '0' && line[i + 1] <= '9'))) {
            val = 0;
            neg = 0;
            if (line[i] == '-') {
                neg = 1;
                i++;
            }
            while (line[i] >= '0' && line[i] <= '9') {
                val = val * 10 + (line[i] - '0');
                i++;
            }
            arr[(*count)++] = neg ? -val : val;
        } else {
            i++;
        }
    }
}

void readHospitalConfig(const char *filename, RumahSakit *rs, Pasien pasienData[MAX_PASIEN]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka file!\n");
        exit(1);
    }

    char line[256];
    int intBuffer[32], count = 0;

    // Baris 1: ukuran denah
    fgets(line, sizeof(line), file);
    parseLineToInts(line, intBuffer, &count);
    rs->rows = intBuffer[0];
    rs->cols = intBuffer[1];

    // Baris 2: kapasitas per ruangan
    fgets(line, sizeof(line), file);
    parseLineToInts(line, intBuffer, &count);
    rs->kapasitasPerRuangan = intBuffer[0];

    // Baris 3-8: state ruangan
    for (int i = 0; i < rs->rows * rs->cols; i++) {
        int r = i / rs->cols;
        int c = i % rs->cols;

        fgets(line, sizeof(line), file);
        parseLineToInts(line, intBuffer, &count);

        if (count == 0) {
            rs->data[r][c].dokterId = 0;
            rs->data[r][c].jumlahPasien = 0;
        } else {
            rs->data[r][c].dokterId = intBuffer[0];
            rs->data[r][c].jumlahPasien = count - 1;
            for (int j = 0; j < count - 1; j++) {
                rs->data[r][c].pasienIds[j] = intBuffer[j + 1];
            }
        }
    }

void simpanKonfigurasi(const char *filename, RumahSakit rs, Pasien pasienData[MAX_PASIEN]) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Gagal membuka file untuk ditulis.\n");
        return;
    }

    // Baris 1: Ukuran rumah sakit (rows cols)
    fprintf(f, "%d %d\n", rs.rows, rs.cols);

    // Baris 2: Kapasitas maksimal per ruangan
    fprintf(f, "%d\n", rs.kapasitasPerRuangan);

    // Baris 3 - 8: State setiap ruangan (dokter dan pasien)
    for (int i = 0; i < rs.rows; i++) {
        for (int j = 0; j < rs.cols; j++) {
            Ruangan r = rs.data[i][j];
            if (r.dokterId == 0) {
                fprintf(f, "0\n");
            } else {
                fprintf(f, "%d", r.dokterId);
                for (int k = 0; k < r.jumlahPasien; k++) {
                    fprintf(f, " %d", r.pasienIds[k]);
                }
                fprintf(f, "\n");
            }
        }
    }

    // Hitung jumlah pasien yang punya obat
    int jumlahPasienObat = 0;
    for (int i = 0; i < MAX_PASIEN; i++) {
        if (pasienData[i].inventory_count > 0) {
            jumlahPasienObat++;
        }
    }

    // Baris 9: Banyak pasien yang punya obat
    fprintf(f, "%d\n", jumlahPasienObat);

    // Baris 10-...: Data obat tiap pasien
    for (int i = 0; i < MAX_PASIEN; i++) {
        if (pasienData[i].inventory_count > 0) {
            fprintf(f, "%d", pasienData[i].id);
            for (int j = 0; j < pasienData[i].inventory_count; j++) {
                fprintf(f, " %d", pasienData[i].inventory[j]);
            }
            fprintf(f, "\n");
        }
    }

    fclose(f);
}
