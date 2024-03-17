#include "project.h"

Project gProject;

void init_project() {
    Track& t1 = gProject.create_track();
    t1.midiChannel = 1;
    t1.name = { "Track 1" };

    Track& t2 = gProject.create_track();
    t2.midiChannel = 5;
    t2.name = { "jsdlkjfslkdjflskjdlfksjdlfk" };

    Track& t3 = gProject.create_track();
    t3.midiChannel = 12;
    t3.name = { "aaaAAAAAA" };
}

Track& Project::create_track() {
    int track_index = gProject.tracks.size();
    gProject.tracks.push_back({});
    Track& track = gProject.tracks[track_index];
    return track;
}

int Project::track_count() {
    return tracks.size();
}
