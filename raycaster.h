#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "volume.h"

class Raycaster {
public:
    Raycaster(int w, int h): _w(w), _h(h) {}
    ~Raycaster()
    int* getView();
private:
    int _w;
    int _h;
    Volume _volume;
};

#endif
