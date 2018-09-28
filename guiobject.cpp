#include "guiobject.hpp"

GUIObject::GUIObject()
{
    m_Lua = NULL;
}

GUIObject::~GUIObject()
{

}

GUIObject *GUIObject::loadFromScript(std::string tfile)
{
    GUIObject *newobject = NULL;

    sol::state lua;

    lua.open_libraries(sol::lib::base);
    lua.script_file(tfile);

    if(lua["gui_rectangle"].valid())  newobject = new GUIRectangle(tfile);

    newobject;
}

// ------------------------------------------------------
//
GUIRectangle::GUIRectangle()
{

}

GUIRectangle::GUIRectangle(std::string luafile)
{
    m_Lua.open_libraries(sol::lib::base);
    m_Lua.script_file(luafile);

    if(m_Lua["gui_rectangle"].valid())
    {
        auto rect = m_Lua["gui_rectangle"];

        if( rect["width"]) m_Dimensions.x = rect["width"];
        if( rect["height"]) m_Dimensions.y = rect["height"];

        if( rect["color"])
        {
            auto tcolor = rect["color"];

            if(tcolor)
            {
                m_FillColor = sf::Color( tcolor[1], tcolor[2], tcolor[3] );
            }
        }

    }

    m_Rectangle = sf::RectangleShape(m_Dimensions);
    m_Rectangle.setFillColor(m_FillColor);

    std::cout << "GUIRectangle constructed\n";
}

GUIRectangle::~GUIRectangle()
{

}

void GUIRectangle::draw(sf::RenderWindow *tscreen)
{
    if(tscreen) tscreen->draw(m_Rectangle);
}
