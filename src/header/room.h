#define MAX_PASIEN 100
#define MAX_RUANGAN 100

typedef struct {
    int dokterId;            // 0 jika tidak ada dokter
    int pasienIds[10];       // max 10 pasien per ruangan
    int jumlahPasien;
} Ruangan;

typedef struct {
    int rows, cols;
    Ruangan data[26][99];    // Matrix 2D ruangan
    int kapasitasPerRuangan;
} RumahSakit;