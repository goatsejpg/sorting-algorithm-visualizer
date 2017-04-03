#include <SDL2/SDL.h>

#include "visualize.h"
#include "values.h"

SDL_Color
BLACK = { 0 , 0 , 0 ,255},
WHITE = {255,255,255,255},
RED   = {255, 0 , 0 ,255},
GREEN = { 0 ,255, 0 ,255},
BLUE  = { 0 , 0 ,245,255};

SDL_Rect TEMP;

void visual::render_bar(const int* ARRAY, const int& index, const SDL_Color& c) {
	TEMP = {index * BAR_WIDTH, HEIGHT - (ARRAY[index] * BAR_HEIGHT),
		BAR_WIDTH, ARRAY[index] * BAR_HEIGHT};
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(renderer, &TEMP);
}

void visual::render_whole(const int* ARRAY) {
	for (int i = 0; i < ENTRIES; ++i) {
		visual::render_bar(ARRAY, i, WHITE);
	}
}

void visual::clear_whole() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	TEMP = {0, 0, WIDTH, HEIGHT};
	SDL_RenderFillRect(renderer, &TEMP);
}

void visual::clear_bar(const int& index) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	TEMP = {BAR_WIDTH * index, 0, BAR_WIDTH, HEIGHT};
	SDL_RenderFillRect(renderer, &TEMP);
}

void visual::end_sequence(int* ARRAY) {
	visual::clear_whole();
	visual::render_whole(ARRAY);
	for (int i = 0; i < ENTRIES; ++i) {
		visual::render_bar(ARRAY, i, GREEN);
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}
	visual::render_whole(ARRAY);
	SDL_RenderPresent(renderer);
}
