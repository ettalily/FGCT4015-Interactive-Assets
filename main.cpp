#include "raylib.h"
#include "raymath.h"

#define WINDOW_SIZE 800.0f
#define FRAME_COUNT 4
#define FRAME_SIZE 256.0f
#define FRAME_SPEED 6

void UpdateWalk(int *timer, int *currentFrame, Sound *walkSound) 
{
    *timer += 1;

    if (*timer != FRAME_SPEED) 
        return;

    *timer = 0;
    *currentFrame += 1;

    if (*currentFrame != FRAME_COUNT)
        return;

    *currentFrame = 0;
    PlaySound(*walkSound);
}

int main(void)
{
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Interactive Assets");
    InitAudioDevice();
    SetTargetFPS(60);

    Texture2D sprite = LoadTexture("./assets/spritesheet.png");
    Sound walkSound = LoadSound("./assets/walk.wav");
    Sound backgroundMusic = LoadSound("./assets/backgroundmusic.mp3");

    int timer = 0;
    int currentFrame = 0;

    while (!WindowShouldClose())
    {
        if (!IsSoundPlaying(backgroundMusic))
            PlaySound(backgroundMusic);

        if (IsKeyDown(KEY_SPACE)) 
            UpdateWalk(&timer, &currentFrame, &walkSound);
        else
        {
            if (currentFrame != 0)
            {
                currentFrame = 0;
                PlaySound(walkSound);
            }
            
            timer = 0;
        }

        BeginDrawing();

        ClearBackground(WHITE);

        DrawText("Hold Space to make the sheep walk!", 20, 20, 40, BLACK);

        Rectangle spriteRec = Rectangle{FRAME_SIZE * currentFrame, 0, FRAME_SIZE, FRAME_SIZE};
        DrawTextureRec(sprite, spriteRec, Vector2{WINDOW_SIZE * 0.35f, WINDOW_SIZE * 0.35f}, WHITE);

        EndDrawing();
    }

    UnloadTexture(sprite);
    UnloadSound(walkSound);
    UnloadSound(backgroundMusic);
    
    CloseAudioDevice();
    CloseWindow();

    return 0;
}