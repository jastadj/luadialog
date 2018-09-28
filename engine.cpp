#include "engine.hpp"

#include <iostream>
#include <string>

#include "guiobject.hpp"

Engine::Engine()
{
    m_Screen = NULL;

    m_BGColor = sf::Color::Transparent;
}

Engine::~Engine()
{

}

int Engine::start()
{
    sol::state lua;
    lua.open_libraries();

    lua.script_file( "variables.lua");
    sol::table resolution = lua["config"]["resolution"];
    std::string windowtitle = "DefaultTitle";
    if( lua["config"]["title"].valid()) windowtitle = lua["config"]["title"];

    if(!resolution.valid())
    {
        std::cout << "No resolution table found in variables.lua!\n";
        exit(1);
    }

    m_Screen = new sf::RenderWindow(sf::VideoMode(resolution.get<int>("x"),resolution.get<int>("y"),32), windowtitle);

    // start main loop
    mainLoop();

    return 0;
}

int Engine::mainLoop()
{
    bool quit = false;

    // lua init
    sol::state lua;
    //lua.open_libraries( sol::lib::base, sol::lib::string); // only open specific libraries
    lua.open_libraries(); // open all libraries


  	// call lua code, and check to make sure it has loaded and run properly:
  	auto handler = &sol::script_default_on_error;
  	lua.script("print('testing handler')", handler);


  	// Use a custom error handler if you need it
  	// This gets called when the result is bad
  	auto simple_handler = [](lua_State*, sol::protected_function_result result) {
  		// You can just pass it through to let the call-site handle it
  		return result;
  	};



    auto result = lua.script("prinft('this is a test')\n", simple_handler); // send a command to lua
    if(!result.valid()) { std::cout << "result is not valid\n";}

    lua.set_function("setBGColor", &Engine::setBGColor, this);
    lua.script_file("background.lua");

    GUIObject *mysquare = GUIObject::loadFromScript("mysquare.lua");

    if(mysquare)
    {
        mysquare->show();
        m_GUIObjects.push_back(mysquare);
    }


    while(!quit)
    {
        sf::Event event;

        m_Screen->clear(m_BGColor);

        while(m_Screen->pollEvent(event))
        {
            if(event.type == sf::Event::Closed) quit = true;
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape) quit = true;
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                std::cout << "test";
                lua["handle_input"](1);
            }
        }

        // update

        for(int i = 0; i < int(m_GUIObjects.size()); i++) m_GUIObjects[i]->update();

        // draw
        for(int i = 0; i < int(m_GUIObjects.size()); i++) m_GUIObjects[i]->draw(m_Screen);

        // display
        m_Screen->display();
    }

    return 0;
}

void Engine::setBGColor(int r, int g, int b)
{
    std::cout << "Setting BG color\n";
    m_BGColor = sf::Color(uint8_t(r), uint8_t(g), uint8_t(b) );
}
