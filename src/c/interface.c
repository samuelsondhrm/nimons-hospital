#include "../header/interface.h"

// Fungsi buat clear screen (cross-platform)
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Fungsi delay dalam milidetik (cross-platform)
void sleep_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

// Fungsi untuk animasi teks (karakter per karakter)
void animate_text(const char *text, int delay_ms) {
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout); // pastikan langsung muncul
        sleep_ms(delay_ms);
    }
}

// Fungsi untuk print teks berwarna
void print_color(const char *text, const char *color_code) {
    printf("%s%s%s", color_code, text, PUTIH); // PUTIH untuk reset ke warna default
}

// Fungsi untuk print header dengan ASCII art dan judul
void print_header(User active_user) {
    // clear_screen();
    printf("					⠀⢐⠰⠠⠆⠀⠄⡆⠂⠴⠔⢢⠀⠢⠠⠠⠔⠂⡶⠐⠰⠠⠀⠆⠂⠦⠠⠂⠂⠀⠀⠰⠰⠐⠀⠠⠀⠒⠄⠠⠐⠀⠴⠰⠰⠀⠀⠆⠀⠀⢀⢀⠀⣀⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⡾⢯⣿⣿⣿⣿⣿⢿⣿⣶⣶⣦⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⢠⣴⣿⣿⡿⣾⣭⣷⣶⡿⠿⠿⠿⢿⣿⣯⣿⣻⡿⣿⣿⣷⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄⠠⠀⠀⠀⠀⠀⠀⠀⠀⣀⣼⣿⣿⣿⣷⣿⡟⠿⣍⢸⡆⠀⠒⣆⡠⢿⣏⠉⣿⡿⣿⣿⣾⣯⣿⣿⣿⣦⣄⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠀⠄⠠⠀⠂⠐⠀⠀⣠⣴⣿⣿⣿⣿⣿⡟⠳⣄⣠⠾⠻⣍⣉⠋⠉⢁⣽⣿⠓⢷⡟⢋⠉⠽⣿⣿⣿⣿⣿⣿⣷⣄⡀⠀⠀\n");
    printf("⠀⠀⠀Nimons⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀    ⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⠏⡀⢣⣀⣿⡧⠴⠞⢿⣉⣟⡛⢿⣿⣿⣶⣯⣝⠢⣝⡶⠁⠸⢻⣿⣿⣿⣿⣿⣷⡀⠀\n");
    printf("⠀⠀⠀L'Hôpital⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠐⠂⠀⠀⠀⠀⠀⠀      ⠀⠀⠀⠀⠀⢠⠇⣿⣿⠙⣿⣿⣄⠘⡆⠹⣁⣸⣴⠞⠛⢩⠛⠛⠿⠾⣯⣄⠀⢈⡿⢿⣀⡒⠦⢼⣿⣿⣿⣿⣿⣿⣿⣔\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   ⠀⠀⠀⠀⣀⣤⠒⣁⣀⣿⣿⣖⡹⡹⣿⡾⠿⣟⡛⠢⣜⢦⣀⣰⣿⣿⣷⣧⡀⡝⣿⣻⠽⠟⠺⣟⢻⢟⡁⣠⣿⣿⣿⣿⣿⣿\n");
    printf("⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀    ⣤⣴⠾⠿⠛⠛⠋⠉⣿⣿⣿⣿⣿⣿⣿⣿⣷⣆⣹⡟⣻⣽⣿⣿⣿⣿⣿⢿⣽⡳⣺⢿⠛⠻⢿⣯⡿⠼⣟⣉⣨⣿⣿⣿⣿⣾\n");
    printf("⠀                                ⠉⠉⠹⣆⠀⠈⠑⠀⠀⠀⢸⠿⣻⠛⢛⠿⢯⡟⠛⢻⠻⢿⣿⣿⣿⣿⣟⣹⣿⣷⣶⣎⣿⠌⠸⡦⠆⣸⣆⣙⢶⣬⡭⠴⢾⣿⣿⣿⢿\n");
    printf("⠀                        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣦⡀⠀⢁⣰⠃⠀⠈⠦⣀⣀⡀⠙⢦⣸⠄⢈⣿⣿⣿⣿⣿⣽⡄⠘⣿⣿⣿⣧⣶⡷⣾⣩⡬⠻⣟⢙⣤⣶⣿⣿⣿⣿⢸\n");
    printf("              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣱⣽⢿⣺⠳⣄⠀⠀⠀⠈⠛⢅⣤⣀⣿⣮⣉⣿⣗⣦⣿⠿⠟⠀⡄⣿⣼⣿⣿⣿⣿⠿⠿⠿⠿⣿⠯⣥⣾⣿⣿⣿⣿⢾\n");
    printf("            ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢺⡱⠛⠃⠈⠀⢀⡉⣓⠲⢄⣀⠠⠈⣿⣿⣿⣷⣽⣿⣻⣿⡇⠀⢀⠀⠁⣿⡿⣹⢌⠹⣿⣷⢶⣜⢂⠘⣧⣉⣽⣿⣿⣿⣿⣾\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀    ⠀⢸⡉⢳⣔⠂⠂⡉⠉⡉⠉⠓⢦⣈⠛⣷⣾⣿⣛⢛⣿⣭⣥⣿⣇⣠⠀⠀⣼⣿⠧⠘⠘⢾⣟⣿⣧⡝⢿⠀⢾⢋⣿⣿⣿⡏⢛⡟\n");
    printf("⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠉⠁⠀⠀⠀⠀⣼⡿⢏⠉⠃⠀⠃⠀⠀⠉⠑⢦⠙⢦⠀⢳⠐⡞⣼⡿⣾⣧⣻⣿⣃⠀⣴⢿⠈⠀⠀⢠⠅⠐⢿⣿⣧⡈⠳⢾⣿⣿⡿⡟⢄⡾⠁\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠈⠀⠀⠀⠀⣠⠟⢀⡇⠘⢆⠀⠘⠀⠀⠀⠀⠂⠈⢣⣸⡆⠀⣿⢻⣿⠁⢩⣿⣭⣿⠀⢰⣿⣿⣳⣤⣆⣀⣇⣰⣿⢿⣿⣶⣶⡿⣿⣫⠟⣌⡾⠁⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣿⢠⠋⠀⠀⢈⠻⣄⠀⠀⠀⠀⠀⠀⢈⣥⣇⣸⢏⣿⡇⢀⡞⠁⢸⣿⢰⣻⡟⣿⣿⠿⣿⠋⢩⣾⡿⠞⠋⠋⠁⠀⣛⣠⣾⠟⠁⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣈⣤⠤⠚⠭⠱⣆⡀⠀⠀⠀⢀⡠⠎⣸⢿⣿⣼⣽⠁⡞⠁⠀⣼⠏⢯⣿⠟⠁⠁⣤⣤⣄⠈⣁⣀⡀⠀⠀⣠⠞⣩⡾⠋⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠓⠲⠶⠤⣖⠶⠿⠑⠁⢠⠞⠀⠰⠃⣸⢣⣿⡟⡜⠀⠀⣼⡿⠀⣼⠏⡄⠈⠀⠀⠈⠉⠙⠋⣠⠗⢚⣛⣁⡼⠋⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄⠀⠀⡀⠀⡄⢀⠀⠀⠀⠀⠀⠀⠀⠈⢳⡄⠀⣴⠃⠀⠀⣠⠞⢹⣿⣿⠳⠆⠐⢠⢿⠃⢰⡿⠋⠀⡀⠀⠀⠀⠀⢀⣰⢣⡖⠛⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠈⡇⡾⠀⡀⣠⡾⢃⡴⣿⡟⣿⡆⠀⠄⢰⡿⠀⡾⠓⠀⠀⠀⠀⠀⠀⢀⣾⢣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf(" ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠐⠐⠐⠀⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡿⡥⡬⣟⡉⢠⣥⣾⣽⣿⡁⠀⠀⠒⣾⠧⢸⡇⠐⠀⠱⡀⠀⢦⠀⣼⣯⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⢡⣯⠀⠉⠉⠀⣿⢹⡿⠰⠀⠀⠀⣾⠁⡿⢋⠄⠀⠀⠱⣄⣸⣿⠟⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡌⢻⠷⠦⠀⣠⡇⢸⣧⠛⠉⠉⢳⣏⢸⡿⠭⡈⠀⠀⢀⠘⢹⢿⣾⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⡾⢯⣿⣿⣿⣿⣿⢿⣿⣶⣶⣦⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("===========================================================================================\n");
    print_color("ACTIVE USER: ", HIJAU);
    printf("\n");
    if(active_user.id <= 0){
        print_color("NOT SIGNED IN\n", MERAH);
    }
    else{
    print_color(USERNAME(active_user), BIRU_M);
    printf(" (");
    if(strcmp(ROLE(active_user), "pasien") == 0) print_color("PASIEN", KUNING);
    else if(strcmp(ROLE(active_user), "dokter") == 0) print_color("DOKTER", BIRU);
    else if(strcmp(ROLE(active_user), "manager") == 0) print_color("MANAGER", UNGU);
    else print_color("INVALID ROLE", MERAH);
    printf(")\n");
    }
}

void print_case(const char *func_name, User active_user){
    print_header(active_user);
    animate_text(func_name, 100);
    printf("\n");
}

boolean accessCheck(const char* required_role, User request) {
    if (strcmp(required_role, ROLE(request)) != 0) {
        printf("Hanya bisa diakses: ");
        if(strcmp(required_role, "pasien") == 0) print_color("PASIEN", KUNING);
        else if(strcmp(required_role, "dokter") == 0) print_color("DOKTER", BIRU);
        else if(strcmp(required_role, "manager") == 0) print_color("MANAGER", UNGU);
        printf("\n");
        printf("Sementara kamu adalah: ", ROLE(request));
        if(strcmp(ROLE(request), "pasien") == 0) print_color("PASIEN", KUNING);
        else if(strcmp(ROLE(request), "dokter") == 0) print_color("DOKTER", BIRU);
        else if(strcmp(ROLE(request), "manaager") == 0) print_color("MANAGER", UNGU);
        else print_color("AKUN TIDAK VALID", MERAH);
        printf("\n");   
        while (getchar() != '\n');
        return false;
    }
    return true;
}