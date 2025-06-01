#include "../header/save.h"
#include "../header/csv_parser.h"

#ifdef _WIN32
#include <direct.h>
#define SEPARATOR '\\'
#else
#include <unistd.h>
#define SEPARATOR '/'
#endif

#define BASE_FOLDER "data"

// Membuat folder secara rekursif
int create_directory_recursive(const char *path) {
    char tmp[256];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);

    if (tmp[len - 1] == SEPARATOR) tmp[len - 1] = '\0';

    for (p = tmp + 1; *p; p++) {
        if (*p == SEPARATOR) {
            *p = '\0';
#ifdef _WIN32
            _mkdir(tmp);
#else
            mkdir(tmp, 0755);
#endif
            *p = SEPARATOR;
        }
    }
#ifdef _WIN32
    return _mkdir(tmp);
#else
    return mkdir(tmp, 0755);
#endif
}

// Mengecek apakah folder ada
int folder_exists(const char *path) {
#ifdef _WIN32
    struct _stat info;
    if (_stat(path, &info) != 0) return 0;
    return (info.st_mode & _S_IFDIR) != 0;
#else
    struct stat info;
    if (stat(path, &info) != 0) return 0;
    return S_ISDIR(info.st_mode);
#endif
}
void simpanConfigTxt(const char *filename, RumahSakit rs, Inventory *invntry) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Gagal membuka %s\n", filename);
        return;
    }

    // Baris 1: ukuran denah
    fprintf(file, "%d %d\n", rs.rows, rs.cols);

    // Baris 2: kapasitas per ruangan & kapasitas baris
    fprintf(file, "%d %d\n", rs.kapasitasPerRuangan, rs.kapasitasBaris);

    // Baris 3-8: state antrian tiap ruangan
    for (int i = 0; i < rs.rows; i++) {
        for (int j = 0; j < rs.cols; j++) {
            Ruangan ruang = rs.data[i][j];
            fprintf(file, "%d", ruang.dokterId);
            
            // Tulis ID pasien dalam ruangan
            Queue temp = ruang.antrianPasienIds;
            int len = lengthQueue(temp);
            for (int k = 0; k < len; k++) {
                int id;
                dequeue(&temp, &id);
                fprintf(file, " %d", id);
                enqueue(&temp, id); // Kembalikan ke queue
            }
            fprintf(file, "\n");
        }
    }

    // Baris 9: jumlah pasien dengan obat di inventory
    int countPasienObat = 0;
    for (int i = 0; i < invntry->jumlahPasienwObat; i++) {
        if (invntry->data[i].jumlahobat > 0) countPasienObat++;
    }
    fprintf(file, "%d\n", countPasienObat);

    // Baris 10-11: data obat di inventory tiap pasien
    for (int i = 0; i < invntry->jumlahPasienwObat; i++) {
        Pasien p = invntry->data[i];
        if (p.jumlahobat > 0) {
            fprintf(file, "%d", p.id);
            for (int j = 0; j < p.jumlahobat; j++) {
                fprintf(file, " %d", p.obat[j]);
            }
            fprintf(file, "\n");
        }
    }

    // Baris 12: jumlah pasien dengan obat di perut
    int countPasienPerut = 0;
    for (int i = 0; i < invntry->jumlahPasienwObat; i++) {
        if (!IsEmptyStack(invntry->data[i].perut)) countPasienPerut++;
    }
    fprintf(file, "%d\n", countPasienPerut);

    // Baris 13+: data obat di perut tiap pasien
    for (int i = 0; i < invntry->jumlahPasienwObat; i++) {
        Pasien p = invntry->data[i];
        if (!IsEmptyStack(p.perut)) {
            fprintf(file, "%d", p.id);
            Stack tempStack = p.perut;
            int tempArray[100];
            int idx = 0;
            
            // Ambil semua dari stack ke array
            while (!IsEmptyStack(tempStack)) {
                int val;
                Pop(&tempStack, &val);
                tempArray[idx++] = val;
            }
            
            // Tulis dari array (urutan terbalik)
            for (int j = idx - 1; j >= 0; j--) {
                fprintf(file, " %d", tempArray[j]);
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
}

// Prosedur utama save
void save_data(ListUser listuser, ListObat listobat, ListPenyakit listpenyakit, ListFormula listformula, RumahSakit rs, Inventory *inventory) {
    char folder_name[128];
    printf("Masukkan nama folder: ");
    if (fgets(folder_name, sizeof(folder_name), stdin) == NULL) {
        printf("Error membaca input!\n");
        return;
    }
    folder_name[strcspn(folder_name, "\n")] = '\0';

    char base_path[256];
    snprintf(base_path, sizeof(base_path), "%s", BASE_FOLDER);

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%c%s", BASE_FOLDER, SEPARATOR, folder_name);

    int base_exists = folder_exists(base_path);
    int folder_exists_flag = folder_exists(full_path);

    printf("Saving...\n");

    // Cek dan buat BASE_FOLDER jika belum ada
    if (!base_exists) {
        if (create_directory_recursive(base_path) == 0) {
            printf("Membuat folder %s...\n", base_path);
        } else {
            printf("Gagal membuat folder %s!\n", base_path);
            return;
        }
    }

    // Cek dan buat folder tujuan jika belum ada
    if (!folder_exists_flag) {
        if (create_directory_recursive(full_path) == 0) {
            printf("Membuat folder %s...\n", full_path);
        } else {
            printf("Gagal membuat folder %s!\n", full_path);
            return;
        }
    }

    // Tulis user.csv
    char user_csv_path[512];
    snprintf(user_csv_path, sizeof(user_csv_path), "%s%cuser.csv", full_path, SEPARATOR);
    tulis_user_csv(user_csv_path, &listuser);

    // Tulis obat.csv
    char obat_csv_path[512];
    snprintf(obat_csv_path, sizeof(obat_csv_path), "%s%cobat.csv", full_path, SEPARATOR);
    tulis_obat_csv(obat_csv_path, listobat);

    // Tulis penyakit.csv
    char penyakit_csv_path[512];
    snprintf(penyakit_csv_path, sizeof(penyakit_csv_path), "%s%cpenyakit.csv", full_path, SEPARATOR);
    tulis_penyakit_csv(penyakit_csv_path, listpenyakit);

    // Tulis obat_penyakit.csv
    char obatpenyakit_csv_path[512];
    snprintf(obatpenyakit_csv_path, sizeof(obatpenyakit_csv_path), "%s%cobat_penyakit.csv", full_path, SEPARATOR);
    tulis_obatpenyakit_csv(obatpenyakit_csv_path, listformula);

    char config_txt_path[512];
    snprintf(config_txt_path, sizeof(config_txt_path), "%s%cconfig.txt", full_path, SEPARATOR);
    simpanConfigTxt(config_txt_path, rs, inventory);



    printf("Berhasil menyimpan data di folder %s!\n", full_path);
}