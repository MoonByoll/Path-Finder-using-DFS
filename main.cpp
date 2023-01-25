#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include "maze.h"

#define CELL_SIZE  60
/// Setareh Tavakoli 39913161032
using namespace std;
using namespace sf;

int main() {

    bool wait = false;
    int boardSize;
    cout << "please enter board size:" << "\n";
    cin >> boardSize;
    if (boardSize < 4 || boardSize > 20) {
        cout << "Not VALIED , run the program again" << "\n";
        exit(0);
    }

    RenderWindow window(sf::VideoMode(boardSize * CELL_SIZE, boardSize * CELL_SIZE), "Maze Generator");

    Maze maze(boardSize, boardSize, CELL_SIZE, 0, 0);

    while (window.isOpen()) {

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            cout << "RESUME" << "\n";
            wait = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            cout << "PAUSE" << "\n";
            wait = false;
        }
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        this_thread::sleep_for(chrono::milliseconds{800});
        window.clear();
        if (wait) {
            maze.frameUpdate();
        }
        maze.draw(window);
        window.display();
    }
    return 0;
}