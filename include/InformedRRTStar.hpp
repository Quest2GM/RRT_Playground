#pragma once

#include <RRTStar.hpp>
#include <eigen3/Eigen/SVD>

using namespace std;

class InformedRRTStar : public RRTStar
{
public:
    Eigen::Matrix2f C;
    vector<RRTNode*> xSoln;

    InformedRRTStar(Point start, Point end, vector<Rectangle> obstacles) : RRTStar(start, end, obstacles)
    {
        C = rotationToWorldFrame();
    }
    Eigen::Vector2f sampleFromUnitCircle();
    Eigen::Matrix2f rotationToWorldFrame();
    Point samplePoint(float cMax);
    bool runIteration(sf::RenderWindow &window) override;
};