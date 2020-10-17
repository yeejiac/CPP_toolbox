#include "k-means.h"

Point::Point(int id, std::string line):pointId_(id), clusterId_(0)
{
    dimensions_ = 0;
    std::stringstream is(line);
    double val;
    while(is>>val)
    {
        values_.push_back(val);
        dimensions_++;
    }
}

int Point::getDimensions()
{
    return dimensions_;
}

int Point::getCluster()
{
    return clusterId_;
}

int Point::getID()
{
    return pointId_;
}

void Point::setCluster(int val)
{
    clusterId_ = val;
}

double Point::getVal(int pos)
{
    return values_[pos];
}


Cluster::Cluster(int clusterId, Point centroid):clusterId_(clusterId)
{
    for(int i = 0; i<centroid.getDimensions(); i++)
    {
        centroid_.push_back(centroid.getVal(i));
    }
    addPoint(centroid);
}

void Cluster::addPoint(Point p)
{
    p.setCluster(this->clusterId_);
    points_.push_back(p);
}

bool Cluster::removePoint(int pointId)
{
    int size = points_.size();
    for(int i = 0; i < size; i++)
    {
        if(points_[i].getID() == pointId)
        {
            points_.erase(points_.begin()+i);
            return true;
        }
    }
    return false;
}

int Cluster::getId()
{
    return clusterId_;
}

Point Cluster::getPoint(int pos)
{
    return points_[pos];
}

int Cluster::getSize()
{
    return points_.size();
}

double Cluster::getCentroidByPos(int pos)
{
    return centroid_[pos];
}

void Cluster::setCentroidByPos(int pos, double val)
{
    centroid_[pos] = val;
}

Kmeans::Kmeans(int center, int iterations):center_(center),iterations_(iterations){}

int Kmeans::getNearestClusterId(Point point)
{
    double sum = 0.0;
    double min_dist;
    int nearestClusterId;
}


