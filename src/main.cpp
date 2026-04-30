#include "raylib.h"
#include "resource_dir.h"
#include "PCG.h" // Import our new module
#include <iostream>

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(PCG::SCREEN_WIDTH, PCG::SCREEN_HEIGHT, "Construct Map Editor");

    //PCG::TileType tileArray[PCG::MAP_ROWS][PCG::MAP_COLUMNS] = { PCG::TileType::TILE_TYPE_OCEAN };
    //PCG::CreateMap(tileArray);
    PCG::TileMap tileMap;
    //tileMap.CreateMap();
    //tileMap.SetMapGenerator(new PCG::RandomMapGenerator());
    tileMap.SetMapGenerator(new PCG::NoiseMapGenerator());
    tileMap.GetMapGenerator()->Generate(tileMap.tileArray); // Generate the map using the selected generator

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        //PCG::DrawMap(tileArray); // Function from PCG.c
        tileMap.DrawMap();
        DrawText("Construct Map Editor", 20, 20, 20, WHITE);
        //PCG::PCG_DrawGUI(tileArray);
        tileMap.DrawGUI();
        EndDrawing();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            std::cout << "Mouse clicked at: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
            if (PCG::TILE_TYPE_TO_SET == '5') {
                tileMap.SetTile(mousePos.x / PCG::TILE_SIZE, mousePos.y / PCG::TILE_SIZE, PCG::TileType::TILE_TYPE_LAND);
            }
            else if (PCG::TILE_TYPE_TO_SET == '1') {
                tileMap.SetTile(mousePos.x / PCG::TILE_SIZE, mousePos.y / PCG::TILE_SIZE, PCG::TileType::TILE_TYPE_OCEAN);
            }
            //tileMap.SetTile(mousePos.x / PCG::TILE_SIZE, mousePos.y / PCG::TILE_SIZE, PCG::TileType::TILE_TYPE_LAND);
        }

    }

    

    
    CloseWindow();
    return 0;
}