//
//  main.cpp
//  Tetris
//
//  Created by Santiago Vera on 07/07/20.
//  Copyright © 2020 Mistic_Lion. All rights reserved.
//

#define OLC_PGE_APPLICATION
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
//#include "soloud.h"
//#include "soloud_wav.h"
#include "olcPixelGameEngine.h"
using namespace std;

class Juego : public olc::PixelGameEngine { // Heritate PGE class from header

private:

    int long score; // Integer for the acumulated amount of tetrominos acumulated

    int Speed = 30; // Fall speed of the pieces

    int FieldWidth = 60; // Width of the field of the tetromino
    int FieldHeight = 100; // Height of the field of the tetromino
    int cont = 0; // General counter that increasses each frame
    int cont_2 = 0; // Counter to get the state of the rotation of an specific tetromino (stick tetromino)
    int cont_3 = 0; // Counter for time in contact with floor or a tetromino from the mesh
    int cont_4 = 0;
    int FramesToGoDown = 0;

    int Tetromino_Type = rand() % 7; // Initialize the tetromino at a random type of piece from the 7 ones
    int long UserTetrominoArraySize = 0; // Gets the amount of blocks of the user tetromino
    int long MeshTetrominoArraySize = 0; // Gets the amount of blocks of a tetromino form the mesh of tetrominos at the bottom
    int long MeshIndex = 0; // Gets the size of the mesh of tetrominos at the bottom
    int long SavedArraySize = 0; // Gets the amount of blocks from the saved tetromino (not useful)

    int const static Block_Size = 4; // Size of each block that composses each tetromino

    struct Coord { // A struct for coordinates to compose an element
        float x, y; // X and Y values
    };

    struct Cubes { // A struct that represents a tetromino
        vector <Coord> Arr; // This contains all the top left coordinates of each cube that the tetromino has
        olc::Pixel Colour; // This is the colour of the tetromino, uses a pixel object from the header
    };

    int Saved_Type; // The type of tetromino that the saved tetromino has
    bool HasBeenPressed = false; // A flag to check if the shift has been pressed and regulates if the switch needs to be made with the saved type or the next type
    int Next_Type = 5; // Initializes the next type as a 5 type

    vector <Cubes> Tetromino; // Vector that contains all the diferent tetrominos
    vector <Cubes> Tetromino_Mesh; // Mesh for all the tetrominos acumulated at the bottom of the field
    vector <Cubes> Next_Tetromino; // Vector for the next tetromino


    float Pos_X; // Has the x position of the current piece
    float Pos_Y = 28; // Has the y position of the current piece
    bool CanSwitch = true; // Allows the current piece to switch with both the saved type or the next type and save the current

    int OffSet_X_SavedTetromino = 0; // X coordinate of the predetermined square that is outside of the saved tetromino
    int OffSet_Y_SavedTetromino = 0; // Y coordinate of the predetermined square that is outside of the saved tetromino
    int OffSet_X_NextTetromino = 0; // X coordinate of the predetermined square that is outside of the next tetromino
    int OffSet_Y_NextTetromino = 0; // Y coordinate of the predetermined square that is outside of the next tetromino

    float User_Flag = 0; // Variable that determines the speed of the movement once the movement keys have been pressed for long enough
    float User_Flag2 = 0; // Unused
    float KeyHoldFlag = 0; // Variable that determines if the movement key has been pressed for long enough
    float KeyHoldFlag2 = 0; // Unused
    float User_Y = 0; // Unused

    int nSample = 0; // Unused

public:
    Juego() {
        sAppName = "Tetris"; // Determines the name of the app that appears on the top of the window
    }
    ~Juego() {}

    //SoLoud::Soloud gSoloud; // Was going to be used to play sounds

    olc::Sprite* sprFondo = nullptr; // Pointer to the sprite of the background
    olc::Decal* Fondo = nullptr; // ponter to the decal of the background

    string Puntaje; // A string that saves the score

    int Layer1 = 0; // Interger of the level of a layer
    int Layer2 = 1; // Interger of the level of a layer

    int PuntajeReal = 0; // Variable for the final score
    int LineasCompletadas = 0; // Variable to count the amount of times a line is completed

    //SoLoud::Wav TitleMusic; // Was going to be used for music

    void DrawField() { // Draws the field
        int BorderField_OOB_X = ((ScreenWidth() - FieldWidth) / 2) - 2; // Sets the top left x coordinate of the field
        int BorderField_OOB_Y = ((ScreenHeight() - FieldHeight) / 2) - 2; // Sets the top left y coordinate of the field

        int x1 = BorderField_OOB_X; // Manually sets a value for the coordinates of each stop at the field renderization
        int y1 = BorderField_OOB_Y;
        int x2 = BorderField_OOB_X + Block_Size;
        int y2 = BorderField_OOB_Y + FieldHeight;
        int x3 = x2;
        int y3 = y2 - Block_Size;
        int x4 = x2 + FieldWidth - Block_Size;
        int y4 = y2 + 1;
        int x5 = x4 - Block_Size;
        int y5 = y1;
        int x6 = x4 + 1;
        int y6 = y4;

        FillRect(x1, y1 - 1, Block_Size, FieldHeight + 1, olc::WHITE); // Fills a rectangle (wide line) on the left of the field vertically
        FillRect(x3, y3, FieldWidth-3, Block_Size, olc::WHITE); // Fills a rectangle (wide line) on the bottom of the field horizontaly
        FillRect(x5+1, y5 - 1, Block_Size, FieldHeight + 1, olc::WHITE); // Fills a rectangle (wide line) on the right of the field verticaly

        
        auto transpColor = olc::Pixel(0, 0, 0, 150); // Creates a black pixel with 150/255 transparency
        for (int i = y1; i < y2; i = i + 4) { // Goes through the field vertically with a separation of the block size each iteration
            DrawLine(x1 + Block_Size, i, x4 - 1 - Block_Size, i, transpColor); // Draws a line from left to right
        }
        for (int j = x1 + Block_Size; j < x4 - Block_Size + 1; j = j + 4) { // Goes through the field horizontaly with a separation of the block size each iteration
            DrawLine(j, y1, j, y2 - Block_Size - 1, transpColor); // Draws a line from top to bottom
        }
        Draw({ x4 - Block_Size , y2 - 4 }, transpColor); // Draws a pixel on a place not considered on the calculations (right bottom of the field)
        

        DrawLine(x5, y5 - 1, x5, y5, olc::BLACK); // Draws some useless line

        DrawSquareNextToField(OffSet_X_SavedTetromino, OffSet_Y_SavedTetromino); // Draws a square for the outside of the saved tetromino
        DrawSquareNextToField(OffSet_X_NextTetromino, OffSet_Y_NextTetromino); // Draws a square for  the outside of the next tetromino
        DrawLine(OffSet_X_NextTetromino + (Block_Size * 4) + 1, OffSet_Y_NextTetromino, OffSet_X_NextTetromino + 1 + (Block_Size * 4), OffSet_Y_NextTetromino + (4 * Block_Size)); // Hardcoded drawing of a line at the right of the next tetromino square

    }

    void DrawSquareNextToField(int x, int y) { // Draws a square of size 4 times the tetromino size
        DrawLine(x, OffSet_Y_SavedTetromino - 1, x + 1 + (Block_Size * 4), y - 1); // Top line
        DrawLine(y + 1 + (Block_Size * 4), OffSet_Y_SavedTetromino, OffSet_X_SavedTetromino + 1 + (Block_Size * 4), y + (Block_Size * 4)); // Right line
        DrawLine(x + 1 + (Block_Size * 4), y + (Block_Size * 4) + 1, x, y + (4 * Block_Size) + 1); // Bottom line
        DrawLine(x - 1, y + (4 * Block_Size) + 1, x - 1, y - 1); // Left line

    }

    void Rotate_Tetromino() { // Rotates the current tetromino at a grid placed at (0,0)
        int ID[8]; // An ID in the grid for each of the maximum 8 tetrominos
        if (GetKey(olc::SPACE).bPressed and Tetromino_Type != 4 and Tetromino_Type != 1) { // Proceeds if the space key is pressed and avoids either if the current type are 4 (cant be rotated) or 1 (diferent rotation)

            for (int i = 0; i < UserTetrominoArraySize; i++) { // Goes through all the blocks of the current tetromino (imagine it as a 4x4 grid)
                int x = (Tetromino[Tetromino_Type].Arr[i].x / 4); // Gets the x coordinate of the current block and divides it in 4 (because of the size) - normalize
                int y = (Tetromino[Tetromino_Type].Arr[i].y / 4); // Gets the y coordinate of the current block and divides it in 4 (because of the size) - normalize

                ID[i] = 3 - y + (4 * x); // Gets the new ID of the block (using the n_id = (w - 1) - y + (w * x) formula) - Formula is the id = (w * y) + x, using the rotated coordinates (n_x = x*cos(90) - y*(sin(90), n_y = x*sin(90) + y*cos(90)) and offsetting x by 3 to correct the rotation inside bounds

                y = (ID[i] / 4); // Gets y by dividing exactly by 4 (width of the grid) and neglecting the reminder - get the column
                x = ID[i] - (4 * y); // Gets x by clearing x in the id = wy + x formula, x = id - wy

                x = x * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid
                y = y * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid

                Tetromino[Tetromino_Type].Arr[i].x = x; // Sets the new x
                Tetromino[Tetromino_Type].Arr[i].y = y; // Sets the new y
            }

        }
        else if (GetKey(olc::SPACE).bPressed and Tetromino_Type == 1) { // For case 1 of tetromino

            if (cont_2 == 0) { // If the position is right it does a clockwise rotation
                for (int i = 0; i < UserTetrominoArraySize; i++) { // Rotation done as in the previous case
                    int x = (Tetromino[Tetromino_Type].Arr[i].x / 4); // Gets the x coordinate of the current block and divides it in 4 (because of the size) - normalize
                    int y = (Tetromino[Tetromino_Type].Arr[i].y / 4); // Gets the y coordinate of the current block and divides it in 4 (because of the size) - normalize
                    ID[i] = 3 - y + (4 * x); // Gets the new ID of the block (using the n_id = (w - 1) - y + (w * x) formula) - Formula is the id = (w * y) + x, using the rotated coordinates (n_x = x*cos(90) - y*(sin(90), n_y = x*sin(90) + y*cos(90)) and offsetting x by 3 to correct the rotation inside bounds

                    y = (ID[i] / 4); // Gets y by dividing exactly by 4 (width of the grid) and neglecting the reminder - get the column
                    x = ID[i] - (4 * y); // Gets x by clearing x in the id = wy + x formula, x = id - wy

                    Tetromino[Tetromino_Type].Arr[i].x = x * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid and sets the new x
                    Tetromino[Tetromino_Type].Arr[i].y = y * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid and sets the new y
                }
                cont_2 = 1; // Sets the counter as 1 (case flip flop)
            }
            else if (cont_2 == 1) { // If the position is diferent to case 1, it does a counterclockwise rotation
                for (int i = 0; i < Tetromino[Tetromino_Type].Arr.size(); i++) { // Iterates through all the blocks of the tetromino
                    int x = (Tetromino[Tetromino_Type].Arr[i].x / 4); // Gets the x coordinate of the current block and divides it in 4 (because of the size) - normalize
                    int y = (Tetromino[Tetromino_Type].Arr[i].y / 4); // Gets the y coordinate of the current block and divides it in 4 (because of the size) - normalize

                    ID[i] = 12 + y - (x * 4); // Gets the new ID of the block (using the n_id = y + (w * (x + (w - 1))) formula) - Formula is the id = (w * y) + x, using the rotated coordinates (n_x = x*cos(90) - y*(sin(90), n_y = x*sin(90) + y*cos(90)) and offsetting y by 3 to correct the rotation inside bounds

                    y = (ID[i] / 4); // Gets y by dividing exactly by 4 (width of the grid) and neglecting the reminder - get the colu
                    x = ID[i] - (4 * y); // Gets x by clearing x in the id = wy + x formula, x = id - wy

                    Tetromino[Tetromino_Type].Arr[i].x = x * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid and sets the new x
                    Tetromino[Tetromino_Type].Arr[i].y = y * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid and sets the new y
                }
                cont_2 = 0; // Sets the counter as 0 (case flip flop)
            }
        }
    }

    bool DoesPieceFit() { // Checks if the piece does not colide with the right wall of the field
        for (int i = 0; i < UserTetrominoArraySize; i++) { // Goes through all the blocks of the tetromino
            if ((Tetromino[Tetromino_Type].Arr[i].x + Pos_X) >= (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (1 * Block_Size)) - Block_Size)return false; // Returns false if greater than the right wall pos
        }

        return true;
    }

    bool DoesPieceFit2() { // Checks if the piece does not colide with the left wall of the field
        for (int i = 0; i < UserTetrominoArraySize; i++) { // Goes through all the blocks of the tetromino
            if ((Tetromino[Tetromino_Type].Arr[i].x + Pos_X) <= (((ScreenWidth() - FieldWidth) / 2) - 2)) return false; // Returns false if lesser than the left wall pos
        }
        return true;
    }

    bool DoesPieceFit3() { // Checks if the piece does not colide with the bottom of the field
        for (int i = 0; i < UserTetrominoArraySize; i++) { // Goes through all the blocks of the tetromino
            if ((Tetromino[Tetromino_Type].Arr[i].y + Pos_Y) >= ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size)) return false; //  // Returns false if greater than the bottom pos
        }
        return true;
    }

    bool DoesPieceFitDown() { // Checks if the down movement of the tetromino does not fit
        for (int i = 0; i < UserTetrominoArraySize; i++) { // Iterates through all the blocks of the player tetromino
            for (int j = 0; j <= MeshIndex; j++) { // Iterates trough the mesh of tetrominos at the bottom
                MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size(); // Gets the size of the current tetromino
                for (int k = 0; k < MeshTetrominoArraySize; k++) { // Iterates through all the blocks of the tetromino
                    if (Tetromino[Tetromino_Type].Arr[i].y + Pos_Y + 4 < Tetromino_Mesh[j].Arr[k].y + 4 and Tetromino[Tetromino_Type].Arr[i].y + Pos_Y + 8 > Tetromino_Mesh[j].Arr[k].y) { // Checks for vertical collision offsetted by block size on y
                        if (Tetromino[Tetromino_Type].Arr[i].x + Pos_X<Tetromino_Mesh[j].Arr[k].x + 4 and Tetromino[Tetromino_Type].Arr[i].x + Pos_X + 4>Tetromino_Mesh[j].Arr[k].x) return false; // If also has a horizontal collision, returns false
                    }
                }
            }
        }
        return true;
    }

    bool DoesPieceFitRight() { // Checks if the right movement of the tetromino does not fit
        for (int i = 0; i < UserTetrominoArraySize; i++) { // Iterates through all the blocks of the player tetromino
            for (int j = 0; j <= MeshIndex; j++) { // Iterates trough the mesh of tetrominos at the bottom
                MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size(); // Gets the size of the current tetromino
                for (int k = 0; k < MeshTetrominoArraySize; k++) { // Iterates through all the blocks of the tetromino
                    if (Tetromino[Tetromino_Type].Arr[i].y + Pos_Y<Tetromino_Mesh[j].Arr[k].y + 4 and Tetromino[Tetromino_Type].Arr[i].y + Pos_Y + 4>Tetromino_Mesh[j].Arr[k].y) { // Checks for vertical collision
                        if (Tetromino[Tetromino_Type].Arr[i].x + Pos_X + 4 < Tetromino_Mesh[j].Arr[k].x + 4 and Tetromino[Tetromino_Type].Arr[i].x + Pos_X + 8 > Tetromino_Mesh[j].Arr[k].x) return false; // If also has a horizontal collision offsetted by block size on x, returns false
                    }
                }
            }
        }
        return true;
    }

    bool DoesPieceFitLeft() { // Checks if the left movement of the tetromino does not fit
        for (int i = 0; i < UserTetrominoArraySize; i++) { // Iterates through all the blocks of the player tetromino
            for (int j = 0; j <= MeshIndex; j++) { // Iterates trough the mesh of tetrominos at the bottom
                MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size(); // Gets the size of the current tetromino
                for (int k = 0; k < MeshTetrominoArraySize; k++) { // Iterates through all the blocks of the tetromino
                    if (Tetromino[Tetromino_Type].Arr[i].y + Pos_Y<Tetromino_Mesh[j].Arr[k].y + 4 and Tetromino[Tetromino_Type].Arr[i].y + Pos_Y + 4>Tetromino_Mesh[j].Arr[k].y) { // Checks for vertical collision
                        if (Tetromino[Tetromino_Type].Arr[i].x + Pos_X - 4 < Tetromino_Mesh[j].Arr[k].x + 4 and Tetromino[Tetromino_Type].Arr[i].x + Pos_X > Tetromino_Mesh[j].Arr[k].x) return false; // If also has a horizontal collision offsetted by block size on x, returns false
                    }
                }
            }
        }
        return true;
    }

    bool NextRotationDoesFit() { // Checks if the next rotation does not fit
        int ID[8]; // An ID in the grid for each of the maximum 8 tetrominos

        if (Tetromino_Type != 4 and Tetromino_Type != 1) { // Avoids either if the current type are 4 (cant be rotated) or 1 (diferent rotation)
            for (int i = 0; i < UserTetrominoArraySize; i++) { // Goes through all the blocks of the current tetromino (imagine it as a 4x4 grid)
                int x = (Tetromino[Tetromino_Type].Arr[i].x / 4); // Gets the x coordinate of the current block and divides it in 4 (because of the size) - normalize
                int y = (Tetromino[Tetromino_Type].Arr[i].y / 4); // Gets the y coordinate of the current block and divides it in 4 (because of the size) - normalize

                ID[i] = 3 - y + (4 * x); // Gets the new ID of the block (using the n_id = (w - 1) - y + (w * x) formula) - Formula is the id = (w * y) + x, using the rotated coordinates (n_x = x*cos(90) - y*(sin(90), n_y = x*sin(90) + y*cos(90)) and offsetting x by 3 to correct the rotation inside bounds

                y = (ID[i] / 4); // Gets y by dividing exactly by 4 (width of the grid) and neglecting the reminder - get the column
                x = ID[i] - (4 * y); // Gets x by clearing x in the id = wy + x formula, x = id - wy

                x = x * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid
                y = y * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid

                //if ((x + Pos_X) > (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (3 * Block_Size)) or (x + Pos_X - 1 < (((ScreenWidth() - FieldWidth) / 2) - 2)) or (y + Pos_Y > ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size))) return false;

                for (int j = 0; j <= MeshIndex; j++) { // Goes through all the tetrominos inside the mesh
                    MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size(); // Gets the size of the current tetromino
                    for (int k = 0; k < MeshTetrominoArraySize; k++) { // Goes through all the blocks of the tetromino
                        if (y + Pos_Y + 1 <= Tetromino_Mesh[j].Arr[k].y + 4 and y + Pos_Y + 3 >= Tetromino_Mesh[j].Arr[k].y) { // Checks for vertical collision
                            if (x + Pos_X + 1 <= Tetromino_Mesh[j].Arr[k].x + 4 and x + Pos_X + 3 >= Tetromino_Mesh[j].Arr[k].x) // Checks for horizontal collision
                                return false;
                        }
                    }
                }
            }
        }
        else if (Tetromino_Type == 1) { // For case 1 of tetromino

            if (cont_2 == 0) { // If the position is right it does a clockwise rotation
                for (int i = 0; i < UserTetrominoArraySize; i++)   Rotation done as in the previous case
                    int x = (Tetromino[Tetromino_Type].Arr[i].x / 4); // Gets the x coordinate of the current block and divides it in 4 (because of the size) - normalize
                    int y = (Tetromino[Tetromino_Type].Arr[i].y / 4); // Gets the y coordinate of the current block and divides it in 4 (because of the size) - normalize

                    ID[i] = 3 - y + (4 * x); // Gets the new ID of the block (using the n_id = (w - 1) - y + (w * x) formula) - Formula is the id = (w * y) + x, using the rotated coordinates (n_x = x*cos(90) - y*(sin(90), n_y = x*sin(90) + y*cos(90)) and offsetting x by 3 to correct the rotation inside bounds

                    y = (ID[i] / 4); // Gets y by dividing exactly by 4 (width of the grid) and neglecting the reminder - get the column
                    x = ID[i] - (4 * y); // Gets x by clearing x in the id = wy + x formula, x = id - wy

                    x = x * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid and sets the new x
                    y = y * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid and sets the new x

                    /*if ((x + Pos_X) > (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (3 * Block_Size)) or (x + Pos_X - 1 < (((ScreenWidth() - FieldWidth) / 2) - 2)) or (y + Pos_Y > ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size)))
                        return false;*/

                    for (int j = 0; j <= MeshIndex; j++) { // Goes through all the tetrominos inside the mesh
                        MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size(); // Gets the size of the current tetromino
                        for (int k = 0; k < MeshTetrominoArraySize; k++) { // Goes through all the blocks of the tetromino
                            if (y + Pos_Y + 1 <= Tetromino_Mesh[j].Arr[k].y + 4 and y + Pos_Y + 3 >= Tetromino_Mesh[j].Arr[k].y) { // Checks for vertical collision
                                if (x + Pos_X + 1 <= Tetromino_Mesh[j].Arr[k].x + 4 and x + Pos_X + 3 >= Tetromino_Mesh[j].Arr[k].x)return false; // Checks for horizontal collision
                            }
                        }
                    }
                }
            }
            else if (cont_2 == 1) { // If the position is diferent to case 1, it does a counterclockwise rotation
                for (int i = 0; i < Tetromino[Tetromino_Type].Arr.size(); i++) { // Iterates through all the blocks of the tetromino
                    int x = (Tetromino[Tetromino_Type].Arr[i].x / 4); // Gets the x coordinate of the current block and divides it in 4 (because of the size) - normalize
                    int y = (Tetromino[Tetromino_Type].Arr[i].y / 4); // Gets the y coordinate of the current block and divides it in 4 (because of the size) - normalize

                    ID[i] = 12 + y - (x * 4); // Gets the new ID of the block (using the n_id = y + (w * (x + (w - 1))) formula) - Formula is the id = (w * y) + x, using the rotated coordinates (n_x = x*cos(90) - y*(sin(90), n_y = x*sin(90) + y*cos(90)) and offsetting y by 3 to correct the rotation inside bounds

                    y = (ID[i] / 4); // Gets y by dividing exactly by 4 (width of the grid) and neglecting the reminder - get the colu
                    x = ID[i] - (4 * y); // Gets x by clearing x in the id = wy + x formula, x = id - wy

                    x = x * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid and sets the new x
                    y = y * 4; // Multiplies by 4 to adjust the coordinate to a 16x16 grid and sets the new x

                    //if ((x + Pos_X) > (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (3 * Block_Size)) or (x + Pos_X - 1 < (((ScreenWidth() - FieldWidth) / 2) - 2)) or (y + Pos_Y > ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size))) return false;

                    for (int j = 0; j <= MeshIndex; j++) { // Goes through all the tetrominos inside the mesh
                        MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size(); // Gets the size of the current tetromino
                        for (int k = 0; k < MeshTetrominoArraySize; k++) { // Goes through all the blocks of the tetromino
                            if (y + Pos_Y + 1 <= Tetromino_Mesh[j].Arr[k].y + 4 and y + Pos_Y + 3 >= Tetromino_Mesh[j].Arr[k].y) { // Checks for vertical collision
                                if (x + Pos_X + 1 <= Tetromino_Mesh[j].Arr[k].x + 4 and x + Pos_X + 3 >= Tetromino_Mesh[j].Arr[k].x) return false; // Checks for horizontal collision
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    bool SavedTypeDoesFit() { // Checks if the saved tetromino does not fit in the mesh
        if (HasBeenPressed) { // If the saved slot contains something
            for (int i = 0; i < Next_Tetromino[Saved_Type].Arr.size(); i++) { // Goes through all the blocks of the tetromino
                int x = Tetromino[Saved_Type].Arr[i].x; // Gets the x position of the current block
                int y = Tetromino[Saved_Type].Arr[i].y; // Gets the y position of the current block

                if ((x + Pos_X) > (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (3 * Block_Size)) or (x + Pos_X - 1 < (((ScreenWidth() - FieldWidth) / 2) - 2)) or (y + Pos_Y > ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size))) // Checks for collisions on the left, the right and the bottom of the field
                    return false;

                for (int j = 0; j <= MeshIndex; j++) { // Goes through all the tetrominos in the mesh
                    MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size(); // Gets the size of the tetromino at the mesh
                    for (int k = 0; k < MeshTetrominoArraySize; k++) { // Goes through all the blocks of the tetromino
                        if (y + Pos_Y + 1 <= Tetromino_Mesh[j].Arr[k].y + 4 and y + Pos_Y + 3 >= Tetromino_Mesh[j].Arr[k].y) { // Checks for vertical colisions
                            if (x + Pos_X + 1 <= Tetromino_Mesh[j].Arr[k].x + 4 and x + Pos_X + 3 >= Tetromino_Mesh[j].Arr[k].x) return false; // Checks for horizontal collisions
                        }
                    }
                }
            }
        }
        return true;
    }

    void MoveTetromino(float vel = 1) { // Moves the tetromino with a certain velocity

        if (GetKey(olc::RIGHT).bPressed and DoesPieceFit() and DoesPieceFitRight()) { // If the right key is pressed and does fit both in the field and in the mesh
            Pos_X = Pos_X + 4; // Increments constantly
        }

        else if (GetKey(olc::RIGHT).bHeld and DoesPieceFit() and DoesPieceFitRight()) { // If the right key is held and does fit both in the field and in the mesh, moves faster
            KeyHoldFlag++; // Increments the hold flag
            if (KeyHoldFlag > (5 / (GetElapsedTime() * 20))) { // Waits to be greater than some amount
                User_Flag = User_Flag + vel * GetElapsedTime() * 20; // Increments the movement flag

                if (User_Flag >= 1) { // After it beeing greater or equal than one
                    Pos_X = Pos_X + 4; // Increments constantly
                    User_Flag = 0; // Movement flag set to cero
                }
            }
        }

        else if (GetKey(olc::RIGHT).bReleased and !GetKey(olc::LEFT).bHeld) KeyHoldFlag = 0; // If key is released, hold flag is set to cero



        else if (GetKey(olc::LEFT).bPressed and DoesPieceFit2() and DoesPieceFitLeft()) { // If the left key is pressed and does fit both in the field and in the mesh
            Pos_X = Pos_X - 4; // Decreases constantly
        }

        else if (GetKey(olc::LEFT).bHeld and DoesPieceFit2() and DoesPieceFitLeft()) { // If the left key is held and does fit both in the field and in the mesh, moves faster
            KeyHoldFlag++; // Increments the hold flag
            if (KeyHoldFlag > (5 / (GetElapsedTime() * 20))) { // Waits to be greater than some amount
                User_Flag = User_Flag + vel * GetElapsedTime() * 20; // Increments the movement flag

                if (User_Flag >= 1) { // After it beeing greater or equal than one
                    Pos_X = Pos_X - 4; // Increments constantly
                    User_Flag = 0; // Movement flag set to cero
                }
            }
        }

        else if (GetKey(olc::LEFT).bReleased and !GetKey(olc::RIGHT).bHeld) KeyHoldFlag = 0; // If key is released, hold flag is set to cero



        if (GetKey(olc::DOWN).bPressed and DoesPieceFit3() and DoesPieceFitDown()) { // If the down key is pressed and does fit both in the field and in the mesh
            Pos_Y = Pos_Y + 4; // Increments constantly
        }

        /*else if (GetKey(olc::DOWN).bHeld and DoesPieceFit3() and DoesPieceFitDown()) {
            KeyHoldFlag2++;
            if (KeyHoldFlag2 > (1 / (GetElapsedTime() * 10))) {
                User_Flag2 = User_Flag2 + vel * GetElapsedTime() * 20;

                if (User_Flag2 >= 1 and DoesPieceFitDown()) {
                    Pos_Y = Pos_Y + 4;
                    User_Flag2 = 0;
                }
            }
        }*/

        else if (GetKey(olc::DOWN).bReleased) KeyHoldFlag2 = 0; // If key is released, hold flag is set to cero



        if (GetKey(olc::UP).bPressed) { // If up key is pressed
            while (DoesPieceFit3() and DoesPieceFitDown()) { // While the piece fits down both in the field and in the mesh
                Pos_Y = Pos_Y + 4; // Increments constantly
            }
            cont_3 = (20 / (GetElapsedTime() * 10)); // The new tetromino counter is set to the limit of evaluation
        }
    }


    void MeshTetrominos() {
        if (!DoesPieceFit3() or !DoesPieceFitDown()) {
            cont_3++;

            if (cont_3 > (20 / (GetElapsedTime()*10) ) ) {
                Tetromino_Mesh.push_back({});
                CanSwitch = true;
                for (int j = 0; j < Tetromino[Tetromino_Type].Arr.size(); j++) {
                    MeshIndex = Tetromino_Mesh.size() - 1;

                    float x = (Tetromino[Tetromino_Type].Arr[j].x + Pos_X);
                    float y = (Tetromino[Tetromino_Type].Arr[j].y + Pos_Y);
                    Tetromino_Mesh[MeshIndex].Arr.push_back({ x, y });
                    Tetromino_Mesh[MeshIndex].Colour = Tetromino[Tetromino_Type].Colour;
                }

                Pos_X = ScreenWidth() / 2;
                Pos_Y = 28;
                Tetromino_Type = Next_Type;

                Next_Type = rand() % 7;

                if (!CheckToEraseCompleteLine()) cout << "";

                cont_3 = 0;

                if (GameOver()) {

                    cout << "Score= " << score << endl;

                    Tetromino_Mesh.clear();
                    Tetromino.clear();
                    Next_Tetromino.clear();
                    HasBeenPressed = false;
                    cont = 0;
                    Speed = 60;
                    score = 0;
                    CanSwitch = true;
                    LineasCompletadas = 0;
                }
            }
        }

    }

    void SaveTetromino() {
        if (HasBeenPressed and GetKey(olc::SHIFT).bPressed and SavedTypeDoesFit() and CanSwitch) { // Checks if shift has been pressed
            int n = Saved_Type;
            Saved_Type = Tetromino_Type;
            Tetromino_Type = n;
            CanSwitch = false;
        }

        if (!HasBeenPressed) {
            if (GetKey(olc::SHIFT).bPressed and CanSwitch) {

                HasBeenPressed = true;

                Saved_Type = Tetromino_Type;
                Tetromino_Type = Next_Type;
                Next_Type = rand() % 7;
                CanSwitch = false;
            }
        }

    }

    void DrawTetromino() {
        if (cont < 1) {

            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});



            Tetromino[0].Arr.push_back({ 8, 0 });
            Tetromino[0].Arr.push_back({ 8, 4 });
            Tetromino[0].Arr.push_back({ 12, 4 });
            Tetromino[0].Arr.push_back({ 8, 8 });
            Tetromino[0].Colour = olc::MAGENTA;

            Tetromino[1].Arr.push_back({ 0, 0 });
            Tetromino[1].Arr.push_back({ 4, 0 });
            Tetromino[1].Arr.push_back({ 8, 0 });
            Tetromino[1].Arr.push_back({ 12, 0 });
            Tetromino[1].Colour = olc::BLUE;

            Tetromino[2].Arr.push_back({ 0,0 });
            Tetromino[2].Arr.push_back({ 4,0 });
            Tetromino[2].Arr.push_back({ 8,0 });
            Tetromino[2].Arr.push_back({ 0,4 });
            Tetromino[2].Colour = olc::DARK_BLUE;

            Tetromino[3].Arr.push_back({ 4, 0 });
            Tetromino[3].Arr.push_back({ 8, 0 });
            Tetromino[3].Arr.push_back({ 12, 0 });
            Tetromino[3].Arr.push_back({ 12, 4 });
            Tetromino[3].Colour = olc::CYAN;

            Tetromino[4].Arr.push_back({ 8, 0 });
            Tetromino[4].Arr.push_back({ 8, 4 });
            Tetromino[4].Arr.push_back({ 12, 0 });
            Tetromino[4].Arr.push_back({ 12, 4 });
            Tetromino[4].Colour = olc::YELLOW;

            Tetromino[5].Arr.push_back({ 4, 4 });
            Tetromino[5].Arr.push_back({ 8, 4 });
            Tetromino[5].Arr.push_back({ 8, 0 });
            Tetromino[5].Arr.push_back({ 12, 0 });
            Tetromino[5].Colour = olc::GREEN;

            Tetromino[6].Arr.push_back({ 4, 0 });
            Tetromino[6].Arr.push_back({ 8, 0 });
            Tetromino[6].Arr.push_back({ 8, 4 });
            Tetromino[6].Arr.push_back({ 12, 4 });
            Tetromino[6].Colour = olc::RED;


            //----------------------------------

            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});



            Next_Tetromino[0].Arr.push_back({ 8, 0 });
            Next_Tetromino[0].Arr.push_back({ 8, 4 });
            Next_Tetromino[0].Arr.push_back({ 12, 4 });
            Next_Tetromino[0].Arr.push_back({ 8, 8 });
            Next_Tetromino[0].Colour = olc::MAGENTA;

            Next_Tetromino[1].Arr.push_back({ 0, 0 });
            Next_Tetromino[1].Arr.push_back({ 4, 0 });
            Next_Tetromino[1].Arr.push_back({ 8, 0 });
            Next_Tetromino[1].Arr.push_back({ 12, 0 });
            Next_Tetromino[1].Colour = olc::BLUE;

            Next_Tetromino[2].Arr.push_back({ 0,0 });
            Next_Tetromino[2].Arr.push_back({ 4,0 });
            Next_Tetromino[2].Arr.push_back({ 8,0 });
            Next_Tetromino[2].Arr.push_back({ 0,4 });
            Next_Tetromino[2].Colour = olc::DARK_BLUE;

            Next_Tetromino[3].Arr.push_back({ 4, 0 });
            Next_Tetromino[3].Arr.push_back({ 8, 0 });
            Next_Tetromino[3].Arr.push_back({ 12, 0 });
            Next_Tetromino[3].Arr.push_back({ 12, 4 });
            Next_Tetromino[3].Colour = olc::CYAN;

            Next_Tetromino[4].Arr.push_back({ 8, 0 });
            Next_Tetromino[4].Arr.push_back({ 8, 4 });
            Next_Tetromino[4].Arr.push_back({ 12, 0 });
            Next_Tetromino[4].Arr.push_back({ 12, 4 });
            Next_Tetromino[4].Colour = olc::YELLOW;

            Next_Tetromino[5].Arr.push_back({ 4, 4 });
            Next_Tetromino[5].Arr.push_back({ 8, 4 });
            Next_Tetromino[5].Arr.push_back({ 8, 0 });
            Next_Tetromino[5].Arr.push_back({ 12, 0 });
            Next_Tetromino[5].Colour = olc::GREEN;

            Next_Tetromino[6].Arr.push_back({ 4, 0 });
            Next_Tetromino[6].Arr.push_back({ 8, 0 });
            Next_Tetromino[6].Arr.push_back({ 8, 4 });
            Next_Tetromino[6].Arr.push_back({ 12, 4 });
            Next_Tetromino[6].Colour = olc::RED;

            OffSet_X_NextTetromino = ((((ScreenWidth() - FieldWidth) / 2) - 2) + FieldWidth + Block_Size) + 1;
            OffSet_Y_NextTetromino = ((ScreenHeight() - FieldHeight) / 2) - 2;

            OffSet_X_SavedTetromino = (((ScreenWidth() - FieldWidth) / 2) - 2) - (5 * Block_Size);
            OffSet_Y_SavedTetromino = ((ScreenHeight() - FieldHeight) / 2) - 2;
        }

        for (int j = 0; j < Tetromino[Tetromino_Type].Arr.size(); j++) {
            int x = Tetromino[Tetromino_Type].Arr[j].x + Pos_X;
            int y = Tetromino[Tetromino_Type].Arr[j].y + Pos_Y;
            olc::Pixel Colour = Tetromino[Tetromino_Type].Colour;

            FillRect(x, y, Block_Size, Block_Size, Colour);
        }

        for (int i = 0; i < Tetromino_Mesh.size(); i++) {
            for (int j = 0; j < Tetromino_Mesh[i].Arr.size(); j++) {
                int x = Tetromino_Mesh[i].Arr[j].x;
                int y = Tetromino_Mesh[i].Arr[j].y;
                olc::Pixel Colour = Tetromino_Mesh[i].Colour;

                FillRect(x, y, Block_Size, Block_Size, Colour);
            }
        }

        for (int j = 0; j < Next_Tetromino[Next_Type].Arr.size(); j++) {
            int x = Next_Tetromino[Next_Type].Arr[j].x + OffSet_X_NextTetromino;
            int y = Next_Tetromino[Next_Type].Arr[j].y + OffSet_Y_NextTetromino;
            int x1 = x + Block_Size;
            int y1 = y + Block_Size;
            olc::Pixel Colour = Next_Tetromino[Next_Type].Colour;

            FillRect(x, y, Block_Size, Block_Size, Colour);
        }

        if (HasBeenPressed == true) {

            for (int j = 0; j < Next_Tetromino[Saved_Type].Arr.size(); j++) {
                int x = Next_Tetromino[Saved_Type].Arr[j].x + OffSet_X_SavedTetromino;
                int y = Next_Tetromino[Saved_Type].Arr[j].y + OffSet_Y_SavedTetromino;
                int x1 = x + Block_Size;
                int y1 = y + Block_Size;
                olc::Pixel Colour = Next_Tetromino[Saved_Type].Colour;

                FillRect(x, y, Block_Size, Block_Size, Colour);
            }

            

        }

        auto transpColor = olc::Pixel(0, 0, 0, 150);
        for (int i = OffSet_Y_SavedTetromino; i < OffSet_Y_SavedTetromino + (4 * Block_Size) + 1; i = i + 4) {
            DrawLine(OffSet_X_SavedTetromino, i, OffSet_X_SavedTetromino + (4 * Block_Size), i, transpColor);
        }
        for (int i = OffSet_X_SavedTetromino; i < OffSet_X_SavedTetromino + (4 * Block_Size) + 1; i = i + 4) {
            DrawLine(i, OffSet_Y_SavedTetromino, i, OffSet_Y_SavedTetromino + (4 * Block_Size), transpColor);
        }

        for (int i = OffSet_Y_NextTetromino; i < OffSet_Y_NextTetromino + (4 * Block_Size) + 1; i = i + 4) {
            DrawLine(OffSet_X_NextTetromino, i, OffSet_X_NextTetromino + (4 * Block_Size), i, transpColor);
        }
        for (int i = OffSet_X_NextTetromino; i < OffSet_X_NextTetromino + (4 * Block_Size) + 1; i = i + 4) {
            DrawLine(i, OffSet_Y_NextTetromino, i, OffSet_Y_NextTetromino + (4 * Block_Size), transpColor);
        }
    }

    bool CheckToEraseCompleteLine() {
        int multiplication = 0;
        int cont = 0;
        for (int h = 28; h <= ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size); h = h + 4) {
            cont = 0;

            for (int a = (((ScreenWidth() - FieldWidth) / 2) - 2); a <= (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (3 * Block_Size)); a = a + 4) {

                for (int j = 0; j <= MeshIndex; j++) {
                    MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                    for (int k = 0; k < MeshTetrominoArraySize; k++) {

                        if (a == Tetromino_Mesh[j].Arr[k].x and h == Tetromino_Mesh[j].Arr[k].y) {
                            cont++;
                        }
                    }
                }
            }
            if (cont >= 13) {
                multiplication++;
                LineasCompletadas++;
                for (int j = 0; j <= MeshIndex; j++) {
                    score = score + (10 * multiplication);

                    MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                    for (int k = 0; k < MeshTetrominoArraySize; k++) {
                        float y = Tetromino_Mesh[j].Arr[k].y;
                        y = y + Block_Size;
                        if (Tetromino_Mesh[j].Arr[k].y < h) Tetromino_Mesh[j].Arr[k].y = y;
                        else if (Tetromino_Mesh[j].Arr[k].y == h) Tetromino_Mesh[j].Arr[k].y = ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - Block_Size;
                    }
                }
            }
        }
        return false;
    }

    bool GameOver() {
        for (int j = 0; j <= MeshIndex; j++) {
            MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
            for (int k = 0; k < MeshTetrominoArraySize; k++) {
                if (Tetromino_Mesh[j].Arr[k].y <= 32) return true;
            }
        }


        return false;
    }

    void GainSpeed() {
        switch (score) {
        case 5:
            Speed = 25;
            break;

        case 10:
            Speed = 20;
            break;

        case 20:
            Speed = 15;
            break;

        case 30:
            Speed = 10;
            break;

        case 40:
            Speed = 5;
            break;
        }
    }


    virtual bool OnUserCreate() {

        //gSoloud.init();

        Pos_X = (float(ScreenWidth()) / 2);

        sprFondo = new olc::Sprite("Sprites/senku.jpg");
        Fondo = new olc::Decal(sprFondo);

        Layer1 = CreateLayer();
        SetDrawTarget(Layer1);
        EnableLayer(Layer1, true);
        SetDrawTarget(nullptr);

        Layer2 = CreateLayer();
        SetDrawTarget(Layer2);
        EnableLayer(Layer2, true);
        SetDrawTarget(nullptr);

        //TitleMusic.load("Audio/TetrisTheme.wav");

        //gSoloud.play(TitleMusic);

        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime) {

        double dExpectedTime = 1.0f / 60.0f;
        if (dExpectedTime >= GetElapsedTime()) Sleep((dExpectedTime - GetElapsedTime()) * 1000);

        //PlaySample(nSample);

        Clear(olc::BLANK);
        Puntaje.clear();

        SetDrawTarget(Layer1);
        Clear(olc::BLANK);
        auto transpColor = olc::Pixel(255, 255, 255, 30);
        FillRect({ (((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size , (((ScreenHeight() - FieldHeight) / 2) - 2) }, { 53, 97 }, transpColor);
        FillRect({ OffSet_X_SavedTetromino, OffSet_Y_SavedTetromino }, { (4 * Block_Size) , (4 * Block_Size) }, transpColor);
        FillRect({ OffSet_X_NextTetromino, OffSet_Y_NextTetromino }, { (4 * Block_Size) , (4 * Block_Size) }, transpColor);
        FillRect({ 43, 135 }, { 70 , 30 }, transpColor);
        SetDrawTarget(nullptr);

        SetDrawTarget(Layer2);
        SetPixelMode(olc::Pixel::ALPHA);
        DrawDecal({ -60,0 }, Fondo, { 0.08,0.08 });
        SetPixelMode(olc::Pixel::NORMAL);
        SetDrawTarget(nullptr);

        SaveTetromino();

        if (cont_4 > (Speed/(GetElapsedTime()*25)) and DoesPieceFitDown() and DoesPieceFit3()) {
            Pos_Y = Pos_Y + 4;
            cont_4 = 0;
        }

        if (NextRotationDoesFit()) {
            Rotate_Tetromino();
        }

        MoveTetromino();

        while (!DoesPieceFit()) {
            Pos_X -= 4;
        }
        while (!DoesPieceFit2()) {
            Pos_X += 4;
        }

        MeshTetrominos();

        DrawTetromino();

        DrawField();

        GainSpeed();


        UserTetrominoArraySize = Tetromino[Tetromino_Type].Arr.size();
        MeshIndex = Tetromino_Mesh.size() - 1;

        if (HasBeenPressed) SavedArraySize = Next_Tetromino[Saved_Type].Arr.size();

        score = Tetromino_Mesh.size();
        PuntajeReal = LineasCompletadas*1000 + score * 100;
        
        Puntaje += to_string(PuntajeReal);

        DrawString({ 48, 140 }, "Puntaje:", olc::BLACK);
        DrawString({ 50, 150 }, Puntaje, olc::BLACK);

        cont++;
        cont_4++;
        return true;
    }

    virtual bool OnUserDestroy()
    {
        //DestroyAudio();
        return true;
    }

};


int main() {

    Juego Demo;

    if (Demo.Construct(160, 160, 4, 4))
        Demo.Start();

    else cout << "Construct Failed";
}
