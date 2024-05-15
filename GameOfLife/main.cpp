#include <iostream>
#include <raylib.h>

#define CELL_COUNT 100
#define ALIVE 1
#define DEAD 0

int CheckNeighbors(int neighbors, int row, int col, int (*cells)[CELL_COUNT])
{
    if(cells[row - 1][col] == 1)
    {
        neighbors++;
    }
    if(cells[row + 1][col] == 1)
    {
        neighbors++;
    }
    if(cells[row][col - 1] == 1)
    {
        neighbors++;
    }
    if(cells[row][col + 1] == 1)
    {
        neighbors++;
    }
    if(cells[row - 1][col - 1] == 1)
    {
        neighbors++;
    }
    if(cells[row + 1][col + 1] == 1)
    {
        neighbors++;
    }
    if(cells[row - 1][col + 1] == 1)
    {
        neighbors++;
    }
    if(cells[row + 1][col - 1] == 1)
    {
        neighbors++;
    }

    return neighbors;
}

int CheckLeftEdge(int neighbors, int row, int col, int (*cells)[CELL_COUNT])
{
    if(cells[row][col + 1] == 1)
    {
    neighbors++;
    }
    if(cells[row - 1][col] == 1)
    {
    neighbors++;
    }
    if(cells[row + 1][col] == 1)
    {
    neighbors++;
    }
    if(cells[row - 1][col + 1] == 1)
    {
    neighbors++;
    }
    if(cells[row + 1][col + 1] == 1)
    {
    neighbors++;
    }
    if(cells[row - 1][CELL_COUNT - 1] == 1)
    {
    neighbors++;
    }
    if(cells[row][CELL_COUNT - 1] == 1)
    {
    neighbors++;
    }
    if(cells[row + 1][CELL_COUNT - 1] == 1)
    {
    neighbors++;
    }
    return neighbors;
}

int main ()
{
    const int screenWidth = 900; // 500 before
    const int screenHeight = 700; // 500 before

    int neighbors;
    int cells[CELL_COUNT][CELL_COUNT] = {DEAD};

    //create initial state --  done manually
    cells[1][0] = ALIVE;
    cells[2][0] = ALIVE;
    cells[3][0] = ALIVE;
    cells[1][CELL_COUNT-1] = ALIVE;
    cells[2][CELL_COUNT-1] = ALIVE;
    cells[3][CELL_COUNT-1] = ALIVE;

    cells[2][3] = ALIVE;
    cells[2][4] = ALIVE;
    cells[6][10] = ALIVE;
    cells[5][10] = ALIVE;
    cells[4][10] = ALIVE;
    cells[3][5] = ALIVE;
    cells[3][4] = ALIVE;
    cells[9][3] = ALIVE;

    cells[50][3] = ALIVE;
    cells[50][4] = ALIVE;
    cells[50][5] = ALIVE;
    cells[25][6] = ALIVE;
    cells[25][4] = ALIVE;
    cells[24][5] = ALIVE;
    cells[25][4] = ALIVE;
    cells[10][3] = ALIVE;

    //Create the game loop
    InitWindow(screenWidth, screenHeight, "My Game of Life!");
    SetTargetFPS(60); //or could be 60 FPS

    //Main game loop
    while(!WindowShouldClose())
    {
        //Begin Drawing
        BeginDrawing();
        //Must clear the background so to see the changes each iteration
        ClearBackground(BLACK);

        for(int row = 0; row < CELL_COUNT; row++)
        {
            for(int col = 0; col < CELL_COUNT; col++)
            {
             
                //Check on dead cell neighbors
                if(cells[row][col] == DEAD)
                {
                neighbors = 0; 
                //Check left edge cells that are not at the top or the bottom 
                if((col == 0) && ((row != 0) || (row != CELL_COUNT)))
                {
                    neighbors = 0;
                    //Rule for dead cells  
                    if(CheckLeftEdge(neighbors, row, col, cells) == 3)
                    {
                        cells[row][col] = ALIVE;
                    }
                }
                //Check for live neigbors then each time we see one we increment 
                //These cells are not on the wall, floor, or ceiling of the array
                //None of these should be true so let's use or 
                if((row != 0) || (col != 0) || (row != CELL_COUNT - 1) || (col != CELL_COUNT - 1))
                {

                    //Rule 4: any dead cell (0) three live neighbors lives 
                    if(CheckNeighbors(neighbors, row, col, cells) == 3)
                    {
                        cells[row][col] = ALIVE;
                    }
                }
                } //checked dead neighbors
                //Check on live cell neighbors
                if(cells[row][col] == ALIVE)
                {
                    neighbors = 0; 

                //Check left edge cells that are not at the top or the bottom 
                if((col == 0) && ((row != 0) || (row != CELL_COUNT)))
                {
                    neighbors = 0;
                    //Rule 1: any live cell (1) with fewer than two live neigbors die (x < 2)
                    if(CheckLeftEdge(neighbors, row, col, cells) < 2)
                    {
                        cells[row][col] = DEAD;
                    }
                    //Rule 2: any live cell (1) with two or three live neighbors live
                    if((CheckLeftEdge(neighbors, row, col, cells) == 2) || (CheckLeftEdge(neighbors, row, col, cells) == 3))
                    {
                        cells[row][col] = ALIVE;
                    }
                    //Rule 3: any live cell (1) with greater than three live cells die
                    if(CheckLeftEdge(neighbors, row, col, cells)> 3)
                    {
                        cells[row][col] = DEAD;
                    }

                }
                    //Check for live neigbors then each time we see one we increment 
                    //These cells are not on the wall, floor, or ceiling of the array
                    //None of these should be true so let's use or 
                    if((row != 0) || (col != 0) || (row != CELL_COUNT - 1) || (col != CELL_COUNT - 1))
                    {
                        //Rule 1: any live cell (1) with fewer than two live neigbors die (x < 2)
                        if(CheckNeighbors(neighbors, row, col, cells) < 2)
                        {
                            cells[row][col] = DEAD;
                        }
                        //Rule 2: any live cell (1) with two or three live neighbors live
                        if((CheckNeighbors(neighbors, row, col, cells) == 2) || (CheckNeighbors(neighbors, row, col, cells) == 3))
                        {
                            cells[row][col] = ALIVE;
                        }
                        //Rule 3: any live cell (1) with greater than three live cells die
                        if(CheckNeighbors(neighbors, row, col, cells) > 3)
                        {
                            cells[row][col] = DEAD;
                        }
                    }
                } //checked live cell neighbors

                //Update to the game loop
                if (cells[row][col] == ALIVE)
                {   
                    DrawRectangle(row * (screenWidth / CELL_COUNT), col * (screenHeight / CELL_COUNT), screenWidth / CELL_COUNT, screenHeight / CELL_COUNT, MAGENTA);
                }
            }
        }

        EndDrawing();
    }

    //Must close the window that was initialized
    CloseWindow();
    return 0;
}