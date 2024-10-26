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
  
void Game(struct Human *human, struct Ork *ork) {
    IMG_Init(IMG_INIT_PNG);
    
    // Pencereyi oluştur
    SDL_Window* window = SDL_CreateWindow("Human vs Ork", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 800, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* squareTexture = loadTexture("images/texture.png", renderer);
    SDL_Texture* background = loadTexture("images/background.png", renderer);
    SDL_Texture* alparslanTexture = loadTexture("images/alparslan.png", renderer);
    SDL_Texture* archerTexture = loadTexture("images/archer.png", renderer);
    SDL_Texture* atesiblisiTexture = loadTexture("images/atesiblisi.png", renderer);
    SDL_Texture* camurdevTexture = loadTexture("images/camurdev.png", renderer);
    SDL_Texture* cavalryTexture = loadTexture("images/cavalry.png", renderer);
    SDL_Texture* devTexture = loadTexture("images/dev.png", renderer);
    SDL_Texture* ejderTexture = loadTexture("images/ejder.png", renderer);
    SDL_Texture* fatih_sultanTexture = loadTexture("images/fatih_sultan.png", renderer);
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
    SDL_Texture* karakurtTexture = loadTexture("images/karakurt.png", renderer);
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
    SDL_Texture* deadPiyadeTexture = loadTexture("images/deadPiyade.png", renderer);
    SDL_Texture* deadOkcuTexture = loadTexture("images/deadOkcu.png", renderer);
    SDL_Texture* deadSuvariTexture = loadTexture("images/deadSuvari.png", renderer);
    SDL_Texture* deadKusatmaTexture = loadTexture("images/deadKusatma.png", renderer);
    SDL_Texture* deadOrkTexture = loadTexture("images/deadOrk.png", renderer);
    SDL_Texture* deadMizrakciTexture = loadTexture("images/deadMizrakci.png", renderer);
    SDL_Texture* deadVargTexture = loadTexture("images/deadVarg.png", renderer);
    SDL_Texture* deadTrollTexture = loadTexture("images/deadTroll.png", renderer);

    // Izgara üzerinde kareler çizmek için başlangıç konumunu hesapla
    int startX = (1300 - (GRID_COLS * SQUARE_SIZE)) / 2;
    int startY = (800 - (GRID_ROWS * SQUARE_SIZE)) / 2;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            int x = startX + col * SQUARE_SIZE;
            int y = startY + row * SQUARE_SIZE;
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
        if(tempPiyade == 0) {

        }
        else if(tempPiyade < 100) {
            drawHuman(renderer, deadPiyadeTexture, startX + 0 * SQUARE_SIZE, startY * currentHumanRow);
        }
        else {
            for(int i = 0; i < (tempPiyade / 100) + 1; i++) {
                drawHuman(renderer, deadPiyadeTexture, startX + 0 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
                currentHumanRow++;
            }
        }
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
        if(tempOkcu == 0) {
            
        }
        else if(tempOkcu < 100) {
            drawHuman(renderer, deadOkcuTexture, startX + 1 * SQUARE_SIZE, startY * currentHumanRow);
        }
        else {
            for(int i = 0; i < (tempOkcu / 100) + 1; i++) {
                drawHuman(renderer, deadOkcuTexture, startX + 1 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
                currentHumanRow++;
            }
        }
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
        if(tempSuvari == 0) {
            
        }
        else if(tempSuvari < 100) {
            drawHuman(renderer, deadSuvariTexture, startX + 2 * SQUARE_SIZE, startY * currentHumanRow);
        }
        else {
            for(int i = 0; i < (tempSuvari / 100) + 1; i++) {
                drawHuman(renderer, deadSuvariTexture, startX + 2 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
                currentHumanRow++;
            }
        }
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
        if(tempKusatmaMakineleri == 0) {
            
        }
        else if(tempKusatmaMakineleri < 100) {
            drawHuman(renderer, deadKusatmaTexture, startX + 3 * SQUARE_SIZE, startY * currentHumanRow);
        }
        else {
            for(int i = 0; i < (tempKusatmaMakineleri / 100) + 1; i++) {
                drawHuman(renderer, deadKusatmaTexture, startX + 3 * SQUARE_SIZE, startY + SQUARE_SIZE * currentHumanRow);
                currentHumanRow++;
            }
        }
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
        if(tempOrkDovusculeri == 0) {
            
        }
        else if(tempOrkDovusculeri < 100) {
            drawHuman(renderer, deadOrkTexture, startX + 9 * SQUARE_SIZE, startY * currentOrkRow);
        }
        else {
            for(int i = 0; i < (tempOrkDovusculeri / 100) + 1; i++) {
                drawHuman(renderer, deadOrkTexture, startX + 9 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
                currentOrkRow++;
            }
        }
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
        if(tempMizrakcilar == 0) {
            
        }
        else if(tempMizrakcilar < 100) {
            drawHuman(renderer, deadMizrakciTexture, startX + 8 * SQUARE_SIZE, startY * currentOrkRow);
        }
        else {
            for(int i = 0; i < (tempMizrakcilar / 100) + 1; i++) {
                drawHuman(renderer, deadMizrakciTexture, startX + 8 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
                currentOrkRow++;
            }
        }
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
        if(tempVargBinicileri == 0) {
            
        }
        else if(tempVargBinicileri < 100) {
            drawHuman(renderer, deadVargTexture, startX + 7 * SQUARE_SIZE, startY * currentOrkRow);
        }
        else {
            for(int i = 0; i < (tempVargBinicileri / 100) + 1; i++) {
                drawHuman(renderer, deadVargTexture, startX + 7 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
                currentOrkRow++;
            }
        }
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
        if(tempTroller == 0) {
            
        }
        else if(tempTroller < 100) {
            drawHuman(renderer, deadTrollTexture, startX + 6 * SQUARE_SIZE, startY * currentOrkRow);
        }
        else {
            for(int i = 0; i < (tempTroller / 100) + 1; i++) {
                drawHuman(renderer, deadTrollTexture, startX + 6 * SQUARE_SIZE, startY + SQUARE_SIZE * currentOrkRow);
                currentOrkRow++;
            }
        }
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
        drawHuman(renderer, alparslanTexture, 30, 600);
    }
    else if(strcmp(human->hero, "Fatih_Sultan_Mehmet") == 0) {
        drawHuman(renderer, fatih_sultanTexture, 30, 600);
    }
    else if(strcmp(human->hero, "Mete_Han") == 0) {
        drawHuman(renderer, metehanTexture, 30, 600);
    }
    else if(strcmp(human->hero, "Tugrul_Bey") == 0) {
        drawHuman(renderer, tugrulTexture, 30, 600);
    }
    else if(strcmp(human->hero, "Yavuz_Sultan_Selim") == 0) {
        drawHuman(renderer, yavuz_sultanTexture, 30, 600);
    }

    if(strcmp(human->creature, "Ejderha") == 0) {
        drawHuman(renderer, ejderTexture, 130, 600);
    }
    else if(strcmp(human->creature, "Agri_Dagi_Devleri") == 0) {
        drawHuman(renderer, devTexture, 130, 600);
    }
    else if(strcmp(human->creature, "Karakurt") == 0) {
        drawHuman(renderer, karakurtTexture, 130, 600);
    }
    else if(strcmp(human->creature, "Samur") == 0) {
        drawHuman(renderer, samurTexture, 130, 600);
    }
    else if(strcmp(human->creature, "Tepegoz") == 0) {
        drawHuman(renderer, tepegozTexture, 130, 600);
    }

    if(strcmp(ork->hero, "Goruk_Vahsi") == 0) {
        drawOrk(renderer, gorukTexture, 1080, 600);
    }
    else if(strcmp(ork->hero, "Thruk_Kemikkiran") == 0) {
        drawOrk(renderer, kemik_kiranTexture, 1080, 600);
    }
    else if(strcmp(ork->hero, "Vrog_Kafakiran") == 0) {
        drawOrk(renderer, kafa_kiranTexture, 1080, 600);
    }
    else if(strcmp(ork->hero, "Ugar_Zalim") == 0) {
        drawOrk(renderer, zalimTexture, 1080, 600);
    }

    if(strcmp(ork->creature, "Kara_Troll") == 0) {
        drawOrk(renderer, karatrollTexture, 1180, 600);
    }
    else if(strcmp(ork->creature, "Golge_Kurtlari") == 0) {
        drawOrk(renderer, golge_kurtlarıTexture, 1180, 600);
    }
    else if(strcmp(ork->creature, "Camur_Devleri") == 0) {
        drawOrk(renderer, camurdevTexture, 1180, 600);
    }
    else if(strcmp(ork->creature, "Ates_Iblisi") == 0) {
        drawOrk(renderer, atesiblisiTexture, 1180, 600);
    }
    else if(strcmp(ork->creature, "Makrog_Savas_Beyi") == 0) {
        drawOrk(renderer, savas_beyiTexture, 1180, 600);
    }
    else if(strcmp(ork->creature, "Buz_Devleri") == 0) {
        drawOrk(renderer, buzdevTexture, 1180, 600);
    }

    SDL_RenderPresent(renderer);
    SDL_Event event;
    int running = 1;
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
    SDL_DestroyTexture(deadPiyadeTexture);
    SDL_DestroyTexture(okcu100);
    SDL_DestroyTexture(okcu80);
    SDL_DestroyTexture(okcu50);
    SDL_DestroyTexture(okcu30);
    SDL_DestroyTexture(okcu10);
    SDL_DestroyTexture(okcu0);
    SDL_DestroyTexture(deadOkcuTexture);
    SDL_DestroyTexture(suvari100);
    SDL_DestroyTexture(suvari80);
    SDL_DestroyTexture(suvari50);
    SDL_DestroyTexture(suvari30);
    SDL_DestroyTexture(suvari10);
    SDL_DestroyTexture(suvari0);
    SDL_DestroyTexture(deadSuvariTexture);
    SDL_DestroyTexture(makine100);
    SDL_DestroyTexture(makine80);
    SDL_DestroyTexture(makine50);
    SDL_DestroyTexture(makine30);
    SDL_DestroyTexture(makine10);
    SDL_DestroyTexture(makine0);
    SDL_DestroyTexture(deadKusatmaTexture);
    SDL_DestroyTexture(ork100);
    SDL_DestroyTexture(ork80);
    SDL_DestroyTexture(ork50);
    SDL_DestroyTexture(ork30);
    SDL_DestroyTexture(ork10);
    SDL_DestroyTexture(ork0);
    SDL_DestroyTexture(deadOrkTexture);
    SDL_DestroyTexture(mizrakci100);
    SDL_DestroyTexture(mizrakci80);
    SDL_DestroyTexture(mizrakci50);
    SDL_DestroyTexture(mizrakci30);
    SDL_DestroyTexture(mizrakci10);
    SDL_DestroyTexture(mizrakci0);
    SDL_DestroyTexture(deadMizrakciTexture);
    SDL_DestroyTexture(varg100);
    SDL_DestroyTexture(varg80);
    SDL_DestroyTexture(varg50);
    SDL_DestroyTexture(varg30);
    SDL_DestroyTexture(varg10);
    SDL_DestroyTexture(varg0);
    SDL_DestroyTexture(deadVargTexture);
    SDL_DestroyTexture(troll100);
    SDL_DestroyTexture(troll80);
    SDL_DestroyTexture(troll50);
    SDL_DestroyTexture(troll30);
    SDL_DestroyTexture(troll10);
    SDL_DestroyTexture(troll0);
    SDL_DestroyTexture(deadTrollTexture);
    SDL_DestroyTexture(background);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

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