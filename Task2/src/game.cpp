#include "character.cpp"
class Game
{
private:
    SDL_Rect camera1={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    bool gameOn;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Map* tileMap;
    Map* pMap;
    Character* player;
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
        tileMap->load("./assets/images/tileMap.png",renderer);
        pMap = new Map();
        pMap->load("./assets/images/ch1.bmp",renderer);
        setTiles(tileSet);
        player=new Character();
        // player->move(tileSet);
        // player->adjustCamera(camera1);
        // SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        // SDL_RenderClear(renderer);
        // for(int i=0;i<TOTAL_TILES;i++){
        //     tileSet[i]->render(camera1,tileMap,renderer);
        // }
        // player->render(camera1,pMap,renderer);
        // SDL_RenderPresent(renderer);
    }

    void handleEvents(){
        SDL_Event e;
        SDL_PollEvent(&e);
        switch (e.type){
            case SDL_QUIT:
                gameOn=false;
                break;
            default:
                break;
        }
        player->handleEvent(e);
    }
    void update(Tile* tileSet[]){
        player->move(tileSet);
        player->adjustCamera(camera1);
    }
    void render(Tile* tileSet[]){
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(renderer);
        for(int i=0;i<TOTAL_TILES;i++){
            tileSet[i]->render(camera1,tileMap,renderer);
        }
        player->render(camera1,pMap,renderer);
        SDL_RenderPresent(renderer);
    }

    void clean(Tile* tileSet[]){
        for(int i=0;i<TOTAL_TILES;i++){
            if(tileSet[i]!=NULL){
                delete tileSet[i];
                tileSet[i]=NULL;
            }
        }
        tileMap->free();
        pMap->free();
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }

    bool on(){return gameOn;}
};