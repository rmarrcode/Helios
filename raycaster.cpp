#include "raycaster.h"

// take t and rotation value
int* Raycaster::getView() {
    int* pixels = new int[_h*_w];
    for (int i = 0; i < _h*_w; i++) {
        pixels[i] = (0 << 24) | (100 << 16) | (0 << 8);
    }
    return pixels;
}

