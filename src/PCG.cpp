#include "PCG.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
// Required to call Raylib gui buttons. Add this near the top of PCG.c
#define RAYGUI_IMPLEMENTATION
#include "raygui.h" 

// =============================================
// Constructor for our TileMap class.
// =============================================
PCG::TileMap::TileMap()
{
    // Initialise our tileMap array to all grass tiles by default when we create a new TileMap object. 
    // We can change this later using the CreateMap() function, or by setting individual tiles with SetTile().
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            tileArray[y][x] = TILE_TYPE_LAND;
        }
    }

    // initialise the mapGenerator to null.
    mapGenerator = nullptr;
}


// =============================================
// Destructor for our TileMap class.
// =============================================
PCG::TileMap::~TileMap()
{
    if (mapGenerator != nullptr) {
        delete mapGenerator; // Clean up the map generator if it exists
        mapGenerator = nullptr;
    }
}


// ============================================= 
// void CreateMap()
// ============================================= 
void PCG::TileMap::CreateMap() {
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            tileArray[y][x] = (TileType)GetRandomValue(0, TILE_COUNT - 1);
        }
    }
}


// ============================================= 
// void SetTile(int x, int y, TileType tileType)
// set a tile in our tileMap array, using the input x and y coordinates, and the type of tile we want to set it to (tileType)
// ============================================= 

void PCG::TileMap::SetTile(int x, int y, TileType tileType)
{
    if (x >= 0 && x < MAP_COLUMNS && y >= 0 && y < MAP_ROWS) {
        tileArray[y][x] = tileType;
    }
}


// ============================================= 
// Color PCG_GetTileColor(TileType tileType)
// Return a colour based on the type type input
// ============================================= 
Color PCG::TileMap::GetTileColor(PCG::TileType _tileType) const {
    switch (_tileType) {
    case PCG::TileType::TILE_TYPE_DEEPLAND:
		return DEEPLAND_COLOR;
    case PCG::TileType::TILE_TYPE_LAND:
        return LAND_COLOR;
	case PCG::TileType::TILE_TYPE_BEACH:
        return BEACH_COLOR;
    case PCG::TileType::TILE_TYPE_OCEAN:
        return OCEAN_COLOR;
    case PCG::TileType::TILE_TYPE_DEEPOCEAN:
		return DEEPOCEAN_COLOR;
    default:
        return UNKNOWN_COLOR;
    }
}


// ============================================= 
// void PCG_DrawMap()
// ============================================= 
void PCG::TileMap::DrawMap() const {
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            DrawRectangle(x * PCG::TILE_SIZE, y * PCG::TILE_SIZE, PCG::TILE_SIZE, PCG::TILE_SIZE, PCG::TileMap::GetTileColor(tileArray[y][x]));
        }
    }
}


// ============================================= 
// void PCG_PrintMap()
// ============================================= 
void PCG::TileMap::PrintMap() const {
    std::cout << "\n-------Map Layout:--------\n";
    // (Existing Print Logic here...)
    std::cout << "--------------------------\n";
}


// ============================================= 
// char GetTileChar(TileType tileType)
// Return a char value based on the type of tile passed in
// ============================================= 
char PCG::TileMap::GetTileChar(PCG::TileType _tileType) const {
    switch (_tileType) {
    case PCG::TileType::TILE_TYPE_DEEPLAND:
        return PCG::DEEPLAND_CHAR;
    case PCG::TileType::TILE_TYPE_LAND:
        return PCG::LAND_CHAR;
    case PCG::TileType::TILE_TYPE_BEACH:
        return PCG::BEACH_CHAR;
    case PCG::TileType::TILE_TYPE_OCEAN:
        return PCG::OCEAN_CHAR;
    case PCG::TileType::TILE_TYPE_DEEPOCEAN:
        return PCG::DEEPOCEAN_CHAR;
    default:
        return '?';
    }
}


// ============================================= 
// void PCG_SaveMapData(const char* _filename)
// Store our tilemap data to a text file using the input _filename
// ============================================= 
void PCG::TileMap::SaveMapData(const char* _filename) const {
    std::fstream file;
    file.open(_filename, std::ios::out); // Open C++ file stream for writing
    if (!file.is_open()) { // Check if file opened successfully
        return;
    }

    // Write each single tileArray character into our file stream
    for (int y = 0; y < PCG::MAP_ROWS; y++) {
        for (int x = 0; x < PCG::MAP_COLUMNS; x++) {
            file.put(PCG::TileMap::GetTileChar(tileArray[y][x])); // Write char to C++ file stream
        }

        file.put('\n'); // New line at end of row for C++ file stream
    }

    file.close(); // Close C++ file stream
    printf("Map saved to %s\n", _filename);
}


// ============================================= 
// void PCG_LoadMapData(const char* _filename)
// Load our tilemap data from a text file, using input _filename
// ============================================= 
void PCG::TileMap::LoadMapData(const char* _filename) {
    std::fstream file;  // C++ file stream object for reading
    file.open(_filename, std::ios::in); // Open C++ file stream for reading

    if (!file.is_open()) { // Check if file opened successfully for C++ stream
        return;
    }


    // Get each character from our file stream, and load it into our tileMap array
    for (int y = 0; y < PCG::MAP_ROWS; y++) {
        for (int x = 0; x < PCG::MAP_COLUMNS; x++) {
            int ch = file.get(); // Get char from C++ file stream
            // Skip invisible newline characters
            while (ch == '\n' || ch == '\r') {
                ch = file.get(); // Get char from C++ file stream for skipping newlines
            }


            if (ch == PCG::LAND_CHAR) {
                tileArray[y][x] = PCG::TileType::TILE_TYPE_LAND;
            }
            else if (ch == PCG::OCEAN_CHAR) {
                tileArray[y][x] = PCG::TileType::TILE_TYPE_OCEAN;
            }
            else if (ch == PCG::DEEPLAND_CHAR) {
                tileArray[y][x] = PCG::TileType::TILE_TYPE_DEEPLAND;
            }
            else if (ch == PCG::DEEPOCEAN_CHAR) {
                tileArray[y][x] = PCG::TileType::TILE_TYPE_DEEPOCEAN;
            }
            else if (ch == PCG::BEACH_CHAR) {
                tileArray[y][x] = PCG::TileType::TILE_TYPE_BEACH;
            }
        }
    }

    file.close(); // Close C++ file stream
    std::cout << "Map loaded from " << _filename << std::endl; // C++ style print statement
}


// ============================================= 
// void PCG_SaveMapImage(const char* filename)
// Store our tileMap data as a .png image, using the input filename.
// ============================================= 
void PCG::TileMap::SaveMapImage(const char* filename) const {
    Image mapImage = GenImageColor(PCG::MAP_COLUMNS, PCG::MAP_ROWS, BLACK);

    for (int y = 0; y < PCG::MAP_ROWS; y++) {
        for (int x = 0; x < PCG::MAP_COLUMNS; x++) {
            Color c = PCG::TileMap::GetTileColor(tileArray[y][x]);
            ImageDrawPixel(&mapImage, x, y, c);
        }
    }

    if (ExportImage(mapImage, filename)) {
        // printf("Image saved: %s\n", filename); // old C-style print statement
        std::cout << "Image saved: " << filename << std::endl; // C++ style print statements
    }

    UnloadImage(mapImage);
}


// ============================================= 
// void PCG_DrawGUI()
// ============================================= 
char PCG::TILE_TYPE_TO_SET = '1';

char* PCG::MAP_TEXT_FILENAME = "pcg_map_data.txt";
char* PCG::MAP_IMAGE_FILENAME = "pcg_map.png";

void PCG::TileMap::DrawGUI() {
    // Reset Button
    if (GuiButton(RESET_BUTTON_BOUNDS, "Reset Map")) {
        //CreateMap();
        // pass in this instances tileArray to our map generator, and call the generate function to fill it with new data.
        GetMapGenerator()->Generate(tileArray);
    }

    // Name Text Box Input
    static char filenameInput[100] = "pcg_map_data.txt"; // Buffer for text input
    Rectangle textBoxRect = { PCG::BUTTON_X, PCG::BUTTON_Y - PCG::SCREEN_HEIGHT + 80, PCG::BUTTON_WIDTH, PCG::BUTTON_HEIGHT };
    GuiTextBox(textBoxRect, filenameInput, sizeof(filenameInput), true); // Text box for filename input
    PCG::MAP_TEXT_FILENAME = filenameInput; // Update the text filename variable with the text box input
    PCG::MAP_IMAGE_FILENAME = filenameInput; // Update the image filename variable with the text box input

    // Save Data Button
    Rectangle saveRect = { PCG::BUTTON_X, PCG::BUTTON_Y - 70, PCG::BUTTON_WIDTH, PCG::BUTTON_HEIGHT };
    if (GuiButton(saveRect, "Save Map Data")) {
        SaveMapData(MAP_TEXT_FILENAME);
    }

    // Load Data Button
    Rectangle loadRect = { PCG::BUTTON_X, PCG::BUTTON_Y - 140, PCG::BUTTON_WIDTH, PCG::BUTTON_HEIGHT };
    if (GuiButton(loadRect, "Load Map Data")) {
        LoadMapData(MAP_TEXT_FILENAME);
    }


    // Save Image Button
    Rectangle imgRect = { PCG::BUTTON_X, PCG::BUTTON_Y - 210, PCG::BUTTON_WIDTH, PCG::BUTTON_HEIGHT };
    if (GuiButton(imgRect, "Save Map PNG")) {
        SaveMapImage(MAP_IMAGE_FILENAME);
    }

    // SET TILE BUTTONS
    // 
    // Set Tile Type to Deep Land Button
    Rectangle deeplandRect = { 10, PCG::BUTTON_Y - 280, PCG::BUTTON_WIDTH, PCG::BUTTON_HEIGHT };
    if (GuiButton(deeplandRect, "Set Tile: Deep Land")) {
        PCG::TILE_TYPE_TO_SET = '5';
    }

    // Set Tile Type to Land Button
    Rectangle landRect = { 10, PCG::BUTTON_Y - 210, PCG::BUTTON_WIDTH, PCG::BUTTON_HEIGHT };
    if (GuiButton(landRect, "Set Tile: Land")) {
        PCG::TILE_TYPE_TO_SET = '4';
    }

    // Set Tile Type to Beach Button
    Rectangle beachRect = { 10, PCG::BUTTON_Y - 140, PCG::BUTTON_WIDTH, PCG::BUTTON_HEIGHT };
    if (GuiButton(beachRect, "Set Tile: Beach")) {
        PCG::TILE_TYPE_TO_SET = '3';
    }

    // Set Tile Type to Ocean Button
    Rectangle oceanRect = { 10, PCG::BUTTON_Y - 70, PCG::BUTTON_WIDTH, PCG::BUTTON_HEIGHT };
    if (GuiButton(oceanRect, "Set Tile: Ocean")) {
        PCG::TILE_TYPE_TO_SET = '2';
    }

    // Set Tile Type to Deep Ocean Button
    Rectangle deepoceanRect = { 10, PCG::BUTTON_Y, PCG::BUTTON_WIDTH, PCG::BUTTON_HEIGHT };
    if (GuiButton(deepoceanRect, "Set Tile: Deep Ocean")) {
        PCG::TILE_TYPE_TO_SET = '1';
    }

}

// =============================================
// SetMapGenerator and GetMapGenerator functions for our TileMap class, to allow us to assign a map generator to our tilemap, and retrieve it when we want to generate new maps.
// =============================================
void PCG::TileMap::SetMapGenerator(PCG::MapGenerator* generator) {
    mapGenerator = generator;
}

// =============================================
// GetMapGenerator returns a pointer to the current map generator assigned to this tilemap, so we can call its Generate function when we want to create new maps.
// =============================================
PCG::MapGenerator* PCG::TileMap::GetMapGenerator() const {
    return mapGenerator;
}

// =============================================
// MapGenerator
// =============================================
// As it is a pure virtual class, we don't need to implement anything here. The derived classes will provide the actual generation logic.


// Derived classes will implement the Generate function to create different types of maps.
// =============================================
// RandomMapGenerator
// =============================================
// Constructor
PCG::RandomMapGenerator::RandomMapGenerator() {
    // nothing to initialize for now, but you could seed a random generator here if you want reproducible maps
}

// Destructor
PCG::RandomMapGenerator::~RandomMapGenerator() {
    // nothing to clean up for now, but if you had allocated resources (like noise generators) you would release them here
}

void PCG::RandomMapGenerator::Generate(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]) {
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            _tileArray[y][x] = (TileType)GetRandomValue(0, TILE_COUNT - 1);
        }
    }
}


// =============================================
// NoiseGenerator
// =============================================
// Constructor
PCG::NoiseMapGenerator::NoiseMapGenerator() {
    // nothing to initialize for now, but you could seed a random noise here if you want reproducible maps
}

// Destructor
PCG::NoiseMapGenerator::~NoiseMapGenerator() {
    // nothing to clean up for now, but if you had allocated resources (like noise generators) you would release them here
}

void PCG::NoiseMapGenerator::Generate(TileType _tileArray[MAP_ROWS][MAP_COLUMNS]) {
    // Random offsets make the map different every time
    int offsetX = GetRandomValue(0, 1000);
    int offsetY = GetRandomValue(0, 1000);
    float scale = 2.5f;

    // Raylib's Perlin Noise function
    Image noiseImg = GenImagePerlinNoise(MAP_COLUMNS, MAP_ROWS, offsetX, offsetY, scale);

    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLUMNS; x++) {
            // Read the brightness of the noise pixel
            Color col = GetImageColor(noiseImg, x, y);
            float brightness = (col.r + col.g + col.b) / (3.0f * 255.0f);

            // Threshold:
            if (brightness < 0.30f) {
                _tileArray[y][x] = TILE_TYPE_DEEPOCEAN;
            }
            else if (brightness < 0.49f && brightness >= 0.30f) {
				_tileArray[y][x] = TILE_TYPE_OCEAN;
            }
			else if (brightness < 0.51f && brightness >= 0.49f) {
                _tileArray[y][x] = TILE_TYPE_BEACH;
			}
            else if (brightness < 0.70f && brightness >= 0.51f) {
                _tileArray[y][x] = TILE_TYPE_LAND;
			}
            else if (brightness >= 0.70f) {
                _tileArray[y][x] = TILE_TYPE_DEEPLAND;
            }
        }
    }
    UnloadImage(noiseImg);
}