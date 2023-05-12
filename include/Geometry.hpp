#pragma once

#include <vector>
#include <eigen3/Eigen/Dense>
#include <SFML/Graphics.hpp>

using namespace std;

class RRTNode
{
public:
    RRTNode* parent = NULL;
    vector<RRTNode*> children;
    int xPos, yPos;
    int nodeId = 0;
    float distToCome = 0;

    RRTNode(int x, int y)
    {
        xPos = x;
        yPos = y;
    }
};

class Point
{
public:
    int x, y;

    Point() {}
    Point(RRTNode* node)
    {
        x = node->xPos;
        y = node->yPos;
    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void draw(int radius, sf::RenderWindow &window, sf::Color colour)
    {
        sf::CircleShape circle(radius);
        circle.setPosition(sf::Vector2f(x - radius, y - radius));
        circle.setFillColor(colour);
        window.draw(circle);
    }
};


class Line
{
public:
    Point a;
    Point b;

    Line(Point a, Point b)
    {
        this->a = a;
        this->b = b;
    }

    Line(RRTNode* node1, RRTNode* node2)
    {
        this->a.x = node1->xPos;
        this->a.y = node1->yPos;
        this->b.x = node2->xPos;
        this->b.y = node2->yPos;
    }

    Line(RRTNode* node, Point p)
    {
        this->a.x = node->xPos;
        this->a.y = node->yPos;
        this->b.x = p.x;
        this->b.y = p.y;
    }

    float getLength()
    {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    }

    void draw(sf::RenderWindow &window, sf::Color colour)
    {
        sf::Vertex branch[] =
        {
            sf::Vertex(sf::Vector2f(a.x, a.y), colour),
            sf::Vertex(sf::Vector2f(b.x, b.y), colour)
        };
        window.draw(branch, 2, sf::Lines);
    }

    void drawThick(sf::RenderWindow &window, sf::Color colour)
    {
        sf::RectangleShape rectangle(sf::Vector2f(getLength(), 5));
        rectangle.setFillColor(colour);
        rectangle.setPosition(sf::Vector2f(a.x, a.y));
        float angle = atan2(b.y - a.y, b.x - a.x) * 180 / M_PI;
        rectangle.setRotation(angle);
        window.draw(rectangle);
    }

};


class Rectangle
{
public:
    int x, y, w, h;

    Rectangle(int x, int y, int w, int h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    void draw(sf::RenderWindow &window)
    {
        sf::RectangleShape rectangle(sf::Vector2f(w, h));
        rectangle.setFillColor(sf::Color(40,40,40));
        rectangle.setPosition(sf::Vector2f(x, y));
        window.draw(rectangle);
    }

    bool checkIntersection(Line l)
    {

        // Determine line intersection with all four sides of rectangle
        bool I1 = checkLineIntersec(x, x + w, y, y, l);
        bool I2 = checkLineIntersec(x, x, y, y + h, l);
        bool I3 = checkLineIntersec(x + w, x + w, y, y + h, l);
        bool I4 = checkLineIntersec(x, x + w, y + h, y + h, l);

        if (I1 || I2 || I3 || I4)
        {
            return true;
        }
        return false;
    }

    bool checkLineIntersec(int x1, int x2, int y1, int y2, Line l)
    {
        Eigen::Vector3d P(x1, y1, 0);
        Eigen::Vector3d R(x2 - x1, y2 - y1, 0);
        Eigen::Vector3d Q(l.a.x, l.a.y, 0);
        Eigen::Vector3d S(l.b.x - l.a.x, l.b.y - l.a.y, 0);

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

        return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
    }

};
