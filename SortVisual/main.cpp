#include <SDL2/SDL.h>
#include <iostream>
#include <random> // for rand() and srand()
#include <time.h> // for time()

#include "values.h"
#include "visualize.h"
#include "sort.h"

const int ENTRIES = 512, MAX_VALUE = 400;
const char BAR_WIDTH = 3, BAR_HEIGHT = 2;
const int WIDTH = ENTRIES * BAR_WIDTH, HEIGHT = MAX_VALUE * BAR_HEIGHT;
const int DELAY = 0;
SDL_Window* window;
SDL_Renderer* renderer;

void error(const char* in) {
	std::cerr << "SDL: " << in << std::endl;
}

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		error("Video init error!");
		return -1;
	}

	window = SDL_CreateWindow("Sort Visualiser", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		error("Window error"); return -2;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		error("Renderer error"); return -2;
	}

	SDL_Event evt;

	srand(time(NULL));
	int ARRAY[ENTRIES];

	for (int* i = ARRAY; i < ARRAY + ENTRIES; ++i) {
		*i = (rand() % MAX_VALUE) + 1;
	}

	if (argc == 1) {
		QUICK_SORT(ARRAY, 0, ENTRIES-1);
	} else {
		std::string i = std::string(argv[1]);
		if (i == "bubble")
			BUBBLE_SORT(ARRAY);
		else if (i == "quicksort")
			QUICK_SORT(ARRAY, 0, ENTRIES-1);
	}

	visual::end_sequence(ARRAY);

	bool playing = true;
	while (playing) {
		while (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_QUIT)
				playing = false;
				break;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
