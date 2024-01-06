#include "raylib.h"
#include <iostream>

int main(){
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "My Pong Game");
    SetTargetFPS(60);

    while(WindowShouldClose() == false){
        BeginDrawing();

        //Line
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, GRAY);

        //Drawing Ball
        DrawCircle(screenWidth/2, screenHeight/2, 20, WHITE);
        
        //Paddles
        DrawRectangle(10, screenHeight/2 - 60, 25, 120, WHITE);
        DrawRectangle(screenWidth - 35, screenHeight/2 - 60, 25, 120, WHITE);

        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}