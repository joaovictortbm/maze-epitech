# Alice's Maze Solver
This project is a maze solver written in C.  
The program reads a maze from a text file, validates it, and attempts to solve it.  

- If a solution exists, the maze is printed with the path marked  
- If no solution is possible, the program prints: `no solution found`

## Installation / Compilation
1. Open your terminal.  
2. Navigate to the project folder.  
3. Run `make` to compile the project.  

This will generate the executable `solver.exe`.  

To clean compiled files:  
```bash
make clean        # remove object files
make fclean       # remove object files and executable
make re           # clean and compile again
