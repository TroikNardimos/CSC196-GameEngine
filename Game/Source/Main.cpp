#include <SDL.h>
#include <stdlib.h>
#include <iostream>

//GitHub: 

int main(int argc, char* argv[])
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	// create window
	// returns pointer to window if successful or nullptr if failed
	SDL_Window* window = SDL_CreateWindow("Game Engine",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	while (true)
	{
		// clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		// draw line
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		//SDL_RenderDrawLine(renderer, 0, 0, 600, 800);
		
		// draw square
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		//SDL_RenderDrawLine(renderer, 300, 200, 500, 200);
		//SDL_RenderDrawLine(renderer, 500, 200, 500, 400);
		//SDL_RenderDrawLine(renderer, 500, 400, 300, 400);
		//SDL_RenderDrawLine(renderer, 300, 400, 300, 200);

		//draw random
		for (int i = 0; i < 1000; i++)
		{
			int value = rand() % 1000; // generate a number between 0-999
			SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 0); // create random color
			SDL_RenderDrawLine(renderer, rand() % 800, rand() % 600, rand() % 800, rand() % 600);
			SDL_RenderDrawPoint(renderer, rand() % 800, rand() % 600);
		}

		// show screen
		SDL_RenderPresent(renderer);
	}

	return 0;
}