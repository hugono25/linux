#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

/*
  Idea: Create a state that becomes permanent at runtime after a key is pressed,
  switch other background colors with keys, working like an UI.
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
  SDL_Renderer *render2 = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

  SDL_Rect quad1 = {0,0, screen_width/2, screen_height/2};
  SDL_Rect quad2 = {0,0 ,screen_width/2, screen_height/2};
  
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  bool quit = false;

  while(!quit){
  SDL_Event event;
    while(SDL_PollEvent(&event) != 0){
      if(event.type == SDL_QUIT){
	quit = true;
      }
    }
    SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
    SDL_RenderClear(render);  
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_RenderFillRect(render, &quad2);
    SDL_RenderPresent(render);

    // inputs
   if(state[SDL_SCANCODE_Q]){
     SDL_SetRenderDrawColor(render, 200, 200, 200, 255);
     SDL_RenderClear(render);
     SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
     SDL_RenderFillRect(render, &quad1);
     SDL_RenderPresent(render);
     printf("Q pressed\n");
     SDL_Delay(300);
   }
  }

  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(render);
  SDL_DestroyRenderer(render2);
  SDL_Quit();

  return 0;
}
