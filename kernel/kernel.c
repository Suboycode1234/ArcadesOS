// ArcadeOS - First Kernel

typedef unsigned short uint16_t;

void clear_screen() {
    uint16_t* video = (uint16_t*)0xB8000;

    for (int i = 0; i < 80 * 25; i++) {
        video[i] = (0x0F << 8) | ' ';
    }
}

void print(const char* str) {
    uint16_t* video = (uint16_t*)0xB8000;

    for (int i = 0; str[i] != '\0'; i++) {
        video[i] = (0x0F << 8) | str[i];
    }
}

void kmain() {
    clear_screen();

    print("=== ARCADE OS ===");
    print("1. START GAME");
    print("2. SETTINGS");
    print("3. EXIT");

    while (1) {
        // OS stays alive here
    }
}