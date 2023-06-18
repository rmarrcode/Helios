#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "volume.h"

class Raycaster {
    public:
        Raycaster(int w, int h, Volume* volume);
        int getPx(int i, int j, int t);
        int* getView(int t, std::vector<float> perspective);
        //Move to utils or something?
        void normalize(std::vector<long double>& v);
        std::vector<long double>* calculatePoint(std::vector<long double> u, std::vector<long double> v, long double t);
        bool pointInCube(std::vector<long double> point, Cube cube);
    private:
        int _w;
        int _h;
        Volume* _volume;
};

#endif
