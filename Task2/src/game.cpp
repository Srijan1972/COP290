#include "character.cpp"
#include "server.cpp"
#include "client.cpp"
std::pair<int,int> dataDecode(std::string s){
    std::pair<int,int> p;
    std::stringstream ss(s);
    std::string pos;
    ss>>pos;
    p.first=std::stoi(pos);
    ss>>pos;
    p.second=std::stoi(pos);
    return p;
}
class Game
{
private:
    SDL_Rect camera1={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    bool gameOn;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music* bgmusic;
    Map* tileMap;
    Map* pMap1;
    Character* player1;
    Map* pMap2;
    Character* player2;
    Server* S;
    Client* C;
    std::pair<int,int> loc1;
    std::pair<int,int> loc2;
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
        pMap1 = new Map();
        pMap1->load("./assets/images/ch2.png",renderer);
        pMap2 = new Map();
        pMap2->load("./assets/images/ch1.bmp",renderer);
        setTiles(tileSet);
        bgmusic=Mix_LoadMUS("./assets/sounds/Duel_of_the_Fates.mp3");
        Mix_PlayMusic(bgmusic,-1);
    }

    void loadplayers(int i){
        player1= new Character(240,0);
        player2= new Character(240,1120);
        if (i == 0){
            S = new Server("127.0.0.1");
        }
        if (i == 1){
            C = new Client("127.0.0.1");
        }
    }

    void handleEvents(int i){
        SDL_Event e;
        SDL_PollEvent(&e);
        switch (e.type){
            case SDL_QUIT:
                gameOn=false;
                break;
            default:
                break;
        }
        if(i == 0) player1->handleEvent(e);
        if(i == 1) player2->handleEvent(e);
    }
    void update(Tile* tileSet[],int i){
        if(i == 0){
            player1->move(tileSet);
            player1->adjustCamera(camera1);
            player2->moveop(dataDecode(S->get()));
            loc1 = player1->giveloc();
            S->send(std::to_string(loc1.first) + " " + std::to_string(loc1.second));

        }else if(i == 1){
            player2->move(tileSet);
            player2->adjustCamera(camera1);
            loc2 = player2->giveloc();
            C->send(std::to_string(loc2.first) + " " + std::to_string(loc2.second));
            player1->moveop(dataDecode(C->get()));

        }
    }
            
    void render(Tile* tileSet[],int i){
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(renderer);
        for(int i=0;i<TOTAL_TILES;i++){
            tileSet[i]->render(camera1,tileMap,renderer);
        }
        player1->render(camera1,pMap1,renderer);
        player2->render(camera1,pMap2,renderer);
        SDL_RenderPresent(renderer);
    }

    void clean(Tile* tileSet[],int i){
        for(int i=0;i<TOTAL_TILES;i++){
            if(tileSet[i]!=NULL){
                delete tileSet[i];
                tileSet[i]=NULL;
            }
        }
        tileMap->free();
        pMap1->free();
        pMap2->free();
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        Mix_FreeMusic(bgmusic);
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        if(i == 0){ S->end();}
        if(i == 1){ C->end();}
    }

    bool on(){return gameOn;}
};