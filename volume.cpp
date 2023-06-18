#include "volume.h"
#include <iostream>


Volume::Volume(std::string path_to_volume) {
    _scene_vars.insert(std::pair<std::string, int>("time", 1));
    _scene_vars.insert(std::pair<std::string, int>("depth", 1));
    _scene_vars.insert(std::pair<std::string, int>("rows", 1));
    _scene_vars.insert(std::pair<std::string, int>("cols", 1));
    _scene_vars.insert(std::pair<std::string, int>("A", 1));
    _scene_vars.insert(std::pair<std::string, int>("B", 1));
    _scene_vars.insert(std::pair<std::string, int>("C", 1));
    _scene_vars.insert(std::pair<std::string, int>("L", 99));

    int time = _scene_vars["time"];
    int depth = _scene_vars["depth"];
    int rows = _scene_vars["rows"];
    int cols = _scene_vars["cols"];

    std::vector<long double> scene_dims_position;
    scene_dims_position.push_back(0);
    scene_dims_position.push_back(0);
    scene_dims_position.push_back(0);

    _scene_dims.side_length = _scene_vars["L"];
    //ON HEAP???
    _scene_dims.position.push_back(0);
    _scene_dims.position.push_back(0);
    _scene_dims.position.push_back(0);

    //populate voxels
    _voxels = new Voxel[time * depth * rows * cols];
    for (int i = 0; i < time * depth * rows * cols; i++) {
        _voxels[i].color = (90 << 24) | (0 << 16) | (0 << 8);
        _voxels[i].cube.position.resize(3);
        _voxels[i].cube.position[0] = 0;
        _voxels[i].cube.position[1] = 0;
        _voxels[i].cube.position[2] = 0;
        _voxels[i].cube.side_length = 5;
    }
}

Voxel* Volume::getVolumeT(int t) {
    int time = _scene_vars["time"];
    int depth = _scene_vars["depth"];
    int rows = _scene_vars["rows"];
    int cols = _scene_vars["cols"];

    Voxel* voxels_t = new Voxel[depth*rows*cols];
    std::memcpy(voxels_t, &(_voxels[depth*rows*cols*t]), (depth*rows*cols) * sizeof(Voxel));
    return voxels_t;
}
