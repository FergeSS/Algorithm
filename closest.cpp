#include "generate.h"
#include <chrono>

int compareX(const void* a, const void* b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x != p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
}

int compareY(const void* a, const void* b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y != p2->y) ? (p1->y - p2->y) : (p1->x - p2->x);
}

float dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

float bruteForce(std::vector<Point>& P) {
    float min = std::numeric_limits<float>::max();
    for (size_t i = 0; i < P.size(); ++i)
        for (size_t j = i + 1; j < P.size(); ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

float min(float x, float y) {
    return (x < y) ? x : y;
}

float stripClosest(std::vector<Point>& strip, float d) {
    float min = d;
    for (size_t i = 0; i < strip.size(); ++i)
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i], strip[j]) < min)
                min = dist(strip[i], strip[j]);
    return min;
}

float closestUtil(const std::vector<Point>& Px, const std::vector<Point>& Py) {
    if (Px.size() <= 3)
        return bruteForce(const_cast<std::vector<Point>&>(Px));

    int mid = Px.size() / 2;
    Point midPoint = Px[mid];

    std::vector<Point> Pyl(Py.begin(), Py.begin() + mid);
    std::vector<Point> Pyr(Py.begin() + mid, Py.end());

    float dl = closestUtil(std::vector<Point>(Px.begin(), Px.begin() + mid), Pyl);
    float dr = closestUtil(std::vector<Point>(Px.begin() + mid, Px.end()), Pyr);

    float d = min(dl, dr);

    std::vector<Point> strip;
    for (const auto& point : Py)
        if (abs(point.x - midPoint.x) < d)
            strip.push_back(point);

    return stripClosest(strip, d);
}

float closest(std::vector<Point>& P) {
    std::vector<Point> Px = P;
    std::vector<Point> Py = P;

    std::qsort(&Px[0], Px.size(), sizeof(Point), compareX);
    std::qsort(&Py[0], Py.size(), sizeof(Point), compareY);

    return closestUtil(Px, Py);
}
int main() {
    int n;
    std::cout << "Enter the number of points: ";
    std::cin >> n;    

    for (int i = 0; i < 10; ++i) {
        std::vector<Point> points = generatePoints(n);
        auto start = std::chrono::high_resolution_clock::now();
        closest(points);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;
    }

    return 0;
}