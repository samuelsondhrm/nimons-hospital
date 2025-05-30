#include "../header/parser_config_txt.h"
#include "stdio.h"

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
    if (dokterId == 0) {
        return;
    }
    int countPasien = 0;
    int val = nextInt(&p);
    while (val > 0 && countPasien < kapasitasPerRuangan + kapasitasBaris){
        enqueue(&ruangan->antrianPasienIds, val);
        val = nextInt(&p);
        countPasien++;
    }
}

void parsePasienObatLine(char *line, Inventory *invntry, int idx) {
    const char *p = line;
    int idPasien = nextInt(&p);
    Pasien *psn = &invntry->data[idx];
    InitializePasien(psn);
    psn->id = idPasien;
    int obatId = nextInt(&p);
    while (obatId > 0 && psn->jumlahobat < MAX_OBAT) {
        psn->obat[psn->jumlahobat++] = obatId;
        obatId = nextInt(&p);
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
    int totalRuangan;

    // Baris 1: ukuran denah
    if (!readLine(fp, line, MAX_LINE_LENGTH)) return 0;
    const char *p = line;
    rs->rows = nextInt(&p);
    rs->cols = nextInt(&p);
    totalRuangan = rs->rows*rs->cols;

    // Baris 2: kapasitas per ruangan & kapasitas baris
    if (!readLine(fp, line, MAX_LINE_LENGTH)) return 0;
    p = line;
    rs->kapasitasPerRuangan = nextInt(&p);
    rs->kapasitasBaris = nextInt(&p);
    *maxAntrianLuar = rs->kapasitasBaris;
    if (totalRuangan > MAX_BARIS_RUANGAN * MAX_KOLOM_RUANGAN) { // Lewat batasan define
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
        parsePasienObatLine(line, invntry, i);
    }
    // Baris berikutnya: jumlah pasien dengan stack obat di perut
    if (!readLine(fp, line, MAX_LINE_LENGTH)) return 0;
    p = line;
    int jumlahPasienPunyaPerut = nextInt(&p);

    // Data stack obat tiap pasien
    for (int i = 0; i < jumlahPasienPunyaPerut; i++) { // ngisi stack
        if (!readLine(fp, line, MAX_LINE_LENGTH)) return 0;
        boolean found = false;
        p = line;
        int idPasien = nextInt(&p);
        Pasien *psn; 
        for(int j = 0; j < invntry->jumlahPasienwObat;j++){
            psn = &invntry->data[j];
            if(idPasien == psn->id){ // id sudah ada, tinggal ngisi stack
                found = true;
                break;
            }
        }
        if(!found){ // masukin id baru
            psn = &invntry->data[invntry->jumlahPasienwObat];
            invntry->jumlahPasienwObat++;
            InitializePasien(psn);
            psn->id = idPasien;
        }
        int ObatdiPerut = 0;
        int obatSementara[MAX_OBAT];

        // Loop ambil semua obat di baris ini
        int temp = nextInt(&p);
        while (temp != -1 && ObatdiPerut < MAX_OBAT) {
            obatSementara[ObatdiPerut++] = temp;
            temp = nextInt(&p);
        }

        // Push ke stack (dari belakang ke depan)
        for (int k = ObatdiPerut - 1; k >= 0; k--) {
            Push(&psn->perut, obatSementara[k]);
        }
    }
    fclose(fp);
    return 1;
}

int main() {
    RumahSakit rs;
    Inventory inv;
    int maxAntrianLuar;

    if (loadConfig("config.txt", &rs, &inv, &maxAntrianLuar)) {
        printf("=== KONFIGURASI BERHASIL DIBACA ===\n");

        // Cetak ukuran denah
        printf("Ukuran denah: %d baris x %d kolom\n", rs.rows, rs.cols);
        printf("Kapasitas per ruangan: %d\n", rs.kapasitasPerRuangan);
        printf("Kapasitas antrian luar per ruangan: %d\n", rs.kapasitasBaris);

        // Cetak isi ruangan
        for (int i = 0; i < rs.rows; i++) {
            for (int j = 0; j < rs.cols; j++) {
                Ruangan *r = &rs.data[i][j];
                printf("Ruangan [%d][%d] - Dokter ID: %d - Antrian pasien: ", i, j, r->dokterId);
                displayQueue(r->antrianPasienIds);
                printf("\n");
            }
        }

        // Cetak data pasien
        printf("\nPasien dengan obat:\n");
        for (int i = 0; i < inv.jumlahPasienwObat; i++) {
            Pasien *p = &inv.data[i];
            printf("Pasien ID: %d | Obat: ", p->id);
            for (int j = 0; j < p->jumlahobat; j++) {
                printf("%d ", p->obat[j]);
            }

            printf("| Stack perut (atas ke bawah): ");
            Stack temp = p->perut;
            while (!IsEmptyStack(temp)) {
                int val;
                Pop(&temp, &val);
                printf("%d ", val);
            }
            printf("\n");
        }

    } else {
        printf("Gagal membaca konfigurasi\n");
    }

    return 0;
}

