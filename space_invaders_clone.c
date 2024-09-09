#include "raylib.h"
#include <stdlib.h>
#include <time.h>

typedef enum { left = -1, right = 1 } directions;

typedef struct {
  float size, speed;
  Rectangle body, bullets[5];
  unsigned int bulletNumber;
} player;

typedef struct {
  Rectangle array[48];
  Rectangle bullets[48];
  unsigned int enemiesPerRow, number;
  bool moveDown;
  directions direction;
} enemies;

void initializingLoop(enemies *enemies, player *player, float bulletsDefaultY,
                      float bulletsSize) {
  for (unsigned int i = 0; i < enemies->number; i++) {
    // Initialize enemies
    if (i == 0) {
      enemies->array[i] = (Rectangle){10.f, 10.f, player->size, player->size};
    } else {
      enemies->array[i] =
          (Rectangle){enemies->array[i - 1].x + player->size + 10,
                      enemies->array[i - 1].y, player->size, player->size};
    }
    // Create bullets
    enemies->bullets[i] =
        (Rectangle){enemies->array[i].x, GetScreenHeight(), 2.f, bulletsSize};

    // Move the enemies to another row every 12 enemies
    if (i % enemies->enemiesPerRow == 0 && i != 0) {
      enemies->array[i].x = 10.f;
      enemies->array[i].y = enemies->array[i - 1].y + player->size + 10.f;
    }

    // Create the player bullets
    if (i < player->bulletNumber) {
      player->bullets[i] =
          (Rectangle){player->body.x, bulletsDefaultY, 2.f, bulletsSize};
    }
  }
}

void shoot(player *player) {
  for (unsigned int i = 0; i < player->bulletNumber; i++) {
    if (player->bullets[i].y < -9.f) {
      player->bullets[i].x = player->body.x + player->body.width / 2;
      player->bullets[i].y = player->body.y + player->body.height / 2;
      break;
    }
  }
}

void playerBulletsHandling(player *player, unsigned int i) {
  if (i > player->bulletNumber) {
    return;
  }

  player->bullets[i].y -= 10.f;

  DrawRectangleRec(player->bullets[i], YELLOW);
}

// All in just one loop
void enemiesHandling(enemies *enemies, player *player, const float size,
                     unsigned int i) {
  // Make the player die >:b
  if (CheckCollisionRecs(enemies->bullets[i], player->body) ||
      CheckCollisionRecs(enemies->array[i], player->body)) {
    CloseWindow(); // I don't know why this returns core dumped, but it doesn't matter
    return;
  }

  // Move they down
  if (enemies->array[i].y != GetScreenHeight() + 2000) {
    if (enemies->moveDown) {
      enemies->array[i].y += 10.f;
    } else {
      enemies->array[i].x += enemies->direction * 2.f; // The speed
    }
  }

  // Move the bullets down
  if (enemies->bullets[i].y < GetScreenHeight()) {
    enemies->bullets[i].y += 10.f;
  }

  // Make it bounce baby
  if (enemies->array[i].x > GetScreenWidth() - size) {
    enemies->direction = left;
    enemies->moveDown = !enemies->moveDown;
  } else if (enemies->array[i].x < 0) {
    enemies->direction = right;
    enemies->moveDown = !enemies->moveDown;
  }

  // Die when a bullet touch them
  for (unsigned int j = 0; j < player->bulletNumber; j++) {
    if (CheckCollisionRecs(enemies->array[i], player->bullets[j])) {
      enemies->array[i].y = GetScreenHeight() + 20000;
      player->bullets[j].y = -9;
    }
  }

  // Make them shoot
  if (rand() % 500 == 1 && enemies->array[i].y != GetScreenHeight() + 20000 &&
      enemies->bullets[i].y == GetScreenHeight()) {
    enemies->bullets[i].y = enemies->array[i].y;
    enemies->bullets[i].x = enemies->array[i].x;
  }

  DrawRectangleRec(enemies->bullets[i], RED);
  DrawRectangleRec(enemies->array[i], WHITE);
}

int main(void) {
  // Initialize
  InitWindow(800, 450, "Space Invaders (clone)");
  SetTargetFPS(60);
  srand(time(NULL));

  const float bulletsSize = 10.f;
  const float bulletsDefaultY = bulletsSize * -1;
  player player = {
      20.f, // Size
      4.f,  // Speed
      {GetScreenWidth() / 2.f - player.size, GetScreenHeight() - 100.f,
       player.size, player.size}, // Body
      {{0, 0, 0, 0}},             // Bullets
      5                           // Bullet number
  };

  enemies enemies = {{{0}}, {{0, 0, 0, 0}}, 12, 48, false, right};

  initializingLoop(&enemies, &player, bulletsDefaultY, bulletsSize);

  // Game loop
  while (!WindowShouldClose()) {
    // Event handling
    if (IsKeyDown(KEY_A)) {
      player.body.x -= player.speed;
    }
    if (IsKeyDown(KEY_D)) {
      player.body.x += player.speed;
    }
    if (IsKeyPressed(KEY_SPACE)) {
      shoot(&player);
    }

    // Player edge collision
    if (player.body.x < 0) {
      player.body.x = 0;
    } else if (player.body.x > GetScreenWidth() - player.size) {
      player.body.x = GetScreenWidth() - player.size;
    }

    // Drawing
    BeginDrawing();
    ClearBackground(BLACK);

    for (unsigned int i = 0; i < enemies.number; i++) {
      playerBulletsHandling(&player, i);
      enemiesHandling(&enemies, &player, player.size, i);
    }

    DrawRectangleRec(player.body, GREEN);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
