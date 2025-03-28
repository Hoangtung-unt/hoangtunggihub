#include "Game.h"


int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    initSDL(window, renderer);

    SDL_Texture* playerTexture = loadTexture("assets/hero.1.png", renderer);
    SDL_Texture* enemyTexture = loadTexture("assets/monsters.png", renderer);
    if (!playerTexture || !enemyTexture) return -1;

    SDL_Rect player = {100, SCREEN_HEIGHT - PLAYER_SIZE - 10, PLAYER_SIZE, PLAYER_SIZE};
    int velocityY = 0;
    bool isJumping = false;
    bool gameOver = false;
    vector<Platform> platforms = {{{0, SCREEN_HEIGHT - 10, SCREEN_WIDTH, 10}}};
    vector<Enemy> enemies;
    vector<Bullet> bullets;

    Uint32 lastEnemySpawnTime = SDL_GetTicks();

    bool running = true;
const int FRAME_DELAY = 1000 / 60; // 60 FPS
Uint32 frameStart;
int frameTime;

while (running && !gameOver) {
    frameStart = SDL_GetTicks();

    handleEvents(running, player, velocityY, isJumping, bullets);
    update(player, velocityY, isJumping, platforms, enemies, bullets, gameOver, lastEnemySpawnTime);
    render(renderer, playerTexture, player, platforms, enemyTexture, enemies, bullets);

    frameTime = SDL_GetTicks() - frameStart;
    if (FRAME_DELAY > frameTime) {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}
SDL_DestroyTexture(playerTexture);
SDL_DestroyTexture(enemyTexture);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
IMG_Quit();
SDL_Quit();

    SDL_Quit();
    return 0;
}
