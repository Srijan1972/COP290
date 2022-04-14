#include<bits/stdc++.h>
#include "game.cpp"

Game* game;
const int FPS=60; // Refresh rate of most screens
const int delay=1000/FPS;

int main(int argc,char* argv[]){
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        std::cerr<<"Failed to initialize: "<<SDL_GetError()<<std::endl;
        return 1;
    }
    game = new Game();
    game->init("IITD Duel",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,720);
    Uint32 start;
    int frame_length;
    while(game->on()){
        start=SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        frame_length=SDL_GetTicks()-start;
        SDL_Delay(std::max(delay-frame_length,0)); // Synchronize device refresh rate and game UI change rate
    }
    game->clean();
    return 0;
}