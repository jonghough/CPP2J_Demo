#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "jloader.h"
#include "controller.h"

using namespace std;
SDL_Window* gWindow = NULL;

//Reshape the JStruct data into a 5x5 matrix of ints.
void To2DMat( JStruct * js, int** arr, int x, int y){
	int index = 0;
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			int val = js -> jData[index];
			arr[i][j] = val;
			index++;
		}
	}
}

int main ( int argc, char** argv )
{
	int* jdll = (int *)malloc(sizeof(int*));
	int jInstance = 0;
	JStruct * jStruct = (JStruct *)malloc(sizeof(JStruct));

	int** pt = (int**) malloc(sizeof(int*)*4);
	int ctr = 0;
	for(ctr=0;ctr<4;ctr++)
	{
		pt[ctr]=(int *)malloc(sizeof(int));
	}

	jInstance = setupJInstance(jdll, jInstance);
	setupArr(jdll, jInstance);

	getArr(jdll, jInstance, jStruct,pt);
	int s = 5;
	int t = 5;
	int ** grid = (int**)malloc(s * sizeof(int*));
	for(int i = 0; i < s; i++){
		grid[i] = (int*)malloc(t* sizeof(int));
	}

	To2DMat(jStruct, grid, t, s);
	// the x and y pointers - which rows / columns to rotate
	int xPointer = 0;
	int yPointer = 0;

	//drawing rect
	SDL_Rect dstrect;

	// initialize SDL video
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "Unable to init SDL: %s\n", SDL_GetError() );
		return 1;
	}


	// make sure SDL cleans up before exit
	atexit(SDL_Quit);
	// create a new window
	gWindow = SDL_CreateWindow( "Demo J Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600,     SDL_WINDOW_SHOWN );

	SDL_Surface* screen = NULL;
	screen = SDL_GetWindowSurface( gWindow );

	if ( !screen )
	{
		printf("Unable to set video: %s\n", SDL_GetError());
		return 1;
	}

	//try to load the images.
	SDL_Surface* r;
	SDL_Surface* w;
	SDL_Surface* b;
	SDL_Surface* y;
	SDL_Surface* g;

	r = IMG_Load("images/red.png");
	w = IMG_Load("images/white.png");
	b = IMG_Load("images/blue.png");
	y = IMG_Load("images/yellow.png");
	g = IMG_Load("images/green.png");

	if (!r || !w || !b || !y || !g)
	{
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		return 1;
	}

	// program main loop

	bool done = false;
	while (!done)
	{ 
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			// check for messages
			switch (event.type)
			{
				// exit if the window is closed
				case SDL_QUIT:
					done = true;
					break;

					// check for keypresses
				case SDL_KEYDOWN:
					{
						// exit if ESCAPE is pressed
						if (event.key.keysym.sym == SDLK_ESCAPE)
							done = true;
						// Rotate horizontrally or vertically, using arrow keys
						else if (event.key.keysym.sym == SDLK_RIGHT){
							rotateRow(jdll, jInstance, yPointer,-1);
							getArr(jdll, jInstance, jStruct,pt);
							To2DMat(jStruct, grid, t, s);
						}
						else if (event.key.keysym.sym == SDLK_LEFT){
							rotateRow(jdll, jInstance, yPointer,1);
							getArr(jdll, jInstance, jStruct,pt);
							To2DMat(jStruct, grid, t, s);
						}
						else if (event.key.keysym.sym == SDLK_DOWN){
							rotateColumn(jdll, jInstance, xPointer,-1);
							getArr(jdll, jInstance, jStruct,pt);
							To2DMat(jStruct, grid, t, s);
						}
						else if (event.key.keysym.sym == SDLK_UP){
							rotateColumn(jdll, jInstance, xPointer,1);
							getArr(jdll, jInstance, jStruct,pt);
							To2DMat(jStruct, grid, t, s);
						}
						// move the horizontal / vertical pointers using w,s,a,d keys.
						else if (event.key.keysym.sym == SDLK_w){
							yPointer = (yPointer - 1 + 5) % 5;
						}
						else if (event.key.keysym.sym == SDLK_s){
							yPointer = (yPointer + 1 + 5) % 5;
						}
						else if (event.key.keysym.sym == SDLK_a){
							xPointer = (xPointer - 1 + 5) % 5;
						}
						else if (event.key.keysym.sym == SDLK_d){
							xPointer = (xPointer + 1 + 5) % 5;
						}

						break;
					}
			}
		}

		// DRAWING STARTS HERE

		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
		// draw bitmap
		dstrect.x = 10;
		dstrect.y = 20;
		for(int i = 0; i < 5; i++){
			dstrect.x = 0;
			for(int j = 0; j < 5; j++){
				dstrect.x +=  r->w;
				int k = grid[i][j];

				SDL_Surface * pic;
				// set the color
				if(k == 0) pic = r;
				else if(k == 1) pic = b;
				else if(k == 2) pic = w;
				else if(k == 3) pic = y;
				else pic = g; 
				SDL_BlitSurface(pic, 0, screen, &dstrect);
			}
			dstrect.y +=r->h;
		}

		// update screen
		SDL_UpdateWindowSurface( gWindow );
		//test if player has won, if win the exit the game loop.
		done |= didWin(jdll, jInstance);
	} // end main loop

	// free loaded bitmap
	SDL_FreeSurface(r);
	SDL_FreeSurface(b);
	SDL_FreeSurface(g);
	SDL_FreeSurface(w);
	SDL_FreeSurface(y);
	for(int i = 0; i < 5; i++){
		free(grid[i]);
	}
	free(grid);
	for(int i = 0; i < 4;i++){
		free(pt[i]);
	}
	free(pt);
	free(jStruct);

	//free J instance
	jFree(jdll, jInstance);
	// exit
	printf("Exited cleanly\n");

	return 0;
}


