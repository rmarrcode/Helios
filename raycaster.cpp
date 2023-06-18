#include "raycaster.h"
#include <algorithm>
#include <iostream>

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

std::vector<long double>* Raycaster::calculatePoint(std::vector<long double> u, std::vector<long double> v, long double t) {
    std::vector<long double> *result = new std::vector<long double>;
    result->push_back(u[0] + t*v[0]);
    result->push_back(u[1] + t*v[1]);
    result->push_back(u[2] + t*v[2]);

    return result;
}

bool Raycaster::pointInCube(std::vector<long double> point, Cube cube) {
    long double minX = cube.position[0] - cube.side_length/(long double)2;
    long double maxX = cube.position[0] + cube.side_length/(long double)2;
    long double minY = cube.position[1] - cube.side_length/(long double)2;
    long double maxY = cube.position[1] + cube.side_length/(long double)2;
    long double minZ = cube.position[2] - cube.side_length/(long double)2;
    long double maxZ = cube.position[2] + cube.side_length/(long double)2;
    if (point[0] <= maxX && point[0] >= minX && point[1] <= maxY && point[1] >= minY && point[2] <= maxZ && point[2] >= minZ) {
        return true;
    }
    return false;
}

long double distance(const std::vector<long double>& v1, const std::vector<long double>& v2) {
    if (v1.size() != v2.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }

    long double dist = 0;
    for (std::size_t i = 0; i < v1.size(); i++) {
        long double diff = v1[i] - v2[i];
        dist += diff * diff;
    }

    return std::sqrt(dist);
}


int Raycaster::getPx(int i, int j, int t) {
    // get volume
    std::map<std::string, int> scene_vars = _volume->getSceneVars();
    long double C = scene_vars["C"];
    long double B = scene_vars["B"];
    long double A = scene_vars["A"];
    long double L = scene_vars["L"];
    Cube scene_dims = _volume->getSceneDims();
    Voxel* voxels_t = _volume->getVolumeT(t);

    std::vector<long double> u;
    u.push_back(0);
    u.push_back(0);
    u.push_back(L/2 + A*L + B*L);

    std::vector<long double> v;
    v.push_back((C*L/2) - ( ((long double)j/(long double)_w)*C*L));
    v.push_back((C*L/-2) + ( ((long double)i/(long double)_h)*C*L));
    v.push_back(-1*B*L);
    normalize(v);
    long double t_inc = (long double)1/std::max(std::max(std::abs(v[0]), std::abs(v[1])), std::abs(v[2]));
    int inc = 1;

    // while point is in search space
    while (true) {
        std::vector<long double> pointT = *calculatePoint(u,v, t_inc*inc);
        if (pointT[2] < -L/2) {
            break;
        }  
        //WHAT IS MAX 
        long double min_dist = 9999999999999;
        int closest_voxel_color;     
        bool hit = false;

        //if in cube
        if (pointInCube(pointT, scene_dims)) {
            //for all voxels
            for (int r = 0; r < scene_vars["rows"]; r++) {
                for (int c = 0; c < scene_vars["cols"]; c++) {
                    for (int d = 0; d < scene_vars["depth"]; d++) {
                        //double check
                        //is 0 case where thres no voxel
                        Voxel voxel = voxels_t[scene_vars["rows"] * scene_vars["cols"] * d + scene_vars["cols"] * r + c];
                        if (voxel.color != -1) {
                            if (pointInCube(pointT, voxel.cube)) {
                                long double dist = distance(u, pointT);
                                //closesr dist found
                                //FIX TO FIND CLOSER DIST
                                return voxel.color;
                            }
                        }
                    }
                }
            }
        }
        inc++;
        // background   
    }
    return (90 << 24) | (109 << 16) | (120 << 8);
}

// take t and rotation value
int* Raycaster::getView(int t, std::vector<float> perspective) {

    // get volume
    int* pixels = new int[_h*_w];


    // int i = 250;
    // int j = 250;
    for (int i = 235; i < 265; i++) {
        for (int j = 235; j < 265; j++) {
            int color = Raycaster::getPx(i, j, t);
            pixels[i*_h + j] = color;
        }
    }
    
    //     }
    // }

    return pixels;
}



