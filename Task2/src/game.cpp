#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include "map.cpp"
class Game
{
private:
    SDL_Rect camera={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    bool gameOn;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Map* tileMap;
public:
    Game(){};
    ~Game(){};
    void init(const char* title,int xpos,int ypos,int width,int height){
    window=SDL_CreateWindow(title,xpos,ypos,width,height,SDL_WINDOW_SHOWN);
        if(window==NULL){
            std::cerr<<"Error in creating window: "<<SDL_GetError()<<std::endl;
            exit(1);
        }
        renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer==NULL){
            std::cerr<<"Error in creating renderer: "<<SDL_GetError()<<std::endl;
            exit(1);
        }
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        int imgFlags=IMG_INIT_PNG;
		if(!(IMG_Init(imgFlags) & imgFlags)){
            std::cerr<<"Error in initializing image: "<<IMG_GetError()<<std::endl;
            exit(1);
    	}
        gameOn=true;
    }

    void loadMedia(Tile* tileSet[]){
        tileMap=new Map();
        tileMap->load("./src/final3.png",renderer);
        setTiles(tileSet);
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(renderer);
        for(int i=0;i<TOTAL_TILES;i++){
            tileSet[i]->render(camera,tileMap,renderer);
        }
        SDL_RenderPresent(renderer);
    }

    void handleEvents(){
        SDL_FlushEvent(SDL_MOUSEMOTION);
        SDL_Event e;
        while(SDL_PollEvent(&e)!=0){
            switch (e.type){
                case SDL_QUIT:
                    gameOn=false;
                    break;
                default:
                    break;
            }
        }
    }
    void update(SDL_Rect& camera,Tile* tileSet[]){
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(renderer);
        for(int i=0;i<TOTAL_TILES;i++){
            tileSet[i]->render(camera,tileMap,renderer);
        }
        SDL_RenderPresent(renderer);
    }
    void render(){}
    void clean(Tile* tileSet[]){
        for(int i=0;i<TOTAL_TILES;i++){
            if(tileSet[i]!=NULL){
                delete tileSet[i];
                tileSet[i]=NULL;
            }
        }
        tileMap->free();
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }
    bool on(){return gameOn;}
};