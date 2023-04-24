#ifndef VOLUME_H
#define VOLUME_H

#include <string>
#include <map>

struct Cube {
    std::vector<long double> position;
    long double side_length;
};

//TODO underscores on all class vars
class Volume {
    public:
        Volume(std::string path_to_volume);
        int* getVolumeT(int t);
        std::map<std::string, int> getSceneVars() {return _scene_vars;}
        Cube getSceneDims() {return _scene_dims;}
    private:
        std::string _path_to_volume;
        int* _voxels;
        std::map<std::vector<int>,Cube> _voxel_position;
        Cube _scene_dims;
        // time needs to be global to whole project
        // maybe keep increasing time but do % time elsewhere
        // Figure out what I'm doing with L
        std::map<std::string, int> _scene_vars = {
            {"time", 99},
            {"depth", 99},
            {"rows", 99},
            {"cols", 99},
            {"A", 1},
            {"B", 1},
            {"C", 1},
            {"L", 99}
        };

};

#endif
