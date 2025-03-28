#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <algorithm>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PLAYER_SIZE = 50;
const int ENEMY_SIZE = 50;
const int BULLET_SIZE = 10;
const int GRAVITY = 1;
const int JUMP_FORCE = 20;
const int ENEMY_SPEED = 1;
const int BULLET_SPEED = 5 ;
const int ENEMY_SPAWN_INTERVAL = 120; // Số frame giữa mỗi lần spawn
using namespace std;
struct Platform {
    SDL_Rect rect;
};

struct Enemy {
    SDL_Rect rect;
    int speed;
};

struct Bullet {
    SDL_Rect rect;
    int speed;
};
struct Tile {
    SDL_Rect rect;
    bool solid; // Xác định ô này có phải địa hình không
};
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer);
void handleEvents(bool& running, SDL_Rect& player, int& velocityY, bool& isJumping, vector<Bullet>& bullets);
void update(SDL_Rect& player, int& velocityY, bool& isJumping, const vector<Platform>& platforms, vector<Enemy>& enemies, vector<Bullet>& bullets, bool& gameOver, Uint32& lastEnemySpawnTime);
void render(SDL_Renderer* renderer, SDL_Texture* playerTexture, const SDL_Rect& player,
            const vector<Platform>& platforms, SDL_Texture* enemyTexture,
            const vector<Enemy>& enemies, const vector<Bullet>& bullets);

