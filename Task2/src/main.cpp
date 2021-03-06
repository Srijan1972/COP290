#include "game.cpp"
#include <chrono>
Game* game;
const int FPS=144; // Refresh rate of most screens
const int delay=1000/FPS;

int main(int argc,char* argv[]){
    // int i = std::stoi(argv[1]);
    bool flag = false;
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        std::cerr<<"Failed to initialize: "<<SDL_GetError()<<std::endl;
        return 1;
    }
    if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY,"1")){
        std::cout<<"Warning: Linear texture filtering not enabled"<<std::endl;
    }
    if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)!=0){
        std::cerr<<"Failed to initialize sound: "<<Mix_GetError()<<std::endl;
        return 1;
    }
    if(TTF_Init()!=0){
        std::cerr<<"Failed to initialize font: "<<TTF_GetError()<<std::endl;
        return 1;
    }
    game=new Game();
    game->init("IIT Delhi Duel",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT);
    Tile* tileSet[TOTAL_TILES];
    game->loadMedia(tileSet);
    game->loadplayers();
    Uint32 start;
    int frame_length;
    int frames=0;
    while(game->on()){
        if(frames == 600){
            frames = 0;
            flag = false;
        }else if(frames == 300){
            flag = true;
        }
        start=SDL_GetTicks();
        game->handleEvents();
        game->update(tileSet,flag);
        game->datasend();
        game->render(tileSet);
        frame_length=SDL_GetTicks()-start;
        SDL_Delay(std::max(delay-frame_length,0)); // Synchronize device refresh rate and game UI change rate
        frames++;
    }
    game->clean(tileSet);
    return 0;
}