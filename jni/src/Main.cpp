#include <SDL.h>
#include <iostream>

SDL_Rect screenDims = { 0, 0, 100, 8 };

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Error while initializing SDL: " << SDL_GetError() << std::endl;
		return -1;
	}
	/*
	SDL_DisplayMode display;
	if( SDL_GetCurrentDisplayMode( 0, &display ) == 0 )
       	{ 
		screenDims.w = display.w; screenDims.h = display.h; 
	}*/
	SDL_Window * window = SDL_CreateWindow("SDL Hello World", 0, 0, screenDims.w, screenDims.h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	
	if (window == NULL)
	{
		std::cout << "SLD Window could not be created: " << SDL_GetError() << std::endl;
		return -1;
	}

	bool quit = false;
	SDL_Event e;

	int red = 0xFF;
	int green = 0x00;
	int blue = 0x00;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) { quit = true; }
			else if (e.type == SDL_FINGERDOWN) {
				SDL_StartTextInput();
			}
			else if (e.type == SDL_TEXTINPUT) {
				SDL_StopTextInput();
				if (e.text.text[0] == 'r') {red=0xFF;green=0x00;blue=0x00;}
				if (e.text.text[0] == 'g') {red=0x00;green=0xFF;blue=0x00;}
				if (e.text.text[0] == 'b') {red=0x00;green=0x00;blue=0xFF;}
				if (e.text.text[0] == 'q') quit = true;
			}
		}

		SDL_Surface * screenSurface = SDL_GetWindowSurface(window);
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, red, green, blue));
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
