#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rwops.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_mixer.h>


/*
  - Create a bottom rectangles with a hole in the middle
  - Create a moving player, the player collide with the "floor"
  - Add gravity to the player, the gravity pull the player down y axis
  - Create states ground, air state( to double jump)
 */

int main(int argc, char *argv[]){

  const int screen_width = 640;   // 40p * 16
  const int screen_height = 360;  // 40p * 9
  const int camera_width = 320;
  const int camera_height = 180;
  
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0){
    printf("error sdl\n");
  }
  SDL_Window *win = SDL_CreateWindow("Camera",
				     SDL_WINDOWPOS_CENTERED,
				     SDL_WINDOWPOS_CENTERED,
				     screen_width,
				     screen_height,
				     SDL_WINDOW_SHOWN);
  SDL_Renderer *render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  if (Mix_Init(MIX_INIT_WAVPACK | MIX_INIT_MP3) == 0) {
    printf("error init mixer\n");
  }
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == 1) {
    printf("error openaudio\n");
  }
  // background
  Mix_Music *music = Mix_LoadMUS("practice.wav");
  Mix_VolumeMusic(32);  //  0 to 128

  // key press
  // note: loadWAV is a macro after 2.6 version
//  SDL_RWops *io = SDL_RWFromFile("untitled.wav", "rb");
// 
//  Mix_Chunk *keyP = Mix_LoadWAV_RW(io, 0);
//  Mix_VolumeChunk(keyP, 64);
//
  // state machine
  // left floor
  SDL_Rect floor1 = {0, screen_height - screen_height/4, screen_width/3, screen_height/4};

  SDL_Rect floor2 = {screen_width/3 + screen_width/6, screen_height - screen_height / 4, screen_width / 3,
                     screen_height / 4};

  SDL_Rect player = {32/2, screen_height/2, 32, 32};
  
  float speed = 12.0f;
  float gravity = 6.0f;
  
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  bool quit = false;

  SDL_Event event;
  //  printf("floorx %d \n", floor2.x);
  //  printf("floory %d \n", floor2.y);
  while(!quit){
    while(SDL_PollEvent(&event) != 0){
      if(event.type == SDL_QUIT){
	quit = true;
      }
      if (state[SDL_SCANCODE_RIGHT]) {
	player.x += speed;
      }
      if (state[SDL_SCANCODE_LEFT]) {
	player.x -= speed;
      }
      if (state[SDL_SCANCODE_DOWN]) {
	player.y += speed;
      }
      if (state[SDL_SCANCODE_UP]) {
	player.y -= speed*2;
      }
      //
      if (player.y + player.h >= floor1.y && player.x <= floor1.w) {
	player.y = floor1.y - player.h;
      }
      // p(max height), player.x (minWidth && maxWidth)
      if (player.y + player.h >= floor2.y && player.x + player.w >= floor2.x && player.x <= floor2.x + floor2.w) {
	player.y = floor2.y - player.h;
      }
      player.y += gravity;
      SDL_SetRenderDrawColor(render, 50, 50, 50, 255);
      SDL_RenderClear(render);
      SDL_SetRenderDrawColor(render, 255, 50, 50, 255);
      SDL_RenderDrawRect(render, &floor1);
      SDL_RenderDrawRect(render, &floor2);
      SDL_SetRenderDrawColor(render, 50, 255, 50, 255);
      SDL_RenderFillRect(render, &player);
      SDL_RenderPresent(render);
      
      Mix_PlayMusic(music, -1);
//
//      if (state[SDL_SCANCODE_Q]) {
//	//Mix_PauseMusic();
//      }
//      if (state[SDL_SCANCODE_W]) {
//        Mix_PauseMusic();
//	Mix_PlayChannelTimed(-1, keyP, -1, 1000);
//      }
    }

  }
  //SDL_RWclose(io);
  //Mix_FreeChunk(keyP);
  Mix_FreeMusic(music);
  Mix_Quit();
  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(render);
  SDL_Quit();
  
  return 0;
}
