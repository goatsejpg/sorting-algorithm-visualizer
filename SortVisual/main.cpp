#include <SDL2/SDL.h>
#include <iostream>
#include <random> // for rand() and srand()
#include <time.h> // for time()
#include <climits>
#include <cstdarg>

#include "values.h"
#include "visualize.h"
#include "sort.h"

int ENTRIES = 0, MAX_VALUE = 0;
int BAR_WIDTH = 0, BAR_HEIGHT = 0;
int WIDTH, HEIGHT;
int DELAY = 0;
SDL_Window* window;
SDL_Renderer* renderer;

void error(const char* in) {
	std::cerr << "SDL: " << in << ": " << SDL_GetError() << std::endl;
}

bool is_num(const std::string& str) {
	for (auto c : str)
		if (c < 48 || c > 57) return false;
	return true;
}

void set_value(int& dest) {
	std::string temp;
	while (true) {
		std::cin >> temp;
		if (is_num(temp)) {
			dest = abs(std::stoi(temp));
			return;
		} else
			std::cerr << temp << " is not a positive integer! Re-enter value." << std::endl;
	}
}

constexpr unsigned int strtoint(const char* str, int h = 0) {
	return !str[h] ? 5381 : (strtoint(str, h+1) * 33) ^ str[h];
}

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		error("Video init error!");
		return -1;
	}

	SDL_DisplayMode dsp_mode;

	std::cout << "Enter ENTRIES, DELAY, MAX_VALUE, BAR_WIDTH, BAR_HEIGHT" << std::endl;
	//std::cin >> ENTRIES >> DELAY >> MAX_VALUE >> BAR_WIDTH >> BAR_HEIGHT;
	set_value(ENTRIES); set_value(DELAY); set_value(MAX_VALUE); 
		set_value(BAR_WIDTH); set_value(BAR_HEIGHT);

	WIDTH  = ENTRIES * BAR_WIDTH; 
	HEIGHT = MAX_VALUE * BAR_HEIGHT;

	std::cout << "\nENTRIES:    " << ENTRIES
	          << "\nDELAY:      " << DELAY
	          << "\nMAX_VALUE:  " << MAX_VALUE
	          << "\nBAR_WIDTH:  " << BAR_WIDTH
	          << "\nBAR_HEIGHT: " << BAR_HEIGHT
	          << "\nWIDTH:      " << WIDTH
	          << "\nHEIGHT:     " << HEIGHT << '\n' << std::endl;

	for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {
		int check = SDL_GetCurrentDisplayMode(i, &dsp_mode);
		if (check != 0)
			std::cerr << "SDL: Display mode for display " << i <<
				" couldn't be found: " << SDL_GetError() << std::endl;
		else if (dsp_mode.w < WIDTH || dsp_mode.h < HEIGHT)
			std::cerr << "WARNING: Window will be too large for display " << i << std::endl;
	}

	std::cout << "Continue? : ";
	std::string temp;
	while (true) {
		std::cin >> temp;
		if (temp[0] == 'y') {
			std::cout << "\nStarting..." << std::endl;
			break;
		}
		else if (temp[0] == 'n') {
			std::cout << "\nAbort" << std::endl;
			return 0;
		}
	}

	window = SDL_CreateWindow("Sort Visualiser", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_MINIMIZED);
	if (window == NULL) {
		error("Window error"); return -2;
	} else error("Window created");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		error("Renderer error"); return -2;
	} else error("Renderer created");

	SDL_Event evt;

	srand(time(NULL));
	int ARRAY[ENTRIES];

	for (int* i = ARRAY; i < ARRAY + ENTRIES; ++i) {
		*i = (rand() % MAX_VALUE) + 1;
	}

	std::cout << "Enter sort to use from this selection\n"\
	             "bubble quicksort" << std::endl;

	unsigned int begin_time;

	bool loop = true;
	while (loop) {
		std::cin >> temp;
		switch (strtoint(temp.c_str())) {
		case strtoint("bubble"):
			loop = false;
			std::cout << "Using bubble sort..." << std::endl;
			SDL_RaiseWindow(window);
			begin_time = SDL_GetTicks();
			BUBBLE_SORT(ARRAY);
			break;
		case strtoint("quicksort"):
			loop = false;
			std::cout << "Using quick sort..." << std::endl;
			SDL_RaiseWindow(window);
			begin_time = SDL_GetTicks();
			QUICK_SORT(ARRAY, 0, ENTRIES);
			break;
		}
	}

	std::cout << "Done!\n"\
	             "Took " << SDL_GetTicks() - begin_time << " ms "\
	             "on " << ENTRIES << " elements with " << DELAY << " ms delay\n"\
	             "Do not take these results as a comprehensive benchmark!" << std::endl;
	visual::end_sequence(ARRAY);

	loop = true;
	while (loop) {
		while (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_QUIT)
				loop = false;
				break;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
