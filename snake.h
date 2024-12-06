#ifndef SNAKE_H
#define SNAKE_H

#include <raylib.h>
#include <stdbool.h>

#define CANVAS_WIDTH 240
#define CANVAS_HEIGHT 120

#define CELL_WIDTH 10   // in pixels
#define CELL_HEIGHT 10  // in pixels

#define EAT_WIDTH 6
#define EAT_HEIGHT 6

#define FIELD_WIDTH 24   // (CANVAS_WIDTH / CELL_WIDTH)
#define FIELD_HEIGHT 12  // (CANVAS_HEIGHT / CELL_HEIGHT)

#define LVL_COUNT 5

#define COOL_DOWN_BEFORE_START 1  // in seconds

extern float cool_down;

typedef struct Coordinates_ {
    int x;
    int y;
} Coordinates;

extern const short LVL[LVL_COUNT][FIELD_HEIGHT][FIELD_WIDTH];
extern const Coordinates SNAKE_SPAWNS[LVL_COUNT];

extern const int DIFFICULTY_COUNT;
extern const char* const DIFFICULTY_NAMES[];
extern const float DIFFICULTY_SPEEDS[];
extern int difficulty;

extern const Vector2 ZERO_VEC;
extern RenderTexture2D canvas;

typedef struct SnakeNode_ {
    int lifetime;
    bool eat_inside;
} SnakeNode;

typedef struct Snake_ {
    int dir_x;  // 1 - right, -1 - left, 0 - nowhere
    int dir_y;  // 1 - up , -1 - down, 0 - nowhere
    int next_dir_x;
    int next_dir_y;
    int length;
    int pos_x;
    int pos_y;
    float speed;                 // in seconds till next movement
    float last_step_updated_at;  // time since last step update
    bool has_changed_dir;
    bool has_eaten;
} Snake;

typedef struct Food_ {
    int x;
    int y;
} Food;

extern int current_lvl;
extern bool is_game_over;
extern Food food;
extern SnakeNode snake_body[FIELD_WIDTH][FIELD_HEIGHT];
extern Snake snake;

extern void (*Draw)(void);
extern void (*Update)(void);

void InitSnake();
void SpawnFood();
void Setup();
void DrawWallBody(int i, int j);
void DrawSnakeBody(int i, int j);
void DrawSnakeHead();
void DrawGameMatrix();
void DrawFood();
void CheckFood();
void CheckCollisionWithWall();
void CheckEnd();
void MoveSnake();
void DrawGame();
void ControlSnake();
void UpdateGame();
Rectangle GetCanvasTarget();
void GoToGame();
void DrawSelectLevel();
void UpdateSelectLevel();
void GoToSelectLevel();
void GameLoop();

#endif // SNAKE_H