#include "snake.h"


int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(CANVAS_WIDTH * 2, CANVAS_HEIGHT * 2, "Snake");
    SetTargetFPS(30);
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);
    canvas = LoadRenderTexture(CANVAS_WIDTH, CANVAS_HEIGHT);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);

    Setup();
    GoToSelectLevel();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(GameLoop, 0, 1);
#else
    while (!WindowShouldClose()) {
        GameLoop();
    }
#endif

    CloseWindow();

    return 0;
}