/* File: interface.h */
/* Fungsi fungsi yang digunakan untuk elemen interface main program*/
#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdio.h>
#include <string.h>
#include "ADT/user.h"
#ifdef _WIN32
#include <windows.h>  // buat Sleep()
#else
#include <unistd.h>   // buat  usleep()
#endif


#define MERAH     "\033[0;31m"
#define HIJAU   "\033[0;32m"
#define KUNING  "\033[0;33m"
#define BIRU    "\033[0;34m"
#define UNGU "\033[0;35m"
#define BIRU_M    "\033[0;36m"
#define PUTIH   "\033[1;37m"

// Fungsi buat clear terminal (cross-platform)
void clear_screen();

// Juga cross-platform, buat pause
void sleep_ms(int ms); 

// Animasi transisi teks
void animate_text(const char *text, int delay_ms);

// Fungsi buat print teks warna, pake kode ANSI (sudah didefine diatas untuk warna warna general)
void print_color(const char *text, const char *color_code);

// Fungsi untuk print header
void print_header(User active_user);

// Fungsi untuk print fungsi
void print_case(const char *func_name, User active_user);


#endif
