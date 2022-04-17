#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<bits/stdc++.h>

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) return false;
    //If none of the sides from A are outside B
    return true;
}

//Screen dimension constants
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;

//The dimensions of the level
const int LEVEL_WIDTH = 2400;
const int LEVEL_HEIGHT = 1440;

//Tile constants
const int TILE_WIDTH = 160;
const int TILE_HEIGHT = 160;
const int TOTAL_TILES = 135;
const int TOTAL_TILE_SPRITES = 40;

//The different tile sprites
const int TILE_Floor = 0;
const int TILE_Grass = 1;
const int TILE_Road = 2;
const int TILE_Zanskar = 3;
const int TILE_Rajdhani = 4;
const int TILE_Kumaon = 5;
const int TILE_Dukan = 6;
const int TILE_Lib = 7;
const int TILE_CSC = 8;
const int TILE_Ara = 9;
const int TILE_Jwala = 10;
const int TILE_Vindy = 11;
const int TILE_LHC1 = 12;
const int TILE_LHC2 = 13;
const int TILE_LHC3 = 14;
const int TILE_LHC4 = 15;
const int TILE_Hima = 16;
const int TILE_Kai = 17;
const int TILE_Nil = 18;
const int TILE_Kara = 19;
const int TILE_Gir = 20;
const int TILE_Hockey = 21;
const int TILE_Cricket = 22;
const int TILE_Foot1 = 23;
const int TILE_Foot2 = 24;
const int TILE_Foot3 = 25;
const int TILE_Foot4 = 26;
const int TILE_Sat = 27;
const int TILE_Shiva = 28;
const int TILE_Udai = 29;
const int TILE_SAC = 30;
const int TILE_SACc = 31;
const int TILE_POOL1 = 32;
const int TILE_POOL2 = 33;
const int TILE_POOL3 = 34;
const int TILE_POOL4 = 35;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

class Map
{
private:
    SDL_Texture* map_text;
    int mapw;
    int maph;
public:
    Map(){
        map_text=nullptr;
        mapw=0;
        maph=0;
    }

    void load(std::string path,SDL_Renderer* renderer){
        free();
        SDL_Texture* new_text=nullptr;
        SDL_Surface* loaded=IMG_Load(path.c_str());
        if(loaded==nullptr){
            std::cerr<<"Could not load image: "<<path<<' '<<SDL_GetError()<<std::endl;
            exit(1);
        }
    	SDL_SetColorKey(loaded,SDL_TRUE,SDL_MapRGB(loaded->format,0,0xFF,0xFF));
        new_text=SDL_CreateTextureFromSurface(renderer,loaded);
        if(new_text==nullptr){
            std::cerr<<"Could not make texture: "<<path<<' '<<SDL_GetError()<<std::endl;
            exit(1);
        }
        mapw=loaded->w;
        maph=loaded->h;
        SDL_FreeSurface(loaded);
        map_text=new_text;
    }

    void free(){
        if(map_text!=nullptr){
            SDL_DestroyTexture(map_text);
            map_text=nullptr;
            mapw=0;
            maph=0;
        }
    }

    void render( int x, int y, SDL_Rect* clip, SDL_Renderer* renderer){
	    SDL_Rect renderQuad = {x, y, mapw, maph};
	    //Set clip rendering dimensions
	    if( clip != NULL )
	    {
		    renderQuad.w = clip->w;
		    renderQuad.h = clip->h;
	    }
	    SDL_RenderCopyEx(renderer, map_text, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
    }

    int getWidth(){return mapw;}
    int getHeight(){return maph;}
    ~Map(){free();};
};
class Tile{
private:
    int tile_type;
    SDL_Rect tile_rect;
public:
    Tile(int x,int y,int tileType){
        tile_rect.x=x;
        tile_rect.y=y;
        tile_rect.w=TILE_WIDTH;
        tile_rect.h=TILE_HEIGHT;
        tile_type=tileType;
    }

    ~Tile(){}

    void render(SDL_Rect& camera,Map* tileMap,SDL_Renderer* renderer){
        if(checkCollision(camera,tile_rect)){
			tileMap->render(tile_rect.x-camera.x,tile_rect.y-camera.y,&gTileClips[tile_type],renderer);
		}
    }
    int getType(){return tile_type;}
    SDL_Rect getTile(){return tile_rect;}
};

void setTiles(Tile* tiles[]){
    int x=0,y=0;
    std::ifstream map("./assets/lazy1.map");
    if(map.fail()){
        std::cerr<<"Unable to load map"<<std::endl;
        exit(1);
    }
	//Initialize the tiles
	for( int i = 0; i < TOTAL_TILES; ++i){
		//Determines what kind of tile will be made
		int tileType = -1;
		//Read tile from map file
		map >> tileType;
		if(map.fail()){
			//Stop loading map
			std::cerr<<"Unexpected end of file"<<std::endl;
            exit(1);
		}
		if((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)){
				tiles[i] = new Tile(x,y,tileType);
		}
			//If we don't recognize the tile type
		else{
			std::cerr<<"Invalid tile type at: "<<i<<std::endl;
			exit(1);
    	}

		//Move to next tile spot
		x += TILE_WIDTH;
			//If we've gone too far
		if( x >= LEVEL_WIDTH ){
			//Move back
			x = 0;
			//Move to the next row
			y += TILE_HEIGHT;
		}
	}

	gTileClips[ TILE_Grass ].x = 960;
	gTileClips[ TILE_Grass ].y = 0;
	gTileClips[ TILE_Grass ].w = TILE_WIDTH;
	gTileClips[ TILE_Grass ].h = TILE_HEIGHT;
	gTileClips[ TILE_Floor ].x = 1120;
	gTileClips[ TILE_Floor ].y = 0;
	gTileClips[ TILE_Floor ].w = TILE_WIDTH;
	gTileClips[ TILE_Floor ].h = TILE_HEIGHT;
	gTileClips[ TILE_Zanskar ].x = 960;
	gTileClips[ TILE_Zanskar ].y = 320;
	gTileClips[ TILE_Zanskar ].w = TILE_WIDTH;
	gTileClips[ TILE_Zanskar ].h = TILE_HEIGHT;
	gTileClips[ TILE_Rajdhani ].x = 1120;
	gTileClips[ TILE_Rajdhani ].y = 160;
	gTileClips[ TILE_Rajdhani ].w = TILE_WIDTH;
	gTileClips[ TILE_Rajdhani ].h = TILE_HEIGHT;
	gTileClips[ TILE_Dukan ].x = 480;
	gTileClips[ TILE_Dukan ].y = 320;
	gTileClips[ TILE_Dukan ].w = TILE_WIDTH;
	gTileClips[ TILE_Dukan ].h = TILE_HEIGHT;
	gTileClips[ TILE_Lib ].x = 960;
	gTileClips[ TILE_Lib ].y = 160;
	gTileClips[ TILE_Lib ].w = TILE_WIDTH;
	gTileClips[ TILE_Lib ].h = TILE_HEIGHT;
	gTileClips[ TILE_Kumaon ].x = 320;
	gTileClips[ TILE_Kumaon ].y = 160;
	gTileClips[ TILE_Kumaon ].w = TILE_WIDTH;
	gTileClips[ TILE_Kumaon ].h = TILE_HEIGHT;
	gTileClips[ TILE_CSC ].x = 320;
	gTileClips[ TILE_CSC ].y = 320;
	gTileClips[ TILE_CSC ].w = TILE_WIDTH;
	gTileClips[ TILE_CSC ].h = TILE_HEIGHT;
	gTileClips[ TILE_Ara ].x = 0;
	gTileClips[ TILE_Ara ].y = 160;
	gTileClips[ TILE_Ara ].w = TILE_WIDTH;
	gTileClips[ TILE_Ara ].h = TILE_HEIGHT;
	gTileClips[ TILE_Jwala ].x = 160;
	gTileClips[ TILE_Jwala ].y = 160;
	gTileClips[ TILE_Jwala ].w = TILE_WIDTH;
	gTileClips[ TILE_Jwala ].h = TILE_HEIGHT;
	gTileClips[ TILE_Vindy ].x = 160;
	gTileClips[ TILE_Vindy ].y = 480;
	gTileClips[ TILE_Vindy ].w = TILE_WIDTH;
	gTileClips[ TILE_Vindy ].h = TILE_HEIGHT;
	gTileClips[ TILE_LHC1 ].x = 640;
	gTileClips[ TILE_LHC1 ].y = 320;
	gTileClips[ TILE_LHC1 ].w = TILE_WIDTH;
	gTileClips[ TILE_LHC1 ].h = TILE_HEIGHT;
	gTileClips[ TILE_LHC2 ].x = 800;
	gTileClips[ TILE_LHC2 ].y = 320;
	gTileClips[ TILE_LHC2 ].w = TILE_WIDTH;
	gTileClips[ TILE_LHC2 ].h = TILE_HEIGHT;
	gTileClips[ TILE_LHC3 ].x = 640;
	gTileClips[ TILE_LHC3 ].y = 480;
	gTileClips[ TILE_LHC3 ].w = TILE_WIDTH;
	gTileClips[ TILE_LHC3 ].h = TILE_HEIGHT;
	gTileClips[ TILE_LHC4 ].x = 800;
	gTileClips[ TILE_LHC4 ].y = 480;
	gTileClips[ TILE_LHC4 ].w = TILE_WIDTH;
	gTileClips[ TILE_LHC4 ].h = TILE_HEIGHT;
	gTileClips[ TILE_Hima ].x = 0;
	gTileClips[ TILE_Hima ].y = 0;
	gTileClips[ TILE_Hima ].w = TILE_WIDTH;
	gTileClips[ TILE_Hima ].h = TILE_HEIGHT;
	gTileClips[ TILE_Kai ].x = 160;
	gTileClips[ TILE_Kai ].y = 0;
	gTileClips[ TILE_Kai ].w = TILE_WIDTH;
	gTileClips[ TILE_Kai ].h = TILE_HEIGHT;
	gTileClips[ TILE_Nil ].x = 480;
	gTileClips[ TILE_Nil ].y = 160;
	gTileClips[ TILE_Nil ].w = TILE_WIDTH;
	gTileClips[ TILE_Nil ].h = TILE_HEIGHT;
	gTileClips[ TILE_Kara ].x = 320;
	gTileClips[ TILE_Kara ].y = 0;
	gTileClips[ TILE_Kara ].w = TILE_WIDTH;
	gTileClips[ TILE_Kara ].h = TILE_HEIGHT;
	gTileClips[ TILE_Gir ].x = 480;
	gTileClips[ TILE_Gir ].y = 0;
	gTileClips[ TILE_Gir ].w = TILE_WIDTH;
	gTileClips[ TILE_Gir ].h = TILE_HEIGHT;
	gTileClips[ TILE_Hockey ].x = 480;
	gTileClips[ TILE_Hockey ].y = 480;
	gTileClips[ TILE_Hockey ].w = TILE_WIDTH;
	gTileClips[ TILE_Hockey ].h = TILE_HEIGHT;
	gTileClips[ TILE_Cricket ].x = 320;
	gTileClips[ TILE_Cricket ].y = 480;
	gTileClips[ TILE_Cricket ].w = TILE_WIDTH;
	gTileClips[ TILE_Cricket ].h = TILE_HEIGHT;
	gTileClips[ TILE_Foot1 ].x = 640;
	gTileClips[ TILE_Foot1 ].y = 0;
	gTileClips[ TILE_Foot1 ].w = TILE_WIDTH;
	gTileClips[ TILE_Foot1 ].h = TILE_HEIGHT;
	gTileClips[ TILE_Foot2 ].x = 800;
	gTileClips[ TILE_Foot2 ].y = 0;
	gTileClips[ TILE_Foot2 ].w = TILE_WIDTH;
	gTileClips[ TILE_Foot2 ].h = TILE_HEIGHT;
	gTileClips[ TILE_Foot3 ].x = 640;
	gTileClips[ TILE_Foot3 ].y = 160;
	gTileClips[ TILE_Foot3 ].w = TILE_WIDTH;
	gTileClips[ TILE_Foot3 ].h = TILE_HEIGHT;
	gTileClips[ TILE_Foot4 ].x = 800;
	gTileClips[ TILE_Foot4 ].y = 160;
	gTileClips[ TILE_Foot4 ].w = TILE_WIDTH;
	gTileClips[ TILE_Foot4 ].h = TILE_HEIGHT;
	gTileClips[ TILE_Shiva ].x = 160;
	gTileClips[ TILE_Shiva ].y = 320;
	gTileClips[ TILE_Shiva ].w = TILE_WIDTH;
	gTileClips[ TILE_Shiva ].h = TILE_HEIGHT;
	gTileClips[ TILE_Sat ].x = 0;
	gTileClips[ TILE_Sat ].y = 320;
	gTileClips[ TILE_Sat ].w = TILE_WIDTH;
	gTileClips[ TILE_Sat ].h = TILE_HEIGHT;
	gTileClips[ TILE_Udai ].x = 0;
	gTileClips[ TILE_Udai ].y = 480;
	gTileClips[ TILE_Udai ].w = TILE_WIDTH;
	gTileClips[ TILE_Udai ].h = TILE_HEIGHT;
	gTileClips[ TILE_Road ].x = 1120;
	gTileClips[ TILE_Road ].y = 320;
	gTileClips[ TILE_Road ].w = TILE_WIDTH;
	gTileClips[ TILE_Road ].h = TILE_HEIGHT;
	gTileClips[ TILE_SAC ].x = 960;
	gTileClips[ TILE_SAC ].y = 480;
	gTileClips[ TILE_SAC ].w = TILE_WIDTH;
	gTileClips[ TILE_SAC ].h = TILE_HEIGHT;
	gTileClips[ TILE_SACc ].x = 1120;
	gTileClips[ TILE_SACc ].y = 480;
	gTileClips[ TILE_SACc ].w = TILE_WIDTH;
	gTileClips[ TILE_SACc ].h = TILE_HEIGHT;
	gTileClips[ TILE_POOL1 ].x = 1280;
	gTileClips[ TILE_POOL1 ].y = 0;
	gTileClips[ TILE_POOL1 ].w = TILE_WIDTH;
	gTileClips[ TILE_POOL1 ].h = TILE_HEIGHT;
	gTileClips[ TILE_POOL2 ].x = 1440;
	gTileClips[ TILE_POOL2 ].y = 0;
	gTileClips[ TILE_POOL2 ].w = TILE_WIDTH;
	gTileClips[ TILE_POOL2 ].h = TILE_HEIGHT;
	gTileClips[ TILE_POOL3 ].x = 1280;
	gTileClips[ TILE_POOL3 ].y = 160;
	gTileClips[ TILE_POOL3 ].w = TILE_WIDTH;
	gTileClips[ TILE_POOL3 ].h = TILE_HEIGHT;
	gTileClips[ TILE_POOL4 ].x = 1440;
	gTileClips[ TILE_POOL4 ].y = 160;
	gTileClips[ TILE_POOL4 ].w = TILE_WIDTH;
	gTileClips[ TILE_POOL4 ].h = TILE_HEIGHT;
    map.close();
}