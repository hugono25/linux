#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int main(int argc, char *argv[]){

  const int screen_width = 640;   // 40p * 16
  const int screen_height = 360;  // 40p * 9

  const int camera_width = 320;
  const int camera_height = 180;
  
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    printf("error sdl\n");
  }
  SDL_Window *win = SDL_CreateWindow("Camera",
				     SDL_WINDOWPOS_CENTERED,
				     SDL_WINDOWPOS_CENTERED,
				     screen_width,
				     screen_height,
				     SDL_WINDOW_SHOWN);
  SDL_Renderer *render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

  SDL_Rect player = {screen_width/2 - 40/2, screen_height/2 - 40/2, 40, 40};

  // camera
  SDL_Rect camera = {screen_width/2 - camera_width/2, screen_height/2 - camera_height/2, camera_width, camera_height};
  /*
    - Render start from top left point to the right bottom
    - Correct positioning is: position - width/2
    - After this the positioning start from bottom left
    
    - Make a condition to render the image if is inside the camera
       (Min Width of the camera, max width camera, min height and max hieght  )    and keeps updating while the camera moves
       formula conditions (without center origin):

       MaxWidth (camera.width + window.width/4) // >= win
       MinWidth (camera.width - window.width/4) // <= 0

       MaxHeight (camera.height - window.height/4)  // >= win
       MinHeight (camera.height + window.height/4)  // <= 0
  */
  SDL_Surface *image = image = SDL_LoadBMP("blackbuck.bmp");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(render, image);
  SDL_FreeSurface(image);

  SDL_Rect srcTexture = {0, 0, camera_width, camera_height}; // image size
  SDL_Rect dstTexture = {0, 0, screen_width, screen_height};
  
  float velocity = 5;
  
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  bool quit = false;

  while(!quit){
  SDL_Event event;
    while(SDL_PollEvent(&event) != 0){
      if(event.type == SDL_QUIT){
	quit = true;
      }
      // inputs
      if(state[SDL_SCANCODE_RIGHT]){
	player.x += velocity;
	camera.x += velocity;
	srcTexture.x += velocity;
	
	printf("right: %d\n", player.x);
      }
      if(state[SDL_SCANCODE_LEFT]){
	player.x -= velocity;
	camera.x -= velocity;
	srcTexture.x -= velocity;
	
	printf("left: %d\n", player.x);
      }
      if(state[SDL_SCANCODE_UP]){
	player.y -= velocity;
	camera.y -= velocity;
	srcTexture.y -= velocity;
	
	printf("up: %d\n", player.y);
      }
      if(state[SDL_SCANCODE_DOWN]){
	player.y += velocity;
	camera.y += velocity;
	srcTexture.y += velocity;
	
	printf("down: %d\n", player.y);
      }
      
      // Min width 
      if(camera.x <= 0 && player.x - 140 <= camera.x){

	camera.x = 0;
	player.x = 140;
      }
      // Max width 
      if(camera.x + camera.w >= screen_width && player.x + camera.x + player.w/2 >= camera.x + camera.w){
	player.x = screen_width - player.w - 140;
	camera.x = screen_width - camera.w;
      }
      // Max height 
      if(camera.y + camera.h >= screen_height && player.y + camera.y + player.h/2 >= camera.y + camera.h){
	player.y = screen_height - player.h - 70;
	camera.y = screen_height - camera.h;
      }
      // Min height 
      if(camera.y <= 0 && player.y -70 <= camera.y){
	camera.y = 0;
	player.y = 70;
      }

      // draw
      SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
      SDL_RenderClear(render);
      if(camera_width - screen_width/4 >= 0 && camera_width + screen_width/4 <= screen_width &&
	 camera_height - screen_height/4 >= 0 && camera_height + screen_height/4 <= screen_height){
	SDL_RenderCopy(render, texture, &srcTexture, &dstTexture);	
	//	printf("Render Background\n");
      }
      
      SDL_SetRenderDrawColor(render, 200, 200, 200, 255);
      SDL_RenderFillRect(render, &player);
      SDL_RenderDrawRect(render, &camera);
      SDL_RenderPresent(render);

    }
  }
  printf("\ncamera.x : %d", camera.x);
  printf("\ncamera.y : %d", camera.y);
  printf("\nplayer.x : %d", player.x);
  printf("\nplayer.y : %d", player.y);
  printf("\nsrcTexture.w : %d", srcTexture.w);
  printf("\nsrcTexture.h : %d", srcTexture.h);
  SDL_DestroyTexture(texture);
  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(render);
  SDL_Quit();
  
  return 0;
}
