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


Point InformedRRTStar::samplePoint(sf::RenderWindow &window)
{
    if (lastNode == NULL)
    {
        Point sample(rand() % 1200, rand() % 800);
        return sample;
    }
    else
    {
        float cMin = startToGoal.getLength()/2;
        float cMax = lastNode->distToCome/2;
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

bool InformedRRTStar::runIteration(sf::RenderWindow &window)
{
    Point newPoint = samplePoint(window);
    RRTNode* newNode = addNode(newPoint, window);

    if (newNode == NULL)
    {
        return false;
    }

    iterations++;
    if (iterations % 100 == 0)
    {
        cout << "Iteration: " << iterations << endl;
    }

    vector<RRTNode*> closeNodes = findNodesWithinRadius(root, newNode, searchRadius);
    rewireEdges(newNode, closeNodes);
   
    // Rebuild tree
    window.clear(sf::Color::White);
    reDrawTree(root, window);
    buildEnvironment(window);

    // Draw path if found
    if (!reachedDest)
    {
        if (inGoalRegion(newNode))
        {
            reachedDest = true;
            lastNode = addNode(end, window);
            traceBack(lastNode, window);
        }
    }
    else
    {
        // Draw ellipse
        float cMax = lastNode->distToCome / 2;
        float cMin = startToGoal.getLength() / 2;
        Ellipse e(start, end, cMax, sqrt(pow(cMax, 2) - pow(cMin, 2)));
        e.draw(window);
        traceBack(lastNode, window);
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