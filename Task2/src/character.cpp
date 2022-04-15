#include "map.cpp"

class Character{
private:
    SDL_Rect char_box;
    int vx,vy;
public:
    const int PL_WIDTH=48;
    const int PL_HEIGHT=48;
    const int maxv=8;
    Character(){
        char_box.x=240;
        char_box.y=0;
        char_box.w=PL_WIDTH;
        char_box.h=PL_HEIGHT;
        vx=vy=0;
    }
    ~Character(){}
    void handleEvent(SDL_Event &e){
        if((e.type==SDL_KEYUP || e.type==SDL_KEYDOWN) && e.key.repeat==0){
            switch (e.key.keysym.sym){
                case SDLK_UP: vy=std::max(-1*maxv,vy-maxv); break;
                case SDLK_DOWN: vy=std::max(maxv,vy+maxv); break;
                case SDLK_LEFT: vx=std::min(maxv,vx+maxv); break;
                case SDLK_RIGHT: vx=std::max(-1*maxv,vx-maxv); break;
            }
        }
    }

    void move(Tile* tileSet[]){
        char_box.x+=vx;
        if(char_box.x<0 || char_box.x+PL_WIDTH>LEVEL_WIDTH || touchesWall(tileSet)){
            char_box.x-=vx;
        }
        char_box.y+=vy;
        if(char_box.y<0 || char_box.y+PL_HEIGHT>LEVEL_HEIGHT || touchesWall(tileSet)){
            char_box.y-=vy;
        }
    }

    void adjustCamera(SDL_Rect &camera){
        camera.x=char_box.x+PL_WIDTH/2-LEVEL_WIDTH/2;
        camera.y=char_box.y+PL_HEIGHT/2-LEVEL_HEIGHT/2;
        if(camera.x<0) camera.x=0;
        if(camera.y<0) camera.y=0;
        if(camera.x>LEVEL_WIDTH) camera.x=LEVEL_WIDTH;
        if(camera.y>LEVEL_HEIGHT) camera.y=LEVEL_HEIGHT;
    }

    void render(SDL_Rect &camera,Map* playerMap,SDL_Renderer* renderer){
        playerMap->render(char_box.x-camera.x,char_box.y-char_box.y,NULL,renderer);
    }

    bool touchesWall(Tile* tiles[]){
    //Go through the tiles
        for(int i=0;i<TOTAL_TILES;++i){
            //If the tile is a wall type tile
            if((tiles[i]->getType()>TILE_Floor) && (tiles[i]->getType()!=TILE_SACc)){
                //If the collision box touches the wall tile
                if(checkCollision(char_box,tiles[i]->getTile())) return true;
            }
        }
        //If no wall tiles were touched
        return false;
    }
};