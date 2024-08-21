#include "raylib.h"

int main(void) {
  // Initialize
  InitWindow(800, 450, "Space Invaders (clone)");

  // Game loop
  while (!WindowShouldClose()) {
    // Event handling
    // TODO: Make the player movement

    // Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);
    EndDrawing();
  }

  // Uninitialize
  CloseWindow();

  return 0;
}
