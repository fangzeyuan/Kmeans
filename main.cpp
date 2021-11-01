#include <ctime>     // for a random seed
#include <fstream>   // for file-reading
#include <iostream>  // for file-reading
#include <sstream>   // for file-reading
#include <vector>

using namespace std;

struct Point {
    double x, y;     // coordinates
    int cluster;     // no default cluster
    double minDist;  // default infinite dist to nearest cluster

    Point() :
            x(0.0),
            y(0.0),
            cluster(-1),
            minDist(__DBL_MAX__) {}

    Point(double x, double y) :
            x(x),
            y(y),
            cluster(-1),
            minDist(__DBL_MAX__) {}

    double distance(Point p) {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
    }
};

vector<Point> readcsv() {
    vector<Point> points;
    string line;
    ifstream file("mall_data.csv");

    while (getline(file, line)) {
        stringstream lineStream(line);
        string bit;
        double x, y;
        getline(lineStream, bit, ',');
        x = stof(bit);
        getline(lineStream, bit, '\n');
        y = stof(bit);

        points.push_back(Point(x, y));
    }
    return points;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
