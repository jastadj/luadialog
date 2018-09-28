#ifndef CLASS_ENGINE
#define CLASS_ENGINE

#include <cstdlib>
#include <sol.hpp>
#include <SFML\Graphics.hpp>
#include "assert.hpp"

// forward
class GUIObject;
class GUIRectangle;

class Engine
{
private:

    sf::RenderWindow *m_Screen;

    int mainLoop();

    sf::Color m_BGColor;

    void setBGColor(int r, int g, int b);

    std::vector<GUIObject*> m_GUIObjects;

public:
    Engine();
    ~Engine();

    int start();
};
#endif // CLASS_ENGINE
