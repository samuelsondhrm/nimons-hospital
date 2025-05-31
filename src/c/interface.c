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
    clear_screen();
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
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡌⢻⠷⠦⠀⣠⡇⢸⣧⠛⠉⠉⢳⣏⢸⡿⠭⡈⠀⠀⢀⠘⢹⢿⣾⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    print_color("ACTIVE USER:\t", HIJAU);
    if(ID(active_user) <= 0){
        print_color("NOT SIGNED IN", MERAH);
    }
    else{
    print_color(USERNAME(active_user), BIRU_M);
    printf(" (");
    if(ROLE(active_user) == "pasien") print_color("pasien", KUNING);
    else if(ROLE(active_user) == "dokter") print_color("dokter", BIRU);
    else if(ROLE(active_user) == "manager") print_color("MANAGER", UNGU);
    else print_color("INVALID ROLE", MERAH);
    printf(")\n");
    }
}

void print_case(const char *func_name, User active_user){
    print_header(active_user);
    animate_text(func_name, 100);
    printf("\n");
}