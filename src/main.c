//BEGIN HEAD
//BEGIN DESCRIPTION

/* Mouse follow/grab
 * click and hold the left mouse button
 * and move it
 */

/* DEFINED PROGRESS GOALS
 * 
 * None atm
 * 
 */
//END   DESCRIPTION

//BEGIN INCLUDES
//system headers
#include <math.h>
//local headers
#include "helper.h"
//END   INCLUDES

//BEGIN CPP DEFINITIONS
#define WHITE 255,255,255,255
#define BLACK 0,0,0,255
#define RED   255,0,0,255
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS

int ww;
int wh;

//BEGIN VISIBLES
SDL_Surface    *temp_surface	= NULL;

SDL_Texture    *bg		= NULL;
SDL_Rect 	bg_dst;

SDL_Texture    *logo		= NULL;
SDL_Rect 	logo_dst;

SDL_Texture    *button		= NULL;
SDL_Rect 	button_dst;

//END 	VISIBLES

//BEGIN MOUSE
SDL_Point	mouse;
SDL_bool 	mouse_follow	= SDL_FALSE;
SDL_Point 	mouse_offset;
//END 	MOUSE

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
void assets_in	(void);
void assets_out	(void);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

//BEGIN INIT
init();
assets_in();

//BEGIN WINDOW
SDL_SetWindowPosition(Window,0,0);
SDL_SetWindowSize(Window,ww,wh);
SDL_SetWindowTitle(Window, "SDL2 Mouse Grab");
SDL_ShowWindow(Window);
//END WINDOW

SDL_Event event;
int running = 1;
//END   INIT

//BEGIN MAIN LOOP
while(running){

	//BEGIN EVENT LOOP
	SDL_GetMouseState(&mouse.x, &mouse.y);
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running =0;
		}
		if(event.type == SDL_MOUSEMOTION){
			;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_RIGHT){
				;
			}
			if(event.button.button == SDL_BUTTON_MIDDLE){
				;
			}
			if(event.button.button==SDL_BUTTON_LEFT){
				if( event.button.button==SDL_BUTTON_LEFT && SDL_PointInRect(&mouse, &button_dst) &&!mouse_follow ){
					mouse_offset.x=mouse.x-button_dst.x;
					mouse_offset.y=mouse.y-button_dst.y;
					mouse_follow=SDL_TRUE;
				}
			}
		}
		if( mouse_follow && event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT){
			mouse_follow=SDL_FALSE;
		}
		if(event.type == SDL_KEYDOWN ){
			switch(event.key.keysym.sym ){
				case SDLK_ESCAPE:
					running =0;
					break;

				case SDLK_r:
				case SDLK_BACKSPACE:
					break;

				case SDLK_p:	
				case SDLK_SPACE:
					break;
					
				default:
					break;
			}
		}
	}
	//END   EVENT LOOP
	if (mouse_follow){
		button_dst.x = mouse.x-mouse_offset.x;
		button_dst.y = mouse.y-mouse_offset.y;
		//BOUNDS CHECK
		//TOP
		if (button_dst.y <= bg_dst.y)
			button_dst.y = bg_dst.y;
		//BOT
		if (button_dst.y+button_dst.h >= bg_dst.y +  bg_dst.h)
			button_dst.y = (bg_dst.y + bg_dst.h)-button_dst.h;
		//LEFT
		if (button_dst.x <= bg_dst.x)
			button_dst.x = bg_dst.x;
		//RIGHT
		if (button_dst.x+button_dst.w >= bg_dst.x+bg_dst.w)
			button_dst.x = bg_dst.x+bg_dst.w-button_dst.w;
	}
	//BEGIN RENDERING
	SDL_SetRenderDrawColor(Renderer, WHITE);
	SDL_RenderClear(Renderer);

	SDL_RenderCopy(Renderer, bg, NULL, &bg_dst);
	SDL_RenderCopy(Renderer, logo, NULL, &logo_dst);
	SDL_RenderCopy(Renderer, button, NULL, &button_dst);

	SDL_RenderPresent(Renderer);
	//END   RENDERING
}
//END   MAIN LOOP

assets_out();
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
void assets_in(void)
{

	//BEGIN BG
	temp_surface = IMG_Load("./assets/gfx/bg.png");
	bg = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(bg, NULL, NULL, &bg_dst.w, &bg_dst.h);
	ww=bg_dst.w;
	wh=bg_dst.h;
	bg_dst.x=0;
	bg_dst.y=0;
	//END 	BG

	//BEGIN LOGO
	temp_surface = IMG_Load("./assets/gfx/logo.png");
	logo = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(logo, NULL, NULL, &logo_dst.w, &logo_dst.h);
	logo_dst.x=(ww/2)-(logo_dst.w/2);
	logo_dst.y=(wh/2)-(logo_dst.h/2);
	//END 	LOGO
	
	//BEGIN BUTTON
	temp_surface = IMG_Load("./assets/gfx/button.png");
	button = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(button, NULL, NULL, &button_dst.w, &button_dst.h);
	button_dst.x=(ww/2)-(button_dst.w/2);
	button_dst.y=(wh/2)-(button_dst.h/2);
	//END 	BUTTON
	
	

}

void assets_out(void)
{
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(logo);
	SDL_DestroyTexture(button);
}
//END   FUNCTIONS
