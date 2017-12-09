#ifndef SWARM_H
#define SWARM_H

#include "Particle.h"

namespace cismalescumlord {

    class Swarm {
    public:
        const static int NUM_PARTICLES = 2500;

        Swarm();
        virtual ~Swarm();
        void update(int elapsed);

        const Particle * const getParticles() {
            return particles;
        };
    private:
        Particle *particles;
        int elapsedTime;
    };
}
#endif /* SWARM_H */

