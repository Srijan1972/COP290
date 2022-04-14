#include "map.cpp"

class Interface
{
private:
    SDL_window* window;
    SDL_renderer* renderer;
    Map* game_map;
public:
    Interface(SDL_Window* w,SDL_Renderer* r);
    ~Interface();
};

Interface::Interface(SDL_Window* w,SDL_Renderer* r){
    window=w;
    renderer=r;
}

Interface::~Interface(){}
