#include <iostream>
#include <SFML/Graphics.hpp>
#include <optional>
/// Setareh Tavakoli 39913161032
using namespace std;
#define MAX_SIZE_STACK 200

/// Define of the stack class and it's methods
class MyArrayStack {
private:
    int stackTop;
    sf::Vector2i arr[MAX_SIZE_STACK];
public:
    MyArrayStack();

    ///checks if stack is Full
    bool stackIsFull();

    ///checks if stack is Empty
    bool stackIsEmpty();
    void push(sf::Vector2i operators);
    optional<sf::Vector2i> pop();
    optional<sf::Vector2i> topOperator();
};