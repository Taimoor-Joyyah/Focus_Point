#define RAYGUI_IMPLEMENTATION


#include "raylib.h"
#include "raymath.h"
#include "raygui.h"
#include <random>

void generatePoints(Vector2 points[100]) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> randX(350, 1800);
    std::uniform_real_distribution<float> randY(100, 1000);

    for (int i = 0; i < 100; ++i) {
        points[i].x = randX(mt);
        points[i].y = randY(mt);
    }
}

bool inRange(const Vector2 &focus, const Vector2 &point, float range) {
    return Vector2Distance(focus, point) <= range;
}

bool inControls(const Vector2 &mouse) {
    return mouse.x <= 300 && mouse.y <= 600;
}

int main() {
    const int width = 800;
    const int height = 800;

    InitWindow(width, height, "Focus Point");
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
    SetTargetFPS(60);

    Vector2 points[100];

    generatePoints(points);

    Vector2 focus{static_cast<float>(900),
                  static_cast<float>(500)};

    float range = 250;
    int countP = 10;
    float radiusP = 10;
    float radiusF = 15;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < countP; ++i) {
            DrawCircle(points[i].x, points[i].y, radiusP, BLACK);
            if (inRange(focus, points[i], range))
                DrawLineEx(points[i], focus, 2, BLUE);
        }
        DrawCircle(focus.x, focus.y, radiusF, RED);


        GuiWindowBox({0, 0, 300, 600}, "Controls");

        GuiLabel({20, 25, 70, 20}, "Range");
        GuiLabel({20, 55, 70, 20}, "Points");
        GuiLabel({20, 85, 70, 20}, "RadiusP");
        GuiLabel({20, 115, 70, 20}, "RadiusF");

        range = GuiSliderPro({100, 25, 150, 20}, "0", "1500", range, 0, 1500, 25);
        countP = (int) GuiSliderPro({100, 55, 150, 20}, "1", "100", (float)countP, 1, 100, 25);
        radiusP = GuiSliderPro({100, 85, 150, 20}, "5", "100", radiusP, 5, 100, 25);
        radiusF = GuiSliderPro({100, 115, 150, 20}, "5", "100", radiusF, 5, 100, 25);

        if (GuiButton({100, 160, 100, 50}, "Random Generate"))
            generatePoints(points);

        DrawFPS(1800, 20);

        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !inControls(mouse))
            focus = mouse;
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
