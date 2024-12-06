#include "snake.h"
#include <math.h>
#include <stdio.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

float cool_down = 0;

const short LVL[LVL_COUNT][FIELD_HEIGHT][FIELD_WIDTH] = {

        {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        // LVL 1
        {
                {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
        },
        // LVL 2
        {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        // LVL 3
        {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        // LVL 4
        {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
                {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
                {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        }
};

const Coordinates SNAKE_SPAWNS[LVL_COUNT] = {
        {6,  6},
        {6,  6},
        {16, 4},
        {4,  0},
        {4,  0},
};

const int DIFFICULTY_COUNT = 3;
const char *const DIFFICULTY_NAMES[] = {"SPEED: SLOW", "SPEED: NORMAL", "SPEED: MAMBA"};
const float DIFFICULTY_SPEEDS[] = {0.2f, 0.1f, 0.05f};
int difficulty = 0;

const Vector2 ZERO_VEC = {0, 0};
RenderTexture2D canvas;

int current_lvl = 0;
bool is_game_over = false;
Food food = {-1, -1};
SnakeNode snake_body[FIELD_WIDTH][FIELD_HEIGHT];
Snake snake;

void (*Draw)(void);

void (*Update)(void);

void InitSnake() {
    for (int i = 0; i < snake.length; i++) {
        int x = snake.pos_x - snake.dir_x * i;
        int y = snake.pos_y - snake.dir_y * i;
        snake_body[x][y].lifetime = snake.length - i;
    }
}

void SpawnFood() {
    int x;
    int y;
    do {
        x = GetRandomValue(0, FIELD_WIDTH - 1);
        y = GetRandomValue(0, FIELD_HEIGHT - 1);
    } while (snake_body[x][y].lifetime > 0 || LVL[current_lvl][y][x] > 0);
    TraceLog(LOG_INFO, "Spawn food at [%d,%d]", x, y);
    food.x = x;
    food.y = y;
}

void Setup() {
    cool_down = 0;
    snake.dir_x = 1;
    snake.dir_y = 0;
    snake.next_dir_x = 1;
    snake.next_dir_y = 0;
    snake.length = 2;
    snake.pos_x = SNAKE_SPAWNS[current_lvl].x;
    snake.pos_y = SNAKE_SPAWNS[current_lvl].y;
    snake.last_step_updated_at = 0;
    snake.has_eaten = false;
    snake.speed = DIFFICULTY_SPEEDS[difficulty];
    is_game_over = false;
    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            snake_body[i][j].lifetime = 0;
            snake_body[i][j].eat_inside = false;
        }
    }

    InitSnake();
    SpawnFood();
}

void DrawWallBody(int i, int j) {
    if (LVL[current_lvl][j][i] == 0) {
        return;
    }

    DrawRectangle(i * CELL_WIDTH, j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, WHITE);
}

void DrawSnakeBody(int i, int j) {
    if (snake_body[i][j].lifetime < 1) {
        return;
    }

    DrawRectangle(i * CELL_WIDTH, j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, DARKBROWN);
}

void DrawSnakeHead() {
    DrawRectangle(snake.pos_x * CELL_WIDTH, snake.pos_y * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, BROWN);
}

void DrawGameMatrix() {
    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            DrawSnakeBody(i, j);
            DrawWallBody(i, j);
        }
    }
    DrawSnakeHead();
}

void DrawFood() {
    int dw = (CELL_WIDTH - EAT_WIDTH) / 2;
    int dh = (CELL_HEIGHT - EAT_HEIGHT) / 2;
    DrawRectangle(food.x * CELL_WIDTH + dw, food.y * CELL_HEIGHT + dh, EAT_HEIGHT, EAT_WIDTH, MAROON);
}

void CheckFood() {
    if (snake.pos_x == food.x && snake.pos_y == food.y) {
        snake.length++;
        snake.has_eaten = true;
        SpawnFood();
    }
}

void CheckCollisionWithWall() {
    if (LVL[current_lvl][snake.pos_y][snake.pos_x] > 0) {
        is_game_over = true;
    }
}

void CheckEnd() {
    if (snake_body[snake.pos_x][snake.pos_y].lifetime > 0) {
        is_game_over = true;
    }
}

void MoveSnake() {
    snake.last_step_updated_at += GetFrameTime();
    if (snake.last_step_updated_at >= snake.speed) {
        snake.last_step_updated_at = 0;
    } else {
        return;
    }

    if (snake.has_eaten) {
        snake.has_eaten = false;
    } else {
        for (int i = 0; i < FIELD_WIDTH; i++) {
            for (int j = 0; j < FIELD_HEIGHT; j++) {
                if (snake_body[i][j].lifetime > 0) {
                    snake_body[i][j].lifetime--;
                }
            }
        }
    }

    snake.dir_x = snake.next_dir_x;
    snake.dir_y = snake.next_dir_y;
    snake.pos_x += snake.dir_x;
    snake.pos_y += snake.dir_y;

    if (snake.pos_x >= FIELD_WIDTH) {
        snake.pos_x = 0;
    }
    if (snake.pos_x < 0) {
        snake.pos_x = FIELD_WIDTH - 1;
    }
    if (snake.pos_y >= FIELD_HEIGHT) {
        snake.pos_y = 0;
    }
    if (snake.pos_y < 0) {
        snake.pos_y = FIELD_HEIGHT - 1;
    }

    CheckEnd();
    CheckCollisionWithWall();
    snake_body[snake.pos_x][snake.pos_y].lifetime = snake.length;
}

void DrawGame() {
    DrawFood();
    DrawGameMatrix();

    if (is_game_over) {
        DrawText("Wasted", 2, CANVAS_HEIGHT / 2, 20, MAGENTA);
        DrawText("PRESS F TO RESTART", 2, CANVAS_HEIGHT / 2 + 20, 12, MAGENTA);
    }
}

void ControlSnake() {
    if ((snake.dir_y == 0) && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))) {
        snake.next_dir_y = -1;
        snake.next_dir_x = 0;
        return;
    }
    if ((snake.dir_y == 0) && (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))) {
        snake.next_dir_y = 1;
        snake.next_dir_x = 0;
        return;
    }
    if ((snake.dir_x == 0) && (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))) {
        snake.next_dir_y = 0;
        snake.next_dir_x = -1;
        return;
    }
    if ((snake.dir_x == 0) && (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))) {
        snake.next_dir_y = 0;
        snake.next_dir_x = 1;
        return;
    }
}

void UpdateGame() {
    if (is_game_over) {
        if (IsKeyPressed(KEY_F)) {
            GoToSelectLevel();
        }
        return;
    }
    if (IsKeyPressed(KEY_R)) {
        GoToSelectLevel();
        return;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        cool_down = 0;
        current_lvl++;
        if (current_lvl < 0) {
            current_lvl = LVL_COUNT - 1;
        }
        if (current_lvl >= LVL_COUNT) {
            current_lvl = 0;
        }
    }

    if (cool_down < COOL_DOWN_BEFORE_START) {
        cool_down += GetFrameTime();
        return;
    }

    MoveSnake();
    CheckFood();
    ControlSnake();
}

Rectangle GetCanvasTarget() {
    float sh = (float) GetScreenHeight();
    float sw = (float) GetScreenWidth();
    float scale = fminf(sh / CANVAS_HEIGHT, sw / CANVAS_WIDTH);
    Rectangle rec = {0, 0, CANVAS_WIDTH * scale, CANVAS_HEIGHT * scale};
    return rec;
}

void GoToGame() {
    Draw = DrawGame;
    Update = UpdateGame;
    Setup();
}

void DrawSelectLevel() {
    DrawText("LEVEL: ", 4, 4, 20, MAGENTA);
    DrawText("press UP or Down", 4, 24, 12, MAGENTA);

    char buffer[3];  // max num is 99
    sprintf(buffer, "%d", current_lvl);
    DrawText(buffer, 84, 4, 20, MAGENTA);

    DrawText(DIFFICULTY_NAMES[difficulty], 4, 42, 20, MAGENTA);
    DrawText("press LEFT or RIGHT", 4, 62, 12, MAGENTA);

    DrawText("Press Enter to start", 4, 92, 12, MAGENTA);
}

void UpdateSelectLevel() {
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        current_lvl--;
    } else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        current_lvl++;
    }
    if (current_lvl < 0) {
        current_lvl = LVL_COUNT - 1;
    }
    if (current_lvl >= LVL_COUNT) {
        current_lvl = 0;
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
        difficulty--;
    } else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
        difficulty++;
    }
    if (difficulty < 0) {
        difficulty = DIFFICULTY_COUNT - 1;
    }

    if (difficulty >= DIFFICULTY_COUNT) {
        difficulty = 0;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        GoToGame();
    }
}

void GoToSelectLevel() {
    Draw = DrawSelectLevel;
    Update = UpdateSelectLevel;
}

void GameLoop() {
    BeginDrawing();
    ClearBackground(GREEN);

    BeginTextureMode(canvas);
    ClearBackground(BLACK);
    Draw();
    EndTextureMode();

    Rectangle canvas_field = {0, 0, (float) canvas.texture.width, -(float) canvas.texture.height};
    DrawTexturePro(canvas.texture, canvas_field, GetCanvasTarget(), ZERO_VEC, 0.0f, WHITE);
    EndDrawing();
    Update();
}