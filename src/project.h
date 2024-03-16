#pragma once
#include <vector>
#include <string>

class Track {
   public:
        int midiChannel = -1;
        std::string name;
};

class Project {
   public:
    Track& create_track();
    std::vector<Track> tracks{};
};

extern Project gProject;

void init_project();