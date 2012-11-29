#ifndef EVENT
#define EVENT

#include <functional>
#include <SDL/SDL.h>
#include <map>

class keyboardHandler {
private:
    std::map <SDLKey, std::function <void()> > functionMap;
public:
    keyboardHandler();
    ~keyboardHandler();
    void addAction(SDLKey key, std::function <void()> fun);
    void process(SDLKey key);
};

#endif // ifndef EVENT
