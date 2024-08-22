#include "raylib.h"

typedef enum { left = -1, right = 1 } directions;

int main(void) {
  // Initialize
  InitWindow(800, 450, "Space Invaders (clone)");
  SetTargetFPS(60);

  const float player_speed = 4.f;
  const float player_size = 20.f;
  Rectangle player = {GetScreenWidth() / 2.f - player_size,
                      GetScreenHeight() - 100.f, player_size, player_size};

  const unsigned int enemies_number = 48;
  const unsigned int enemies_per_row = 12;
  directions enemies_direction = right;
  Rectangle enemies[enemies_number];

  for (unsigned int i = 0; i < enemies_number; i++) {
    if (i == 0) {
      enemies[i] = (Rectangle){10.f, 10.f, player_size, player_size};
    } else {
      enemies[i] = (Rectangle){enemies[i - 1].x + player_size + 10,
                               enemies[i - 1].y, player_size, player_size};
    }

    if (i % enemies_per_row == 0 && i != 0) {
      enemies[i].x = 10.f;
      enemies[i].y = enemies[i - 1].y + player_size + 10.f;
    }
  }

  // Game loop
  while (!WindowShouldClose()) {
    // Event handling
    if (IsKeyDown(KEY_A)) {
      player.x -= player_speed;
    }
    if (IsKeyDown(KEY_D)) {
      player.x += player_speed;
    }

    // Drawing
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(player, GREEN);

    // Enemies operations
    for (unsigned int i = 0; i < enemies_number; i++) {
      enemies[i].x += enemies_direction;

      if (enemies[i].x > GetScreenWidth() - player_size) {
        enemies_direction = left;
      } else if (enemies[i].x < 0) {
        enemies_direction = right;
      }

      DrawRectangleRec(enemies[i], WHITE);
    }
    EndDrawing();
  }

  // Uninitialize
  CloseWindow();

  return 0;
}
