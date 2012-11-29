#include "event.hpp"

keyboardHandler::keyboardHandler()
{
    
}

keyboardHandler::~keyboardHandler()
{

}

void keyboardHandler::addAction(SDLKey key, std::function <void()> fun)
{
    functionMap[key] = fun;
}

void keyboardHandler::process(SDLKey key)
{
    if (functionMap.count(key)) {
	std::function <void ()> f = functionMap[key];
	f();
    }
}

