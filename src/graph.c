#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "url.h"
#include "battle_mechanics.h"

#define GRID_COLS 10  // Sütun sayısı
#define GRID_ROWS 10  // Satır sayısı
#define SQUARE_SIZE 80 // Karelerin boyutu

SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer);
void drawSquareWithTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
void drawHealthBar(SDL_Renderer* renderer, SDL_Texture* healthTexture, int x, int y);
void drawHuman(SDL_Renderer* renderer, SDL_Texture* humanTexture, int x, int y);
void drawOrk(SDL_Renderer* renderer, SDL_Texture* orkTexture, int x, int y);

void StartScreen() {
    // SDL'yi başlat
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL başlatılamadı: %s\n", SDL_GetError());
    }

    // 1300x800 boyutunda bir pencere oluştur
    SDL_Window* window = SDL_CreateWindow("Human vs Ork", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        1300, 800, SDL_WINDOW_SHOWN);
    
    if (!window) {
        printf("Pencere oluşturulamadı: %s\n", SDL_GetError());
        SDL_Quit();
    }

    // Bir render oluştur
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer oluşturulamadı: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // Zamanlayıcı için başlangıç zamanı
    Uint32 start_time = SDL_GetTicks();
    int running = 1;
    
    while (running) {
        // Olay kontrolü
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Ekranı temizle
        SDL_SetRenderDrawColor(renderer, 255, 105, 180, 255);
        SDL_RenderClear(renderer);

        // Burada GIF çerçevesini çizebilirsiniz.

        // Ekranı güncelle
        SDL_RenderPresent(renderer);

        // 3 saniye geçene kadar bekle
        if (SDL_GetTicks() - start_time >= 3000) {
            running = 0; // 3 saniye dolunca döngüyü bitir
        }
    }

    // Temizleme
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game(struct Human *human, struct Ork *ork) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    
    // Pencereyi oluştur
    SDL_Window* window = SDL_CreateWindow("Human vs Ork", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 800, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Kare içine yerleştirilecek texture'ı yükle
    SDL_Texture* squareTexture = loadTexture("images/texture.png", renderer);
    SDL_Texture* background = loadTexture("images/background.png", renderer);
    // Sağlık barı için texture'ları yükle
    SDL_Texture* healthHigh = loadTexture("images/saglikYuksek.png", renderer);
    SDL_Texture* healthMedium = loadTexture("images/saglikOrta.png", renderer);
    SDL_Texture* healthLow = loadTexture("images/saglikDusuk.png", renderer);

    SDL_Texture* alparslanTexture = loadTexture("images/alparslan.png", renderer);
    SDL_Texture* archerTexture = loadTexture("images/archer.png", renderer);
    SDL_Texture* atesiblisiTexture = loadTexture("images/atesiblisi.png", renderer);
   // SDL_Texture* buzdeviTexture = loadTexture("images/buzdevi.jpeg", renderer);
    SDL_Texture* camurdevTexture = loadTexture("images/camurdev.png", renderer);
    SDL_Texture* cavalryTexture = loadTexture("images/cavalry.png", renderer);
    SDL_Texture* devTexture = loadTexture("images/dev.png", renderer);
    SDL_Texture* ejderTexture = loadTexture("images/ejder.png", renderer);
    SDL_Texture* fatih_sultanTexture = loadTexture("images/fatih_sultan.png", renderer);
   // SDL_Texture* golgekurtTexture = loadTexture("images/golgekurt.jpeg", renderer);
    SDL_Texture* gorukTexture = loadTexture("images/goruk.png", renderer);
    SDL_Texture* infantryTexture = loadTexture("images/infantry.png", renderer);
    SDL_Texture* kafa_kiranTexture = loadTexture("images/kafa_kiran.png", renderer);
    SDL_Texture* karatrollTexture = loadTexture("images/karatroll.png", renderer);
    SDL_Texture* kemik_kiranTexture = loadTexture("images/kemik_kiran.png", renderer);
    SDL_Texture* metehanTexture = loadTexture("images/metehan.png", renderer);
    SDL_Texture* ork_warriorTexture = loadTexture("images/ork_warrior.png", renderer);
    SDL_Texture* samurTexture = loadTexture("images/samur.png", renderer);
    SDL_Texture* savas_beyiTexture = loadTexture("images/savas_beyi.png", renderer);
    SDL_Texture* siege_machineTexture = loadTexture("images/siege_machine.png", renderer);
    SDL_Texture* spearmanTexture = loadTexture("images/spearman.png", renderer);
    SDL_Texture* tepegozTexture = loadTexture("images/tepegoz.png", renderer);
    SDL_Texture* trollTexture = loadTexture("images/troll.png", renderer);
    SDL_Texture* tugrulTexture = loadTexture("images/tugrul.png", renderer);
    SDL_Texture* warg_riderTexture = loadTexture("images/warg_rider.png", renderer);
    SDL_Texture* yavuz_sultanTexture = loadTexture("images/yavuz_sultan.png", renderer);
    SDL_Texture* zalimTexture = loadTexture("images/zalim.png", renderer);
    SDL_Texture* golge_kurtlarıTexture = loadTexture("images/golgekurt.png", renderer);
    SDL_Texture* buzdevTexture = loadTexture("images/buzdevi.png", renderer);
    SDL_Texture* karakurtTexture = loadTexture("images/karakurt.jpeg", renderer);
    SDL_Texture* piyade100 = loadTexture("images/piyade100.png", renderer);
    SDL_Texture* piyade80 = loadTexture("images/piyade80.png", renderer);
    SDL_Texture* piyade50 = loadTexture("images/piyade50.png", renderer);
    SDL_Texture* piyade30 = loadTexture("images/piyade30.png", renderer);
    SDL_Texture* piyade10 = loadTexture("images/piyade10.png", renderer);
    SDL_Texture* piyade0 = loadTexture("images/piyade0.png", renderer);
    SDL_Texture* okcu100 = loadTexture("images/okcu100.png", renderer);
    SDL_Texture* okcu80 = loadTexture("images/okcu80.png", renderer);
    SDL_Texture* okcu50 = loadTexture("images/okcu50.png", renderer);
    SDL_Texture* okcu30 = loadTexture("images/okcu30.png", renderer);
    SDL_Texture* okcu10 = loadTexture("images/okcu10.png", renderer);
    SDL_Texture* okcu0 = loadTexture("images/okcu0.png", renderer);
    SDL_Texture* suvari100 = loadTexture("images/suvari100.png", renderer);
    SDL_Texture* suvari80 = loadTexture("images/suvari80.png", renderer);
    SDL_Texture* suvari50 = loadTexture("images/suvari50.png", renderer);
    SDL_Texture* suvari30 = loadTexture("images/suvari30.png", renderer);
    SDL_Texture* suvari10 = loadTexture("images/suvari10.png", renderer);
    SDL_Texture* suvari0 = loadTexture("images/suvari0.png", renderer);
    SDL_Texture* makine100 = loadTexture("images/makine100.png", renderer);
    SDL_Texture* makine80 = loadTexture("images/makine80.png", renderer);
    SDL_Texture* makine50 = loadTexture("images/makine50.png", renderer);
    SDL_Texture* makine30 = loadTexture("images/makine30.png", renderer);
    SDL_Texture* makine10 = loadTexture("images/makine10.png", renderer);
    SDL_Texture* makine0 = loadTexture("images/makine0.png", renderer);
    SDL_Texture* ork100 = loadTexture("images/ork100.png", renderer);
    SDL_Texture* ork80 = loadTexture("images/ork80.png", renderer);
    SDL_Texture* ork50 = loadTexture("images/ork50.png", renderer);
    SDL_Texture* ork30 = loadTexture("images/ork30.png", renderer);
    SDL_Texture* ork10 = loadTexture("images/ork10.png", renderer);
    SDL_Texture* ork0 = loadTexture("images/ork0.png", renderer);
    SDL_Texture* mizrakci100 = loadTexture("images/mizrakci100.png", renderer);
    SDL_Texture* mizrakci80 = loadTexture("images/mizrakci80.png", renderer);
    SDL_Texture* mizrakci50 = loadTexture("images/mizrakci50.png", renderer);
    SDL_Texture* mizrakci30 = loadTexture("images/mizrakci30.png", renderer);
    SDL_Texture* mizrakci10 = loadTexture("images/mizrakci10.png", renderer);
    SDL_Texture* mizrakci0 = loadTexture("images/mizrakci0.png", renderer);
    SDL_Texture* varg100 = loadTexture("images/varg100.png", renderer);
    SDL_Texture* varg80 = loadTexture("images/varg80.png", renderer);
    SDL_Texture* varg50 = loadTexture("images/varg50.png", renderer);
    SDL_Texture* varg30 = loadTexture("images/varg30.png", renderer);
    SDL_Texture* varg10 = loadTexture("images/varg10.png", renderer);
    SDL_Texture* varg0 = loadTexture("images/varg0.png", renderer);
    SDL_Texture* troll100 = loadTexture("images/troll100.png", renderer);   
    SDL_Texture* troll80 = loadTexture("images/troll80.png", renderer);
    SDL_Texture* troll50 = loadTexture("images/troll50.png", renderer);
    SDL_Texture* troll30 = loadTexture("images/troll30.png", renderer);
    SDL_Texture* troll10 = loadTexture("images/troll10.png", renderer);
    SDL_Texture* troll0 = loadTexture("images/troll0.png", renderer);

    // Grid üzerinde kareler çizmek için başlangıç konumunu hesapla
    int startX = (1300 - (GRID_COLS * SQUARE_SIZE)) / 2; // X koordinatı için başlangıç
    int startY = (800 - (GRID_ROWS * SQUARE_SIZE)) / 2; // Y koordinatı için başlangıç

    // Render öncesi arka planı beyaz yap
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Beyaz
    SDL_RenderClear(renderer); // Ekranı temizle
    SDL_RenderCopy(renderer, background, NULL, NULL);

    // Grid üzerinde kareler çiz
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            int x = startX + col * SQUARE_SIZE; // X koordinatı
            int y = startY + row * SQUARE_SIZE; // Y koordinatı
            drawSquareWithTexture(renderer, squareTexture, x, y); // Texture ile kareyi çiz
        }
    }
    // Sağlık barlarını çiz
    drawHealthBar(renderer, (piyade_health > 80) ? piyade100 : (piyade_health > 50) ? piyade80 : (piyade_health > 30) ? piyade50 : (piyade_health > 10) ? piyade30 : (piyade_health > 0) ? piyade10 : piyade0, 10, 60);
    drawHealthBar(renderer, (okcu_health > 64) ? okcu100 : (okcu_health > 40) ? okcu80 : (okcu_health > 24) ? okcu50 : (okcu_health > 8) ? okcu30 : (okcu_health > 0) ? okcu10 : okcu0, 10, 120);
    drawHealthBar(renderer, (suvari_health > 96) ? suvari100 : (suvari_health > 60) ? suvari80 : (suvari_health > 36) ? suvari50 : (suvari_health > 12) ? suvari30 : (suvari_health > 0) ? suvari10 : suvari0, 10, 180);
    drawHealthBar(renderer, (kusatmaMakineleri_health > 120) ? makine100 : (kusatmaMakineleri_health > 75) ? makine80 : (kusatmaMakineleri_health > 45) ? makine50 : (kusatmaMakineleri_health > 15) ? makine30 : (kusatmaMakineleri_health > 0) ? makine10 : makine0, 10, 240);

    drawHealthBar(renderer, (orkDovusculeri_health > 80) ? ork100 : (orkDovusculeri_health > 50) ? ork80 : (orkDovusculeri_health > 30) ? ork50 : (orkDovusculeri_health > 10) ? ork30 : (orkDovusculeri_health > 0) ? ork10 : ork0, 1060, 60);
    drawHealthBar(renderer, (mizrakcilar_health > 72) ? mizrakci100 : (mizrakcilar_health > 45) ? mizrakci80 : (mizrakcilar_health > 27) ? mizrakci50 : (mizrakcilar_health > 9) ? mizrakci30 : (mizrakcilar_health > 0) ? mizrakci10 : mizrakci0, 1060, 120);
    drawHealthBar(renderer, (vargBinicileri_health > 104) ? varg100 : (vargBinicileri_health > 65) ? varg80 : (vargBinicileri_health > 39) ? varg50 : (vargBinicileri_health > 13) ? varg30 : (vargBinicileri_health > 0) ? varg10 : varg0, 1060, 180);
    drawHealthBar(renderer, (troller_health > 160) ? troll100 : (troller_health > 100) ? troll80 : (troller_health > 60) ? troll50 : (troller_health > 20) ? troll30 : (troller_health > 0) ? troll10 : troll0, 1060, 240);

    int currentHumanRow = 0;
    if(human->infantry_count == 0) {

    }
    else if(human->infantry_count < 100) {
        drawHuman(renderer, infantryTexture, startX + 0 * SQUARE_SIZE, startY * currentHumanRow);
    }
    for(int i = 0; i < human->infantry_count / 100; i++) {
        if(human->infantry_count % 100 == 0) {
            drawHuman(renderer, infantryTexture, startX + 0 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
            currentHumanRow++;
        }
        else {
            drawHuman(renderer, infantryTexture, startX + 0 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
            currentHumanRow++;
            drawHuman(renderer, infantryTexture, startX + 0 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
        }
        if(currentHumanRow >= 20) break;
    }


    currentHumanRow = 0;
    if(human->archer_count == 0) {

    }
    else if(human->archer_count < 100) {
        drawHuman(renderer, archerTexture, startX + 1 * SQUARE_SIZE, startY * currentHumanRow);
    }
    for(int i = 0; i < human->archer_count / 100; i++) {
        if(human->archer_count % 100 == 0) {
            drawHuman(renderer, archerTexture, startX + 1 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
            currentHumanRow++;
        }
        else {
            drawHuman(renderer, archerTexture, startX + 1 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
            currentHumanRow++;
            drawHuman(renderer, archerTexture, startX + 1 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
        }
        if(currentHumanRow >= 20) break;
    }

    currentHumanRow = 0;
    if(human->cavalry_count == 0) {

    }
    else if(human->cavalry_count < 100) {
        drawHuman(renderer, cavalryTexture, startX + 2 * SQUARE_SIZE, startY * currentHumanRow);
    }
    for(int i = 0; i < human->cavalry_count / 100; i++) {
        if(human->cavalry_count % 100 == 0) {
            drawHuman(renderer, cavalryTexture, startX + 2 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
            currentHumanRow++;
        }
        else {
            drawHuman(renderer, cavalryTexture, startX + 2 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
            currentHumanRow++;
            drawHuman(renderer, cavalryTexture, startX + 2 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
        }
        if(currentHumanRow >= 20) break;
    }

    currentHumanRow = 0;
    if(human->siege_count == 0) {

    }
    else if(human->siege_count < 100) {
        drawHuman(renderer, siege_machineTexture, startX + 3 * SQUARE_SIZE, startY * currentHumanRow);
    }
    for(int i = 0; i < human->siege_count / 100; i++) {
        if(human->siege_count % 100 == 0) {
            drawHuman(renderer, siege_machineTexture, startX + 3 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
            currentHumanRow++;
        }
        else {
            drawHuman(renderer, siege_machineTexture, startX + 3 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
            currentHumanRow++;
            drawHuman(renderer, siege_machineTexture, startX + 3 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
        }
        if(currentHumanRow >= 20) break;
    }

    int currentOrkRow = 0;
    if(ork->ork_warrior_count == 0) {

    }
    else if(ork->ork_warrior_count < 100) {
        drawOrk(renderer, ork_warriorTexture, startX + 9 * SQUARE_SIZE, startY * currentOrkRow);
    }
    for(int i = 0; i < ork->ork_warrior_count / 100; i++) {
        if(ork->ork_warrior_count % 100 == 0) {
            drawOrk(renderer, ork_warriorTexture, startX + 9 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
            currentOrkRow++;
        }
        else {
            drawOrk(renderer, ork_warriorTexture, startX + 9 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
            currentOrkRow++;
            drawOrk(renderer, ork_warriorTexture, startX + 9 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
        }
        if(currentOrkRow >= 20) break;
    }

    currentOrkRow = 0;
    if(ork->spearman_count == 0) {

    }
    else if(ork->spearman_count < 100) {
        drawOrk(renderer, spearmanTexture, startX + 8 * SQUARE_SIZE, startY * currentOrkRow);
    }
    for(int i = 0; i < ork->spearman_count / 100; i++) {
        if(ork->spearman_count % 100 == 0) {
            drawOrk(renderer, spearmanTexture, startX + 8 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
            currentOrkRow++;
        }
        else {
            drawOrk(renderer, spearmanTexture, startX + 8 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
            currentOrkRow++;
            drawOrk(renderer, spearmanTexture, startX + 8 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
        }
        if(currentOrkRow >= 20) break;
    }

    currentOrkRow = 0;
    if(ork->warg_rider_count == 0) {

    }
    else if(ork->warg_rider_count < 100) {
        drawOrk(renderer, warg_riderTexture, startX + 7 * SQUARE_SIZE, startY * currentOrkRow);
    }
    for(int i = 0; i < ork->warg_rider_count / 100; i++) {
        if(ork->warg_rider_count % 100 == 0) {
            drawOrk(renderer, warg_riderTexture, startX + 7 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
            currentOrkRow++;
        }
        else {
            drawOrk(renderer, warg_riderTexture, startX + 7 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
            currentOrkRow++;
            drawOrk(renderer, warg_riderTexture, startX + 7 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
        }
        if(currentOrkRow >= 20) break;
    }

    currentOrkRow = 0;
    if(ork->troll_count == 0) {

    }
    else if(ork->troll_count < 100) {
        drawOrk(renderer, trollTexture, startX + 6 * SQUARE_SIZE, startY * currentOrkRow);
    }
    for(int i = 0; i < ork->troll_count / 100; i++) {
        if(ork->troll_count % 100 == 0) {
            drawOrk(renderer, trollTexture, startX + 6 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
            currentOrkRow++;
        }
        else {
            drawOrk(renderer, trollTexture, startX + 6 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
            currentOrkRow++;
            drawOrk(renderer, trollTexture, startX + 6 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
        }
        if(currentOrkRow >= 20) break;
    }


    if(strcmp(human->hero, "Alparslan") == 0) {
        drawHuman(renderer, alparslanTexture, 50, 600);
    }
    else if(strcmp(human->hero, "Fatih_Sultan_Mehmet") == 0) {
        drawHuman(renderer, fatih_sultanTexture, 50, 600);
    }
    else if(strcmp(human->hero, "Mete_Han") == 0) {
        drawHuman(renderer, metehanTexture, 50, 600);
    }
    else if(strcmp(human->hero, "Tugrul_Bey") == 0) {
        drawHuman(renderer, tugrulTexture, 50, 600);
    }
    else if(strcmp(human->hero, "Yavuz_Sultan_Selim") == 0) {
        drawHuman(renderer, yavuz_sultanTexture, 50, 600);
    }

    if(strcmp(human->creature, "Ejderha") == 0) {
        drawHuman(renderer, ejderTexture, 150, 600);
    }
    else if(strcmp(human->creature, "Agri_Dagi_Devleri") == 0) {
        drawHuman(renderer, devTexture, 150, 600);
    }
    else if(strcmp(human->creature, "Karakurt") == 0) {
        drawHuman(renderer, karakurtTexture, 150, 600);
    }
    else if(strcmp(human->creature, "Samur") == 0) {
        drawHuman(renderer, samurTexture, 150, 600);
    }
    else if(strcmp(human->creature, "Tepegoz") == 0) {
        drawHuman(renderer, tepegozTexture, 150, 600);
    }


    if(strcmp(ork->hero, "Goruk_Vahsi") == 0) {
        drawOrk(renderer, gorukTexture, 1050, 600);
    }
    else if(strcmp(ork->hero, "Thruk_Kemikkiran") == 0) {
        drawOrk(renderer, kemik_kiranTexture, 1050, 600);
    }
    else if(strcmp(ork->hero, "Vrog_Kafakiran") == 0) {
        drawOrk(renderer, kafa_kiranTexture, 1050, 600);
    }
    else if(strcmp(ork->hero, "Ugar_Zalim") == 0) {
        drawOrk(renderer, zalimTexture, 1050, 600);
    }

    if(strcmp(ork->creature, "Kara_Troll") == 0) {
        drawOrk(renderer, karatrollTexture, 1150, 600);
    }
    else if(strcmp(ork->creature, "Golge_Kurtlari") == 0) {
        drawOrk(renderer, golge_kurtlarıTexture, 1150, 600);
    }
    else if(strcmp(ork->creature, "Camur_Devleri") == 0) {
        drawOrk(renderer, camurdevTexture, 1150, 600);
    }
    else if(strcmp(ork->creature, "Ates_Iblisi") == 0) {
        drawOrk(renderer, atesiblisiTexture, 1150, 600);
    }
    else if(strcmp(ork->creature, "Makrog_Savas_Beyi") == 0) {
        drawOrk(renderer, savas_beyiTexture, 1150, 600);
    }
    else if(strcmp(ork->creature, "Buz_Devleri") == 0) {
        drawOrk(renderer, buzdevTexture, 1150, 600);
    }




    SDL_RenderPresent(renderer);
    // SDL_Event event;
    // int running = 1;
    // while (running) {
    //     while (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_QUIT) {
    //             running = 0;
    //         }
    //     }
    // }

    SDL_Event event;
    int running = 1;

    // Başlangıç zamanı (milisaniye olarak)
    Uint32 start_time = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Geçen zamanı kontrol et
        Uint32 current_time = SDL_GetTicks();
        if (current_time - start_time > 5000) { // 5000 milisaniye = 5 saniye
            running = 0;
        }
    }
    
    SDL_DestroyTexture(squareTexture);
    SDL_DestroyTexture(healthHigh);
    SDL_DestroyTexture(healthMedium);
    SDL_DestroyTexture(healthLow);

    SDL_DestroyTexture(alparslanTexture);
    SDL_DestroyTexture(archerTexture);
    SDL_DestroyTexture(atesiblisiTexture);
    SDL_DestroyTexture(camurdevTexture);
    SDL_DestroyTexture(cavalryTexture);
    SDL_DestroyTexture(devTexture);
    SDL_DestroyTexture(ejderTexture);
    SDL_DestroyTexture(fatih_sultanTexture);
    SDL_DestroyTexture(gorukTexture);
    SDL_DestroyTexture(infantryTexture);
    SDL_DestroyTexture(kafa_kiranTexture);
    SDL_DestroyTexture(karatrollTexture);
    SDL_DestroyTexture(kemik_kiranTexture);
    SDL_DestroyTexture(metehanTexture);
    SDL_DestroyTexture(ork_warriorTexture);
    SDL_DestroyTexture(siege_machineTexture);
    SDL_DestroyTexture(spearmanTexture);
    SDL_DestroyTexture(tepegozTexture);
    SDL_DestroyTexture(trollTexture);
    SDL_DestroyTexture(tugrulTexture);
    SDL_DestroyTexture(warg_riderTexture);
    SDL_DestroyTexture(yavuz_sultanTexture);
    SDL_DestroyTexture(zalimTexture);
    SDL_DestroyTexture(piyade100);
    SDL_DestroyTexture(piyade80);
    SDL_DestroyTexture(piyade50);
    SDL_DestroyTexture(piyade30);
    SDL_DestroyTexture(piyade10);
    SDL_DestroyTexture(piyade0);
    SDL_DestroyTexture(okcu100);
    SDL_DestroyTexture(okcu80);
    SDL_DestroyTexture(okcu50);
    SDL_DestroyTexture(okcu30);
    SDL_DestroyTexture(okcu10);
    SDL_DestroyTexture(okcu0);
    SDL_DestroyTexture(suvari100);
    SDL_DestroyTexture(suvari80);
    SDL_DestroyTexture(suvari50);
    SDL_DestroyTexture(suvari30);
    SDL_DestroyTexture(suvari10);
    SDL_DestroyTexture(suvari0);
    SDL_DestroyTexture(makine100);
    SDL_DestroyTexture(makine80);
    SDL_DestroyTexture(makine50);
    SDL_DestroyTexture(makine30);
    SDL_DestroyTexture(makine10);
    SDL_DestroyTexture(makine0);
    SDL_DestroyTexture(ork100);
    SDL_DestroyTexture(ork80);
    SDL_DestroyTexture(ork50);
    SDL_DestroyTexture(ork30);
    SDL_DestroyTexture(ork10);
    SDL_DestroyTexture(ork0);
    SDL_DestroyTexture(mizrakci100);
    SDL_DestroyTexture(mizrakci80);
    SDL_DestroyTexture(mizrakci50);
    SDL_DestroyTexture(mizrakci30);
    SDL_DestroyTexture(mizrakci10);
    SDL_DestroyTexture(mizrakci0);
    SDL_DestroyTexture(varg100);
    SDL_DestroyTexture(varg80);
    SDL_DestroyTexture(varg50);
    SDL_DestroyTexture(varg30);
    SDL_DestroyTexture(varg10);
    SDL_DestroyTexture(varg0);
    SDL_DestroyTexture(troll100);
    SDL_DestroyTexture(troll80);
    SDL_DestroyTexture(troll50);
    SDL_DestroyTexture(troll30);
    SDL_DestroyTexture(troll10);
    SDL_DestroyTexture(troll0);
    SDL_DestroyTexture(background);
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

}


// int main(int argc, char* argv[]) {
//     // SDL_Init(SDL_INIT_VIDEO);
//     // IMG_Init(IMG_INIT_PNG);
    
//     // // Pencereyi oluştur
//     // SDL_Window* window = SDL_CreateWindow("Grid Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 800, 0);
//     // SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//     // // Kare içine yerleştirilecek texture'ı yükle
//     // SDL_Texture* squareTexture = loadTexture("images/texture.png", renderer);

//     // // Sağlık barı için texture'ları yükle
//     // SDL_Texture* healthHigh = loadTexture("images/saglikYuksek.png", renderer);
//     // SDL_Texture* healthMedium = loadTexture("images/saglikOrta.png", renderer);
//     // SDL_Texture* healthLow = loadTexture("images/saglikDusuk.png", renderer);

//     // // Grid üzerinde kareler çizmek için başlangıç konumunu hesapla
//     // int startX = (1300 - (GRID_COLS * SQUARE_SIZE)) / 2; // X koordinatı için başlangıç
//     // int startY = (800 - (GRID_ROWS * SQUARE_SIZE)) / 2; // Y koordinatı için başlangıç

//     // // Render öncesi arka planı beyaz yap
//     // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Beyaz
//     // SDL_RenderClear(renderer); // Ekranı temizle

//     // // Grid üzerinde kareler çiz
//     // for (int row = 0; row < GRID_ROWS; row++) {
//     //     for (int col = 0; col < GRID_COLS; col++) {
//     //         int x = startX + col * SQUARE_SIZE; // X koordinatı
//     //         int y = startY + row * SQUARE_SIZE; // Y koordinatı
//     //         drawSquareWithTexture(renderer, squareTexture, x, y); // Texture ile kareyi çiz
//     //     }
//     // }


//     // // Örnek sağlık değerleri
//     // int humanHealth = 85; // 100 üzerinden insan sağlığı
//     // int orkHealth = 30;    // 100 üzerinden ork sağlığı

//     // // Sağlık barlarını çiz
//     // drawHealthBar(renderer, (humanHealth >= 80) ? healthHigh : (humanHealth >= 40) ? healthMedium : healthLow, 10, 100);
//     // drawHealthBar(renderer, (orkHealth >= 80) ? healthHigh : (orkHealth >= 40) ? healthMedium : healthLow, 1035, 100);

//     // SDL_RenderPresent(renderer);
    
//     // SDL_Event event;
//     // int running = 1;
//     // while (running) {
//     //     while (SDL_PollEvent(&event)) {
//     //         if (event.type == SDL_QUIT) {
//     //             running = 0;
//     //         }
//     //     }
//     // }
    
//     // SDL_DestroyTexture(squareTexture);
//     // SDL_DestroyTexture(healthHigh);
//     // SDL_DestroyTexture(healthMedium);
//     // SDL_DestroyTexture(healthLow);
//     // SDL_DestroyRenderer(renderer);
//     // SDL_DestroyWindow(window);
//     // IMG_Quit();
//     // SDL_Quit();

//     // return 0;
//     struct Human human = {1000, 150, 150, 150, "Tugrul_Bey", "Karakurt"};
//     struct Ork ork = {205, 205, 205, 250, "Camurdev", "Camurdev"};
//     Game(&human, &ork);
// }

SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, file);
    if (!texture) {
        printf("Resim yüklenirken hata: %s\n", IMG_GetError());
        exit(1);
    }
    return texture;
}

void drawSquareWithTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = SQUARE_SIZE;
    destRect.h = SQUARE_SIZE;

    // Texture'ı kare boyutunda çiz
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void drawHealthBar(SDL_Renderer* renderer, SDL_Texture* healthTexture, int x, int y) {
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = 240; // Sağlık barı genişliği
    destRect.h = 60; // Sağlık barı yüksekliği

    // Sağlık barını çiz
    SDL_RenderCopy(renderer, healthTexture, NULL, &destRect);
}

void drawHuman(SDL_Renderer* renderer, SDL_Texture* humanTexture, int x, int y) {
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = 80;
    destRect.h = 80;

    SDL_RenderCopy(renderer, humanTexture, NULL, &destRect);
}

void drawOrk(SDL_Renderer* renderer, SDL_Texture* orkTexture, int x, int y) {
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = 80;
    destRect.h = 80;

    SDL_RenderCopy(renderer, orkTexture, NULL, &destRect);
}