#include "Functions.h"
#include <random>

int getRandomNumber(int min, int max) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}
