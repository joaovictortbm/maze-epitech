#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 1000
#define MAX_HEIGHT 1000

char maze[MAX_HEIGHT][MAX_WIDTH];

// Function to read and validate the maze
int ReadValidateMaze(const char *filename, int *width, int *height) {

    FILE *file = fopen(filename, "r");
    if (!file) {
        return 0;  
    }

    int row = 0;           
    int col = 0;          
    int first_width = -1;  
    char c;                

    while ((c = fgetc(file)) != EOF) {
        if (c == '\r') continue;

        if (c == '\n') {
            if (first_width == -1) first_width = col;
            else if (col != first_width && col > 0) {
                fclose(file);
                return 0;  
            }

            if (col > 0) {
                row++;
                col = 0;
            }
            continue;
        }

        if (row >= MAX_HEIGHT || col >= MAX_WIDTH) {
            fclose(file);
            return 0;
        }

        maze[row][col] = c;
        col++;
    }

    if (col > 0) {
        if (first_width == -1) first_width = col;
        else if (col != first_width) {
            fclose(file);
            return 0;
        }
        row++;
    }

    fclose(file);

    *width = first_width;
    *height = row;

    if (*width < 1 || *height < 1) return 0;

    if (maze[0][0] == 'X' || maze[*height - 1][*width - 1] == 'X') return 0;

    return 1;  
}

// Recursive function to solve the maze
int solveMaze(int x, int y, int width, int height) {
    if (x < 0 || y < 0 || x >= height || y >= width)
        return 0;

    if (maze[x][y] == 'X' || maze[x][y] == '.')
        return 0;

    if (x == height - 1 && y == width - 1) {
        maze[x][y] = 'o';
        return 1;
    }

    // Mark as visited
    maze[x][y] = '.';

    // Try moving: down, right, up, left
    if (solveMaze(x + 1, y, width, height) ||
        solveMaze(x, y + 1, width, height) ||
        solveMaze(x - 1, y, width, height) ||
        solveMaze(x, y - 1, width, height)) {
        maze[x][y] = 'o'; 
        return 1;
    }

    return 0; 
}

// Function to print the maze
void printMaze(int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("There is no maze to solve\n");
        return 1;
    }

    int width, height;

    if (!ReadValidateMaze(argv[1], &width, &height)) {
        printf("no solution found\n");
        return 1;
    }

    if (solveMaze(0, 0, width, height)) {
        printMaze(width, height);
    } else {
        printf("no solution found\n");
    }

    return 0;
}
