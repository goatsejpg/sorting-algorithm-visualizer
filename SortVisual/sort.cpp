#include <SDL2/SDL.h>

#include "sort.h"
#include "visualize.h"
#include "values.h"

using namespace visual;

void BUBBLE_SORT(int* ARRAY) {
	bool sorted;
	render_whole(ARRAY);
	SDL_RenderPresent(renderer);
	for (int i = 0; i < ENTRIES; ++i) {
		sorted = true;
		for (int j = 0; j < ENTRIES - i - 1; ++j) {
			if (j != 0) {
				clear_bar(j-1);
				render_bar(ARRAY, j-1, WHITE);
			}

			render_bar(ARRAY, j   , RED);
			render_bar(ARRAY, j+1 , RED);
			SDL_RenderPresent(renderer);
			SDL_Delay(DELAY);

			if (ARRAY[j] > ARRAY[j+1]) {
				sorted = false;
				ARRAY[j] ^= ARRAY[j+1];
				ARRAY[j+1] ^= ARRAY[j];
				ARRAY[j] ^= ARRAY[j+1];
			}
			SDL_RenderPresent(renderer);
			SDL_Delay(DELAY);
		}
		clear_whole(); render_whole(ARRAY);
		if (sorted) break;
	}
	SDL_RenderPresent(renderer);
}

void QUICK_SORT(int* ARRAY, int LEFT, int RIGHT) {
	int i = LEFT, j = RIGHT;
	int temp;
	int pivot = ARRAY[LEFT + ((j - i) / 2)];
	
	clear_whole();
	render_whole(ARRAY);
	render_bar(ARRAY, i, BLUE);
	render_bar(ARRAY, j, BLUE);
	SDL_RenderPresent(renderer);

	while (i <= j) {
		while (ARRAY[i] < pivot) {
			render_bar(ARRAY, i, WHITE);
			++i;
			render_bar(ARRAY, i, BLUE);
			SDL_RenderPresent(renderer);
			SDL_Delay(DELAY);
		}
		render_bar(ARRAY, i, WHITE);

		while (ARRAY[j] > pivot) {
			render_bar(ARRAY, j, WHITE);
			--j;
			render_bar(ARRAY, j, BLUE);
			SDL_RenderPresent(renderer);
			SDL_Delay(DELAY);
		}
		render_bar(ARRAY, j, WHITE);

		if (i <= j) {
			temp = ARRAY[i];
			ARRAY[i] = ARRAY[j];
			ARRAY[j] = temp;
			++i; --j;
			clear_bar(i); clear_bar(i);
			render_bar(ARRAY, i, GREEN);
			render_bar(ARRAY, j, GREEN);
			SDL_RenderPresent(renderer);
			SDL_Delay(DELAY);
		}
	}

	if (LEFT < j)
		QUICK_SORT(ARRAY, LEFT, j);
	if (i < RIGHT)
		QUICK_SORT(ARRAY, i, RIGHT);
}
