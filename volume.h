#ifndef VOLUME_H
#define VOLUME_H

#include <string>
#include <map>
#include <iostream>

struct Cube {
    std::vector<long double> position;
    long double side_length;
};

struct Voxel {
    int color;
    Cube cube;
};

//TODO underscores on all class vars
class Volume {
    public:
        Volume(std::string path_to_volume);
        Voxel* getVolumeT(int t);
        std::map<std::string, int> getSceneVars() {return _scene_vars;}
        Cube getSceneDims() {return _scene_dims;}
        //better to do 1d array and index as 3D?
    private:
        std::string _path_to_volume;
        Cube _scene_dims;
        // time needs to be global to whole project
        // maybe keep increasing time but do % time elsewhere
        // Figure out what I'm doing with L
        std::map<std::string, int> _scene_vars;
        Voxel* _voxels;
};

#endif
