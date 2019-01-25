#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "game.h"

#define SIZE 20;
#define REFRESH_TIME 0.2

int main() {
	int size = SIZE;
	Game game(size, 25);

	if (!al_init())
		return -1; //unable to load allegro

	if (!al_init_primitives_addon())
		return -1; //unable to load primitives addon

	ALLEGRO_DISPLAY * display = al_create_display(size * 25, size * 25);
	
	if (!display)
		return -1; //unable to create display

	if (!al_install_keyboard())
		return -1; //unable to install keyboard

	ALLEGRO_KEYBOARD_STATE keyboard;

	double time = al_get_time();

	do {
		if (al_get_time() - time >= REFRESH_TIME) {
			game.update();
			time = al_get_time();
		}
		al_get_keyboard_state(&keyboard);

		al_clear_to_color(al_map_rgb(255, 255, 255));
		game.display();
		al_flip_display();
	} while (!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE));


	al_destroy_display(display);
	return 0;
}
