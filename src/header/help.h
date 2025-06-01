#ifndef HELP_H
#define HELP_H

#include <stdio.h>
#include "..\header\ADT\user.h"
#include <stdlib.h>
#include "..\header\login.h"

void helpManager(User u);
// Print fitur apa saja yang bisa diakses oleh Manager
void helpPasien(User u);
// Print fitur apa saja yang bisa diakses oleh Pasien
void helpDokter(User u);
// Print fitur apa saja yang bisa diakses oleh Dokter
void notLogin();
// Menangani kasus jika user belum login
void templateHelp(User u);
// Template header dan footnote dari fitur help

#endif