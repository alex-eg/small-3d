#ifndef EVENT
#define EVENT

#include <functional>
#include <SDL/SDL.h>
#include <map>
#include <set>

class keyboardHandler {
private:
    std::map <SDLKey, std::function <void()> > functionMap;
    std::set <SDLKey> definedKeys;
public:
    keyboardHandler();
    ~keyboardHandler();
    void addAction(SDLKey key, std::function <void()> fun);
    void process(SDLKey key);
};

#endif // ifndef EVENT
