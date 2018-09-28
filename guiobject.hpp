#ifndef CLASS_GUIOBJECT
#define CLASS_GUIOBJECT

#include <cstdlib>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <sol.hpp>

class GUIObject
{
protected:

    std::string m_Name;

    sol::state m_Lua;

public:
    GUIObject();
    ~GUIObject();

    virtual void draw(sf::RenderWindow *tscreen)=0;
    virtual void update() {};

    static GUIObject *loadFromScript(std::string tfile);

    virtual void show()
    {
        std::cout << "---------\n";
        std::cout << "GUIObject\n";
        std::cout << "---------\n";
        std::cout << "name:" << m_Name << std::endl;
    }
};

class GUIRectangle: public GUIObject
{
private:

    sf::RectangleShape m_Rectangle;
    sf::Vector2f m_Dimensions;
    sf::Color m_FillColor;

public:
    GUIRectangle();
    GUIRectangle(std::string luafile);
    ~GUIRectangle();

    void draw(sf::RenderWindow *tscreen);

    void show()
    {
        GUIObject::show();
        std::cout << "dimensions:" << m_Dimensions.x << "," << m_Dimensions.y << std::endl;
        std::cout << "color:" << int(m_FillColor.r) << "," << int(m_FillColor.g) << "," << int(m_FillColor.b) << std::endl;
    }
};
#endif // CLASS_GUIOBJECT
