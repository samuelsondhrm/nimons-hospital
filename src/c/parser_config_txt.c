#include "../header/parser_config_txt.h"

#define MAX_LINE_LENGTH 256
int nextInt(const char **p) {
    while (**p != '\0' && !( (**p >= '0' && **p <= '9') || **p == '-' )) {
        (*p)++;
    }
    if (**p == '\0') return -1;
    int sign = 1;
    if (**p == '-') {
        sign = -1;
        (*p)++;
    }
    int val = 0;
    while (**p != '\0' && (**p >= '0' && **p <= '9')) {
        val = val * 10 + (**p - '0');
        (*p)++;
    }
    return val * sign;
}

// Baca satu baris dari file ke buffer, return 0 kalau EOF
int readLine(FILE *fp, char *buffer, int maxLen) {
    int i = 0;
    int ch;
    while (i < maxLen - 1) {
        ch = fgetc(fp);
        if (ch == EOF) break;
        if (ch == '\n') break;
        buffer[i++] = (char)ch;
    }
    buffer[i] = '\0';
    if (ch == EOF && i == 0) return 0;
    return 1;
}
void parseRuanganLine(char *line, Ruangan *ruangan, int kapasitasPerRuangan, int kapasitasBaris) {
    const char *p = line;
    int dokterId = nextInt(&p);
    ruangan->dokterId = dokterId;
    ruangan->jumlahPasien = 0;
    if (dokterId == 0) {
        return;
    }
    int countPasien = 0;
    int val = nextInt(&p);
    while (val != -1 && countPasien < kapasitasPerRuangan){
        ruangan->pasienIds[countPasien] = val;
        val = nextInt(&p);
        countPasien++;
    }
    ruangan->jumlahPasien = countPasien;
    int countBaris = 0;
    while(val != -1 && countBaris < kapasitasBaris){
        enqueue(&ruangan->baris, val);
        val = nextInt(&p);
        countBaris++;
    }
}

void parsePasienObatLine(char *line, Inventory *invntry) {
    const char *p = line;
    int idPasien = nextInt(&p);
    Pasien *psn = &invntry->data[idPasien];
    psn->id = idPasien;
    psn->jumlahobat = 0;
    InitializePasien(psn);

    int obatId = nextInt(&p);
    while (obatId != -1 && psn->jumlahobat < MAX_OBAT) {
        psn->obat[psn->jumlahobat++] = obatId;
        obatId = nextInt(&p);
    }

    if (idPasien >= invntry->jumlahPasienwObat) {
        invntry->jumlahPasienwObat = idPasien + 1;
    }
}

int loadConfig(const char *filename, RumahSakit *rs, Inventory *invntry, int *maxAntrianLuar) {
    InitializeRumahSakit(rs);
    InitializeInventory(invntry);
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file");
        return 0;
    }

    char line[MAX_LINE_LENGTH];

    // Baris 1: ukuran denah
    if (!readLine(fp, line, MAX_LINE_LENGTH)) return 0;
    const char *p = line;
    rs->rows = nextInt(&p);
    rs->cols = nextInt(&p);

    // Baris 2: kapasitas per ruangan & kapasitas baris
    if (!readLine(fp, line, MAX_LINE_LENGTH)) return 0;
    p = line;
    rs->kapasitasPerRuangan = nextInt(&p);
    rs->kapasitasBaris = nextInt(&p);
    *maxAntrianLuar = rs->kapasitasBaris;

    int totalRuangan = rs->rows * rs->cols;
    if (totalRuangan > MAX_BARIS_RUANGAN * MAX_KOLOM_RUANGAN) {
        printf("Ukuran denah terlalu besar\n");
        fclose(fp);
        return 0;
    }

    // Baris 3 s.d. (3 + totalRuangan - 1)
    for (int i = 0; i < totalRuangan; i++) {
        if (!readLine(fp, line, MAX_LINE_LENGTH)) return 0;
        int r = i / rs->cols;
        int c = i % rs->cols;
        parseRuanganLine(line, &rs->data[r][c], rs->kapasitasPerRuangan, rs->kapasitasBaris);
    }

    // Baris berikutnya: jumlah pasien dengan obat
    if (!readLine(fp, line, MAX_LINE_LENGTH)) return 0;
    p = line;
    int jumlah = nextInt(&p);
    invntry->jumlahPasienwObat = jumlah;

    // Baris berikutnya: data pasien
    for (int i = 0; i < jumlah; i++) {
        if (!readLine(fp, line, MAX_LINE_LENGTH)) return 0;
        parsePasienObatLine(line, invntry);
    }
     // Baris berikutnya: jumlah pasien dengan stack obat di perut
    if (!readLine(fp, line, MAX_LINE_LENGTH)) return 0;
    p = line;
    int jumlahPasienPunyaPerut = nextInt(&p);

    // Data stack obat tiap pasien
    for (int i = 0; i < jumlahPasienPunyaPerut; i++) {
        if (!readLine(fp, line, MAX_LINE_LENGTH)) return 0;
        p = line;
        int idPasien = nextInt(&p);
        Pasien *psn = &invntry->data[idPasien];
        InitializePasien(psn); // kalau belum diinisialisasi

        int jumlahObatDalamPerut = nextInt(&p);

        // Untuk memasukkan dari bawah ke atas stack
        int obatSementara[MAX_OBAT];
        for (int j = 0; j < jumlahObatDalamPerut && j < MAX_OBAT; j++) {
            obatSementara[j] = nextInt(&p);
        }

        // Masukkan ke stack (dari bawah ke atas)
        for (int j = 0; j < jumlahObatDalamPerut && j < MAX_OBAT; j++) {
            Push(&psn->perut, obatSementara[j]);
        }
    }
    fclose(fp);
    return 1;
}
