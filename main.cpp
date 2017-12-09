#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <SDL.h>
#include <time.h>

#include "Screen.h"
#include "Swarm.h"

using namespace std;
using namespace cismalescumlord;

int main(int argc, char** argv) {

    srand(time(NULL));

    Screen screen;
    if (!screen.init()) {
        cout << "Error initialising SDL" << endl;
        return 1;
    }

    Swarm swarm;

    bool finished = false;
    while (!finished) {

        const Particle * const particles = swarm.getParticles();

        int elapsed = SDL_GetTicks();
        unsigned char red = (1 + sin(elapsed * 0.0001)) * 128;
        unsigned char green = (1 + sin(elapsed * 0.0002)) * 128;
        unsigned char blue = (1 + cos(elapsed * 0.0003)) * 128;
        swarm.update(elapsed);

        for (int i = 0; i < Swarm::NUM_PARTICLES; i++) {
            int x = ((particles+i)->x + 1) * Screen::HALF_WIDTH;
            int y = (particles+i)->y * Screen::HALF_WIDTH + Screen::HALF_HEIGHT;
            screen.setPixel(x, y, red, green, blue);
        }

        screen.boxBlur();
        screen.update();

        finished = screen.handleEvents();
    }

    screen.close();

    return 0;
}

