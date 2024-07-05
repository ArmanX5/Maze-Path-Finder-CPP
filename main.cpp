// A Data Structure and Algorithm Project
// Contributors: Arman Akhoundy, Setareh Hashempour

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;

class Graph {
private:
    // Adjacency matrix to represent the graph
    vector<vector<int>> adjacencyMatrix;
    // List of vertices (each represented as a string "row,col")
    vector<string> vertices;
    // Number of rows and columns in the maze
    int rows, cols;
    // Start and end indices in the graph
    int graphStartIndex, graphEndIndex;

    // Helper function to get the index of a vertex in the vertices list
    int getIndex(int row, int col) {
        string vertex = to_string(row) + "," + to_string(col);
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i] == vertex) {
                return i;
            }
        }
        return -1;
    }

    // Helper function to get the row number from a vertex string
    int getRow(string vertex) {
        int row = stoi(vertex.substr(0, vertex.find(',')));
        return row;
    }

    // Helper function to get the column number from a vertex string
    int getCol(string vertex) {
        int col = stoi(vertex.substr(vertex.find(',') + 1));
        return col;
    }

    // Helper function to generate a vertex string from row and column numbers
    string getVertexName(int row, int col) {
        return to_string(row) + "," + to_string(col);
    }

    // Set the starting index based on predefined start positions
    void setStartIndex() {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i] == "0,1" || vertices[i] == "1,0") {
                graphStartIndex = i;
                break;
            }
        }
    }

    // Set the ending index based on predefined end positions
    void setEndIndex() {
        string vertexName_1 = to_string(rows - 1) + "," + to_string(cols - 2);
        string vertexName_2 = to_string(rows - 2) + "," + to_string(cols - 1);
        for (int i = vertices.size() - 1; i >= 0; i--) {
            if (vertices[i] == vertexName_1 || vertices[i] == vertexName_2) {
                graphEndIndex = i;
                break;
            }
        }
    }

public:
    // Constructor to initialize the graph with given rows and columns
    Graph(int rows, int cols) : rows(rows), cols(cols) {}

    // Add a vertex to the graph
    void addVertex(int row, int col) {
        string vertex = getVertexName(row, col);
        vertices.push_back(vertex);
        int newSize = vertices.size();
        // Resize the adjacency matrix to accommodate the new vertex
        adjacencyMatrix.resize(newSize, vector<int>(newSize, 0));
        for (int i = 0; i < newSize; i++) {
            adjacencyMatrix[i].resize(newSize, 0);
        }
    }

    // Add an edge between two vertices in the graph
    void addEdge(int row1, int col1, int row2, int col2) {
        int index1 = getIndex(row1, col1);
        int index2 = getIndex(row2, col2);
        if (index1 != -1 && index2 != -1) {
            adjacencyMatrix[index1][index2] = 1;
            adjacencyMatrix[index2][index1] = 1;
        }
    }

    // Read the maze and construct the graph
    void readMaze(vector<vector<int>>& maze) {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (maze[row][col] == 0) {
                    addVertex(row, col);
                    // Add edges to adjacent vertices (if they are part of the maze)
                    if (row > 0 && maze[row - 1][col] == 0)
                        addEdge(row, col, row - 1, col);
                    if (row < rows - 1 && maze[row + 1][col] == 0)
                        addEdge(row, col, row + 1, col);
                    if (col > 0 && maze[row][col - 1] == 0)
                        addEdge(row, col, row, col - 1);
                    if (col < cols - 1 && maze[row][col + 1] == 0)
                        addEdge(row, col, row, col + 1);
                }
            }
        }
        setStartIndex();
        setEndIndex();
    }

    // Print the adjacency list representation of the graph
    void printGraph() {
        for (int i = 0; i < vertices.size(); i++) {
            cout << vertices[i] << "\t->\t";
            for (int j = 0; j < vertices.size(); j++) {
                if (adjacencyMatrix[i][j] == 1) {
                    cout << vertices[j] << "\t";
                }
            }
            cout << endl;
        }
    }

    // BFS solution from the start index to the end index
    void BFS_solution() {
        vector<bool> visited(vertices.size(), false);
        vector<int> queue;
        vector<int> predecessor(vertices.size(), -1);
        queue.push_back(graphStartIndex);
        visited[graphStartIndex] = true;

        while (!queue.empty()) {
            int vertexIndex = queue.front();
            queue.erase(queue.begin());

            if (vertexIndex == graphEndIndex) {
                vector<string> path;
                for (int at = graphEndIndex; at != -1; at = predecessor[at]) {
                    path.insert(path.begin(), vertices[at]);
                }
                cout << "Path length (BFS): " << path.size() << endl;
                for (string vertex : path) {
                    cout << vertex << endl;
                }
                cout << endl;
                return;
            }

            for (int i = 0; i < adjacencyMatrix[vertexIndex].size(); i++) {
                if (adjacencyMatrix[vertexIndex][i] == 1 && !visited[i]) {
                    queue.push_back(i);
                    visited[i] = true;
                    predecessor[i] = vertexIndex;
                }
            }
        }

        cout << "No path found from start to end." << endl;
    }

    // General BFS method for any start and end vertices
    void BFS(string start, string end) {
        vector<bool> visited(vertices.size(), false);
        vector<int> queue;
        vector<int> predecessor(vertices.size(), -1);
        int startIndex = getIndex(getRow(start), getCol(start));
        int endIndex = getIndex(getRow(end), getCol(end));
        queue.push_back(startIndex);
        visited[startIndex] = true;

        while (!queue.empty()) {
            int vertexIndex = queue.front();
            queue.erase(queue.begin());

            if (vertexIndex == endIndex) {
                vector<string> path;
                for (int at = endIndex; at != -1; at = predecessor[at]) {
                    path.insert(path.begin(), vertices[at]);
                }
                cout << "Path length (BFS): " << path.size() << endl;
                for (string vertex : path) {
                    cout << vertex << endl;
                }
                cout << endl;
                return;
            }

            for (int i = 0; i < adjacencyMatrix[vertexIndex].size(); i++) {
                if (adjacencyMatrix[vertexIndex][i] == 1 && !visited[i]) {
                    queue.push_back(i);
                    visited[i] = true;
                    predecessor[i] = vertexIndex;
                }
            }
        }

        cout << "No path found from start to end." << endl;
    }

    // DFS solution from the start index to the end index
    void DFS_solution() {
        vector<bool> visited(vertices.size(), false);
        vector<int> predecessor(vertices.size(), -1);
        stack<int> stack;
        stack.push(graphStartIndex);
        visited[graphStartIndex] = true;

        while (!stack.empty()) {
            int vertexIndex = stack.top();
            stack.pop();

            if (vertexIndex == graphEndIndex) {
                vector<string> path;
                for (int at = graphEndIndex; at != -1; at = predecessor[at]) {
                    path.insert(path.begin(), vertices[at]);
                }
                cout << "Path length (DFS): " << path.size() << endl;
                for (string vertex : path) {
                    cout << vertex << endl;
                }
                cout << endl;
                return;
            }

            for (int i = 0; i < adjacencyMatrix[vertexIndex].size(); i++) {
                if (adjacencyMatrix[vertexIndex][i] == 1 && !visited[i]) {
                    stack.push(i);
                    visited[i] = true;
                    predecessor[i] = vertexIndex;
                }
            }
        }

        cout << "No path found from start to end." << endl;
    }

    // General DFS method for any start and end vertices
    void DFS(string start, string end) {
        vector<bool> visited(vertices.size(), false);
        vector<int> predecessor(vertices.size(), -1);
        stack<int> stack;
        int startIndex = getIndex(getRow(start), getCol(start));
        int endIndex = getIndex(getRow(end), getCol(end));
        stack.push(startIndex);
        visited[startIndex] = true;

        while (!stack.empty()) {
            int vertexIndex = stack.top();
            stack.pop();

            if (vertexIndex == endIndex) {
                vector<string> path;
                for (int at = endIndex; at != -1; at = predecessor[at]) {
                    path.insert(path.begin(), vertices[at]);
                }
                cout << "Path length (DFS): " << path.size() << endl;
                for (string vertex : path) {
                    cout << vertex << endl;
                }
                cout << endl;
                return;
            }

            for (int i = 0; i < adjacencyMatrix[vertexIndex].size(); i++) {
                if (adjacencyMatrix[vertexIndex][i] == 1 && !visited[i]) {
                    stack.push(i);
                    visited[i] = true;
                    predecessor[i] = vertexIndex;
                }
            }
        }

        cout << "No path found from start to end." << endl;
    }
};

int main() {
    // Read the number of rows and columns for the maze
    int rows, cols;
    cin >> rows >> cols;

    // Initialize the maze
    vector<vector<int>> maze(rows, vector<int>(cols));

    // Read the maze from the input
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            cin >> maze[row][col];
        }
    }

    // Create the graph from the maze
    Graph graph(rows, cols);
    graph.readMaze(maze);

    // Solve the maze using BFS and DFS
    graph.BFS_solution();
    graph.DFS_solution();
}

// // Test code. You can use this to test the code :)
// int main() {
//     int rows, cols;
//     rows = 15;
//     cols = 17;

//     vector<vector<int> > maze(rows, vector<int>(cols));

//     int maze_array[15][17] = {
//         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//         {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
//         {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
//         {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
//         {1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
//         {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
//         {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
//         {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//         {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
//         {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
//         {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
//         {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
//         {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
//     };

//     // Read the maze from the input
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             maze[i][j] = maze_array[i][j];
//         }
//     }

//     Graph graph(rows, cols);
//     graph.readMaze(maze);

//     cout << "BFS Path (Shortest Path): " << endl;
//     graph.BFS_solution();
    
//     cout << "DFS Path: " << endl;
//     graph.DFS_solution();

//     cout << "BFS Path (from (13,1) to (11,9)): " << endl;
//     graph.BFS("13,1", "11,9");

//     cout << "DFS Path (from (13,1) to (11,9)): " << endl;
//     graph.DFS("13,1", "11,9");


//     return 0;
// }
