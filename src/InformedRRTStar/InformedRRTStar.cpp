#include <InformedRRTStar.hpp>

using namespace std;


Eigen::Vector2f InformedRRTStar::sampleFromUnitCircle()
{
    float rand1 = rand() / static_cast<float>(RAND_MAX);
    float radius = rand() / static_cast<float>(RAND_MAX);
    float theta = rand1 * 2 * M_PI;
    Eigen::Vector2f samplePoint(radius * cos(theta), radius * sin(theta));
    return samplePoint;
}


Eigen::Matrix2f InformedRRTStar::rotationToWorldFrame()
{   
    Line sG(start, end);
    Eigen::Vector2f a1(end.x - start.x, end.y - start.y);
    a1 /= sG.getLength();
    Eigen::Vector2f eye1(1, 0);
    Eigen::Matrix2f M = a1 * eye1.transpose();
    Eigen::JacobiSVD<Eigen::Matrix2f> svd(M, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::Matrix2f D;
    D << 1, 0,
         0, svd.matrixU().determinant() * svd.matrixV().determinant();
    Eigen::Matrix2f C;
    C = svd.matrixU() * D * svd.matrixV().transpose();
    return C;
}


Point InformedRRTStar::samplePoint()
{
    if (lastNode == NULL)
    {
        Point sample(rand() % 1200, rand() % 800);
        return sample;
    }
    else
    {
        Line startToGoal(start, end);
        float cMin = startToGoal.getLength();
        float cMax = lastNode->distToCome;
        Point center = startToGoal.getMidpoint();
        Eigen::Matrix2f L;
        L << cMax / 2, 0,
             0, sqrt(pow(cMax, 2) - pow(cMin, 2))/2;
        Eigen::Vector2f xBall = sampleFromUnitCircle();
        Eigen::Vector2f out = C * L * xBall;
        Point sample(out.coeff(0) + center.x, out.coeff(1) + center.y);
        return sample;
    }
}