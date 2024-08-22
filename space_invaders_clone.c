#include "raylib.h"

typedef enum { left = -1, right = 1 } directions;

void enemiesHandling(Rectangle *enemy, const float playerSize,
                     directions *enemiesDirection) {
  enemy->x += *enemiesDirection * 2.f; // The speed

  // Make it bounce baby
  if (enemy->x > GetScreenWidth() - playerSize) {
    *enemiesDirection = left;
  } else if (enemy->x < 0) {
    *enemiesDirection = right;
  }

  DrawRectangleRec(*enemy, WHITE);
}

int main(void) {
  // Initialize
  InitWindow(800, 450, "Space Invaders (clone)");
  SetTargetFPS(60);

  const float playerSpeed = 4.f;
  const float playerSize = 20.f;
  Rectangle player = {GetScreenWidth() / 2.f - playerSize,
                      GetScreenHeight() - 100.f, playerSize, playerSize};

  const unsigned int enemiesNumber = 48;
  const unsigned int enemiesPerRow = 12;
  directions enemiesDirection = right;
  Rectangle enemies[enemiesNumber];

  for (unsigned int i = 0; i < enemiesNumber; i++) {
    if (i == 0) {
      enemies[i] = (Rectangle){10.f, 10.f, playerSize, playerSize};
    } else {
      enemies[i] = (Rectangle){enemies[i - 1].x + playerSize + 10,
                               enemies[i - 1].y, playerSize, playerSize};
    }

    if (i % enemiesPerRow == 0 && i != 0) {
      enemies[i].x = 10.f;
      enemies[i].y = enemies[i - 1].y + playerSize + 10.f;
    }
  }

  // Game loop
  while (!WindowShouldClose()) {
    // Event handling
    if (IsKeyDown(KEY_A)) {
      player.x -= playerSpeed;
    }
    if (IsKeyDown(KEY_D)) {
      player.x += playerSpeed;
    }

    // Player dege collision
    if (player.x < 0) {
      player.x = 0;
    } else if (player.x > GetScreenWidth() - playerSize) {
      player.x = GetScreenWidth() - playerSize;
    }

    // Drawing
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(player, GREEN);
    for (unsigned int i = 0; i < enemiesNumber; i++) {
      enemiesHandling(&enemies[i], playerSize, &enemiesDirection);
    }
    EndDrawing();
  }

  // Uninitialize
  CloseWindow();

  return 0;
}
