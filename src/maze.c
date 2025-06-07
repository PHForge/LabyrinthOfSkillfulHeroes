#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/maze.h"
#include "../include/utils.h"

Maze *create_maze(int rows, int cols) {
    Maze *maze = malloc(sizeof(Maze));
    maze->rows = rows;
    maze->cols = cols;
    maze->grid = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        maze->grid[i] = malloc(cols * sizeof(char));
        for (int j = 0; j < cols; j++) {
            maze->grid[i][j] = '#'; // Initialize with walls
        }
    }
    maze->player_row = 1;
    maze->player_col = 1;
    maze->grid[1][1] = 'P'; // Player start
    return maze;
}

void generate_maze(Maze *maze, int row, int col) {
    maze->grid[row][col] = '.';
    int directions[4][2] = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}}; // Up, down, left, right
    shuffle(directions, 4);
    for (int i = 0; i < 4; i++) {
        int new_row = row + directions[i][0];
        int new_col = col + directions[i][1];
        if (new_row > 0 && new_row < maze->rows - 1 && new_col > 0 && new_col < maze->cols - 1 && maze->grid[new_row][new_col] == '#') {
            maze->grid[row + directions[i][0] / 2][col + directions[i][1] / 2] = '.';
            generate_maze(maze, new_row, new_col);
        }
    }
    maze->grid[maze->rows - 2][maze->cols - 2] = 'E'; // Exit
}

void display_maze(Maze *maze) {
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            printf("%c ", *(maze->grid[i] + j)); // Pointer arithmetic
        }
        printf("\n");
    }
}

void move_player(Maze *maze, char direction, const char *lang) {
    int new_row = maze->player_row, new_col = maze->player_col;
    if (strcmp(lang, "fr") == 0) {
        if (direction == 'z') new_row--;
        else if (direction == 's') new_row++;
        else if (direction == 'q') new_col--;
        else if (direction == 'd') new_col++;
    } else {
        if (direction == 'w') new_row--;
        else if (direction == 's') new_row++;
        else if (direction == 'a') new_col--;
        else if (direction == 'd') new_col++;
    }
    if (new_row >= 0 && new_row < maze->rows && new_col >= 0 && new_col < maze->cols && *(maze->grid[new_row] + new_col) != '#') {
        *(maze->grid[maze->player_row] + maze->player_col) = '.';
        maze->player_row = new_row;
        maze->player_col = new_col;
        *(maze->grid[new_row] + new_col) = 'P';
    }
}

void free_maze(Maze *maze) {
    if (!maze) return;
    for (int i = 0; i < maze->rows; i++) {
        free(maze->grid[i]);
    }
    free(maze->grid);
    free(maze);
}
