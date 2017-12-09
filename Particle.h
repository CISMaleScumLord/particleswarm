#ifndef PARTICLE_H
#define PARTICLE_H

namespace cismalescumlord {

    struct Particle {
        double x;
        double y;



    public:
        Particle();
        virtual ~Particle();
        void update(int interval);
        
    private:
        double speed;
        double direction;
        void init();
    };
}
#endif /* PARTICLE_H */

