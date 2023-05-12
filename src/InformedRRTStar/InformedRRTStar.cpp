#include <InformedRRTStar.hpp>

using namespace std;


Eigen::Vector2f InformedRRTStar::sampleFromUnitCircle()
{
    float rand1 = rand() / static_cast<float>(RAND_MAX);
    float theta = rand1 * 2 * M_PI;
    float x = cos(theta);
    float y = sin(theta);
    Eigen::Vector2f samplePoint(x, y);
    return samplePoint;
}


Eigen::Matrix2f InformedRRTStar::rotationToWorldFrame()
{   
    Line sG(start, end);
    Eigen::Vector2f a1(end.x - start.x, end.y - start.y);
    a1 /= sG.getLength();
    Eigen::Vector2f eye1(1, 0);
    Eigen::Matrix2f M = a1 * eye1.transpose();
    Eigen::BDCSVD<Eigen::Matrix2f> svd(M, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::Matrix2f X;
    X << 1, 0,
         0, svd.matrixU().determinant() * svd.matrixV().determinant();
    Eigen::Matrix2f C;
    C = svd.matrixU() * X * svd.matrixV().transpose();
    return C;
}


Point InformedRRTStar::samplePoint(float cMax)
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
        Point center = startToGoal.getMidpoint();
        Eigen::Matrix2f L;
        L << cMax / 2, 0,
             0, sqrt(pow(cMax, 2) - pow(cMin, 2))/2;
        Eigen::Vector2f circSample = sampleFromUnitCircle();
        Eigen::Vector2f out = C * L * circSample;
        Point sample(out.coeff(0) + center.x, out.coeff(1) + center.y);
        return sample;
    }
}


bool InformedRRTStar::runIteration(sf::RenderWindow &window)
{
    float cBest = 1000000;

    if (lastNode != NULL)
    {
        vector<RRTNode*> closeNodesToGoal = findNodesWithinRadius(root, lastNode, goalRadius);
        for (int i = 0; i < closeNodesToGoal.size(); i++)
        {
            Line l(closeNodesToGoal[i], lastNode);
            if (closeNodesToGoal[i]->distToCome + l.getLength() < cBest)
            {
                cBest = closeNodesToGoal[i]->distToCome + l.getLength();
            }
        }
    }

    Point newPoint = samplePoint(cBest);
    RRTNode* newNode = addNode(newPoint, window);

    if (newNode == NULL)
    {
        return false;
    }

    iterations++;
    if (iterations % 100 == 0)
    {
        cout << iterations << endl;
    }

    vector<RRTNode*> closeNodes = findNodesWithinRadius(root, newNode, searchRadius);
    rewireEdges(newNode, closeNodes);

    // Rebuild tree
    window.clear(sf::Color::White);
    reDrawTree(root, window);
    buildEnvironment(window);

    // Draw path if found
    if ((inGoalRegion(newNode)) && (xSoln.size() == 0))
    {
        xSoln.push_back(newNode);
        reachedDest = true;
        lastNode = addNode(end, window);
        traceBack(lastNode, window);
    }
    else
    {
        if (inGoalRegion(newNode))
        {
            xSoln.push_back(newNode);
        }
        if (reachedDest)
        {
            traceBack(lastNode, window);
        }
    }

    // Exit if maxIterations reached
    if (iterations >= maxIterations)
    {
        cout << "Max Iterations Reached!" << endl;
        if (lastNode == NULL)
        {
            cout << "Could not find goal!" << endl;
        }
        else
        {
            cout << "Distance to Come: " << lastNode->distToCome << endl;
        }
        return true;
    }

    return false;
}