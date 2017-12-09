#include "Swarm.h"

namespace cismalescumlord {

    Swarm::Swarm() : elapsedTime(0) {
        particles = new Particle[NUM_PARTICLES];
    }

    Swarm::~Swarm() {
        delete [] particles;
    }

    void Swarm::update(int elapsed) {
        int interval = elapsed - elapsedTime;
        
        for (int i = 0; i < Swarm::NUM_PARTICLES; i++) {
            particles[i].update(interval);
        }
        
        elapsedTime = elapsed;
    }
}
