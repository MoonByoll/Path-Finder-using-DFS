#include "maze.h"
#include <random>
/// Setareh Tavakoli 39913161032
#define THROW_IF_VISITED if (!cellData[returnedPosition.x][returnedPosition.y].visited) return returnedPosition; else return {};

using namespace std;

Maze::Maze(int width, int height, int sizeOfCell, int startX, int startY)
        : mazeWidth{width}, mazeHeight{height}, mazeCellResolution{sizeOfCell},
          mazePosition{startX, startY} {

    for (int i = 0; i < width; i++) {
        cellData[i] = new Cell[width];
    }

    ///goal initializer
    Random number;
    cellData[number.random_maker(3, width - 1)][number.random_maker(3, height - 1)].isGoal = true;

    ///slink initializer loop
    ///set the game matrix based on sfml coordinates
    for (int j = 0; j < width; j++) {
        for (int i = 0; i < height; i++) {
            ///set start point
            if (i == 0 && j == 0) {
                cellData[i][j].isSlink = false;
                cout << cellData[i][j].isSlink << " ";
                continue;
            }
            ///set goal point
            if (cellData[i][j].isGoal) {
                cellData[i][j].isSlink = false;
                cout << cellData[i][j].isSlink << " ";
                continue;
            }
            ///make random slinks
            if (number.random_maker(0, 1) == 1) {
                cellData[i][j].isSlink = true;
                ///set random direction
                cellData[i][j].slink.direction = number.random_maker(1, 8);
                ///set random steps
                cellData[i][j].slink.stepsCount = number.random_maker(1, width / 2);
                cout << cellData[i][j].isSlink << " ";
            } else {
                cellData[i][j].isSlink = false;
                cout << cellData[i][j].isSlink << " ";
            }
        }
        cout << "\n";
    }
    ///push start point to the stack
    mazeCurrentPosition = &cellData[mazePosition.x][mazePosition.y];
    mazeCurrentPosition->visited = true;
    mazeStackPath.push(mazePosition);
}

///frame by frame updater
void Maze::frameUpdate() {
    run();
}

void Maze::run() {
    ///returns the coordinate of the next valid neighbor
    auto position = nextCellCoordinateFinder();

    if (position) {

        mazeStackPath.push({mazePosition.x, mazePosition.y});
        Cell *next = &cellData[position->x][position->y];
        next->visited = true;
        ///set next cell as the current cell, and next cell coordinates as current coordinates
        mazePosition = *position;
        mazeCurrentPosition = next;
        mazeStackPath.push(mazePosition);

        ///if there was no way to go back track to the last coordinate you have saved in stack
    } else {
        if (!mazeStackPath.stackIsEmpty()) {
            auto position = mazeStackPath.topOperator();
            mazePosition.x = position->x;
            mazePosition.y = position->y;
            mazeCurrentPosition = &cellData[mazePosition.x][mazePosition.y];
            ///backtracking rules:
            mazeStackPath.pop();
        } else if (mazeStackPath.stackIsEmpty()) {
            cout << "NO Path FOUND ";
            exit(0);
        }
    }
}

///this function returns the coordinate of the next valid neighbor
optional<sf::Vector2i> Maze::nextCellCoordinateFinder() {
    int step = 1, i = 0;
    ///stores valid neighbors
    sf::Vector2i next_cell_list[10];

    ///if the current coordinate is goal exit program
    if (cellData[mazePosition.x][mazePosition.y].isGoal) {
        cout << "YES YOU FOUND THE GOAL ";
        exit(0);
    }

    ///if the current coordinate is slink setup next house
    if (cellData[mazePosition.x][mazePosition.y].isSlink) {

        sf::Vector2i delta;
        sf::Vector2i returnedPosition;
        cout << step << "  " << cellData[mazePosition.x][mazePosition.y].slink.direction << "\n";
        step = cellData[mazePosition.x][mazePosition.y].slink.stepsCount;

        switch (cellData[mazePosition.x][mazePosition.y].slink.direction) {
            case slink_dir::U:
                returnedPosition = sf::Vector2i(mazePosition.x, max(0, mazePosition.y - step));
                THROW_IF_VISITED
            case slink_dir::UR:
                delta.x = min(mazeWidth - mazePosition.x - 1, step);
                delta.y = min(mazePosition.y, step);
                if (delta.x < delta.y) { delta.y = delta.x; }
                else { delta.x = delta.y; }
                returnedPosition = sf::Vector2i(mazePosition.x + delta.x, mazePosition.y - delta.y);
                THROW_IF_VISITED
            case slink_dir::R:
                returnedPosition = sf::Vector2i(min(mazePosition.x + step, mazeWidth - 1), mazePosition.y);
                THROW_IF_VISITED
            case slink_dir::DR:
                delta.x = min(mazeWidth - mazePosition.x - 1, step);
                delta.y = min(mazeHeight - mazePosition.y - 1, step);
                if (delta.x < delta.y) { delta.y = delta.x; }
                else { delta.x = delta.y; }
                returnedPosition = sf::Vector2i(mazePosition.x + delta.x, mazePosition.y + delta.y);
                THROW_IF_VISITED
            case slink_dir::D:
                returnedPosition = sf::Vector2i(mazePosition.x, min(mazeHeight - 1, mazePosition.y + step));
                THROW_IF_VISITED
            case slink_dir::DL:
                delta.x = min(mazePosition.x, step);
                delta.y = min(mazeHeight - mazePosition.y - 1, step);
                if (delta.x < delta.y) { delta.y = delta.x; }
                else { delta.x = delta.y; }
                returnedPosition = sf::Vector2i(mazePosition.x - delta.x, mazePosition.y + delta.y);
                THROW_IF_VISITED
            case slink_dir::L:
                returnedPosition = sf::Vector2i(max(mazePosition.x - step, 0), mazePosition.y);
                THROW_IF_VISITED
            case slink_dir::UL:
                delta.x = min(mazePosition.x, step);
                delta.y = min(mazePosition.y, step);
                if (delta.x < delta.y) { delta.y = delta.x; }
                else { delta.x = delta.y; }
                returnedPosition = sf::Vector2i(mazePosition.x - delta.x, mazePosition.y - delta.y);
                THROW_IF_VISITED
        }
    } else { ///if current house is ot a slink, find not visited neighbors and choose randomly among them

        // Check left
        if (mazePosition.x - step >= 0) {
            if (!cellData[mazePosition.x - step][mazePosition.y].visited) {
                next_cell_list[i++] = {mazePosition.x - step, mazePosition.y};
            }
        }
        // Check right
        if (mazePosition.x + step < mazeWidth) {
            if (!cellData[mazePosition.x + step][mazePosition.y].visited) {
                next_cell_list[i++] = {mazePosition.x + step, mazePosition.y};
            }
        }
        // Check up
        if (mazePosition.y - step >= 0) {
            if (!cellData[mazePosition.x][mazePosition.y - step].visited) {
                next_cell_list[i++] = {mazePosition.x, mazePosition.y - step};
            }
        }
        // Check down
        if (mazePosition.y + step < mazeHeight) {
            if (!cellData[mazePosition.x][mazePosition.y + step].visited) {
                next_cell_list[i++] = {mazePosition.x, mazePosition.y + step};
            }
        }
        // Check up right
        if (mazePosition.x + step < mazeWidth && mazePosition.y - step >= 0) {
            if (!cellData[mazePosition.x + step][mazePosition.y - step].visited) {
                next_cell_list[i++] = {mazePosition.x + step, mazePosition.y - step};
            }
        }
        // Check up left
        if (mazePosition.x - step >= 0 && mazePosition.y - step >= 0) {
            if (!cellData[mazePosition.x - step][mazePosition.y - step].visited) {
                next_cell_list[i++] = {mazePosition.x - step, mazePosition.y - step};
            }
        }
        //Check down right
        if (mazePosition.x + step < mazeWidth && mazePosition.y + step < mazeHeight) {
            if (!cellData[mazePosition.x + step][mazePosition.y + step].visited) {
                next_cell_list[i++] = {mazePosition.x + step, mazePosition.y + step};
            }
        }
        //Check down left
        if (mazePosition.x - step >= 0 && mazePosition.y + step < mazeHeight) {
            if (!cellData[mazePosition.x - step][mazePosition.y + step].visited) {
                next_cell_list[i++] = {mazePosition.x - step, mazePosition.y + step};
            }
        }
        ///Choose a neighbor to go randomly
        if (i > 0) {
            int index = rand() % i;
            return next_cell_list[index];
        }
    }
    return {};
}


void Maze::draw(sf::RenderWindow &window) {
    for (int x = 0; x < mazeHeight; x++) {
        for (int y = 0; y < mazeWidth; y++) {
            int gx = x * mazeCellResolution;
            int gy = y * mazeCellResolution;
            Cell *cell = &cellData[x][y];
            if (cell == mazeCurrentPosition) {
                sf::RectangleShape rectangle;
                rectangle.setFillColor(sf::Color::Blue);
                rectangle.setSize(sf::Vector2f(mazeCellResolution - 4, mazeCellResolution - 4));
                rectangle.setPosition(gx + 1, gy + 1);
                window.draw(rectangle);
            } else {
                if (!cell->visited) {
                    sf::RectangleShape rectangle;
                    rectangle.setFillColor(sf::Color{255, 225, 255, 255});
                    rectangle.setSize(sf::Vector2f(mazeCellResolution - 4, mazeCellResolution - 4));
                    rectangle.setPosition(gx + 2, gy + 2);
                    window.draw(rectangle);
                }
                if (cell->isSlink) {
                    sf::RectangleShape rectangle;
                    rectangle.setFillColor(sf::Color::Red);
                    rectangle.setSize(sf::Vector2f(mazeCellResolution - 30, mazeCellResolution - 30));
                    rectangle.setPosition(gx + 15, gy + 15);
                    window.draw(rectangle);
                }
                if (cell->isGoal) {
                    sf::RectangleShape rectangle;
                    rectangle.setFillColor(sf::Color::Yellow);
                    rectangle.setSize(sf::Vector2f(mazeCellResolution - 16, mazeCellResolution - 16));
                    rectangle.setPosition(gx + 8, gy + 8);
                    window.draw(rectangle);
                }
            }
            if (cell->top) {
                sf::RectangleShape rectangle;
                rectangle.setFillColor(sf::Color::White);
                rectangle.setSize(sf::Vector2f(mazeCellResolution, 1));
                rectangle.setPosition(gx, gy);
                window.draw(rectangle);
            }
            if (cell->bottom) {
                sf::RectangleShape rectangle;
                rectangle.setFillColor(sf::Color::White);
                rectangle.setSize(sf::Vector2f(mazeCellResolution, 1));
                rectangle.setPosition(gx, gy + mazeCellResolution - 1);
                window.draw(rectangle);
            }
            if (cell->left) {
                sf::RectangleShape rectangle;
                rectangle.setFillColor(sf::Color::White);
                rectangle.setSize(sf::Vector2f(1, mazeCellResolution));
                rectangle.setPosition(gx, gy);
                window.draw(rectangle);
            }
            if (cell->right) {
                sf::RectangleShape rectangle;
                rectangle.setFillColor(sf::Color::White);
                rectangle.setSize(sf::Vector2f(1, mazeCellResolution));
                rectangle.setPosition(gx + mazeCellResolution - 1, gy);
                window.draw(rectangle);
            }
        }
    }
}