#ifndef LIHATUSER_H
#define LIHATUSER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ADT/user.h"
#include "cariuser.h"

// Core function to handle LIHAT_USER, LIHAT_PASIEN, LIHAT_DOKTER
void lihatUser(ListUser *lUser, int mode);

#endif