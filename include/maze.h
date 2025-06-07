#ifndef MAZE_H
#define MAZE_H

//#include "../include/.h" 

typedef struct {
    int rows, cols;
    char **grid; // Dynamic 2D grid
    int player_row, player_col;
} Maze;

Maze *create_maze(int rows, int cols);
void generate_maze(Maze *maze, int row, int col);
void display_maze(Maze *maze);
void move_player(Maze *maze, char direction, const char *lang);
void free_maze(Maze *maze);

#endif