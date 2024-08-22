#include "raylib.h"

typedef enum { left = -1, right = 1 } directions;

typedef struct {
  float size;
  Rectangle body;
  float speed;
} player;

typedef struct {
  Rectangle array[48];
  unsigned int enemiesPerRow;
  unsigned int number;
  bool moveDown;
  directions direction;
} enemies;

// TODO: Make the enemies shoot
void enemiesHandling(enemies *enemies, const float size, unsigned int i) {
  if (enemies->moveDown) {
    enemies->array[i].y += 10.f;
  } else {
    enemies->array[i].x += enemies->direction * 2.f; // The speed
  }

  // Make it bounce baby
  if (enemies->array[i].x > GetScreenWidth() - size) {
    enemies->direction = left;
    enemies->moveDown = !enemies->moveDown;
  } else if (enemies->array[i].x < 0) {
    enemies->direction = right;
    enemies->moveDown = !enemies->moveDown;
  }

  DrawRectangleRec(enemies->array[i], WHITE);
}

int main(void) {
  // Initialize
  InitWindow(800, 450, "Space Invaders (clone)");
  SetTargetFPS(60);

  player player = {20.f,
                   {GetScreenWidth() / 2.f - player.size,
                    GetScreenHeight() - 100.f, player.size, player.size},
                   4.f};

  enemies enemies = {{{0}}, 12, 48, false, right};

  for (unsigned int i = 0; i < enemies.number; i++) {
    if (i == 0) {
      enemies.array[i] = (Rectangle){10.f, 10.f, player.size, player.size};
    } else {
      enemies.array[i] =
          (Rectangle){enemies.array[i - 1].x + player.size + 10,
                      enemies.array[i - 1].y, player.size, player.size};
    }

    if (i % enemies.enemiesPerRow == 0 && i != 0) {
      enemies.array[i].x = 10.f;
      enemies.array[i].y = enemies.array[i - 1].y + player.size + 10.f;
    }
  }

  // Game loop
  while (!WindowShouldClose()) {
    // Event handling
    // TODO: Make the player shoot
    if (IsKeyDown(KEY_A)) {
      player.body.x -= player.speed;
    }
    if (IsKeyDown(KEY_D)) {
      player.body.x += player.speed;
    }

    // Player dege collision
    if (player.body.x < 0) {
      player.body.x = 0;
    } else if (player.body.x > GetScreenWidth() - player.size) {
      player.body.x = GetScreenWidth() - player.size;
    }

    // Drawing
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(player.body, GREEN);
    for (unsigned int i = 0; i < enemies.number; i++) {
      enemiesHandling(&enemies, player.size, i);
    }
    EndDrawing();
  }

  // Uninitialize
  CloseWindow();

  return 0;
}
