#pragma once

#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <SDL2/SDL.h>

#include "values.h"

namespace visual {
	void render_whole(const int* ARRAY);
	void clear_whole();
	void render_bar(const int* ARRAY, const int& index, const SDL_Color& c);
	void clear_bar(const int& index);
	void end_sequence(int* ARRAY);
}

#endif // VISUALIZE_H
