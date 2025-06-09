#ifndef MAZE_H
#define MAZE_H

typedef struct {
    int rows, cols;                 // Dimensions of the maze
    char **grid;                    // 2D array representing the maze grid
    int player_row, player_col;     // Player's current position in the maze
} Maze;

Maze *create_maze(int rows, int cols);
void generate_maze(Maze *maze, int row, int col);
void display_maze(Maze *maze);
void move_player(Maze *maze, char direction, const char *lang);
void free_maze(Maze *maze);

#endif