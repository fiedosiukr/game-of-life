#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //hides console

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "game.h"

int SIZE = 20;
int CELL_SIZE = 25;
double REFRESH_TIME = 0.2;

int main() {
	Game game(SIZE, CELL_SIZE);

	if (!al_init())
		return -1; //unable to initialize allegro

	if (!al_init_primitives_addon())
		return -1; //unable to initialize primitives addon

	ALLEGRO_DISPLAY * display = al_create_display(SIZE * CELL_SIZE, SIZE * CELL_SIZE);
	
	if (!display)
		return -1; //unable to create display

	if (!al_install_keyboard())
		return -1; //unable to install keyboard

	if (!al_init_font_addon())
		return -1; //unable to initialize font addon

	if (!al_init_ttf_addon())
		return -1; //unable to initialize ttf addon

	ALLEGRO_KEYBOARD_STATE keyboard;
	ALLEGRO_FONT * font = al_load_font("fonts/arial.ttf", 24, 0);

	double time = al_get_time();

	do {
		al_get_keyboard_state(&keyboard);
		al_clear_to_color(al_map_rgb(255, 255, 255));
		game.display();
		al_draw_text(font, al_map_rgb(0, 0, 0), 100, 100, 0, "Press ENTER to start!");
		al_flip_display();
	} while (!al_key_down(&keyboard, ALLEGRO_KEY_ENTER));

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
	al_destroy_font(font);
	return 0;
}
