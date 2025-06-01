#include "../header/csv_parser.h"

// ==================== UTILITIES ====================
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

// ==================== BAGIAN OBAT ====================
// Membaca obat.csv
void parse_obat_csv(const char *filename,  ListObat *l) {
    InitializeListObat(l);
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka %s\n", filename);
        return;
    }
    char ch = fgetc(file);
    char field[MAX_FIELD];
    int field_pos = 0;
    int col = 0;
    int row = 0;
    while (ch != EOF && ch != '\n') {     // Skip header
        ch = fgetc(file);
    }
    while ((ch = fgetc(file)) != EOF && row < MAX_FIELD) {
        if (ch == ',' || ch == '\n' || ch == ';') {
            field[field_pos] = '\0';
            switch (col) {
                case 0: l->obats[row].id = string_to_int(field); break;
                case 1: strcpy(l->obats[row].nama, field); break;
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
            case 0: l->obats[row].id = string_to_int(field); break;
            case 1: strcpy(l->obats[row].nama, field); break;
        }
        row++;
    }
    l->jumlahobat = row;
    fclose(file);
}
void tulis_obat_csv(const char *filename, ListObat l) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Gagal membuka %s\n", filename);
        return;
    }
    fprintf(file,"obat_id,nama_obat\n");
    for (int i = 0; i < l.jumlahobat; i++) {
        Obat o = l.obats[i];
        fprintf(file,"%d,%s\n",o.id, o.nama);
    }
    fclose(file);
}


//  ==================== BAGIAN PENYAKIT ====================
// Membaca penyakit.csv
void parse_penyakit_csv(const char *filename,  ListPenyakit *l) {
    InitializeListPenyakit(l);
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka %s\n", filename);
        return;
    }
    char ch = fgetc(file);
    char field[MAX_FIELD];
    int field_pos = 0;
    int col = 0;
    int row = 0;
    while (ch != EOF && ch != '\n') {     // Skip header
        ch = fgetc(file);
    }
    while ((ch = fgetc(file)) != EOF && row < MAX_FIELD) {
        if (ch == ',' || ch == '\n' || ch == ';') {
            field[field_pos] = '\0';
            switch (col) {
                case 0: l->penyakits[row].id = string_to_int(field); break;
                case 1: strcpy(l->penyakits[row].nama, field); break;
                case 2: l->penyakits[row].suhu_min = string_to_float(field); break;
                case 3: l->penyakits[row].suhu_max = string_to_float(field); break;
                case 4: l->penyakits[row].sys_min = string_to_int(field); break;
                case 5: l->penyakits[row].sys_max = string_to_int(field); break;
                case 6: l->penyakits[row].dias_min = string_to_int(field); break;
                case 7: l->penyakits[row].dias_max = string_to_int(field); break;
                case 8: l->penyakits[row].detak_min = string_to_int(field); break;
                case 9: l->penyakits[row].detak_max = string_to_int(field); break;
                case 10: l->penyakits[row].saturasi_min = string_to_float(field); break;
                case 11: l->penyakits[row].saturasi_max = string_to_float(field); break;
                case 12: l->penyakits[row].gula_min = string_to_float(field); break;
                case 13: l->penyakits[row].gula_max = string_to_float(field); break;
                case 14: l->penyakits[row].berat_min = string_to_float(field); break;
                case 15: l->penyakits[row].berat_max = string_to_float(field); break;
                case 16: l->penyakits[row].tinggi_min = string_to_int(field); break;
                case 17: l->penyakits[row].tinggi_max = string_to_int(field); break;
                case 18: l->penyakits[row].kolesterol_min = string_to_int(field); break;
                case 19: l->penyakits[row].kolesterol_max = string_to_int(field); break;
                case 20: l->penyakits[row].trombosit_min = string_to_int(field); break;
                case 21: l->penyakits[row].trombosit_max = string_to_int(field); break;
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
            case 0: l->penyakits[row].id = string_to_int(field); break;
                case 1: strcpy(l->penyakits[row].nama, field); break;
                case 2: l->penyakits[row].suhu_min = string_to_float(field); break;
                case 3: l->penyakits[row].suhu_max = string_to_float(field); break;
                case 4: l->penyakits[row].sys_min = string_to_int(field); break;
                case 5: l->penyakits[row].sys_max = string_to_int(field); break;
                case 6: l->penyakits[row].dias_min = string_to_int(field); break;
                case 7: l->penyakits[row].dias_max = string_to_int(field); break;
                case 8: l->penyakits[row].detak_min = string_to_int(field); break;
                case 9: l->penyakits[row].detak_max = string_to_int(field); break;
                case 10: l->penyakits[row].saturasi_min = string_to_float(field); break;
                case 11: l->penyakits[row].saturasi_max = string_to_float(field); break;
                case 12: l->penyakits[row].gula_min = string_to_float(field); break;
                case 13: l->penyakits[row].gula_max = string_to_float(field); break;
                case 14: l->penyakits[row].berat_min = string_to_float(field); break;
                case 15: l->penyakits[row].berat_max = string_to_float(field); break;
                case 16: l->penyakits[row].tinggi_min = string_to_int(field); break;
                case 17: l->penyakits[row].tinggi_max = string_to_int(field); break;
                case 18: l->penyakits[row].kolesterol_min = string_to_int(field); break;
                case 19: l->penyakits[row].kolesterol_max = string_to_int(field); break;
                case 20: l->penyakits[row].trombosit_min = string_to_int(field); break;
                case 21: l->penyakits[row].trombosit_max = string_to_int(field); break;
        }
        row++;
    }
    l->jumlahpenyakit = row;
    fclose(file);
}

void tulis_penyakit_csv(const char *filename, ListPenyakit l) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Gagal membuka %s\n", filename);
        return;
    }
    fprintf(file,
        "id,nama_penyakit,suhu_tubuh_min,suhu_tubuh_max,tekanan_darah_sistolik_min,tekanan_darah_sistolik_max,tekanan_darah_diastolik_min,tekanan_darah_diastolik_max,detak_jantung_min,detak_jantung_max,saturasi_oksigen_min,saturasi_oksigen_max,kadar_gula_darah_min,kadar_gula_darah_max,berat_badan_min,berat_badan_max,tinggi_badan_min,tinggi_badan_max,kadar_kolesterol_min,kadar_kolesterol_max,trombosit_min,trombosit_max\n");
    for (int i = 0; i < l.jumlahpenyakit; i++) {
        Penyakit p = l.penyakits[i];
        fprintf(file,
            "%d,%s,%.1f,%.1f,%d,%d,%d,%d,%d,%d,%.1f,%.1f,%.1f,%.1f,"
            "%.1f,%.1f,%d,%d,%d,%d,%d,%d\n",
            p.id, p.nama, p.suhu_min, p.suhu_max,
            p.sys_min, p.sys_max, p.dias_min, p.dias_max,
            p.detak_min, p.detak_max, p.saturasi_min, p.saturasi_max,
            p.gula_min, p.gula_max, p.berat_min, p.berat_max,
            p.tinggi_min, p.tinggi_max, p.kolesterol_min, p.kolesterol_max,
            p.trombosit_min, p.trombosit_max
        );
    }
    fclose(file);
}




// ==================== BAGIAN OBATPENYAKIT ====================
void parse_obatpenyakit_csv(const char *filename, ListFormula *l) {
    l->jumlahformula = 0;
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka %s\n", filename);
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
    while ((ch = fgetc(file)) != EOF && row < MAX_FORMULA) {
        if (ch == ',' || ch == '\n' || ch == ';') {
            field[field_pos] = '\0';
            switch (col) {
                case 0: l->formulas[row].obat_id = string_to_int(field); break;
                case 1: l->formulas[row].penyakit_id = string_to_int(field); break;
                case 2: l->formulas[row].urutan = string_to_int(field); break;
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
    if (field_pos > 0 && col > 0) {
        field[field_pos] = '\0';
        switch (col) {
            case 0: l->formulas[row].obat_id = string_to_int(field); break;
            case 1: l->formulas[row].penyakit_id = string_to_int(field); break;
            case 2: l->formulas[row].urutan = string_to_int(field); break;
        }
        row++;
    }
    l->jumlahformula = row;
    fclose(file);
}
void tulis_obatpenyakit_csv(const char *filename, ListFormula l) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Gagal membuka %s\n", filename);
        return;
    }
    fprintf(file, "obat_id,penyakit_id,urutan_minum\n");
    for (int i = 0; i < l.jumlahformula; i++) {
        Formula op = l.formulas[i];
        fprintf(file, "%d,%d,%d\n", op.obat_id, op.penyakit_id, op.urutan);
    }
    fclose(file);
}

void parse_user_csv(const char *filename, ListUser *ListUser) {
    InitializeListUser(ListUser);
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka %s\n", filename);
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
        if (ch == ',' || ch == '\n' || ch == ';') {
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

// ==================== BAGIAN USER ====================
// Menulis data user ke file CSV
void tulis_user_csv(const char *filename, ListUser *l) {
    ListUser tulis = *l;
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Gagal membuka %s\n", filename);
        return;
    }

    fprintf(file,
        "id,username,password,role,riwayat_penyakit,suhu_tubuh,"
        "tekanan_darah_sistolik,tekanan_darah_diastolik,detak_jantung,"
        "saturasi_oksigen,kadar_gula_darah,berat_badan,tinggi_badan,"
        "kadar_kolesterol,kadar_kolesterol_ldl,trombosit\n");

    for (int i = 0; i < tulis.jumlahuser; i++) {
        User u = tulis.users[i];
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
