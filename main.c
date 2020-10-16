#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    time_t t;
    srand((unsigned) time(&t));
  
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    float speed = 4.0f;
    int foodCollected = 0;
    
    
    float agentSize = 30.0f;
    float foodSize = 40.0f;
    
    InitWindow(screenWidth, screenHeight, "John's 3D Game");

   
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.0f, 210.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };    
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };        
    camera.fovy = 45.0f;                               
    camera.type = CAMERA_PERSPECTIVE;                

    Vector3 agentPosition = { 0.0f, 0.0f, 0.0f };
    Vector3 foodPosition = { 0.0f, 0.0f, -750.0f };
    float foodSpeed = 2.5f;

    SetCameraMode(camera, CAMERA_PERSPECTIVE); 
    

    SetTargetFPS(60);   
   
    while (!WindowShouldClose())        
    {
        
        UpdateCamera(&camera);         

        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        
        camera.target = agentPosition;
        
        
        foodPosition.z += foodSpeed;
        
        
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) agentPosition.x += speed;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) agentPosition.x -= speed;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) agentPosition.y -= speed;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) agentPosition.y += speed;
        
        if (IsKeyDown(KEY_R) || IsMouseButtonDown(1)) agentPosition.z += speed;
        if (IsKeyDown(KEY_E) || IsMouseButtonDown(0)) agentPosition.z -= speed;
        
        
        float collision1 = agentSize/2 + foodSize/2;
        float collision2 = agentSize/-2 + foodSize/-2;
        if (
            //INCLUDE FOOD SIZE 
            agentPosition.x - foodPosition.x <= collision1 && 
            agentPosition.x - foodPosition.x >=  collision2 &&
            
            agentPosition.y - foodPosition.y <= collision1 && 
            agentPosition.y - foodPosition.y >=  collision2 &&
            
            agentPosition.z - foodPosition.z <= collision1 && 
            agentPosition.z - foodPosition.z >=  collision2
            ){
            
                    printf("Touvhed");  
                    foodCollected += 1; 
                    foodPosition.z = -750.0f;
                    agentSize += 6.0f;
                    foodSpeed = (float)(rand() % 4 + 1);
                    
                    foodPosition.x = rand() % 120;
                    foodPosition.y = rand() % 120;
                }
        
        
        
        
        BeginDrawing();

            ClearBackground(GREEN);

            BeginMode3D(camera);

                agentSize += 0.005;
                DrawCube(agentPosition, agentSize, agentSize, agentSize, Fade(RED, 0.9f));
                DrawCubeWires(agentPosition, agentSize, agentSize, agentSize, GOLD);
                
                
                DrawCube(foodPosition, foodSize, foodSize, foodSize, BLUE);

            EndMode3D();

        EndDrawing();
    }

    
    CloseWindow();       

    return 0;
}
