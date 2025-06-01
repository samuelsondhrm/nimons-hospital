#include <stdio.h>
#include "..\header\ADT\user.h"
#include <stdlib.h>
#include "..\header\login.h"

void helpManager(User u){
    printf("Halo manager %s." , u.username);
    printf(" Kenapa kamu memanggil command HELP? Kan kamu manager, tapi\nyasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan\nsekarang: \n");
    printf("1. LOGOUT : Keluar dari akun yang sedang digunakan\n");
    printf("2. LUPA_PASSWORD : Melakukan update password\n");
    printf("3. LIHAT_DENAH : Melihat denah ruangan\n");
    printf("4. LIHAT_RUANGAN <nama_ruang> : Melihat ruangan. nama_ruang : A1 , A2 dst\n");
    printf("5. LIHAT_USER : Melihat data seluruh pengguna\n");
    printf("6. CARI_USER : Mencari data pengguna secara spesifik\n");
    printf("7. LIHAT_SEMUA_ANTRIAN : Melihat seluruh rincian di seluruh ruangan\n");
    printf("8. TAMBAH_DOKTER : Menambahkan dokter baru\n");
    printf("9. EXIT : Keluar dari program\n");
} 

void helpPasien(User u){
    printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut\nadalah hal-hal yang dapat kamu lakukan sekarang:\n" , u.username);
    printf("1. LOGOUT : Keluar dari akun yang sedang digunakan\n");
    printf("2. LUPA_PASSWORD : Melakukan update password\n");
    printf("3. LIHAT_DENAH : Melihat denah ruangan\n");
    printf("4. LIHAT_RUANGAN <nama_ruang> : Melihat ruangan. nama_ruang : A1 , A2 dst\n");
    printf("5. PULANGDOK : Akyu boleh pulang ga, dok? >////<\n");
    printf("6. DAFTAR_CHECKUP : Mendaftar untuk melakukan check-up dengan dokter\n");
    printf("7. ANTRIAN : Melihat status antrian\n");
    printf("8. MINUM_OBAT : Minum obatttt\n");
    printf("9. PENAWAR : Penawar khusus jika kamu salah minum obat\n");
    printf("9. EXIT: \n");
}

void helpDokter(User u){
    printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut\nadalah hal-hal yang dapat kamu lakukan sekarang:\n" , u.username);
    printf("1. LOGOUT : Keluar dari akun yang sedang digunakan\n");
    printf("2. LUPA_PASSWORD : Melakukan update password\n");
    printf("3. LIHAT_DENAH : Melihat denah ruangan\n");
    printf("4. LIHAT_RUANGAN <nama_ruang> : Melihat ruangan. nama_ruang : A1 , A2 dst\n");
    printf("5. DIAGNOSIS : Auto-Diagnose-2.0 ; Diagnosis secara otomatis!\n");
    printf("6. NGOBATIN : Auto-Prescription-2.0 ; Sistem peresepan obat\n");
    printf("7. EXIT : \n");
}


void notLogin(){
    printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n");
    printf("1. LOGIN : Masuk ke dalam akun yang sudah terdaftar\n");
    printf("2. REGISTER: Membuat akun baru\n");
}
void templateHelp(User u){
    printf("=========== HELP ===========\n\n");
    if(&u == NULL){
        notLogin();
    } 
    else{
        if(u.role == "pasien"){
            helpPasien(u);
        }
        else if(u.role == "dokter"){
            helpDokter(u);
        }
        else if(u.role == "manager"){
            helpManager(u);
        }
    }
    printf("Footnote:\n");
    printf("1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("2. Jangan lupa untuk memasukkan input yang valid\n");
}
