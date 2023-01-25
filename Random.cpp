#include "Random.h"
/// Setareh Tavakoli 39913161032
Random::Random() {
    srand((unsigned) time(NULL));
}

int Random::random_maker(int first, int last) {
    int range = (last - first) + 1;
    return first + (rand() % range);;
}