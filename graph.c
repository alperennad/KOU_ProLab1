    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <stdio.h>
    #include <stdlib.h> // rand için gerekli
    #include <string.h>

    #define WINDOW_WIDTH 1000
    #define WINDOW_HEIGHT 1000
    #define GRID_SIZE 50  // Izgara hücre boyutu (piksel cinsinden)

    struct HumanCount {
        int infantry_count;
        int archer_count;
        int cavalry_count;
        int siege_count;
        char *hero;
    };

    struct OrkCount {
        int ork_warrior_count;
        int spearman_count;
        int warg_rider_count;
        int troll_count;
        char *hero;
    };

    void runGame(struct HumanCount* human, struct OrkCount* ork) {
        // SDL ve SDL_image başlat
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            printf("SDL başlatılamadı! SDL_Error: %s\n", SDL_GetError());
            return;
        }

        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            printf("SDL_image başlatılamadı! SDL_image Error: %s\n", IMG_GetError());
            SDL_Quit();
            return;
        }

        // Pencere oluştur
        SDL_Window* window = SDL_CreateWindow("Humans vs Orks",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            WINDOW_WIDTH, WINDOW_HEIGHT,
                                            SDL_WINDOW_SHOWN);
        if (!window) {
            printf("Pencere oluşturulamadı! SDL_Error: %s\n", SDL_GetError());
            SDL_Quit();
            return;
        }

        // Renderer (çizici) oluştur
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            printf("Renderer oluşturulamadı! SDL_Error: %s\n", SDL_GetError());
            SDL_DestroyWindow(window);
            SDL_Quit();
            return;
        }

        // Resimleri yükle
        SDL_Surface* archer = IMG_Load("images/archer.png");
        SDL_Surface* cavalry = IMG_Load("images/cavalry.png");
        SDL_Surface* infantry = IMG_Load("images/infantry.png");
        SDL_Surface* ork_warrior = IMG_Load("images/ork_warrior.png");
        SDL_Surface* siege_machine = IMG_Load("images/siege_machine.png");
        SDL_Surface* troll = IMG_Load("images/troll.png");
        SDL_Surface* warg_rider = IMG_Load("images/warg_rider.png");
        SDL_Surface* spearman = IMG_Load("images/spearman.png");

        SDL_Surface* alparslan = IMG_Load("images/alparslan.png");
        SDL_Surface* fatih_sultan = IMG_Load("images/fatih_sultan.png");
        SDL_Surface* goruk = IMG_Load("images/goruk.png");
        SDL_Surface* kafa_kiran = IMG_Load("images/kafa_kiran.png");
        SDL_Surface* kemik_kiran = IMG_Load("images/kemik_kiran.png");
        SDL_Surface* metehan = IMG_Load("images/metehan.png");
        SDL_Surface* tugrul = IMG_Load("images/tugrul.png");
        SDL_Surface* yavuz_sultan = IMG_Load("images/yavuz_sultan.png");
        SDL_Surface* zalim = IMG_Load("images/zalim.png");


        if (!archer || !cavalry || !infantry || !ork_warrior || !siege_machine || !troll || !warg_rider || !spearman || !alparslan || !fatih_sultan || !goruk || !kafa_kiran || !kemik_kiran || !metehan
        || !tugrul || !yavuz_sultan || !zalim
        ) {
            printf("Resim yüklenemedi! SDL_image Error: %s\n", IMG_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
            return;
        }

        SDL_Texture* cavalryTexture = SDL_CreateTextureFromSurface(renderer, cavalry);
        SDL_FreeSurface(cavalry);  // Artık yüzeye ihtiyacımız yok

        SDL_Texture* archerTexture = SDL_CreateTextureFromSurface(renderer, archer);
        SDL_FreeSurface(archer); 

        SDL_Texture* infantryTexture = SDL_CreateTextureFromSurface(renderer, infantry);
        SDL_FreeSurface(infantry); 

        SDL_Texture* ork_warriorTexture = SDL_CreateTextureFromSurface(renderer, ork_warrior);
        SDL_FreeSurface(ork_warrior); 

        SDL_Texture* siege_machineTexture = SDL_CreateTextureFromSurface(renderer, siege_machine);
        SDL_FreeSurface(siege_machine); 

        SDL_Texture* trollTexture = SDL_CreateTextureFromSurface(renderer, troll);
        SDL_FreeSurface(troll);

        SDL_Texture* warg_riderTexture = SDL_CreateTextureFromSurface(renderer, warg_rider);
        SDL_FreeSurface(warg_rider); 

        SDL_Texture* spearmanTexture = SDL_CreateTextureFromSurface(renderer, spearman);
        SDL_FreeSurface(spearman); 


        SDL_Texture* alparslanTexture = SDL_CreateTextureFromSurface(renderer, alparslan);
        SDL_FreeSurface(alparslan);
        
        SDL_Texture* fatih_sultanTexture = SDL_CreateTextureFromSurface(renderer, fatih_sultan);
        SDL_FreeSurface(fatih_sultan);

        SDL_Texture* gorukTexture = SDL_CreateTextureFromSurface(renderer, goruk);
        SDL_FreeSurface(goruk);

        SDL_Texture* kafa_kiranTexture = SDL_CreateTextureFromSurface(renderer, kafa_kiran);
        SDL_FreeSurface(kafa_kiran);

        SDL_Texture* kemik_kiranTexture = SDL_CreateTextureFromSurface(renderer, kemik_kiran);
        SDL_FreeSurface(kemik_kiran);

        SDL_Texture* metehanTexture = SDL_CreateTextureFromSurface(renderer, metehan);
        SDL_FreeSurface(metehan);

        SDL_Texture* tugrulTexture = SDL_CreateTextureFromSurface(renderer, tugrul);
        SDL_FreeSurface(tugrul);

        SDL_Texture* yavuz_sultanTexture = SDL_CreateTextureFromSurface(renderer, yavuz_sultan);
        SDL_FreeSurface(yavuz_sultan);

        SDL_Texture* zalimTexture = SDL_CreateTextureFromSurface(renderer, zalim);
        SDL_FreeSurface(zalim);


        if (!cavalryTexture || !archerTexture || !infantryTexture || !ork_warriorTexture || !siege_machineTexture || !trollTexture || !warg_riderTexture || !spearmanTexture
        || !alparslanTexture || !fatih_sultanTexture || !gorukTexture || !kafa_kiranTexture || !kemik_kiranTexture || !metehanTexture || !tugrulTexture || !yavuz_sultanTexture || !zalimTexture
        ) {
            printf("Texture oluşturulamadı! SDL_Error: %s\n", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
            return;
        }

        // Beyaz arka planı temizle
        SDL_SetRenderDrawColor(renderer, 255, 192, 203, 255); // Renk: Beyaz
        SDL_RenderClear(renderer);

        // Izgarayı çiz
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Renk: Siyah
        for (int y = 0; y <= WINDOW_HEIGHT; y += GRID_SIZE) {
            SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
        }
        for (int x = 0; x < WINDOW_WIDTH; x += GRID_SIZE) {
            SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
        }

        int currentHumanRow = 0; // İnsanların yerleştirileceği satır

        if(human->cavalry_count < 100) {
            SDL_Rect gridCell;
            gridCell.x = 1 * GRID_SIZE; // Son ikinci sütun
            gridCell.y = currentHumanRow * GRID_SIZE;
            gridCell.w = GRID_SIZE;
            gridCell.h = GRID_SIZE;
            SDL_RenderCopy(renderer, cavalryTexture, NULL, &gridCell);
            currentHumanRow++;
        }

        for (int i = 0; i < human->cavalry_count / 100; i++) {
            SDL_Rect gridCell;
            if(human->cavalry_count % 100 == 0) {
                gridCell.x = 1 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentHumanRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, cavalryTexture, NULL, &gridCell);
                currentHumanRow++;
            }
            else{
                gridCell.x = 1 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentHumanRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, cavalryTexture, NULL, &gridCell);
                currentHumanRow++;
                gridCell.y = currentHumanRow * GRID_SIZE;
                SDL_RenderCopy(renderer, cavalryTexture, NULL, &gridCell);
            }
            if (currentHumanRow >= 20) break; // 20 satırdan fazla yerleştirme
        }

        currentHumanRow = 0; // Yeni satıra geri döner

        if(human->archer_count < 100) {
            SDL_Rect gridCell;
            gridCell.x = 2 * GRID_SIZE; // Son ikinci sütun
            gridCell.y = currentHumanRow * GRID_SIZE;
            gridCell.w = GRID_SIZE;
            gridCell.h = GRID_SIZE;
            SDL_RenderCopy(renderer, archerTexture, NULL, &gridCell);
            currentHumanRow++;
        }

        for (int i = 0; i < human->archer_count / 100; i++) {
            SDL_Rect gridCell;
            if(human->archer_count % 100 == 0) {
                gridCell.x = 2 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentHumanRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, archerTexture, NULL, &gridCell);
                currentHumanRow++;
            }
            else{
                gridCell.x = 2 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentHumanRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, archerTexture, NULL, &gridCell);
                currentHumanRow++;
                gridCell.y = currentHumanRow * GRID_SIZE;
                SDL_RenderCopy(renderer, archerTexture, NULL, &gridCell);
            }
            if (currentHumanRow >= 20) break; // 20 satırdan fazla yerleştirme
        }

        currentHumanRow = 0; // Yeni satıra geri döner

        if(human->infantry_count < 100) {
            SDL_Rect gridCell;
            gridCell.x = 3 * GRID_SIZE; // Son ikinci sütun
            gridCell.y = currentHumanRow * GRID_SIZE;
            gridCell.w = GRID_SIZE;
            gridCell.h = GRID_SIZE;
            SDL_RenderCopy(renderer, infantryTexture, NULL, &gridCell);
            currentHumanRow++;
        }

        for (int i = 0; i < human->infantry_count / 100; i++) {
            SDL_Rect gridCell;
            if(human->infantry_count % 100 == 0) {
                gridCell.x = 3 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentHumanRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, infantryTexture, NULL, &gridCell);
                currentHumanRow++;
            }
            else{
                gridCell.x = 3 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentHumanRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, infantryTexture, NULL, &gridCell);
                currentHumanRow++;
                gridCell.y = currentHumanRow * GRID_SIZE;
                SDL_RenderCopy(renderer, infantryTexture, NULL, &gridCell);
            }
            if (currentHumanRow >= 20) break; // 20 satırdan fazla yerleştirme
        }

        currentHumanRow = 0; // Yeni satıra geri döner
        if(human->siege_count < 100) {
            SDL_Rect gridCell;
            gridCell.x = 4 * GRID_SIZE; // Son ikinci sütun
            gridCell.y = currentHumanRow * GRID_SIZE;
            gridCell.w = GRID_SIZE;
            gridCell.h = GRID_SIZE;
            SDL_RenderCopy(renderer, siege_machineTexture, NULL, &gridCell);
            currentHumanRow++;
        }

        for (int i = 0; i < human->siege_count / 100; i++) {
            SDL_Rect gridCell;
            if(human->siege_count % 100 == 0) {
                gridCell.x = 4 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentHumanRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, siege_machineTexture, NULL, &gridCell);
                currentHumanRow++;
            }
            else{
                gridCell.x = 4 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentHumanRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, siege_machineTexture, NULL, &gridCell);
                currentHumanRow++;
                gridCell.y = currentHumanRow * GRID_SIZE;
                SDL_RenderCopy(renderer, siege_machineTexture, NULL, &gridCell);
            }
            if (currentHumanRow >= 20) break; // 20 satırdan fazla yerleştirme
        }

        int currentOrkRow = 0;
        if(ork->spearman_count < 100) {
                SDL_Rect gridCell;
                gridCell.x = 18 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, spearmanTexture, NULL, &gridCell);
                currentOrkRow++;
        }

        for (int i = 0; i < ork->spearman_count / 100; i++) {
            SDL_Rect gridCell;
            if(ork->spearman_count % 100 == 0) {
                gridCell.x = 18 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, spearmanTexture, NULL, &gridCell);
                currentOrkRow++;
            }
            else{
                gridCell.x = 18 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, spearmanTexture, NULL, &gridCell);
                currentOrkRow++;
                gridCell.y = currentOrkRow * GRID_SIZE;
                SDL_RenderCopy(renderer, spearmanTexture, NULL, &gridCell);
            }
            if (currentOrkRow >= 20) break; // 20 satırdan fazla yerleştirme
        }

        currentOrkRow = 0;
        if(ork->ork_warrior_count < 100) {
                SDL_Rect gridCell;
                gridCell.x = 17 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, ork_warriorTexture, NULL, &gridCell);
                currentOrkRow++;
        }

        for (int i = 0; i < ork->ork_warrior_count / 100; i++) {
            SDL_Rect gridCell;
            if(ork->ork_warrior_count % 100 == 0) {
                gridCell.x = 17 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, ork_warriorTexture, NULL, &gridCell);
                currentOrkRow++;
            }
            else{
                gridCell.x = 17 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, ork_warriorTexture, NULL, &gridCell);
                currentOrkRow++;
                gridCell.y = currentOrkRow * GRID_SIZE;
                SDL_RenderCopy(renderer, ork_warriorTexture, NULL, &gridCell);
            }
            if (currentOrkRow >= 20) break; // 20 satırdan fazla yerleştirme
        }
        currentOrkRow = 0;
        if(ork->troll_count < 100) {
                SDL_Rect gridCell;
                gridCell.x = 16 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, trollTexture, NULL, &gridCell);
                currentOrkRow++;
        }
        // Yeni satıra geri döner
        for (int i = 0; i < ork->troll_count / 100; i++) {
            SDL_Rect gridCell;
            if(ork->troll_count % 100 == 0) {
                gridCell.x = 16 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, trollTexture, NULL, &gridCell);
                currentOrkRow++;
            }
            else{
                gridCell.x = 16 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, trollTexture, NULL, &gridCell);
                currentOrkRow++;
                gridCell.y = currentOrkRow * GRID_SIZE;
                SDL_RenderCopy(renderer, trollTexture, NULL, &gridCell);
            }
            if (currentOrkRow >= 20) break; // 20 satırdan fazla yerleştirme
        }
        currentOrkRow = 0; // Yeni satıra geri döner

        if(ork->warg_rider_count < 100) {
                SDL_Rect gridCell;
                gridCell.x = 15 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, warg_riderTexture, NULL, &gridCell);
                currentOrkRow++;
        }
        for (int i = 0; i < ork->warg_rider_count / 100; i++) 
        {
            SDL_Rect gridCell;
            if(ork->warg_rider_count % 100 == 0) {
                gridCell.x = 15 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, warg_riderTexture, NULL, &gridCell);
                currentOrkRow++;
            }
            else {
                gridCell.x = 15 * GRID_SIZE; // Son ikinci sütun
                gridCell.y = currentOrkRow * GRID_SIZE;
                gridCell.w = GRID_SIZE;
                gridCell.h = GRID_SIZE;
                SDL_RenderCopy(renderer, warg_riderTexture, NULL, &gridCell);
                currentOrkRow++;
                gridCell.y = currentOrkRow * GRID_SIZE;
                SDL_RenderCopy(renderer, warg_riderTexture, NULL, &gridCell);
            }
            if (currentOrkRow >= 20) break; // 20 satırdan fazla yerleştirme
        }

        SDL_Rect gridCell;
        gridCell.x = 0 * GRID_SIZE; // Son ikinci sütun
        gridCell.y = 0 * GRID_SIZE;
        gridCell.w = GRID_SIZE;
        gridCell.h = GRID_SIZE;

        if (strcmp(human->hero, "Alparslan") == 0) {
            SDL_RenderCopy(renderer, alparslanTexture, NULL, &gridCell);
        } else if (strcmp(human->hero, "Fatih_Sultan_Mehmet") == 0) {
            SDL_RenderCopy(renderer, fatih_sultanTexture, NULL, &gridCell);
        } else if (strcmp(human->hero, "Mete_Han") == 0) {
            SDL_RenderCopy(renderer, metehanTexture, NULL, &gridCell);
        } else if (strcmp(human->hero, "Yavuz_Sultan_Selim") == 0) {
            SDL_RenderCopy(renderer, yavuz_sultanTexture, NULL, &gridCell);
        } else if (strcmp(human->hero, "Tugrul_Bey") == 0) {
            SDL_RenderCopy(renderer, tugrulTexture, NULL, &gridCell);
        }


        gridCell.x = 19 * GRID_SIZE; // Son ikinci sütun
        gridCell.y = 0 * GRID_SIZE;
        gridCell.w = GRID_SIZE;
        gridCell.h = GRID_SIZE;        

        if (strcmp(ork->hero, "Goruk_Vahsi") == 0) {
            SDL_RenderCopy(renderer, gorukTexture, NULL, &gridCell);
        } else if (strcmp(ork->hero, "Vrog_Kafakiran") == 0) {
            SDL_RenderCopy(renderer, kafa_kiranTexture, NULL, &gridCell);
        } else if (strcmp(ork->hero, "Thruk_Kemikkiran") == 0) {
            SDL_RenderCopy(renderer, kemik_kiranTexture, NULL, &gridCell);
        } else if (strcmp(ork->hero, "Ugar_Zalim") == 0) {
            SDL_RenderCopy(renderer, zalimTexture, NULL, &gridCell);
        }

        // Ekranı güncelle
        SDL_RenderPresent(renderer);
        SDL_Delay(5000); // 5 saniye bekle

        // Temizleme işlemleri
        SDL_DestroyTexture(cavalryTexture);
        SDL_DestroyTexture(archerTexture);
        SDL_DestroyTexture(infantryTexture);
        SDL_DestroyTexture(ork_warriorTexture);
        SDL_DestroyTexture(siege_machineTexture);
        SDL_DestroyTexture(trollTexture);
        SDL_DestroyTexture(warg_riderTexture);
        SDL_DestroyTexture(spearmanTexture);

        SDL_DestroyTexture(metehanTexture);
        SDL_DestroyTexture(alparslanTexture);
        SDL_DestroyTexture(yavuz_sultanTexture);
        SDL_DestroyTexture(fatih_sultanTexture);
        SDL_DestroyTexture(kemik_kiranTexture);
        SDL_DestroyTexture(kafa_kiranTexture);
        SDL_DestroyTexture(zalimTexture);
        SDL_DestroyTexture(gorukTexture);
        SDL_DestroyTexture(tugrulTexture);

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }

    int main() {
        char human_hero[20] = "Mete_Han";
        char ork_hero[20] = "Vrog_Kafakiran";
        struct HumanCount human = {99, 99, 101, 99, human_hero}; ///piyadecount/100
        struct OrkCount ork = {100,100,100,100, ork_hero};
        runGame(&human, &ork);
    }
        
