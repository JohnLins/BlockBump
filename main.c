#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

Vector3 rotateCube(Vector3 cubePosition)
{
    //Make this function rotate cube
    return cubePosition;
}


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
   // Vector3 foodPosition = { rand() % screenWidth, rand() % screenHeight, rand() % screenHeight };
   // Vector3 foodPositionRA = { rand() % screenWidth + 4, rand() % screenHeight + 4, rand() % screenHeight + 4 };

    SetCameraMode(camera, CAMERA_PERSPECTIVE); // Set a free camera mode
    

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
        
        
        //NEEDS FIXING
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
            
            /*cubePosition.y - foodPosition.y <= cubesize/2 &&
            cubePosition.y - foodPosition.y >= cubesize/2 &&
            
            cubePosition.z - foodPosition.z <= cubesize/2 &&
            cubePosition.z - foodPosition.z >= cubesize/2*/
            
                    printf("Touvhed");  
                    foodCollected += 1; 
                    foodPosition.z = -320.0f;
                    cubeSize += 6.0f;
                    foodSpeed += (float)(rand() % 2);
                    
                    foodPosition.x = rand() % 120;
                    foodPosition.y = rand() % 120;
                    //camera.position.z += 30.0f;
                    //cubePosition.y += 110.0f;

            //ballPosition.x = screenWidth/2;
           //ballPosition.y = screenHeight/2;
           
                  //  foodPosition.x += 5.0f; //rand() % screenWidth;
                  // foodPosition.y += 5.0f; //rand() % screenHeight;  
                  // foodPosition.z += 5.0f; //rand() % screenHeight;
                }
        
        
        
        
        BeginDrawing();

            ClearBackground(GREEN);

            BeginMode3D(camera);

                cubeSize += 0.005;
                DrawCube(cubePosition, cubeSize, cubeSize, cubeSize, RED);
                
               // DrawCircle3D(foodPosition, 20.0f, foodPositionRA, 20.0f, BLACK);
                
                
                DrawCube(foodPosition, foodSize, foodSize, foodSize, BLUE);
                
                
                
                
                
                
        
        
                
                /*
                Vector3 cubePosition2 = { 1.0f, 2.0f, 2.0f };
                DrawCube(cubePosition2, h, h, h, BLUE);*/
                
                
               // DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                //DrawGrid(10, 1.0f);

            EndMode3D();

          //  DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
            
          //  DrawRectangleLines( 10, 10, 320, 133, BLUE);

           /* DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
            DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);*/

        EndDrawing();
    }

    
    CloseWindow();       

    return 0;
}