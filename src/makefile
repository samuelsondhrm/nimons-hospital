# Lokasi Makefile: src/makefile

# ---------------------- Variabel Konfigurasi ----------------------
# Kompiler yang digunakan
CC = gcc

# Flag untuk kompiler:
# -g : untuk informasi debug
# -Wall : untuk menampilkan semua warning
# -Iheader : menambah direktori 'header' sebagai search path untuk #include "file.h"
# -Iheader/ADT : menambah direktori 'header/ADT' sebagai search path
CFLAGS = -g -Wall -Iheader -Iheader/ADT

# Flag untuk linker (jika ada library tambahan, tambahkan di sini, misal -lm untuk math library)
LDFLAGS =

# Flag untuk menghasilkan dependensi otomatis (file .d)
# -MMD : Membuat file dependensi tanpa dependensi sistem
# -MP  : Membuat target fiktif untuk header agar make tidak error jika header dihapus
DEPFLAGS = -MMD -MP

# Direktori output untuk hasil build (file objek, executable)
# Karena Makefile ada di 'src/', '../build' akan menempatkan direktori 'build' di root proyek
BUILD_DIR = ../build

# Nama executable target
TARGET_NAME = main
TARGET_EXEC = $(BUILD_DIR)/$(TARGET_NAME)

# ---------------------- Mendefinisikan File Sumber dan Objek ----------------------
# File sumber utama (main.c)
MAIN_SRC = main.c

# File sumber dari direktori 'c/' dan 'c/ADT/'
# $(wildcard pattern) akan mencari semua file yang cocok dengan pattern
C_FILES = $(wildcard c/*.c)
ADT_FILES = $(wildcard c/ADT/*.c)

# Gabungkan semua file sumber .c
SRCS = $(MAIN_SRC) $(C_FILES) $(ADT_FILES)

# Membuat daftar file objek (.o) dari file sumber (.c)
# Semua file objek akan ditempatkan di dalam $(BUILD_DIR) dengan struktur direktori yang sama
# Contoh:
#   main.c -> $(BUILD_DIR)/main.o
#   c/foo.c -> $(BUILD_DIR)/c/foo.o
#   c/ADT/bar.c -> $(BUILD_DIR)/c/ADT/bar.o
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Membuat daftar file dependensi (.d) dari file objek (.o)
DEPS = $(OBJS:.o=.d)

# ---------------------- Aturan (Rules) ----------------------

# Target default: 'all'. Akan dijalankan jika Anda hanya mengetik 'make'
# Target ini bergantung pada executable utama.
.PHONY: all
all: $(TARGET_EXEC)
	@echo "Build complete. Executable: $(TARGET_EXEC)"

# Aturan untuk linking:
# Membuat executable utama ($(TARGET_EXEC)) dari semua file objek ($(OBJS)).
$(TARGET_EXEC): $(OBJS)
	@echo "LD $^ -> $@"
	@mkdir -p $(@D) # Pastikan direktori untuk executable ada (@D adalah direktori dari $@)
	$(CC) $(LDFLAGS) $^ -o $@

# Aturan pola untuk kompilasi:
# Mengompilasi setiap file sumber (.c) menjadi file objek (.o) yang sesuai di $(BUILD_DIR).
# %.c : file sumber yang cocok
# $(BUILD_DIR)/%.o : file objek target
# $< : nama prerequisite pertama (file .c)
# $@ : nama target (file .o)
$(BUILD_DIR)/%.o: %.c
	@echo "CC $< -> $@"
	@mkdir -p $(@D) # Pastikan direktori untuk file objek ada
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Target untuk membersihkan hasil build
.PHONY: clean
clean:
	@echo "Cleaning build files..."
	rm -rf $(BUILD_DIR) # Hapus seluruh direktori build
	@echo "Clean complete."

# Menyertakan file-file dependensi yang telah dibuat secara otomatis.
# Tanda '-' di depan 'include' berarti make akan melanjutkan meskipun file dependensi tidak ditemukan (misalnya saat build pertama kali).
-include $(DEPS)