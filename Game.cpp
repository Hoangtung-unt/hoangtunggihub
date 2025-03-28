#include "Game.h"

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL không thể khởi tạo! SDL_Error: " << SDL_GetError() << endl;
        exit(-1);
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "SDL_image không thể khởi tạo! IMG_Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(-1);
    }
    window = SDL_CreateWindow("Game Side-Scrolling", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Không thể tạo cửa sổ! SDL_Error: " << SDL_GetError() << endl;
        SDL_Quit();
        exit(-1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Không thể tạo renderer! SDL_Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-1);
    }
}

SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        cout << "Không thể tải ảnh! IMG_Error: " << IMG_GetError() << endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}

void handleEvents(bool& running, SDL_Rect& player, int& velocityY, bool& isJumping, vector<Bullet>& bullets) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && !isJumping) {
                velocityY = -JUMP_FORCE;
                isJumping = true;
            } else if (event.key.keysym.scancode == SDL_SCANCODE_X) {
                bullets.push_back({{player.x + PLAYER_SIZE, player.y + PLAYER_SIZE / 2, BULLET_SIZE, BULLET_SIZE}, BULLET_SPEED});
            }
        }
    }
}

void update(SDL_Rect& player, int& velocityY, bool& isJumping, const vector<Platform>& platforms, vector<Enemy>& enemies, vector<Bullet>& bullets, bool& gameOver, Uint32& lastEnemySpawnTime) {
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT]) player.x -= 5;
    if (keys[SDL_SCANCODE_RIGHT]) player.x += 5;

    velocityY += GRAVITY;
    player.y += velocityY;

    for (const auto& platform : platforms) {
        if (player.y + PLAYER_SIZE > platform.rect.y &&
            player.y + PLAYER_SIZE - velocityY <= platform.rect.y &&
            player.x + PLAYER_SIZE > platform.rect.x &&
            player.x < platform.rect.x + platform.rect.w) {
            player.y = platform.rect.y - PLAYER_SIZE;
            velocityY = 0;
            isJumping = false;
        }
    }

    if (player.x < 0) player.x = 0;
    if (player.x > SCREEN_WIDTH - PLAYER_SIZE) player.x = SCREEN_WIDTH - PLAYER_SIZE;

    for (auto& enemy : enemies) {
        enemy.rect.x -= enemy.speed;
        if (checkCollision(player, enemy.rect)) {
            gameOver = true;
        }
    }

    for (auto& bullet : bullets) {
        bullet.rect.x += bullet.speed;
    }

    bullets.erase(remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return b.rect.x > SCREEN_WIDTH; }), bullets.end());

    auto bulletIt = bullets.begin();
    while (bulletIt != bullets.end()) {
        bool bulletRemoved = false;
        auto enemyIt = enemies.begin();
        while (enemyIt != enemies.end()) {
            if (checkCollision(enemyIt->rect, bulletIt->rect)) {
                enemyIt = enemies.erase(enemyIt); // Xóa quái
                bulletIt = bullets.erase(bulletIt); // Xóa đạn
                bulletRemoved = true;
                break; // Thoát khỏi vòng lặp để tránh lỗi iterator
            } else {
                ++enemyIt;
            }
        }
        if (!bulletRemoved) {
            ++bulletIt;
        }
    }

    // Sinh quái theo khoảng thời gian
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastEnemySpawnTime >= ENEMY_SPAWN_INTERVAL * 16) {
        enemies.push_back({{SCREEN_WIDTH, SCREEN_HEIGHT - ENEMY_SIZE - 10, ENEMY_SIZE, ENEMY_SIZE}, ENEMY_SPEED});
        lastEnemySpawnTime = currentTime;
    }
}

void render(SDL_Renderer* renderer, SDL_Texture* playerTexture, const SDL_Rect& player,
            const vector<Platform>& platforms, SDL_Texture* enemyTexture,
            const vector<Enemy>& enemies, const vector<Bullet>& bullets) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu nền đỏ
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Màu nền cho platform
    for (const auto& platform : platforms) {
        SDL_RenderFillRect(renderer, &platform.rect);
    }

    SDL_RenderCopy(renderer, playerTexture, NULL, &player);
    for (const auto& enemy : enemies) {
        SDL_RenderCopy(renderer, enemyTexture, NULL, &enemy.rect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Màu vàng cho đạn
    for (const auto& bullet : bullets) {
        SDL_RenderFillRect(renderer, &bullet.rect);
    }

    SDL_RenderPresent(renderer);
}

