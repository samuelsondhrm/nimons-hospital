#include "../header/csv_parser.h"
#include "../header/Boolean.h"

boolean usernameFound(const char *username, const char *filename); 

void runLengthEncoding(const char *username, char *username_encoded);

boolean kodeUnik(const char *username_dicari, const char *kode);

void getRole(const char *username_dicari, const char *filename, char *role);

void updatePassword(const char *username_dicari, const char *password_baru, const char *filename);

void lupaPass();