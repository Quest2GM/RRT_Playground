#include <RRT.hpp>

RRTNode::RRTNode(int x, int y)
{
    xPos = x; yPos = y;
    parent = NULL;
    distToCome = 0;
}

RRTNode::~RRTNode() {};

RRT::RRT(int startX, int startY, int endX, int endY)
{
    this->startX = startX;
    this->startY = startY;
    this->endX = endX;
    this->endY = endY;
    root = NULL;
}

RRT::~RRT() 
{
    cout << "RRT Destructed" << endl;
}

RRTNode* RRT::addNode(int x, int y, sf::RenderWindow& window)
{   
    RRTNode* child = new RRTNode(x, y);

    if (root == NULL)
    {
        root = child;
        root->nodeId = id++;
        return root;
    }

    RRTNode* parent = findClosest(root, x, y);
    
    child->parent = parent;
    child->nodeId = id++;
    child->distToCome = parent->distToCome + findDistance(x, parent->xPos, y, parent->yPos);
    parent->children.push_back(child);
    drawBranch(parent->xPos, parent->yPos, x, y, window, sf::Color::White);

    return child;
}

void RRT::drawBranch(int x1, int y1, int x2, int y2, sf::RenderWindow& window, sf::Color colour)
{
    sf::Vertex branch[] =
    {
        sf::Vertex(sf::Vector2f(x1, y1), colour),
        sf::Vertex(sf::Vector2f(x2, y2), colour)
    };
    window.draw(branch, 2, sf::Lines);
}

RRTNode* RRT::findClosest(RRTNode* node, int x, int y)
{ 
    static RRTNode* minNode = root;

    if (node == NULL)
    {
        return minNode;
    }
    
    static float minDist = findDistance(x, minNode->xPos, y, minNode->yPos);

    // Reset static variables if first iteration
    if (node == root)
    {
        minNode = root;
        minDist = findDistance(x, minNode->xPos, y, minNode->yPos);
    }

    float currDist = findDistance(x, node->xPos, y, node->yPos);
    if (currDist < minDist)
    {
        minDist = currDist;
        minNode = node;
    }
    
    for (int i = 0; i < node->children.size(); i++)
    {
        findClosest(node->children[i], x, y);
    }

    return minNode;
}

float RRT::findDistance(int x1, int x2, int y1, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool RRT::runIteration(sf::RenderWindow &window)
{
    int rX = rand() % 1200, rY = rand() % 800;
    addNode(rX, rY, window);

    if (findDistance(rX, endX, rY, endY) < 5)
    {
        RRTNode* finalNode = addNode(endX, endY, window);
        traceBack(finalNode, window);
        return true;
    }
    return false;
}

void RRT::dispStartEnd(sf::RenderWindow &window)
{
    addNode(startX, startY, window);
    sf::CircleShape startCircle(5);
    startCircle.setPosition(sf::Vector2f(startX-5, startY-5));
    startCircle.setFillColor(sf::Color(0, 255, 0));
    sf::CircleShape endCircle(5);
    endCircle.setPosition(sf::Vector2f(endX-5, endY-5));
    endCircle.setFillColor(sf::Color(255, 0, 0));
    window.draw(startCircle);
    window.draw(endCircle);
}

void RRT::traceBack(RRTNode* finalNode, sf::RenderWindow& window)
{
    RRTNode* currNode = finalNode;
    while (currNode->parent != NULL)
    {
        RRTNode* par = currNode->parent;
        drawBranch(par->xPos, par->yPos, currNode->xPos, currNode->yPos, window, sf::Color::Red);
        currNode = par;
    }
}