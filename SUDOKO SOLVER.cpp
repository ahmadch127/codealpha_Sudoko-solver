#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

const int N = 9;
int grid[N][N] = {
    {5,3,0,0,7,0,0,0,0},
    {6,0,0,1,9,5,0,0,0},
    {0,9,8,0,0,0,0,6,0},
    {8,0,0,0,6,0,0,0,3},
    {4,0,0,8,0,3,0,0,1},
    {7,0,0,0,2,0,0,0,6},
    {0,6,0,0,0,0,2,8,0},
    {0,0,0,4,1,9,0,0,5},
    {0,0,0,0,8,0,0,7,9}
};

// Sudoku solving logic
bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool solveSudoku(int grid[N][N]) {
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku(grid))
                            return true;
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
    return true;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(450, 450), "Sudoku Solver (Press S to Solve)");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Failed to load font\n";
        return -1;
    }

    int cellSize = 50;
    int selectedRow = -1, selectedCol = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Click to select cell
            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / cellSize;
                int y = event.mouseButton.y / cellSize;
                if (x >= 0 && x < 9 && y >= 0 && y < 9) {
                    selectedCol = x;
                    selectedRow = y;
                }
            }

            // Key press to enter number
            if (event.type == sf::Event::TextEntered && selectedRow != -1 && selectedCol != -1) {
                char c = static_cast<char>(event.text.unicode);
                if (c >= '1' && c <= '9') {
                    grid[selectedRow][selectedCol] = c - '0';
                } else if (c == '0') {
                    grid[selectedRow][selectedCol] = 0;
                }
            }

            // Press 'S' to solve
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
                solveSudoku(grid);
            }
        }

        // Draw
        window.clear(sf::Color::White);

        // Draw grid
        for (int i = 0; i <= 9; i++) {
            sf::RectangleShape line(sf::Vector2f(450, (i % 3 == 0 ? 3 : 1)));
            line.setPosition(0, i * cellSize);
            line.setFillColor(sf::Color::Black);
            window.draw(line);

            line.setSize(sf::Vector2f((i % 3 == 0 ? 3 : 1), 450));
            line.setPosition(i * cellSize, 0);
            window.draw(line);
        }

        // Draw numbers
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] != 0) {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(to_string(grid[i][j]));
                    text.setCharacterSize(28);
                    text.setFillColor(sf::Color::Black);
                    text.setPosition(j * cellSize + 18, i * cellSize + 10);
                    window.draw(text);
                }
            }
        }

        window.display();
    }

    return 0;
}
