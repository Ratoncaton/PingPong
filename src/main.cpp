#include "raylib.h"
#include <iostream>

int player_score = 0;
int cpu_score = 0;

class Ball{
    public:
        float x, y;
        int speed_x, speed_y;
        int radius;

    void Draw(){
        DrawCircle(x, y, radius, WHITE);
    }

    void Update(){
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0){
            //Reverse Speed
            speed_y *= -1;
        }
        if(x + radius >= GetScreenWidth()) //CPU wins
        {
            cpu_score++;
            Reset();
        }
        
        if (x - radius <= 0 ) //Player Wins
        {
            player_score++;
            Reset();
        }
    }

    void Reset(){
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int speed_choices[2] = {-1,1};
        speed_x *= speed_choices[GetRandomValue(0,1)];
        speed_y *= speed_choices[GetRandomValue(0,1)];

    }

};

class Paddle{
    protected:

    void LimitMovement(){
        if(y <= 0){
            y = 0;
        }
        if(y + height >= GetScreenHeight()){
            y = GetScreenHeight() - height;
        }
    }

    public:
        float x, y;
        float width, height;
        int speed;

    void Draw(){
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update(){
        if(IsKeyDown(KEY_UP)){
            y = y -speed;
        }
        if(IsKeyDown(KEY_DOWN)){
            y = y + speed;
        }
        
        LimitMovement();
    }

};

class CpuPaddle: public Paddle{
    public:

    void Update(int ball_y){
        if(y + height/2 > ball_y){
            y -= speed;
        }
        if(y + height/2 <= ball_y){
            y += speed;
        }
        
        LimitMovement();
    }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main(){
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "My Pong Game");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screenWidth/2;
    ball.y = screenHeight/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = screenWidth -player.width - 10;
    player.y = screenHeight/2 - player.height/2;
    player.speed = 7;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screenHeight/2 - cpu.height/2;
    cpu.speed = 6;

    while(WindowShouldClose() == false){
        BeginDrawing();
        
        //Updating
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        //Check Collisions
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})){
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})){
            ball.speed_x *= -1;
        }

        //Clear screen
        ClearBackground(BLACK);

        //Line
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, GRAY);
        
        //Ball
        ball.Draw();
        
        //Paddles
        cpu.Draw();
        player.Draw();

        //Score
        DrawText(TextFormat("%i", cpu_score), screenWidth/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screenWidth/4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}