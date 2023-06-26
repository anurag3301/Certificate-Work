# GAME OF LIFE in C
#### Video Demo:  https://www.youtube.com/watch?v=A6BIHOGluEA
#### Description:
This is an implementation of [Game Of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C language. 

To run it just run `make` in terminal to compile it and then run `./out`. Make sure you have ncurses installed on your computer as it uses ncurses for the TUI.

The Game of Life is a cellular automaton that simulates the evolution of a grid of cells based on a set of rules.

#### Code Explaination
The code starts by including the necessary libraries for input/output, screen manipulation, and random number generation. It defines various functions for creating, destroying, and drawing the game grid.

The `create_newwin` function creates a new window using the ncurses library. The `create_matrix` function initializes and returns a randomly generated matrix of cells representing the game grid. The `destroy_matrix` function frees the memory allocated for the matrix. The `draw_matrix` function displays the current state of the game grid on the screen.

The `calc_neighbour` function calculates the number of live neighboring cells for a given cell in the grid. The `next_move` function generates the next state of the grid based on the rules of the Game of Life. It applies the rules to each cell and creates a new matrix representing the next generation.

The main function initializes the necessary variables and starts the ncurses library. It creates a game window, initializes the game grid matrix, and displays the initial state on the screen. It then waits for user input to determine whether to continuously run the simulation or step through generations one by one.

If the user chooses to continuously run the simulation, the code enters a loop where it updates the grid to the next generation, displays the new state on the screen, and waits for a short delay before repeating the process.

If the user chooses to step through generations, the code enters a loop that waits for user input after each generation before proceeding to the next one. This allows the user to control the pace of the simulation.

The code also takes care of cleaning up the allocated memory and terminating the ncurses library before exiting.

Overall, this code provides a basic implementation of Conway's Game of Life using ncurses for a terminal-based graphical representation of the simulation.

#### Game of life (Explaination)
The rules of the Game of Life are as follows:

1. Any live cell with fewer than two live neighbors dies, as if by underpopulation.
2. Any live cell with two or three live neighbors survives to the next generation.
3. Any live cell with more than three live neighbors dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
With these rules, the Game of Life creates complex patterns and behaviors that can be unpredictable and fascinating to observe.

The process of the Game of Life can be described as follows:

1. Initialization:

    - A grid of cells is created. Each cell is assigned an initial state, either alive or dead. This initial state can be randomly generated or predefined by the user.

2. Generation Update:
    - For each generation, the state of each cell is updated based on the rules of the game.
    - For each cell in the grid:
        - The number of live neighbors surrounding the cell is calculated.
        - Based on the current state of the cell and the number of live neighbors, the new state of the cell is determined.
        - If the cell is alive, it stays alive only if it has 2 or 3 live neighbors; otherwise, it dies.
        - If the cell is dead, it becomes alive if it has exactly 3 live neighbors.
    - The state of all cells in the grid is simultaneously updated, ensuring that the new generation is computed based on the previous generation's state.

3. Display:

    - After each generation update, the state of the grid is displayed visually. This can be done using various graphical representations, such as characters or symbols representing alive and dead cells.
    - The updated grid is shown on the screen, allowing the user to observe the evolution of the patterns.
4. Repeat:

    - The process of generation update and display is repeated for subsequent generations, creating a continuous simulation.
    - The simulation can continue indefinitely or until a specific condition is met, such as a stable state where the grid no longer changes.

By following these steps, the Game of Life simulates the emergence of various patterns, including stable configurations, oscillators, gliders, and other complex structures. These patterns can interact with each other, collide, and create new formations, making the Game of Life a fascinating and captivating simulation to observe and study.
