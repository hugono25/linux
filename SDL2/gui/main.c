#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/*
  - Create some rectangles with textures of buttons and animation when the
button is pressed
  - Idea: create a rectangle put a texture inside and a text, when a key is
pressed the key switch color. Later make that when the mouse is hover.
  - Instead off switch texture, add to small texture movind when the key is
  pressed
  - Make the same effect when the mouse hover over the button
*/						
int main(int argc, char *argv[]) {
  const int screen_width = 640;   // 40p * 16
  const int screen_height = 360;  // 40p * 9

  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0){
    printf("error sdl\n");
  }
  SDL_Window *win = SDL_CreateWindow("Window manage",
				     SDL_WINDOWPOS_CENTERED,
				     SDL_WINDOWPOS_CENTERED,
				     screen_width,
				     screen_height,
				     SDL_WINDOW_SHOWN);
  SDL_Renderer *render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  // note: Can only use one render per window, the first render is selected
  // and the second ignored
  if (TTF_Init() == 1) {
    printf("error ttf\n");
  }
  SDL_Color color = {255, 0, 0};
  TTF_Font *font = TTF_OpenFont("ParagonCleanersMedium.ttf", 32);
  SDL_Surface *fontSurface = TTF_RenderText_Solid(font, "Start Game", color);
  SDL_Texture *fonText = SDL_CreateTextureFromSurface(render, fontSurface); 
  SDL_FreeSurface(fontSurface);
  SDL_Rect fontRect = {screen_width/2 - 100/2, screen_height/2 - 50/2, 100, 50};  //  position
  // Point (640/2 - 150/2) ; Point (360/2 - 100/2)
  // p (245, 130)
  SDL_Rect quad1 = {screen_width/2 - 150/2, screen_height/2 - 100/2, 150, 100};
  SDL_Surface *quadSurface = SDL_LoadBMP("panel-001.bmp");
  if (!quadSurface) {
    printf("error quadsurface\n");
  }
  SDL_Texture *quadText = SDL_CreateTextureFromSurface(render, quadSurface);
  SDL_FreeSurface(quadSurface);
  //  left
  SDL_Rect quad2 = {screen_width/2 - 100/2 - 150, screen_height/2 - 20/2, 100, 20};
  SDL_Surface *quadSurface2 = SDL_LoadBMP("divider-003.bmp");
  if (!quadSurface2) {
    printf("error quadsurface\n");
  }
  SDL_Texture *quadText2 = SDL_CreateTextureFromSurface(render, quadSurface2);
  SDL_FreeSurface(quadSurface2);

  SDL_Rect quad3 = {screen_width/2 - 100/2 + 150, screen_height/2 - 20/2, 100, 20};
    SDL_Surface *quadSurface3 = SDL_LoadBMP("divider-003.bmp");
  if (!quadSurface3) {
    printf("error quadsurface\n");
  }
  SDL_Texture *quadText3 = SDL_CreateTextureFromSurface(render, quadSurface3);
  SDL_FreeSurface(quadSurface3);
  SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
  // dividers moves 10px and restart
  // quad2.x = 120; quad2.y = 170
  // quad3.x = 420; quad3.y = 170
  
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  bool quit = false;
  // 245, 130, 150, 100
  //  Mouse limits to hover ( start from top left)
  //  (245 > x) ; (x < 395) ; (130 > x) ; (x < 230)
  //  mouse state
  int x, y;  
  Uint32 buttons;
  int minWidth = screen_width/2 - quad1.w/2;
  int maxWidth = screen_width/2 - quad1.w/2 + quad1.w;
  int minHeight = screen_height / 2 - quad1.h / 2;
  int maxHeight = screen_height/2 -quad1.h/2 + quad1.h;
  
  printf("Min width %d\n", minWidth);
  printf("Max width %d\n", maxWidth);
  printf("Min height %d\n", minHeight);
  printf("Max height %d\n", maxHeight);
  
  SDL_Event event;
  while(!quit){

    while(SDL_PollEvent(&event) != 0){
      if (event.type == SDL_QUIT){
	quit = true;
      }
      //      if (event.type == SDL_MOUSEMOTION) {
    
      //        printf("mouse.x : %d, mouse.y : %d", x, y);
      //
      //      }
      //
    }
    
    buttons =  SDL_GetMouseState(&x, &y);
    if (state[SDL_SCANCODE_ESCAPE]) {
      quit = true;
    }
    if(state[SDL_SCANCODE_Q]){
      SDL_SetRenderDrawColor(render, 1, 1, 1, 255);
      SDL_RenderClear(render);
      SDL_SetRenderDrawColor(render, 200, 50, 50, 255);
      SDL_RenderFillRect(render, &quad1);
      SDL_RenderCopy(render, quadText, NULL, &quad1);
      SDL_RenderCopy(render, quadText2, NULL, &quad2);
      SDL_RenderCopyEx(render, quadText2, NULL, &quad3, 0, NULL, flip);
      SDL_RenderCopy(render, fonText, NULL, &fontRect);
      SDL_RenderPresent(render);
      quad2.x += 2;
      quad3.x -= 2;
      if(quad2.x > 140){ quad2.x = 120;}
      if(quad3.x < 400){ quad3.x = 420;}
      SDL_Delay(200);
    }

    if (screen_width/2 - quad1.w/2 <= x && x <= screen_width/2 - quad1.w/2 + quad1.w && screen_height/2 - quad1.h/2 <= y && y <= screen_height/2 - quad1.h/2 + quad1.h) {
      SDL_SetRenderDrawColor(render, 1, 1, 1, 255);
      SDL_RenderClear(render);
      SDL_SetRenderDrawColor(render, 200, 50, 50, 255);
      SDL_RenderFillRect(render, &quad1);
      SDL_RenderCopy(render, quadText, NULL, &quad1);
      SDL_RenderCopy(render, quadText2, NULL, &quad2);
      SDL_RenderCopyEx(render, quadText2, NULL, &quad3, 0, NULL, flip);
      SDL_RenderCopy(render, fonText, NULL, &fontRect);
      SDL_RenderPresent(render);
      quad2.x += 2;
      quad3.x -= 2;
      if(quad2.x > 140){ quad2.x = 120;}
      if(quad3.x < 400){ quad3.x = 420;}
      SDL_Delay(200);
      
    }
    SDL_SetRenderDrawColor(render, 1, 1, 1, 255);
    SDL_RenderClear(render);
    //    SDL_SetRenderDrawColor(render, 200, 200, 200, 255);    
    SDL_RenderCopy(render, quadText, NULL, &quad1);
    SDL_RenderCopy(render, fonText, NULL, &fontRect);
    //    SDL_RenderDrawLine(render, minWidth, minHeight, maxWidth, maxHeight);
    SDL_RenderPresent(render);
  }
  SDL_DestroyTexture(quadText);
  SDL_DestroyTexture(fonText);
  TTF_CloseFont(font);
  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(render);
  SDL_Quit();

  return 0;
}
