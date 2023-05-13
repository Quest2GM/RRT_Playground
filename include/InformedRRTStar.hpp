#pragma once

#include <RRTStar.hpp>
#include <eigen3/Eigen/SVD>
#include <random>

using namespace std;

class InformedRRTStar : public RRTStar
{
public:
    Eigen::Matrix2f C;

    InformedRRTStar(Point start, Point end, vector<Rectangle> obstacles) : RRTStar(start, end, obstacles)
    {
        C = rotationToWorldFrame();
    }
    Eigen::Vector2f sampleFromUnitCircle();
    Eigen::Matrix2f rotationToWorldFrame();
    Point samplePoint() override;
};