#include "raylib.h"

int main(void) {
  // Initialize
  InitWindow(800, 450, "Space Invaders (clone)");
  SetTargetFPS(60);

  const float player_speed = 4.f;
  const float player_size = 20.f;
  Rectangle player = {GetScreenWidth() / 2.f - player_size,
                      GetScreenHeight() - 100.f, player_size, player_size};

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
    EndDrawing();
  }

  // Uninitialize
  CloseWindow();

  return 0;
}
