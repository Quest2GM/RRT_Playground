#include <RRTStar.hpp>

class AnytimeRRT : public RRTStar
{
public:
    AnytimeRRT(Point start, Point end, vector<Rectangle> obstacles) : RRTStar(start, end, obstacles) {};
    bool runIteration(sf::RenderWindow &window) override;
};