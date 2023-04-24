#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "raycaster.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window *window;
SDL_Renderer *renderer;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 

//REMOVE
SDL_Point center = {.x = 100, .y = 100};
const int radius = 100;

// define the 2D array and its dimensions
const int w = 1000;
const int h = 1000;

void redraw() {

  SDL_SetRenderDrawColor(renderer, 92, 94, 117, 1);
  SDL_RenderClear(renderer);

  Volume* volume = new Volume("fake scan file");
  Raycaster raycaster(w, h, volume);

  // create a texture from the 2D array
  SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);
  void* pixels_ptr;
  int pitch = w;
  //int *pixels = raycaster.getView();
  SDL_LockTexture(texture, NULL, &pixels_ptr, &pitch);
  //memcpy(pixels_ptr, pixels, w * h * sizeof(int));
  SDL_UnlockTexture(texture);

  // draw the texture to the screen
  SDL_Rect dest = { 0, 0, w, h };
  SDL_RenderCopy(renderer, texture, NULL, &dest);
  SDL_RenderPresent(renderer);
  SDL_DestroyTexture(texture);
}

uint32_t ticksForNextKeyDown = 0;

bool handle_events() {
  SDL_Event event;
  SDL_PollEvent(&event);
  if (event.type == SDL_QUIT) {
    return false;
  }
  if (event.type == SDL_KEYDOWN) {
    uint32_t ticksNow = SDL_GetTicks();
    if (SDL_TICKS_PASSED(ticksNow, ticksForNextKeyDown)) {
      // Throttle keydown events for 10ms.
      ticksForNextKeyDown = ticksNow + 10;
      switch (event.key.keysym.sym) {
        case SDLK_UP:
          center.y -= 1;
          break;
        case SDLK_DOWN:
          center.y += 1;
          break;
        case SDLK_RIGHT:
          center.x += 1;
          break;
        case SDLK_LEFT:
          center.x -= 1;
          break;
      }
      redraw();
    }
  }
  return true;
}

void run_main_loop() {
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop([]() { handle_events(); }, 0, true);
#else
  while (handle_events())
    ;
#endif
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_CreateWindowAndRenderer(1920, 1080, 0, &window, &renderer);

  redraw();
  run_main_loop();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
}