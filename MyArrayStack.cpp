#include "MyArrayStack.h"
#include <iostream>
#include <optional>
/// Setareh Tavakoli 39913161032
using namespace std;

MyArrayStack::MyArrayStack() {
    stackTop = -1;
}

bool MyArrayStack::stackIsFull() {
    if (this->stackTop == MAX_SIZE_STACK - 1) return true;
    else return false;
}

bool MyArrayStack::stackIsEmpty() {
    if (this->stackTop == (-1)) return true;
    else return false;
}

void MyArrayStack::push(sf::Vector2i operators) {
    if (stackIsFull()) {
        cout << "The Stack is Full" << "\n";
    } else {
        this->stackTop++;
        this->arr[this->stackTop] = {operators.x, operators.y};
    }
}

optional<sf::Vector2i> MyArrayStack::pop() {
    if (stackIsEmpty()) {
        cout << "The Stack is Empty" << "\n";
        exit(0);
    } else {
        sf::Vector2i k = this->arr[this->stackTop];
        this->arr[this->stackTop] = {0, 0};
        this->stackTop--;
        return k;
    }
}

optional<sf::Vector2i> MyArrayStack::topOperator() {
    if (stackIsEmpty()) {
        cout << " Nothing to show " << "\n";
        return nullopt;
    } else {
        return this->arr[this->stackTop];
    }
}