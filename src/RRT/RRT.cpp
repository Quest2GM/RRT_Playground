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

    if (isCollision(parent, child))
    {
        return NULL;
    }
    
    child->parent = parent;
    child->nodeId = id++;
    child->distToCome = parent->distToCome + findDistance(x, parent->xPos, y, parent->yPos);
    parent->children.push_back(child);
    drawBranch(parent->xPos, parent->yPos, x, y, window, sf::Color::Magenta);

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

void RRT::drawObstacles(sf::RenderWindow &window)
{
    sf::RectangleShape rectangle(sf::Vector2f(300, 700));
    rectangle.setFillColor(sf::Color(40,40,40));
    rectangle.setPosition(sf::Vector2f(150, 0));
    obsLocs.push_back({150, 0, 300, 700});
    window.draw(rectangle);
    sf::RectangleShape rectangle2(sf::Vector2f(300, 700));
    rectangle2.setFillColor(sf::Color(40,40,40));
    rectangle2.setPosition(sf::Vector2f(700, 100));
    obsLocs.push_back({700, 100, 300, 700});
    window.draw(rectangle2);
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
    dispStartEnd(window);

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

bool RRT::isCollision(RRTNode* p, RRTNode* c)
{
    for (int i = 0; i < obsLocs.size(); i++)
    {
        int rectX = obsLocs[i][0];
        int rectY = obsLocs[i][1];
        int rectW = obsLocs[i][2];
        int rectH = obsLocs[i][3];

        bool I1 = checkIntersection(rectX, rectX + rectW, rectY, rectY,
                                    p->xPos, c->xPos, p->yPos, c->yPos);
        bool I2 = checkIntersection(rectX, rectX, rectY, rectY + rectH,
                                    p->xPos, c->xPos, p->yPos, c->yPos);
        bool I3 = checkIntersection(rectX + rectW, rectX + rectW, rectY, rectY + rectH,
                                    p->xPos, c->xPos, p->yPos, c->yPos);
        bool I4 = checkIntersection(rectX, rectX + rectW, rectY + rectH, rectY + rectH,
                                    p->xPos, c->xPos, p->yPos, c->yPos);

        if (I1 || I2 || I3 || I4)
        {
            return true;
        }
    }
    return false;
}

bool RRT::checkIntersection(int x1, int x2, int y1, int y2, int a1, int a2, int b1, int b2)
{
    Eigen::Vector3d P(x1, y1, 0);
    Eigen::Vector3d R(x2 - x1, y2 - y1, 0);
    Eigen::Vector3d Q(a1, b1, 0);
    Eigen::Vector3d S(a2 - a1, b2 - b1, 0);

    float crossRS = R.cross(S).coeff(2);
    float crossQmPR = (Q - P).cross(R).coeff(2);
    float crossQmPS = (Q - P).cross(S).coeff(2);
    float dotQmPR = (Q - P).dot(R);
    float dotRR = R.dot(R);
    float dotQpSmPR = (Q + S - P).dot(R);
    
    if (crossRS == 0 && crossQmPR == 0)
    {
        if ((dotQmPR >= 0 && dotRR >= dotQmPR) || (dotQpSmPR >= 0 && dotRR >= dotQpSmPR))
        {
            return true;
        }
        return false;
    }

    if (crossRS == 0 && crossQmPR != 0)
    {
        return false;
    }
    
    float t = crossQmPS / crossRS;
    float u = crossQmPR / crossRS;

    return (0 <= t && t <= 1 && 0 <= u && u <= 1);
}

