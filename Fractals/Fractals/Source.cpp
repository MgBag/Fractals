#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

using namespace std;

void CalculatePoints(double* x, double* y, const double* a, const double* b, const double* c, const double* d);

const int SCREEN_W = 800;
const int SCREEN_H = 600;
const double FPS = 30;
const double SCALE = 200;

int main()
{
	ALLEGRO_EVENT_QUEUE* eventQueue = 0;
	ALLEGRO_DISPLAY* display = 0;
	ALLEGRO_TIMER* frame = 0;
	bool quit = false;
	double x = 1, y = 1;

	double a = -0.966918; // Between -3.0 and 3.0
	double b = 2.879879;  // Between -3.0 and 3.0
	double c = 0.765145;  // Between -0.5 and 1
	double d = 0.744728;  // Between -0.5 and 1

	ALLEGRO_COLOR clearColor;
	ALLEGRO_COLOR pointColor;

	// Initialze Allegro and her pluggins
	if (!al_init())
	{
		cout << "Allegro failed to initiate\n";
		system("pause");
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		cout << "Allegro primitives addon failed to initiate\n";
		system("pause");
		return -1;
	}

	if (!al_install_keyboard())
	{
		cout << "Allegro install keyboard\n";
		system("pause");
		return -1;
	}

	eventQueue = al_create_event_queue();
	if (!eventQueue)
	{
		cout << "Failed to initiate event queue\n";
		system("pause");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display)
	{
		cout << "Failed to initiate display \n";
		al_destroy_event_queue(eventQueue);
		system("pause");
		return -1;
	}

	frame = al_create_timer(1.0 / FPS);
	if (!frame)
	{
		cout << "Failed to initiate frame \n";
		al_destroy_display(display);
		al_destroy_event_queue(eventQueue);
		system("pause");
		return -1;
	}

	clearColor = al_map_rgb(0, 0, 0);
	pointColor = al_map_rgba(255, 0, 0, 16);

	// Registering events
	al_register_event_source(eventQueue, al_get_timer_event_source(frame));
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	// Start timer for FPS
	al_start_timer(frame);

	//al_clear_to_color(clearColor);
	al_draw_filled_rectangle(0, 0, SCREEN_W, SCREEN_H, clearColor);

	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_ALPHA);

	while (!quit)
	{
		ALLEGRO_EVENT e;
		al_wait_for_event(eventQueue, &e);

		if (e.type == ALLEGRO_EVENT_TIMER)
		{
			for (int i = 0; i < 1000; ++i)
			{
				al_put_blended_pixel(x * SCALE + SCREEN_W / 2, y * SCALE + SCREEN_H / 2, pointColor);
				CalculatePoints(&x, &y, &a, &b, &c, &d);
			}

			al_flip_display();

			a += 0.001;
			b += 0.001;
			c += 0.001;
			d += 0.001;
			x = 1;
			y = 1;
		}
		else if (e.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			quit = true;
		}
	}

	return 0;
}

void CalculatePoints(double* x, double* y, const double* a, const double* b, const double* c, const double* d)
{
	*x = sin((*y)*(*b)) + (*c)*sin((*x)*(*b));
	*y = sin((*x)*(*a)) + (*d)*sin((*y)*(*a));
}