#include "map.cpp"

class Character{
private:
    SDL_Rect char_box;
    int vx,vy;
    bool attacking;
    bool healing;
public:
    int health=1000;
    const int PL_WIDTH=48;
    const int PL_HEIGHT=48;
    const int maxv=10;
    Character(int posx,int posy){
        char_box.x=posx;
        char_box.y=posy;
        char_box.w=PL_WIDTH;
        char_box.h=PL_HEIGHT;
        vx=vy=0;
    }
    ~Character(){}
    void handleEvent(SDL_Event &e){
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
            //Adjust the velocity
            switch( e.key.keysym.sym )
            {
                case SDLK_UP: vy -= maxv; break;
                case SDLK_DOWN: vy += maxv; break;
                case SDLK_LEFT: vx -= maxv; break;
                case SDLK_RIGHT: vx += maxv; break;
                case SDLK_SPACE: attacking=true; break;
                case SDLK_h: healing=true;break;
            }
        }
        //If a key was released
        else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
        {
            //Adjust the velocity
            switch( e.key.keysym.sym )
            {
                case SDLK_UP: vy += maxv; break;
                case SDLK_DOWN: vy -= maxv; break;
                case SDLK_LEFT: vx += maxv; break;
                case SDLK_RIGHT: vx -= maxv; break;
                case SDLK_SPACE: attacking=true; break;
                case SDLK_h: healing=true;break;
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

    std::pair<int,int> giveloc(){
        std::pair<int,int> p;
        p.first = char_box.x;
        p.second = char_box.y;
        return p;
    }

    SDL_Rect getBox(){return char_box;}

    bool attack(Character* other){
        bool b;
        if(attacking && checkCollision(char_box,other->getBox())) b = attacking;
        attacking=false;
        return b;
    }

    void heal(Character* other){
        if(healing && checkCollision(char_box,other->getBox())) health+=25;
        healing=false;
    }

    void update(std::vector<int> data,Character* other){
        char_box.x=data[0];
        char_box.y=data[1];
        health=data[2];
        if (data[3] == 1){
            other->health-=50;
        }

    }

    void adjustCamera(SDL_Rect& camera){
        camera.x=(char_box.x+PL_WIDTH/2)-SCREEN_WIDTH/2;
        camera.y=(char_box.y+PL_HEIGHT/2)-SCREEN_HEIGHT/2;
        if(camera.x<0) camera.x=0;
        if(camera.y<0) camera.y=0;
        if(camera.x>LEVEL_WIDTH-camera.w) camera.x=LEVEL_WIDTH-camera.w;
        if(camera.y>LEVEL_HEIGHT-camera.h) camera.y=LEVEL_HEIGHT-camera.h;
    }

    void render(SDL_Rect &camera,Map* playerMap,SDL_Renderer* renderer){
        playerMap->render(char_box.x-camera.x,char_box.y-camera.y,NULL,renderer);
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