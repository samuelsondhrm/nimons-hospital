#ifndef LUPAPASSWORD_H
#define LUPAPASSWORD_H

#include "ADT/user.h"
#include "Boolean.h"

/*
Dapat mengganti password user.
Validasi dilakukan dengan mencocokkan Run-Length Encoding, Case Sensitive dari username.
*/

void lupaPassword(ListUser *LU);

#endif
