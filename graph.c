#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

//derleme = gcc -o game graph.c -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lSDL2_image
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define GRID_SIZE 20
#define CELL_SIZE 40

// Fonksiyon prototipleri
void drawGrid(SDL_Renderer* renderer);
SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer);

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    
    SDL_Window* window = SDL_CreateWindow("Izgara", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Pencere arka planını beyaz yap
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    drawGrid(renderer);

    // Resim dosyalarının isimleri
    const char* imageFiles[] = {
        "images/alparslan.png",
        "images/archer.png",
        "images/cavalry.png",
        "images/fatih_sultan.png",
        "images/goruk.png",
        "images/infantry.png",
        "images/kafa_kiran.png",
        "images/kemik_kiran.png",
        "images/metehan.png",
        "images/ork_warrior.png",
        "images/siege_machine.png",
        "images/spearman.png",
        "images/troll.png",
        "images/tugrul.png",
        "images/warg_rider.png",
        "images/yavuz_sultan.png",
        "images/zalim.png"
    };

    SDL_Texture* textures[GRID_SIZE * GRID_SIZE] = {NULL};
    int imageCount = sizeof(imageFiles) / sizeof(imageFiles[0]);

    // Resimleri yükle
    for (int i = 0; i < imageCount; i++) {
        textures[i] = loadTexture(imageFiles[i], renderer);
    }

    // Resimleri ızgaranın üst yarısına yerleştir
    SDL_Rect destRect;
    for (int i = 0; i < GRID_SIZE / 2; i++) { // Sadece üst yarısı için döngü
        for (int j = 0; j < GRID_SIZE; j++) {
            int index = i * GRID_SIZE + j;
            if (index < imageCount) {
                destRect.x = j * CELL_SIZE;
                destRect.y = i * CELL_SIZE;
                destRect.w = CELL_SIZE;
                destRect.h = CELL_SIZE;
                SDL_RenderCopy(renderer, textures[index], NULL, &destRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
    
    // Olay döngüsü
    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }
    
    // Temizlik
    for (int i = 0; i < imageCount; i++) {
        SDL_DestroyTexture(textures[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

void drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Grid rengi
    for (int i = 0; i <= GRID_SIZE; i++) {
        // Dikey çizgiler
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_HEIGHT);
        // Yatay çizgiler
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, WINDOW_WIDTH, i * CELL_SIZE);
    }
}

SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, file);
    if (!texture) {
        printf("Resim yüklenirken hata: %s\n", IMG_GetError());
        exit(1);
    }
    return texture;
}
