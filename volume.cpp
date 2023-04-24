#include "volume.h"

Volume::Volume(std::string path_to_volume) {
    int time = _scene_vars["time"];
    int depth = _scene_vars["depth"];
    int rows = _scene_vars["rows"];
    int cols = _scene_vars["cols"];

    _voxels = new int[time * depth * rows * cols];
    for (int i = 0; i < time*depth*rows*cols; i++) {
        int rng = rand() % 10;
        if (rng == 0) {
            _voxels[i] = (100 << 24) | (0 << 16) | (0 << 8);
        }
        if (rng == 1) {
            _voxels[i] = (0 << 24) | (100 << 16) | (0 << 8);
        }
        if (rng == 2) {
            _voxels[i] = (0 << 24) | (0 << 16) | (100 << 8);
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            for(int d = 0; d < depth; d++) {
                Cube cube;
                cube.position = { double((rows/-2)+r), double((cols/-2)+c), double(depth/-2)+d};
                cube.side_length = 1;
                _voxel_position[{r, c, d}] = cube;
            }
        }
    }

    _voxels_dims.position = {0,0,0};
    _voxels_dims.side_length = _scene_vars["L"];
}

int* Volume::getVolumeT(int t) {
    int time = _scene_vars["time"];
    int depth = _scene_vars["depth"];
    int rows = _scene_vars["rows"];
    int cols = _scene_vars["cols"];

    int* voxels_t = new int[depth*rows*cols];
    std::memcpy(voxels_t, &(_voxels[depth*rows*cols*time]), (depth*rows*cols*time) * sizeof(int));
    return voxels_t;
}
