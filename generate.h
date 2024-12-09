#include "point.h"
#include <random>

std::vector<Point> generatePoints(int n) {
    std::vector<Point> points(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1e6);

    for (int i = 0; i < n; ++i) {
        points[i].x = dis(gen);
        points[i].y = dis(gen);
    }

    return points;
}