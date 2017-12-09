#include "Screen.h"

namespace cismalescumlord {

    Screen::Screen() : window(NULL), renderer(NULL), texture(NULL), buffer1(NULL), buffer2(NULL) {

    }

    bool Screen::init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            return false;
        }

        window = SDL_CreateWindow(
                "Particle fire explosion",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                WIDTH,
                HEIGHT,
                SDL_WINDOW_SHOWN);

        if (window == NULL) {
            SDL_Quit();
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL) {
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
        if (texture == NULL) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        buffer1 = new Uint32[WIDTH * HEIGHT];
        buffer2 = new Uint32[WIDTH * HEIGHT];

        memset(buffer1, 0x00, HEIGHT * WIDTH * sizeof (Uint32));
        memset(buffer2, 0x00, HEIGHT * WIDTH * sizeof (Uint32));

        return true;
    }
    
    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
        
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
            return;
        }
        
        Uint32 colour = 0;
        colour += red;
        colour <<= 8;
        colour += green;
        colour <<= 8;
        colour += blue;
        colour <<= 8;
        colour += 0xFF;
        
        buffer1[(y * WIDTH) + x] = colour;
    }
    
    void Screen::boxBlur() {
        Uint32 *temp = buffer1;
        buffer1 = buffer2;
        buffer2 = temp;
        
        for (int y=0; y < HEIGHT; y++) {
            for (int x=0; x < WIDTH; x++) {
                
                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;
                
                for (int row=-1; row <= 1; row++) {
                    for (int col=-1; col <= 1; col++) {
                        int currentX = x + col;
                        int currentY = y + row;
                        
                        if (currentX >= 0 && currentX < WIDTH && currentY >= 0 && currentY < HEIGHT) {
                            Uint32 color = buffer2[currentY*WIDTH+currentX];
                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;
                            
                            redTotal += red;
                            greenTotal += green;
                            blueTotal += blue;
                        }
                    }
                }
                
                Uint8 red = redTotal / 9;
                Uint8 green = greenTotal / 9;
                Uint8 blue = blueTotal / 9;
                
                setPixel(x, y, red, green, blue);
            }
        }
    }
    
    void Screen::update() {
        SDL_UpdateTexture(texture, NULL, buffer1, WIDTH * sizeof (Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    bool Screen::handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return true;
            }
        }
        
        return false;
    }

    void Screen::close() {
        delete [] buffer1;
        delete [] buffer2;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(texture);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

};