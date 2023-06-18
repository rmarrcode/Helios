helios:
	g++ driver.cpp raycaster.cpp volume.cpp -o driver -I include -L lib -l SDL2-2.0.0

emcc driver.cpp raycaster.cpp volume.cpp -o driver.html -s USE_SDL=2 -s USE_SDL_GFX=2

