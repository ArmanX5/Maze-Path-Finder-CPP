# Maze Path Finder

This code implements a graph representation of a maze and utilizes Breadth-First Search (BFS) and Depth-First Search (DFS) algorithms to find paths from a starting point to an ending point within the maze.

## Functionality

1. **Graph Representation:** The code defines a `Graph` class that represents the maze as an adjacency matrix. Each cell in the maze is a vertex in the graph, and connections between cells are represented by edges.
2. **Maze Input:** The code takes the maze dimensions (rows and columns) and the maze layout as input. The maze layout is a 2D array of integers where 0 represents an open cell and 1 represents a wall.
3. **Path Finding:** The code implements two functions:
    * `BFS_solution()`: This function performs a BFS traversal on the graph to find the shortest path from a predefined starting point (cell (0, 1) or (1, 0)) to a predefined ending point (cell (rows - 1, cols - 2) or (rows - 2, cols - 1)).
    * `DFS_solution()`: This function performs a DFS traversal on the graph to find a path from the predefined starting point to the predefined ending point.
4. **Overloaded BFS and DFS:** The code also includes overloaded functions `BFS(string start, string end)` and `DFS(string start, string end)` that allow specifying custom starting and ending points within the maze using their cell coordinates in the format "row,column".

## Usage

1. Compile the code using a C++ compiler.
2. Run the executable.
3. The program will prompt you to enter the maze dimensions (rows and columns).
4. Then, you will be asked to enter the maze layout, where 0 represents an open cell and 1 represents a wall.
5. The program will find the BFS and DFS paths (if they exist) and print the path lengths and the cell coordinates along the paths.

**Note:** The provided code includes commented-out test code that demonstrates how to use the `Graph` class with a predefined maze layout.

## Additional Notes

* The code assumes that the maze has a valid starting and ending point.
* The BFS solution is guaranteed to find the shortest path if one exists.
* The DFS solution may not find the shortest path and might explore longer paths before finding a valid solution.

## Contributors

* Arman Akhoundy
* Setareh Hashempour
