#ifndef EXIT_H
#define EXIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/save.h"
#include "../header/ADT/user.h"

#include "../header/csv_parser.h"
#include "../header/parser_config_txt.h"


void exitProgram(ListUser listuser, ListObat Listobat, ListPenyakit Listpenyakit, ListFormula listformula);
// Prosedur untuk menyimpan data ke dalam file

#endif