#ifndef LIHATUSER_H
#define LIHATUSER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ADT/user.h"

// Convert string to lowercase for case-insensitive compare
void toLowerCase(char *dest, const char *src);

// Swap two User elements
void swapUser(User *a, User *b);

// Sort array of User by ID or username
void sortUsers(User arr[], int n, int byId, int asc);

// Display format functions
void displayHeader(int mode);

void displayUser(const User *u, int mode);

// Core function to handle LIHAT_USER, LIHAT_PASIEN, LIHAT_DOKTER
void lihatUser(ListUser *lUser, int mode);

#endif