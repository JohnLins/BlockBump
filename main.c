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
    
    
    float cubeSize = 30.0f;
    float foodSize = 40.0f;
    
    InitWindow(screenWidth, screenHeight, "John's 3D Game");

   
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.0f, 210.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };    
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };        
    camera.fovy = 45.0f;                               
    camera.type = CAMERA_PERSPECTIVE;                

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    Vector3 foodPosition = { 0.0f, 0.0f, -720.0f };
    float foodSpeed = 2.5f;

    SetCameraMode(camera, CAMERA_PERSPECTIVE); 
    

    SetTargetFPS(60);   
   
    while (!WindowShouldClose())        
    {
        
        UpdateCamera(&camera);         

        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        
        camera.target = cubePosition;
        
        //THIS KEEPS IT FIXED (Delete if you want it to be fixed)
        //camera.position.x = cubePosition.x;
        //camera.position.y = cubePosition.y + 50.0f;
        /////////////////////
        
        foodPosition.z += foodSpeed;
        
        
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) cubePosition.x += speed;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) cubePosition.x -= speed;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) cubePosition.y -= speed;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) cubePosition.y += speed;
        
        if (IsKeyDown(KEY_R) || IsMouseButtonDown(1)) cubePosition.z += speed;
        if (IsKeyDown(KEY_E) || IsMouseButtonDown(0)) cubePosition.z -= speed;
        
        
        
        float collision1 = cubeSize/2 + foodSize/2;
        float collision2 = cubeSize/-2 + foodSize/-2;
        if (
            //INCLUDE FOOD SIZE 
            cubePosition.x - foodPosition.x <= collision1 && 
            cubePosition.x - foodPosition.x >=  collision2 &&
            
            cubePosition.y - foodPosition.y <= collision1 && 
            cubePosition.y - foodPosition.y >=  collision2 &&
            
            cubePosition.z - foodPosition.z <= collision1 && 
            cubePosition.z - foodPosition.z >=  collision2
            ){
                    printf("Touched ");  
                    foodCollected += 1; 
                    foodPosition.z = -320.0f;
                    cubeSize += 6.0f;
                    foodSpeed += (float)(rand() % 2);
                    
                    foodPosition.x = rand() % 120;
                    foodPosition.y = rand() % 120;
                }
        
        
        BeginDrawing();

            ClearBackground(GREEN);

            BeginMode3D(camera);

                cubeSize += 0.005;
                DrawCube(cubePosition, cubeSize, cubeSize, cubeSize, RED);
                
                DrawCube(foodPosition, foodSize, foodSize, foodSize, BLUE);
                
                
           
            EndMode3D();

   

        EndDrawing();
    }

    
    CloseWindow();       

    return 0;
}
