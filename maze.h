#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <optional>
#include "Random.h"
#include "MyArrayStack.h"
/// Setareh Tavakoli 39913161032
namespace slink_dir {
    enum slinkDirections {
        U = 1, UR, R, DR, D, DL, L, UL
    };
}

using namespace std;

class Maze {
private:

    struct Slink {
        int direction;
        int stepsCount;
    };
    struct Cell {
        Slink slink;
        bool isGoal = false;
        bool isSlink = false;
        bool visited = false;
        bool top = true;
        bool bottom = true;
        bool left = true;
        bool right = true;
    };
    int mazeWidth, mazeHeight, mazeCellResolution;

    ///get coordinates
    sf::Vector2i mazePosition{0, 0};

    Cell **cellData = new Cell *[mazeHeight];

    Cell *mazeCurrentPosition{nullptr};

    MyArrayStack mazeStackPath;

    void run();

    optional<sf::Vector2i> nextCellCoordinateFinder();

public:
    Maze(int width, int height, int sizeOfCell, int startX, int startY);

    void frameUpdate();

    void draw(sf::RenderWindow &window);
};