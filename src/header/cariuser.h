#ifndef CARIUSER_H
#define CARIUSER_H

/*

3 PROSEDUR PEMANGGILAN:
    cariUser(&lu);
    cariPasien(&lu);
    cariDokter(&lu);

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ADT/user.h"

void toLowerCase(char *dest, const char *src);

void swapUser(User *a, User *b);

void sortUsers(User arr[], int n, int byId, int asc);

int binarySearchById(User arr[], int n, int id);

int sequentialSearchByName(User arr[], int n, const char *name);

int searchPatientsByDisease(User arr[], int n, const char *disease, int result[]);

void displayHeader(int mode);

void displayUser(const User *u, int mode);

void cariUser(ListUser *lu);

void cariPasien(ListUser *lu);

void cariDokter(ListUser *lu);

#endif