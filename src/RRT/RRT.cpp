#include <RRT.hpp>

using namespace std;

RRT::RRT(Point start, Point end, vector<Rectangle> obstacles)
{
    this->start = start;
    this->end = end;
    this->obstacles = obstacles;
    root = NULL;
}

RRT::~RRT()
{
    deleteNodes(root);
}

void RRT::deleteNodes(RRTNode* node)
{
    for (int i = 0; i < node->children.size(); i++)
    {
        deleteNodes(node->children[i]);
    }
    delete node;
}


RRTNode* RRT::addNode(Point childPoint, sf::RenderWindow& window)
{   
    RRTNode* child = new RRTNode(childPoint.x, childPoint.y);

    if (root == NULL)
    {
        root = child;
        root->nodeId = id++;
        return root;
    }

    RRTNode* parent = findClosest(root, childPoint);

    Line parToChild(parent, child);
    float pcDist = parToChild.getLength();

    // If pcDist > expandDist, avoid collision checking. Thus, don't merge if statements.
    if (pcDist > expandDist)
    {
        delete child;
        return NULL;
    }
    else if (isCollision(parent, child))
    {
        delete child;
        return NULL;
    }
    
    // Add child node
    child->parent = parent;
    child->nodeId = id++;
    child->distToCome = parent->distToCome + pcDist;
    parent->children.push_back(child);
    parToChild.draw(window, sf::Color::Magenta);

    return child;
}

RRTNode* RRT::findClosest(RRTNode* node, Point p)
{ 
    static RRTNode* minNode = root;

    if (node == NULL)
    {
        return minNode;
    }
    
    Line minLine(minNode, p);
    static float minDist = minLine.getLength();

    // Reset static variables if first iteration
    if (node == root)
    {
        minNode = root;
        minDist = minLine.getLength();
    }

    // Update minimum node if current node is closer to point
    Line nodeLine(node, p);
    float currDist = nodeLine.getLength();
    if (currDist < minDist)
    {
        minDist = currDist;
        minNode = node;
    }
    
    for (int i = 0; i < node->children.size(); i++)
    {
        findClosest(node->children[i], p);
    }

    return minNode;
}

void RRT::traceBack(RRTNode* finalNode, sf::RenderWindow& window)
{
    RRTNode* currNode = finalNode;
    while (currNode->parent != NULL)
    {
        RRTNode* par = currNode->parent;
        Line newTraceLine(par, currNode);
        newTraceLine.drawThick(window, sf::Color::Blue);
        currNode = par;
    }
}

bool RRT::isCollision(RRTNode* p, RRTNode* c)
{
    Line parToChild(p, c);
    for (int i = 0; i < obstacles.size(); i++)
    { 
        if (obstacles[i].checkIntersection(parToChild))
        {
            return true;
        }
    }
    return false;
}

Point RRT::samplePoint()
{
    Point sample(rand() % 1200, rand() % 800);
    return sample;
}

void RRT::reDrawTree(RRTNode* node, sf::RenderWindow &window)
{
    if (node != NULL)
    {
        for (int i = 0; i < node->children.size(); i++)
        {
            Line branch(node, node->children[i]);
            branch.draw(window, sf::Color::Magenta);
            reDrawTree(node->children[i], window);
        }
    }    
}

void RRT::buildEnvironment(sf::RenderWindow &window)
{
    // Display start and end points
    start.draw(5, window, sf::Color::Green);
    end.draw(5, window, sf::Color::Red);

    // Create obstacles
    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles[i].draw(window);
    }
}


bool RRT::runIteration(sf::RenderWindow &window)
{
    Point newPoint = samplePoint();
    RRTNode* newNode = addNode(newPoint, window);

    if (newNode == NULL)
    {
        return false;
    }
    iterations++;

    // Redraw tree for text display purposes (wouldn't do this in true RRT)
    window.clear(sf::Color::White);
    reDrawTree(root, window);
    buildEnvironment(window);

    Line newLine(newPoint, end);
    if (newLine.getLength() < goalRadius)
    {
        RRTNode* finalNode = addNode(end, window);
        lastNode = finalNode;
        traceBack(finalNode, window);
        cout << "Number of Iterations: " << iterations << endl;
        cout << "Distance to Come: " << lastNode->distToCome << endl;
        return true;
    }
    return false;
}
