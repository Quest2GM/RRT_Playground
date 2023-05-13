#include <AnytimeRRT.hpp>

using namespace std;

bool AnytimeRRT::runIteration(sf::RenderWindow &window)
{
    Point newPoint = samplePoint();
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

    // This if statement makes it "Anytime"
    if (reachedDest)
    {
        vector<RRTNode*> closeNodes = findNodesWithinRadius(root, newNode, searchRadius);
        rewireEdges(newNode, closeNodes);
    }
   
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