#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>

namespace cismalescumlord {

    class Screen {
    public:
        const static int WIDTH = 800;
        const static int HEIGHT = 600;
        const static int HALF_WIDTH = WIDTH / 2;
        const static int HALF_HEIGHT = HEIGHT / 2;
        
        Screen();
        bool init();
        void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
        void update();
        void boxBlur();
        bool handleEvents();
        void close();
        
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        Uint32 *buffer1;
        Uint32 *buffer2;
    };

};

#endif /* SCREEN_H */

