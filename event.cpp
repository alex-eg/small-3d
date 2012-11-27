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
    definedKeys.insert(key);
}

void keyboardHandler::process(SDLKey key)
{
    if (definedKeys.find(key) != definedKeys.end()) {
	std::function <void ()> f = functionMap[key];
	f();
    }
}

