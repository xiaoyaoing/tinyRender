//
// Created by 打工人 on 2022/3/25.
//
#include "window.h"
using namespace  std;

Window * windowApp=nullptr;

void Window::processEvent() {
    while (SDL_PollEvent(&events) != 0)
    {

//        camera->handleCameraEvent();

    }

}

bool Window::init(int width, int height, Camera * camera,const char * title)  {
    this->width=width;
    this->height=height;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { // 初始化SDL
        cout << "SDL could not initialized with error: " << SDL_GetError() <<endl;
    }
     windowHandle=  SDL_CreateWindow(title,
                     SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width, height, SDL_WINDOW_SHOWN);

    if (windowHandle == nullptr)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Get window surface
    screenSurface = SDL_GetWindowSurface(windowHandle);
    renderer=SDL_CreateRenderer(windowHandle, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderPresent(renderer);

    return true;
}
void Window::updateSurface(unsigned  char * buffer) {
    SDL_LockSurface(screenSurface);
    {
//        unsigned  char * screenPixels=(unsigned  char *) screenSurface->pixels;
        Uint32* destPixels = (Uint32*)screenSurface->pixels;
        for(int i=0;i<width*height;i++)
        {Uint32 color = SDL_MapRGB(
                    screenSurface->format,
                    static_cast<uint8_t>(buffer[i * 4 + 0]),
                    static_cast<uint8_t>(buffer[i * 4 + 1]),
                    static_cast<uint8_t>(buffer[i * 4 + 2]));
            destPixels[i] = color;
        }
    }
    SDL_UnlockSurface(screenSurface);
    SDL_UpdateWindowSurface(windowHandle);
}

bool Window::isClose() {
    return close;
}
void Window::setClose(bool c) {
    close=c;
}
