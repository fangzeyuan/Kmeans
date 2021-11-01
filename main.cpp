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
void kMeansClustering(vector<Point>* points, int epochs, int k) {
    vector<Point> centroids;
    srand(time(0));  // need to set the random seed
    int n = points->size();
    for (int i = 0; i < k; ++i) {
        centroids.push_back(points->at(rand() % n));
    }


    for (int i = 0; i < epochs ; i++) {
        for (vector<Point>::iterator c = begin(centroids);
             c != end(centroids); ++c) {
            // quick hack to get cluster index
            int clusterId = c - begin(centroids);

            for (vector<Point>::iterator it = points->begin();
                 it != points->end(); ++it) {

                Point p = *it;
                double dist = c->distance(p);
                if (dist < p.minDist) {
                    p.minDist = dist;
                    p.cluster = clusterId;
                }
                *it = p;
            }
        }
        vector<int> nPoints;
        vector<double> sumX, sumY;

// Initialise with zeroes
        for (int j = 0; j < k; ++j) {
            nPoints.push_back(0);
            sumX.push_back(0.0);
            sumY.push_back(0.0);
        }
    // Iterate over points to append data to centroids
        for (vector<Point>::iterator it = points->begin();
            it != points->end(); ++it) {
            int clusterId = it->cluster;
            nPoints[clusterId] += 1;
            sumX[clusterId] += it->x;
            sumY[clusterId] += it->y;

            it->minDist = __DBL_MAX__;  // reset distance
        }
        for (vector<Point>::iterator c = begin(centroids);
             c != end(centroids); ++c) {
            int clusterId = c - begin(centroids);
            c->x = sumX[clusterId] / nPoints[clusterId];
            c->y = sumY[clusterId] / nPoints[clusterId];
        }
    }

// Compute the new centroids


}
vector<Point> readcsv() {
    vector<Point> points;
    string line;
    ifstream file("Mall_data2d.csv");

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
    vector<Point> points = readcsv();
    kMeansClustering(&points,100000,5);
    ofstream myfile;
    myfile.open("output.csv");
    myfile << "x,y,c" << endl;

    for (vector<Point>::iterator it = points.begin();
         it != points.end(); ++it) {
        myfile << it->x << "," << it->y << "," << it->cluster << endl;
    }
    myfile.close();
    return 0;
}
