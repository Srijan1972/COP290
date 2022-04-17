#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

class Interface
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* background;
    TTF_Font* font1;
    SDL_Texture* fontarea;
public:
    SDL_Texture* background;
    Interface(SDL_Window* w,SDL_Renderer* r){
        window=w;
        renderer=r;
        background=IMG_LoadTexture(renderer,"./assets/images/bg.png");
        font1=TTF_OpenFont("./assets/fonts/a.ttf",16);
        if(font1==NULL){
            std::cerr<<"Failed to load font: "<<TTF_GetError()<<std::endl;
            exit(1);
        }
    }
    ~Interface(){}
};
