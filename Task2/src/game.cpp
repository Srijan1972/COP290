#include "character.cpp"
#include "server.cpp"
#include "client.cpp"
#include "interface.cpp"

std::vector<int> dataDecode(std::string s){
    std::vector<int> v;
    std::stringstream ss(s);
    std::string pos;
    while(ss>>pos) v.push_back(std::stoi(pos));
    return v;
}
// std::pair<int,int> dataDecode(std::string s){
//     std::pair<int,int> p;
//     std::stringstream ss(s);
//     std::string pos;
//     ss>>pos;
//     p.first=std::stoi(pos);
//     ss>>pos;
//     p.second=std::stoi(pos);
//     return p;
// }
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
    Map* pMap3;
    Character* life;
    Server* S;
    Client* C;
    std::pair<int,int> loc1;
    std::pair<int,int> loc2;
    int atck12;
    int atck21;
    // Interface* interface;
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
        // interface=new Interface(window,renderer);
        gameOn=true;
    }

    void loadMedia(Tile* tileSet[]){
        tileMap=new Map();
        tileMap->load("./assets/images/tileMap.png",renderer);
        pMap1 = new Map();
        pMap1->load("./assets/images/ch2.png",renderer);
        pMap2 = new Map();
        pMap2->load("./assets/images/ch1.bmp",renderer);
        pMap3 = new Map();
        pMap3->load("./assets/images/heart.png",renderer);
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
    void update(Tile* tileSet[],int i,bool lifeflag){
        if(lifeflag){
            life= new Character(540,880);
        }else{
            life= new Character(1540,880);
        }
        if(i == 0){
            if(player1->attack(player2)){
                atck12 = 1;
            }else{
                atck12 = 0;
            }
            player1->heal(life);
            player1->move(tileSet);
            player1->adjustCamera(camera1);
            loc1 = player1->giveloc();
        }else if(i == 1){
            if (player2->attack(player1)){
                atck21 = 1;
            }else{
                atck21 = 0;
            }
            player2->heal(life);
            player2->move(tileSet);
            player2->adjustCamera(camera1);
            loc2 = player2->giveloc();
        }
    }

    void datasend(int i){
        if(i == 0){
            player2->update(dataDecode(S->get()),player1);
            S->send(std::to_string(loc1.first) + " " + std::to_string(loc1.second) + " " + std::to_string(player1->health) + " " + std::to_string(atck12));

        }else if(i == 1){
            C->send(std::to_string(loc2.first) + " " + std::to_string(loc2.second) + " " + std::to_string(player2->health) + " " + std::to_string(atck21));
            player1->update(dataDecode(C->get()),player2);
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
        life->render(camera1,pMap3,renderer);
        SDL_RenderPresent(renderer);
        // std::cout<<player1->health<<" "<<player2->health<<"\n";
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
        pMap3->free();
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