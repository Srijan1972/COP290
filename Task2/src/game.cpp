#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
class Game
{
private:
    bool gameOn;
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    Game();
    ~Game();
    void init(const char* title,int xpos,int ypos,int width,int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool on(){return gameOn;}
};

Game::Game(){}

Game::~Game(){}

void Game::init(const char* title,int xpos,int ypos,int width,int height){
    window=SDL_CreateWindow(title,xpos,ypos,width,height,0);
    if(window==NULL){
        std::cerr<<"Error in creating window: "<<SDL_GetError()<<std::endl;
        exit(1);
    }
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer==NULL){
        std::cerr<<"Error in creating renderer: "<<SDL_GetError()<<std::endl;
        exit(1);
    }
    gameOn=true;
}

void Game::handleEvents(){
    SDL_FlushEvent(SDL_MOUSEMOTION);
    SDL_Event e;
    SDL_PollEvent(&e);
    switch (e.type)
    {
    case SDL_QUIT:
        gameOn=false;
        break;
    default:
        break;
    }
}

void Game::update(){}

void Game::render(){}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}