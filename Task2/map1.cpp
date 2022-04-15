/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, strings, and file streams
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

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
const int TILE_Road = 2;
const int TILE_Grass = 1;
const int TILE_Floor = 0;
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


//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The tile
class Tile
{
    public:
		//Initializes position and type
		Tile( int x, int y, int tileType );

		//Shows the tile
		void render( SDL_Rect& camera );

		//Get the tile type
		int getType();

		//Get the collision box
		SDL_Rect getBox();

    private:
		//The attributes of the tile
		SDL_Rect mBox;

		//The tile type
		int mType;
};

//The dot that will move around on the screen
class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and check collision against tiles
		void move( Tile *tiles[] );

		//Centers the camera over the dot
		void setCamera( SDL_Rect& camera );

		//Shows the dot on the screen
		void render( SDL_Rect& camera );

    private:
		//Collision box of the dot
		SDL_Rect mBox;

		//The velocity of the dot
		int mVelX, mVelY;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tiles[] );

//Frees media and shuts down SDL
void close( Tile* tiles[] );

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

//Checks collision box against set of tiles
bool touchesWall( SDL_Rect box, Tile* tiles[] );

//Sets tiles from tile map
bool setTiles( Tile *tiles[] );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gDotTexture;
LTexture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;
}

void Tile::render( SDL_Rect& camera )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

Dot::Dot()
{
    //Initialize the collision box
    mBox.x = 240;
    mBox.y = 0;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move( Tile *tiles[] )
{
    //Move the dot left or right
    mBox.x += mVelX;

    //If the dot went too far to the left or right or touched a wall
    if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH ) || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.x -= mVelX;
    }

    //Move the dot up or down
    mBox.y += mVelY;

    //If the dot went too far up or down or touched a wall
    if( ( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.y -= mVelY;
    }
}

void Dot::setCamera( SDL_Rect& camera )
{
	//Center the camera over the dot
	camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
	{ 
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Dot::render( SDL_Rect& camera )
{
    //Show the dot
	gDotTexture.render( mBox.x - camera.x, mBox.y - camera.y );
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia( Tile* tiles[] )
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gDotTexture.loadFromFile( "ch1.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load tile texture
	if( !gTileTexture.loadFromFile("final3.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	//Load tile map
	if( !setTiles( tiles ) )
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	}

	return success;
}

void close( Tile* tiles[] )
{
	//Deallocate tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] != NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}

	//Free loaded images
	gDotTexture.free();
	gTileTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

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
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool setTiles( Tile* tiles[] )
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "lazy1.map" );

    //If the map couldn't be loaded
    if( map.fail() )
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{
		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{
				tiles[ i ] = new Tile( x, y, tileType );
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}
		
		//Clip the sprite sheet
		if( tilesLoaded )
		{

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
		}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() > TILE_Floor ) && ( tiles[ i ]->getType() != TILE_SACc ))
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//The level tiles
		Tile* tileSet[ TOTAL_TILES ];

		//Load media
		if( !loadMedia( tileSet ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot;

			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					dot.handleEvent( e );
				}

				//Move the dot
				dot.move( tileSet );
				dot.setCamera( camera );

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet[ i ]->render( camera );
				}

				//Render dot
				dot.render( camera );

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
		
		//Free resources and close SDL
		close( tileSet );
	}

	return 0;
}