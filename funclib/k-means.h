#ifndef KMEANS_H_
#define KMEANS_H_

#include <iostream>
#include <cmath>
#include <string.h>
#include <time.h>
#include <map>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#define min_pt 0
#define data_HV 300 //資料上限
#define data_LV 20 // 資料下限

class Point
{
public:
    Point(int id, std::string line);
    int getDimensions();
    int getCluster();
    int getID();
    void setCluster(int val);
    double getVal(int pos);
private:
    int pointId_;
    int clusterId_;
    int dimensions_;
    std::vector<double> values_;
};

class Cluster
{
public:
    Cluster(int clusterId, Point centroid);
    void addPoint(Point p);
    bool removePoint(int pointId);
    int getId();
    Point getPoint(int pos);
    int getSize();
    double getCentroidByPos(int pos);
    void setCentroidByPos(int pos, double val);
private:
    int clusterId_;
    std::vector<double> centroid_;
    std::vector<Point> points_;
};

class Kmeans
{
public:
    Kmeans(int center, int iterations);
    ~Kmeans();
    void getRawData(std::string path);
    int getNearestClusterId(Point point);
    void calculation(std::vector<Point> &rawData);

private:
    int data_volumns_;
    int data_dimensions_;
    int center_; //k
    int iterations_; // 迭代次數
    std::map<std::string, Cluster> clusterInfo_;

};

#endif