#include "raycaster.h"
#include <algorithm>

Raycaster::Raycaster(int w, int h, Volume* volume) {
    _w = w;
    _h = h;
    _volume = volume;
}

void Raycaster::normalize(std::vector<long double>& v) {
    long double length = 0.0;
    for (long double x : v) {
        length += x * x;
    }
    length = std::sqrt(length);
    for (long double& x : v) {
        x /= length;
    }
}

std::vector<long double> Raycaster::calculatePoint(std::vector<long double> u, std::vector<long double> v, long double t) {
    return {u[0] + t*v[0], u[1] + t*v[1], u[2] + t*v[2]};
}

bool Raycaster::pointInCube(std::vector<long double> point, Cube cube) {
    long double minX = cube.position[0] - cube.side_length/2;
    long double maxX = cube.position[0] - cube.side_length/2;
    long double minY = cube.position[1] - cube.side_length/2;
    long double maxY = cube.position[1] - cube.side_length/2;
    long double minZ = cube.position[2] - cube.side_length/2;
    long double maxZ = cube.position[2] - cube.side_length/2;
    if (point[0] <= maxX && point[0] >= minX && point[1] <= maxY && point[1] >= minY && point[2] <= maxZ && point[2] >= minZ) {
        return true;
    }
    return false;
}

// take t and rotation value
int* Raycaster::getView(int t, std::vector<float> perspective) {

    // get volume
    int* voxels_t = _volume->getVolumeT(t);
    std::map<std::string, int> scene_vars = _volume->getSceneVars();
    long double C = scene_vars["C"];
    long double B = scene_vars["B"];
    long double A = scene_vars["A"];
    long double L = scene_vars["L"];
    
    Cube voxels_dims = _volume->getSceneDims();

    int* pixels = new int[_h*_w];
    for (int i = 0; i < _h; i++) {
        for (int j = 0; j < _w; j++) {
            // create rotated ray
            std::vector<long double> u = {0, 0, L/2 + A*L + B*L};
            //dont hardcode pixel values
            std::vector<long double> v = {(C*L/2) - (j/1000*C*L), (C*L/-2) + (i/1000*C*L), -1*B*L};
            normalize(v);

            long double t_inc = 1/std::max(std::max(v[0], v[1]), v[2]);
            int inc = 0;
            // while point is in search space
            while (true) {
                std::vector<long double> pointT = calculatePoint(u,v, t_inc*inc);
                if (calculatePoint(u,v, t_inc*inc)[2] >= -L/2) {
                    break;
                }
                //if in cube
                if (pointInCube(pointT, voxels_dims)) {
                    //if in voxel
                        //set color of voxel
                }
                inc++;
            }
            

            //background        
            //pixels[i*_h + j] = (0 << 24) | (100 << 16) | (0 << 8);
        }
    }
    return pixels;
}



