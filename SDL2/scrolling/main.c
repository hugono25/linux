#include <SDL2/SDL_pixels.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
  const int screen_width = 640;   // 40p * 16
  const int screen_height = 360;  // 40p * 9

  const int camera_width = 320;
  const int camera_height = 180;
  
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0){
    printf("error sdl\n");
  }
  SDL_Window *win = SDL_CreateWindow("Camera",
				     SDL_WINDOWPOS_CENTERED,
				     SDL_WINDOWPOS_CENTERED,
				     screen_width,
				     screen_height,
				     SDL_WINDOW_SHOWN);
  SDL_Renderer *render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface *image = SDL_LoadBMP("cloud.bmp");
  SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0xFF, 0, 0xFF));
  SDL_Texture *texture = SDL_CreateTextureFromSurface(render, image);
  SDL_FreeSurface(image);

	SDL_Rect srcTexture = {0, 0, screen_width, screen_height}; // image size
  SDL_Rect dstTexture = {0, 0, screen_width, screen_height};

  SDL_Surface *mountains = SDL_LoadBMP("mountain.bmp");
  SDL_SetColorKey(mountains, SDL_TRUE, SDL_MapRGB(mountains->format, 0xFF, 0, 0xFF));
  SDL_Texture *mtexture = SDL_CreateTextureFromSurface(render, mountains);
  SDL_FreeSurface(mountains);

	SDL_Rect srcmTexture = {0, 0, screen_width, screen_height}; // image size
  SDL_Rect dstmTexture = {0, 0, screen_width, screen_height};

  SDL_Surface *ground = SDL_LoadBMP("ground.bmp");
  SDL_SetColorKey(ground, SDL_TRUE, SDL_MapRGB(ground->format, 0xFF, 0, 0xFF));
  SDL_Texture *gtexture = SDL_CreateTextureFromSurface(render, ground);
  SDL_FreeSurface(ground);

	SDL_Rect srcgTexture = {0, 0, screen_width, screen_height}; // image size
  SDL_Rect dstgTexture = {0, 0, screen_width, screen_height};

  // parallax offset second image
	SDL_Rect srcTexture2 = {0, 0, screen_width, screen_height}; // image size
  SDL_Rect dstTexture2 = {-screen_width+1, 0, screen_width, screen_height};
	
	SDL_Rect srcgTexture2 = {0, 0, screen_width, screen_height}; // image size
  SDL_Rect dstgTexture2 = {-screen_width+1, 0, screen_width, screen_height};
	
	SDL_Rect srcmTexture2 = {0, 0, screen_width, screen_height}; // image size
  SDL_Rect dstmTexture2 = {-screen_width+1, 0, screen_width, screen_height};

  const Uint8 *state = SDL_GetKeyboardState(NULL);
  bool quit = false;
  

  while(!quit){
		SDL_Event event;
    while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT){
				quit = true;
			}
    }
		
      SDL_SetRenderDrawColor(render, 50, 200, 50, 255);
      SDL_RenderClear(render);
			SDL_Delay(20);
			dstTexture.x += 1;
			dstTexture2.x += 1;
			dstgTexture.x += 2;
			dstgTexture2.x += 2;
			dstmTexture.x += 1;
			dstmTexture2.x += 1;
			// when the window reach the maximum screen width it restart 									
			if(dstTexture.x > screen_width-1){dstTexture.x = -screen_width+1;}
			if(dstTexture2.x > screen_width-1){dstTexture2.x = -screen_width+1;}
			if(dstgTexture.x > screen_width-1){dstgTexture.x = -screen_width+1;}
			if(dstgTexture2.x > screen_width-1){dstgTexture2.x = -screen_width+1;}
			if(dstmTexture.x > screen_width-1){dstmTexture.x = -screen_width+1;}
			if(dstmTexture2.x > screen_width-1){dstmTexture2.x = -screen_width+1;}
			SDL_RenderCopy(render, texture, NULL, &dstTexture);
			SDL_RenderCopy(render, texture, NULL, &dstTexture2);
			SDL_RenderCopy(render, mtexture, &srcmTexture, &dstmTexture);
			SDL_RenderCopy(render, mtexture, &srcmTexture2, &dstmTexture2);	
			SDL_RenderCopy(render, gtexture, &srcgTexture, &dstgTexture);
			SDL_RenderCopy(render, gtexture, &srcgTexture2, &dstgTexture2);
			SDL_RenderPresent(render);

  }
  SDL_DestroyTexture(texture);
  SDL_DestroyTexture(gtexture);
  SDL_DestroyTexture(mtexture);	
  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(render);
  SDL_Quit();


  return 0;
}
